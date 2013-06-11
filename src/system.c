/*
 * system.c
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

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "system.h"
#include "keypad.h"
#include "player.h"
#include "ui.h"
#include "powermanager.h"
#include "audio_if.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SystemState_Typedef SystemState;
static SystemState_Typedef SystemStateNew;

u32 msDelay;

u32 SysMsCounter;

u32 MSC_RxSpeed, MSC_TxSpeed;
u32 displayVariableFlags[MAX_DISPLAY_VARIABLES];

bool debug_mode = false;
static bool can_sleep = false;

static char *stateNames[] =
{
        "START",
        "PLAYER",
        "USB_MSC",
        "SHUTDOWN"
};

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void System_ForbidDebugging(void)
{
  //todo disable JTAG port in BSP

  if (!debug_mode)
  {
    can_sleep = true;
  }
}

static void System_Check_PPP_Button(void)
{
  if (SystemState != SS_START)
    return;

  if (!BSP_Keypad_GetKeyStatus(KEY_PPP))
  {
    BSP_PowerDisable();
  }
}

void System_PowerEnable(void)
{
  BSP_PowerEnable();

  Scheduler_RemoveTask(System_Check_PPP_Button);

  UI_Init();

//  Vibrator_SendSignal(30);
}

static void System_StartPlayer(void)
{
//  if (SystemState != SS_START)
//    return;

  System_SetState(SS_PLAYER);
}

void System_VbusApplied(void)
{
  System_StartPlayer();

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

void System_Init(void)
{
  Scheduler_Reset();

  CPU_EnableSysTick(HZ);

  SystemState = SS_START;

  BSP_Keypad_Init();

  PowerManager_Init();
  PowerManager_MainThread();

  if (PowerManager_GetState() == PM_ONLINE)
  {
    System_StartPlayer();
  }
  else
  {
#ifdef HAS_BATTERY
    Scheduler_PutTask(10, System_Check_PPP_Button, REPEAT);
    Scheduler_PutTask(1000, System_StartPlayer, NO_REPEAT);
#endif
  }

  Scheduler_PutTask(10000, System_ForbidDebugging, NO_REPEAT);
}

void RAM_FUNC System_SysTickHandler(void)
{
#ifndef PROFILING
  Keypad_1msScan();
  Scheduler_1msCycle();

  if (msDelay)
    msDelay--;
#endif

  SysMsCounter++;
}

/* TODO add check of calling from an isr */
void RAM_FUNC System_SetState(SystemState_Typedef NewState)
{
  SystemStateNew = NewState;
  if (NewState == SS_SHUTDOWN)
  {
    //Scheduler_PutTask(1000, BSP_PowerDisable, NO_REPEAT);
  }
}

/*
 * Can only be called from the main thread
 */
static void SetState(SystemState_Typedef NewState)
{
  trace("system: leaving state %s\n", stateNames[SystemState]);

  if (NewState == SS_SHUTDOWN)
  {
    Vibrator_SendSignal(30);
  }

  switch (SystemState)
  {
    case SS_PLAYER:
      Player_DeInit();
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
      CPU_DisableInterrupts();
      BSP_PowerDisable();
      break;

    case SS_PLAYER:
      System_PowerEnable();
      Player_Init();
      break;

    case SS_USB_MSC:
      USB_MSC_Init();
      break;

    default:
      break;
  }

  SetVariable(VAR_SystemState, SystemState, NewState);
}

void System_MainThread(void)
{
  u32 NewStateCached = SystemStateNew;

  if (NewStateCached != SystemState)
  {
    SetState(NewStateCached);
  }

  /* Main work */
#if! PROFILING
  UI_MainCycle();
#endif
  PowerManager_MainThread();

  switch (SystemState)
  {
    case SS_PLAYER:
      Player_MainThread();
      break;

    case SS_USB_MSC:
    default:
      break;
  }

  /* Finally */
  if (can_sleep)
  {
    CPU_WaitForInterrupt();
  }
}
