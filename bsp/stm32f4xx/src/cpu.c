/*
 * cpu.c
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
#include "cpu.h"
#include "system.h"
#include "profile.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static volatile int nesting = 0;

u32 profile_entry_points[PF_MAX];
u32 profile_results[PF_MAX];
char* profile_func_names[PF_MAX];

extern unsigned int _sstack;
extern unsigned int _estack;

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CPU_EnableSysTick(u16 hz)
{
  RCC_ClocksTypeDef RCC_Clocks;

  /* SysTick end of count event each 1ms !!! */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / hz);
}

void CPU_EnterLowPowerState(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Save the GPIO pins current configuration then put all GPIO pins in Analog
   Input mode ...*/

  //USB_OTG_BSP_DeInit(0);

  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
  RCC_AHB1PeriphClockCmd(
          RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC
                  | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Disable GPIOs clock */
  RCC_AHB1PeriphClockCmd(
          RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC
                  | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, DISABLE);

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Enable WakeUp pin */
  //  PWR_WakeUpPinCmd(ENABLE);

  /* Enable Clock Security System(CSS) */
//  RCC_ClockSecuritySystemCmd(ENABLE);

//  PWR_FlashPowerDownCmd(ENABLE);

//  PWR_EnterSTANDBYMode();
  while(1)
    ;
}

void CPU_DisableInterrupts(void)
{
  __disable_irq();
  nesting++;
}

void CPU_RestoreInterrupts(void)
{
  assert_param(nesting > 0);

  nesting--;

  if (!nesting)
  {
    __enable_irq();
  }
}

extern unsigned int _sheap_user;
extern unsigned int _eheap_user;

void *CPU_GetUserHeapStart(void)
{
  return &_sheap_user;
}

size_t CPU_GetUserHeapSize(void)
{
  return (size_t) ((char *) &_eheap_user - (char *) &_sheap_user);
}

size_t CPU_GetStackSize(void)
{
  return (size_t) ((char *) &_estack - (char *) &_sstack);
}

void CPU_RefillStack(void)
{
  char *p = (char *) &_sstack;
  char *end = (char *) __get_MSP();

  while (p < end)
  {
    *p = 0xa5;
    p++;
  }
}

size_t CPU_GetStackFree(void)
{
  char *p = (char *) &_sstack;
  char *end = (char *) __get_MSP();

  while (p < end)
  {
    if (*p != 0xa5)
      break;

    p++;
  }

  return (size_t) (p - (char *) &_sstack);
}

#ifdef PROFILING
void Profiler_Init(void)
{
  memset(profile_entry_points, 0, sizeof(profile_entry_points));
  memset(profile_results, 0, sizeof(profile_results));
  memset(profile_func_names, 0, sizeof(profile_func_names));
}

unsigned int Profiler_GetResult(ProfileFunction_Typedef func)
{
  assert_param(func < PF_MAX);

  return profile_results[func];
}

void Profiler_SetTotal(u32 total)
{
  profile_results[PF_TOTAL] = total;
}

void Profiler_Print(void)
{
  int i;

  if (!profile_results[PF_TOTAL])
  {
    printf("Ooops... no profile results\n");
    return;
  }

  printf("\nCPU profile results:\n");

  for (i = 0; i < PF_MAX; i++)
  {
    printf("%s:\t%3u.%02u%%\n", profile_func_names[i],
            FLOAT_TO_1_2((double) profile_results[i] / ((double) profile_results[PF_TOTAL] / 100)));
  }
}
#endif
