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

/* Private function prototypes -----------------------------------------------*/
static void DisableBacklightCallback(xTimerHandle xTimer);
static void HoldTimeoutCallback(xTimerHandle xTimer);
static void UI_MainCycle(void);

/* Private functions ---------------------------------------------------------*/
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
          configUI_PRESS_TIMEOUT_MS, pdFALSE, (void *) HoldTimeoutCallback,
          HoldTimeoutCallback);

  assert_param(xKeyHoldTimer);

  UI_EnableBacklight();

  while (1)
  {
    UI_MainCycle();
    vTaskDelay(1 / portTICK_RATE_MS);
    Keypad_1msScan();
    Disp_MainThread();
  }
}

void UI_MainCycle(void)
{
  u8 i = 0;

  assert_param(UiMode < UIM_MAX);

  u32 displayVariableFlags_Local[MAX_DISPLAY_VARIABLES];

  vPortEnterCritical();
  memcpy(displayVariableFlags_Local, displayVariableFlags, MAX_DISPLAY_VARIABLES * sizeof(u32));
  bzero(displayVariableFlags, MAX_DISPLAY_VARIABLES * sizeof(u32));
  vPortExitCritical();

  if (displayVariableFlags_Local[VAR_SystemState])
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

    SyncVariable(VAR_BatteryState);

    displayVariableFlags_Local[VAR_SystemState] = false;
  }

  for (; i < MAX_DISPLAY_VARIABLES; ++i)
  {
    if (displayVariableFlags_Local[i])
    {
      char str_buf[6];

      switch (i)
      {
        case VAR_BatteryState:
#ifdef HAS_BATTERY
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
          break;

        default:
          break;
      }

      if (Screens[UiMode] && Screens[UiMode]->UpdateVar)
      {
        (Screens[UiMode]->UpdateVar)(i);
      }

      displayVariableFlags_Local[i] = false;
    }
  }
}

void Keypad_KeyPressedCallback(KEY_Typedef key)
{
  assert_param(UiMode < UIM_MAX);

  KeyProcessed = RESET;
  if (!(UiMode == UIM_Player && PlayerScreen_IsLocked()))
  {
    xTimerStop(xBacklightTimer, configTIMER_API_TIMEOUT_MS);
    Disp_SetBKL(ENABLE);
  }

  if ((key == KEY_PPP && !PlayerScreen_IsLocked()) || key == KEY_BTN)
  {
    UI_StartHoldTimer(configUI_PRESS_TIMEOUT_MS);
    return;
  }

  if (key == KEY_APP_PLAYER && SystemState != SS_PLAYER)
  {
    System_SetState(SS_PLAYER);
    return;
  }

  if (key == KEY_APP_MSC && SystemState != SS_USB_MSC)
  {
    System_SetState(SS_USB_MSC);
    return;
  }

  if (Screens[UiMode] && Screens[UiMode]->KeyPressedHandler)
  {
    u16 timeout = Screens[UiMode]->KeyPressedHandler(key);
    if (timeout)
    {
      UI_StartHoldTimer(timeout);
    }
  }
}

void HoldTimeoutCallback(xTimerHandle xTimer)
{
  KEY_Typedef key = Keypad_CurrentKey();

  if (KeyProcessed == SET)
  {
    KeyProcessed = RESET;
    return;
  }

  if ((key == KEY_PPP && !PlayerScreen_IsLocked()) || key == KEY_BTN)
  {
    System_SetState(SS_SHUTDOWN);
    return;
  }

  if (Screens[UiMode] && Screens[UiMode]->KeyHoldHandler)
  {
    u16 timeout = Screens[UiMode]->KeyHoldHandler(key);
    if (timeout)
    {
      UI_StartHoldTimer(timeout);
    }
  }
}

void Keypad_KeyReleasedCallback(KEY_Typedef key)
{
  assert_param(UiMode < UIM_MAX);

  if (KeyProcessed == SET)
  {
    KeyProcessed = RESET;
    return;
  }

  xTimerStart(xBacklightTimer, configTIMER_API_TIMEOUT_MS);

  xTimerStop(xKeyHoldTimer, configTIMER_API_TIMEOUT_MS);

  if (Screens[UiMode] && Screens[UiMode]->KeyReleasedHandler)
  {
    Screens[UiMode]->KeyReleasedHandler(key);
  }
}

void UI_EnableBacklight(void)
{
  xTimerStart(xBacklightTimer, configTIMER_API_TIMEOUT_MS);
  Disp_SetBKL(ENABLE);
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
