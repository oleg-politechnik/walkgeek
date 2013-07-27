/*
 * main.c
 *
 * Copyright (c) 2012, 2013, Oleg Tsaregorodtsev
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

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "system.h"
#include "keypad.h"
#include "player.h"
#include "ui.h"
#include "powermanager.h"
#include "audio_if.h"
#include "cpu_config.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern void prvPlayerTask(void *);
extern void prvUiTask(void *);

/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SystemState_Typedef SystemState = SS_START;
u32 displayVariableFlags[MAX_DISPLAY_VARIABLES];
static bool debug_mode = false;
static bool can_sleep = false;

static xQueueHandle xSystemStateQueue;
static xTimerHandle xEnterLowPowerModeTimer;

static char *stateNames[] =
{
        "START",
        "PLAYER",
        "USB_MSC",
        "SHUTDOWN"
};

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void SetState(SystemState_Typedef NewState);

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void System_EnterLowPowerModeCallback(xTimerHandle xTimer)
{
  if (!debug_mode)
  {
    can_sleep = true;
  }
}

static void prvInitTask(void *pvParameters)
{
  xSystemStateQueue = xQueueCreate( mainSYSTEM_STATE_QUEUE_SIZE, sizeof( SystemState_Typedef ) );

  BSP_Keypad_Init();

  PowerManager_Init();
  PowerManager_MainThread();

  if (PowerManager_GetState() != PM_ONLINE)
  {
#ifdef HAS_BATTERY
    portBASE_TYPE delay = 0;

    while (delay < 1000)
    {
      if (!BSP_Keypad_GetKeyStatus(KEY_PPP))
      {
        BSP_PowerDisable();
      }

      vTaskDelay(10 / portTICK_RATE_MS); //todo const
      delay += 10;
    }
#endif

    System_SetState(SS_PLAYER);
  }
  else
  {
    System_SetState(debug_mode ? SS_PLAYER : SS_USB_MSC);
  }

  xTaskCreate(prvUiTask, (signed portCHAR *) "UI", mainUI_TASK_STACK_SIZE, NULL, mainUI_TASK_PRIORITY, NULL);

  xTaskCreate(prvPlayerTask, (signed portCHAR *) "Player", mainPLAYER_TASK_STACK_SIZE, NULL, mainPLAYER_TASK_PRIORITY, NULL);

  {
    xEnterLowPowerModeTimer = xTimerCreate(
            (signed portCHAR *) "Enter Low Power Mode Timer",
            10000 / portTICK_RATE_MS, pdFALSE,
            (void *) System_EnterLowPowerModeCallback,
            System_EnterLowPowerModeCallback);
    xTimerStart(xEnterLowPowerModeTimer, configTIMER_API_TIMEOUT_TICKS);
  }

  while (1)
  {
    SystemState_Typedef NewSystemState;

    if (xQueueReceive(xSystemStateQueue, &(NewSystemState), (portTickType) 10))
    {
      SetState(NewSystemState);
    }

    PowerManager_MainThread();
  }
}

void System_VbusApplied(void)
{
  if (SystemState != SS_USB_MSC)
  {
    USB_CDC_Init();
    return;
  }
}

void System_VbusDetached(void)
{
  //XXX de-init USB properly?
  //the need of vbus sensing (st stack may be de-initializing smth)
  USB_DeInit();
}

void System_SetState(SystemState_Typedef NewState)
{
  if (NewState == SS_USB_MSC && PowerManager_GetState() != PM_ONLINE)
  {
    return;
  }

  xQueueSend( xSystemStateQueue, ( void * ) &NewState, portMAX_DELAY );
}

/*
 * Can only be called from the main thread
 */
void SetState(SystemState_Typedef NewState)
{
  trace("system: leaving state %s\n", stateNames[SystemState]);

  if (NewState == SS_SHUTDOWN)
  {
    Vibrator_SendSignal(30);
  }

  switch (SystemState)
  {
    case SS_PLAYER:
      Player_AsyncCommand(PC_SAVE_CURRENT_DIR, 0);
      Player_AsyncCommand(PC_DEINIT, 0);
      break;

    case SS_USB_MSC:
      USB_DeInit();
      break;

    default:
      break;
  }

  trace("system: entering state %s\n", stateNames[NewState]);

  switch (NewState)
  {
    case SS_SHUTDOWN:
      BSP_PowerDisable();
      break;

    case SS_PLAYER:
      BSP_PowerEnable();
      Player_AsyncCommand(PC_INIT, 0);
      break;

    case SS_USB_MSC:
      USB_MSC_Init();
      break;

    default:
      break;
  }

  SetVariable(VAR_SystemState, SystemState, NewState);
}

extern void Player_Init(void);

int main(void)
{
  CPU_PreInit();

  xTaskCreate(prvInitTask, (signed portCHAR *) "Init", mainINIT_TASK_STACK_SIZE, NULL, mainINIT_TASK_PRIORITY, NULL);

  /* Start the scheduler. */
  vTaskStartScheduler();

  assert_param(!"Fatal RTOS startup error");

  return 42;
}

void vApplicationIdleHook(void)
{
  if (can_sleep)
  {
    CPU_WaitForInterrupt();
  }
}

void vApplicationTickHook(void)
{
}

void vApplicationMallocFailedHook(void)
{
  assert_param(!"Malloc failed");
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask,
    signed portCHAR *pcTaskName)
{
  assert_param(!"Stack overflow");
}

