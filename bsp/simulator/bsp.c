/*
 * bsp.c
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
#include "powermanager.h"
#include "disp_1100.h"
#include <stdlib.h>
#include "audio_if.h"
#include <pthread.h>
#include <unistd.h>
#include "ui.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char user_heap[256*1024];
char stack[64*1024];

static bool stop;

pthread_t thread;

void CPU_DisableInterrupts(void)
{
}

void CPU_RestoreInterrupts(void)
{
}

void *CPU_GetUserHeapStart(void)
{
  return user_heap;
}

size_t CPU_GetUserHeapSize(void)
{
  return sizeof(user_heap);
}

void *CPU_AllocFromStackBottom(size_t size)
{
  if (size < sizeof(stack))
    return stack;

  return NULL;
}

void CPU_FreeStackBottom(void)
{
}

void CPU_EnableFPU(void)
{
}

void *systick_thread(void *arg)
{
  while (!stop)
  {
    System_SysTickHandler();

    usleep(1000);
  }
  pthread_exit(NULL);
}

void CPU_EnableSysTick(u16 n)
{
  trace("This is walkgeek SIMULATOR\n");
  trace("You can use keyboard to control it\n");
  trace("'p' = previous track\n");
  trace("'n' = next track\n");
  int rc = pthread_create(&thread, NULL, systick_thread, 0);
  if (rc)
  {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }
}

/* Power monitoring --------------------------------------------------------- */
u32 BSP_GetLast_ADC_Result_mV(void)
{
  return 0;
}

void BSP_InitPowerManager(void)
{
}

void BSP_InitPowerSourcesSense(void)
{
}

void BSP_StartPowerManagerADC(ADC_Source_Typedef ADC_Source)
{
}

bool BSP_IsPowerSourceConnected(void)
{
  return true;
}

void BSP_PowerEnable(void)
{
}

void BSP_PowerDisable(void)
{
  stop = true;
  pthread_join(thread, NULL);
  exit(0);
}

/* disp_1100 -----------------------------------------------------------------*/
//void Disp_GPIO_Init()
//{
//}
//
//void Disp_SetBKL(FunctionalState enabled)
//{
//}
//
//void Disp_SetCS(FunctionalState enabled)
//{
//}
//
//bool Disp_GetCS(void)
//{
//  return (GPIO_ReadInputDataBit(DISP_GPIO, DISP_Pin_CS) == Bit_RESET);
//}
//
//void Disp_SetRST(FunctionalState enabled)
//{
//  (enabled == ENABLE) ? GPIO_ResetBits(DISP_GPIO, DISP_Pin_RST) : GPIO_SetBits(
//          DISP_GPIO, DISP_Pin_RST);
//}

/* sdio ----------------------------------------------------------------------*/
/* keyboard ------------------------------------------------------------------*/
void BSP_Keypad_Init(void)
{
}

void Keypad_Init(void)
{
}

void Vibrator_Init(void)
{
}

void Keypad_1msScan(void)
{
  char buf;
  int cnt = fread(&buf, 1, 1, stdin);

  if (cnt > 0)
  {
    switch (buf)
    {
    case 's':
      System_SetState(SS_SHUTDOWN);
      break;

    case 'n':
      Keypad_KeyPressedCallback(KEY_NEXT);
      Keypad_KeyReleasedCallback(KEY_NEXT);
      break;

    case 'p':
      Keypad_KeyPressedCallback(KEY_PREV);
      Keypad_KeyReleasedCallback(KEY_PREV);
      break;

    case '4':
      Keypad_KeyPressedCallback(KEY_PREV_DIR);
      Keypad_KeyReleasedCallback(KEY_PREV_DIR);
      break;

    case '6':
      Keypad_KeyPressedCallback(KEY_NEXT_DIR);
      Keypad_KeyReleasedCallback(KEY_NEXT_DIR);
      break;
    }
  }
}

void Vibrator_Enable(void)
{
}

void Vibrator_Disable(void)
{
}

bool BSP_Keypad_GetKeyStatus(KEY_Typedef key)
{
  return false;
}

/* vibrator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//void Vibrator_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//
//  RCC_AHB1PeriphClockCmd(VIBRATOR_RCC_AHB1Periph_GPIO, ENABLE);
//
//  GPIO_InitStructure.GPIO_Pin = VIBRATOR_PIN;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(VIBRATOR_GPIO, &GPIO_InitStructure);
//
//  Vibrator_Disable();
//}
//
//void Vibrator_Disable(void)
//{
//  GPIO_SetBits(VIBRATOR_GPIO, VIBRATOR_PIN);
//}
//
//
//void Vibrator_Enable(void)
//{
//  GPIO_ResetBits(VIBRATOR_GPIO, VIBRATOR_PIN);
//}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line, uint8_t* expr)
{
  fprintf(stderr, "ASSERT FAILED\n");
  fprintf(stderr, "line %i in %s\n", (int) line, strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
  fprintf(stderr, "%s\n", expr);

  while(1)
    ;
}
#endif


void BSP_USBD_MSC_Init()
{
}

void BSP_USBD_CDC_Init()
{
}

void BSP_USBD_DeInit()
{
}

void Audio_DeInit(void)
{
}

KEY_Typedef Keypad_CurrentKey(void)
{
  return  KEY_MAX;
}

FuncResult Audio_CommandSync(AudioCommand_Typedef cmd)
{
  return FUNC_SUCCESS;
}

FuncResult Audio_SetVolume(u8 NewVolume)
{
  return FUNC_SUCCESS;
}

FuncResult Audio_ChangeVolume(s8 delta)
{
  return FUNC_SUCCESS;
}

FuncResult Audio_PeriodicKick(void)
{
  return FUNC_SUCCESS;
}

AudioState_Typedef Audio_GetState(void)
{
  return FUNC_SUCCESS;
}

int Audio_GetSampleRate(void)
{
  return FUNC_SUCCESS;
}

int Audio_GetVolume(void)
{
  return FUNC_SUCCESS;
}
