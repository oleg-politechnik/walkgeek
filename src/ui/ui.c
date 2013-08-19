/*
 * ui.c
 *
 * Copyright (c) 2012, Oleg Tsaregorodtsev
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Includes ------------------------------------------------------------------*/
#include <FreeRTOS.h>
#include <timers.h>
#include "queue.h"

#include "system.h"
#include "ui.h"
#include "player.h"
#include "disp_1100.h"
#include "keypad.h"
#include "powermanager.h"
#include <malloc.h>
#include "common.h"

extern Screen_Typedef MenuScreen;
extern Screen_Typedef PlayerScreen;
extern bool PlayerScreen_IsLocked(void);
extern Screen_Typedef UsbScreen;

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  eUserInterfaceEvent event;
  int arg;
} sUserInterfaceEvent;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
;
static volatile u32 dispBKL_Timeout;
volatile u32 KeyProcessed;

static UserInterfaceMode_Typedef UiMode = UIM_Uninitialized;

static Screen_Typedef *Screens[UIM_MAX];

static xTimerHandle xBacklightTimer;
static xTimerHandle xKeyHoldTimer;

static xQueueHandle xUI_EventQueue;

static KEY_Typedef CurrentKey = _KEY_DUMMY;

/* Private function prototypes -----------------------------------------------*/
static void DisableBacklightCallback(xTimerHandle xTimer);

/* Private functions ---------------------------------------------------------*/
static void UiVariableChanged(int var)
{
  if (var == VAR_SystemState)
  {
    if (Screens[UiMode] && Screens[UiMode]->DeInit)
    {
      (Screens[UiMode]->DeInit)();
    }

    switch (SystemState)
    {
      case SS_PLAYER:
        UiMode = UIM_Player;
        break;

      case SS_USB_MSC:
        UiMode = UIM_USB;
        break;

      default:
        UiMode = UIM_Uninitialized;
        break;
    }

    Disp_Clear();
    if (Screens[UiMode] && Screens[UiMode]->Init)
    {
      (Screens[UiMode]->Init)();
    }

    UI_SyncVariable(VAR_BatteryState);
  }

  if (var == VAR_BatteryState)
  {
#ifdef HAS_BATTERY
    char str_buf[6];

    if (PowerManager_GetState() == PM_ONLINE)
    {
      snprintf(str_buf, 6, F1_2"C",
              FLOAT_TO_1_2(PowerManager_GetChargingCurrent()));
    }
    else
    {
      snprintf(str_buf, 6, F1_2"v",
              FLOAT_TO_1_2(PowerManager_GetBatteryVoltage()));
    }
    DISP_ALIGN_LEFT(0, str_buf);
#endif
  }
}

static void HoldTimeoutEvent(xTimerHandle xTimer)
{
  UI_SendEvent(UIE_KeyHoldTimeout, 0);
}

static void UiKeyPressedCallback(void)
{
  assert_param(UiMode < UIM_MAX);

  KeyProcessed = RESET;
  if (!(UiMode == UIM_Player && PlayerScreen_IsLocked()))
  {
    xTimerStop(xBacklightTimer, configTIMER_API_TIMEOUT_MS);
    Disp_SetBKL(ENABLE);
  }

  if ((CurrentKey == KEY_PPP && !PlayerScreen_IsLocked()) || CurrentKey == KEY_BTN)
  {
    UI_StartHoldTimer(configUI_PRESS_TIMEOUT_MS);
    return;
  }

  if (CurrentKey == KEY_APP_PLAYER && SystemState != SS_PLAYER)
  {
    System_SetState(SS_PLAYER);
    return;
  }

  if (CurrentKey == KEY_APP_MSC && SystemState != SS_USB_MSC)
  {
    System_SetState(SS_USB_MSC);
    return;
  }

  if (Screens[UiMode] && Screens[UiMode]->KeyPressedHandler)
  {
    u16 timeout = Screens[UiMode]->KeyPressedHandler(CurrentKey);
    if (timeout)
    {
      UI_StartHoldTimer(timeout);
    }
  }
}

void UiKeyHoldTimeoutCallback(void)
{
  if (KeyProcessed == SET)
  {
    KeyProcessed = RESET;
    return;
  }

  if ((CurrentKey == KEY_PPP && !PlayerScreen_IsLocked()) || CurrentKey == KEY_BTN)
  {
    System_SetState(SS_SHUTDOWN);
    return;
  }

  if (Screens[UiMode] && Screens[UiMode]->KeyHoldHandler)
  {
    u16 timeout = Screens[UiMode]->KeyHoldHandler(CurrentKey);
    if (timeout)
    {
      UI_StartHoldTimer(timeout);
    }
  }
}

