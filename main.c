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
#include <FreeRTOS.h>
#include <task.h>

#include "system.h"
#include "keypad.h"
#include "player.h"
#include "ui.h"
#include "powermanager.h"
#include "audio_if.h"
#include "cpu_config.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SystemState_Typedef SystemState;
static SystemState_Typedef SystemStateNew;

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

//  Scheduler_RemoveTask(System_Check_PPP_Button);
#ifndef PROFILING
  UI_Init();
#endif

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

/* TODO add check of calling from an isr */
void RAM_FUNC System_SetState(SystemState_Typedef NewState)
{
  if (NewState == SS_USB_MSC && PowerManager_GetState() != PM_ONLINE)
  {
    return;
  }

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
#ifndef PROFILING
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

}

int main(void)
{
  CPU_EnableSysTick(HZ);

  SystemState = SS_START;

  BSP_Keypad_Init();

  PowerManager_Init();
  PowerManager_MainThread();

#ifdef PROFILING
  System_StartPlayer();
  return;
#endif

  if (PowerManager_GetState() == PM_ONLINE)
  {
    System_StartPlayer();
  }
  else
  {
#ifdef HAS_BATTERY
//    Scheduler_PutTask(10, System_Check_PPP_Button, REPEAT);
//    Scheduler_PutTask(1000, System_StartPlayer, NO_REPEAT);
#endif
  }

//  Scheduler_PutTask(10000, System_ForbidDebugging, NO_REPEAT);

  /* Start the scheduler. */
  vTaskStartScheduler();

  while (1)
    ;

  return 42;
}

























/*
    FreeRTOS V7.4.2 - Copyright (C) 2013 Real Time Engineers Ltd.

    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.

    >>>>>>NOTE<<<<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
    details. You should have received a copy of the GNU General Public License
    and the FreeRTOS license exception along with FreeRTOS; if not it can be
    viewed here: http://www.freertos.org/a00114.html and also obtained by
    writing to Real Time Engineers Ltd., contact details for whom are available
    on the FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, and our new
    fully thread aware and reentrant UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems, who sell the code with commercial support,
    indemnification and middleware, under the OpenRTOS brand.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the standard demo application tasks.
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Fast Interrupt Test" - A high frequency periodic interrupt is generated
 * using a free running timer to demonstrate the use of the
 * configKERNEL_INTERRUPT_PRIORITY configuration constant.  The interrupt
 * service routine measures the number of processor clocks that occur between
 * each interrupt - and in so doing measures the jitter in the interrupt timing.
 * The maximum measured jitter time is latched in the ulMaxJitter variable, and
 * displayed on the OLED display by the 'OLED' task as described below.  The
 * fast interrupt is configured and handled in the timertest.c source file.
 *
 * "OLED" task - the OLED task is a 'gatekeeper' task.  It is the only task that
 * is permitted to access the display directly.  Other tasks wishing to write a
 * message to the OLED send the message on a queue to the OLED task instead of
 * accessing the OLED themselves.  The OLED task just blocks on the queue waiting
 * for messages - waking and displaying the messages as they arrive.
 *
 * "Check" hook -  This only executes every five seconds from the tick hook.
 * Its main function is to check that all the standard demo tasks are still
 * operational.  Should any unexpected behaviour within a demo task be discovered
 * the tick hook will write an error to the OLED (via the OLED task).  If all the
 * demo tasks are executing with their expected behaviour then the check task
 * writes PASS to the OLED (again via the OLED task), as described above.
 *
 * "uIP" task -  This is the task that handles the uIP stack.  All TCP/IP
 * processing is performed in this task.
 */




/*************************************************************************
 * Please ensure to read http://www.freertos.org/portLM3Sxxxx_Eclipse.html
 * which provides information on configuring and running this demo for the
 * various Luminary Micro EKs.
 *************************************************************************/




/* Standard includes. */
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*-----------------------------------------------------------*/

/* Size of the stack allocated to the uIP task. */
#define mainBASIC_WEB_STACK_SIZE            ( configMINIMAL_STACK_SIZE * 3 )

/* The OLED task uses the sprintf function so requires a little more stack too. */
#define mainOLED_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 50 )

/* Task priorities. */
#define mainQUEUE_POLL_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainSEM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1 )
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainCREATOR_TASK_PRIORITY           ( tskIDLE_PRIORITY + 3 )
#define mainINTEGER_TASK_PRIORITY           ( tskIDLE_PRIORITY )
#define mainGEN_QUEUE_TASK_PRIORITY			( tskIDLE_PRIORITY )

/*-----------------------------------------------------------*/

/*
 * The task that handles the uIP stack.  All TCP/IP processing is performed in
 * this task.
 */
extern void vuIP_Task( void *pvParameters );

/*
 * The display is written two by more than one task so is controlled by a
 * 'gatekeeper' task.  This is the only task that is actually permitted to
 * access the display directly.  Other tasks wanting to display a message send
 * the message to the gatekeeper.
 */
//static void vOLEDTask( void *pvParameters );

/*
 * Configure the hardware for the demo.
 */
//static void prvSetupHardware( void );

/*
 * Configures the high frequency timers - those used to measure the timing
 * jitter while the real time kernel is executing.
 */
extern void vSetupHighFrequencyTimer( void );

/*
 * The idle hook is used to run a test of the scheduler context switch
 * mechanism.
 */
void vApplicationIdleHook( void );
/*-----------------------------------------------------------*/

/* The queue used to send messages to the OLED task. */
xQueueHandle xOLEDQueue;

/* The welcome text. */
const portCHAR * const pcWelcomeMessage = "   www.FreeRTOS.org";

/* Variables used to detect the test in the idle hook failing. */
unsigned portLONG ulIdleError = pdFALSE;

//int main( void )
//{
//	prvSetupHardware();
//

//}

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

void vApplicationStackOverflowHook(xTaskHandle *pxTask,
        signed portCHAR *pcTaskName)
{
  for (;;)
    ;
}

