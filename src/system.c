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
#include "keyboard.h"
#include "player.h"
#include "ui.h"
#include "powermanager.h"
#include "disp_1100.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
volatile SystemState_Typedef SystemState;
static SystemState_Typedef SystemStateNew;

u32 MSC_RxSpeed, MSC_TxSpeed;
u32 displayVariableFlags[MAX_DISPLAY_VARIABLES];

static bool debug_mode = false;
static bool can_sleep = false;

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

void System_PowerEnable(void)
{
  UI_Init();
  BSP_PowerEnable();
  //  if (SystemState != SS_START)
//  System_SetState(SS_PLAYER); /* TODO NO_APP */
}

static void System_StartPlayer(void)
{
  if (SystemState != SS_START)
    return;

  System_PowerEnable();
  System_SetState(SS_PLAYER);
}

void System_Init(void)
{
  Scheduler_Reset();
  BSP_InitPowerSourcesSense();

  BSP_InitPPPButton();

  CPU_EnableSysTick(HZ);

  SystemState = SS_START;

  /*BSP_PowerDisable();*/
  PowerManager_Init();
  Scheduler_PutTask(2000, System_StartPlayer, NO_REPEAT);
  Scheduler_PutTask(10000, System_ForbidDebugging, NO_REPEAT);
}

void RAM_FUNC System_SysTickHandler(void)
{
  Keyboard_Scan();
  Scheduler_1msCycle();
  //  Delay_1msCallback();
}

/* TODO add check of calling from an isr */
void RAM_FUNC System_SetState(SystemState_Typedef NewState)
{
  SystemStateNew = NewState;
}

/*
 * Can only be called from the main thread
 */
static void SetState(SystemState_Typedef NewState)
{
  switch (SystemState)
  {
    case SS_PLAYER:
      Player_DeInit();
      Audio_Command(AC_STOP);
      break;

    case SS_USB:
      //      USBD_Shutdown();
      break;

    default:
      break;
  }

  switch (NewState)
  {
    case SS_SHUTDOWN:
      CPU_DisableInterrupts();
      BSP_PowerDisable();
      CPU_EnterLowPowerState();
      break;

    case SS_PLAYER:
      //BSP_PowerEnable();
      UI_Init();
      Player_Init();
      break;

    case SS_USB:
      UI_Init();
      //      MSC_Init();
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
  UI_MainCycle();
  PowerManager_MainThread();

  switch (SystemState)
  {
    case SS_PLAYER:
      Player_MainCycle();
      break;

    case SS_USB:
      //      USBD_MainCycle();
      break;

    default:
      break;
  }

  /* Finally */
  if (can_sleep)
  {
    CPU_WaitForInterrupt();
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line, uint8_t* expr)
{
  /* User can add his own implementation to report the file name and line number,
   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  char *buf[1024];
  int row = 0;

  //TODO: add application state

  Disp_Clear();

  Disp_String(0, row++, "ASSERT FAILED", true);
  Disp_String(0, row, expr, true);
  row += 2;

  sprintf(buf, "line %i in %s", (int) line, strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
  /*todo: test on windows*/
  Disp_String(0, row, buf, true);

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