void UiKeyReleasedCallback(KEY_Typedef key)
{
  assert_param(UiMode < UIM_MAX);

  xTimerStart(xBacklightTimer, configTIMER_API_TIMEOUT_MS);

  xTimerStop(xKeyHoldTimer, configTIMER_API_TIMEOUT_MS);

  if (KeyProcessed == SET)
  {
    KeyProcessed = RESET;
    return;
  }

  if (Screens[UiMode] && Screens[UiMode]->KeyReleasedHandler)
  {
    Screens[UiMode]->KeyReleasedHandler(key);
  }
}

void UI_PreInit(void)
{
  xUI_EventQueue = xQueueCreate( 50 /*fixme*/, sizeof( sUserInterfaceEvent ) );
  configASSERT(xUI_EventQueue);
}

void prvUiTask(void *pvParameters)
{
  /* if any application (Player, Usb) gets selected afterwards, it will be
   * served properly later in UI_VariableChangedHandler */

  trace("[init] UI\n");

  Disp_Init();
  Keypad_Init();
  Vibrator_Init();

  Screens[UIM_Player] = &PlayerScreen;
  Screens[UIM_USB] = &UsbScreen;

  xBacklightTimer = xTimerCreate((signed portCHAR *) "Backlight Timer",
          configUI_BACKLIGHT_TIMEOUT_MS, pdFALSE,
          (void *) DisableBacklightCallback,
          DisableBacklightCallback);

  assert_param(xBacklightTimer);

  xKeyHoldTimer = xTimerCreate((signed portCHAR *) "Key Hold Timer",
          configUI_PRESS_TIMEOUT_MS, pdFALSE, (void *) HoldTimeoutEvent,
          HoldTimeoutEvent);

  assert_param(xKeyHoldTimer);

  UI_EnableBacklight();

  for (;;)
  {
    sUserInterfaceEvent e;
    if (xQueueReceive(xUI_EventQueue, &e, portMAX_DELAY))
    {
      switch (e.event)
      {
        case UIE_KeyPressed:
          configASSERT(e.arg >= 0 && e.arg < KEY_MAX);
          if (CurrentKey == _KEY_DUMMY)
          {
            CurrentKey = e.arg;
            UiKeyPressedCallback();
          }
          break;

        case UIE_KeyReleased:
          configASSERT(e.arg >= 0 && e.arg < KEY_MAX);
          if (CurrentKey == e.arg)
          {
            CurrentKey = _KEY_DUMMY;
            UiKeyReleasedCallback(e.arg);
          }
          break;

        case UIE_VariableChanged:
          configASSERT(e.arg >= 0 && e.arg < VAR_MAX);

          UiVariableChanged(e.arg);

          if (Screens[UiMode] && Screens[UiMode]->UpdateVar)
          {
            (Screens[UiMode]->UpdateVar)(e.arg);
          }
          break;

        case UIE_KeyHoldTimeout:
          UiKeyHoldTimeoutCallback();
          break;

        default:
          break;
      }
    }
  }
}

void UI_EnableBacklight(void)
{
  xTimerStart(xBacklightTimer, configTIMER_API_TIMEOUT_MS);
  Disp_SetBKL(ENABLE);
}

void UI_DisableBacklight(void)
{
  xTimerStop(xBacklightTimer, configTIMER_API_TIMEOUT_MS);
  Disp_SetBKL(DISABLE);
}

void UI_StartHoldTimer(u16 timeout)
{
  xTimerChangePeriod(xKeyHoldTimer, timeout, configTIMER_API_TIMEOUT_MS);
  xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_MS);
}

void DisableBacklightCallback(xTimerHandle xTimer)
{
  Disp_SetBKL(DISABLE);
}

void Vibrator_SendSignal(u16 ms)
{
  //  Vibrator_Enable();
  //  Scheduler_PutTask(ms, Vibrator_Disable, NO_REPEAT);
}

void UI_SendEvent(eUserInterfaceEvent event, int arg)
{
  if (xUI_EventQueue)
  {
    sUserInterfaceEvent e;
    e.event = event;
    e.arg = arg;

    xQueueSend( xUI_EventQueue, ( void * ) &e, portMAX_DELAY );
  }
}

void UI_SendEventFromISR(eUserInterfaceEvent event, int arg)
{
  if (xUI_EventQueue)
  {
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    sUserInterfaceEvent e;

    e.event = event;
    e.arg = arg;

    xQueueSendFromISR( xUI_EventQueue, ( void * ) &e, &xHigherPriorityTaskWoken );

    /* Switch context if necessary. */
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
  }
}

void UI_SyncVariable(VAR_Index var)
{
  UI_SendEvent(UIE_VariableChanged, var);
}
