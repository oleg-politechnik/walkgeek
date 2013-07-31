/*
 * usbd.c
 *
 * Copyright (c) 2013, Oleg Tsaregorodtsev
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

#ifdef USE_DEVICE_MODE

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "FreeRTOS.h"
#include "timers.h"

#include "system.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

extern void BSP_USBD_MSC_Init(void);
extern void BSP_USBD_CDC_Init(void);
extern void BSP_USBD_DeInit(void);

u32 MSC_DataIn, MSC_DataOut;
u32 MSC_RxSpeed, MSC_TxSpeed;

static xTimerHandle xShowUsbSpeedTimer;

void USB_MSC_DisplaySpeed(xTimerHandle xTimer)
{
  SetVariable(VAR_MSC_Speed, MSC_RxSpeed, MSC_DataIn * USBD_MSC_SPEED_MPS);
  SetVariable(VAR_MSC_Speed, MSC_TxSpeed, MSC_DataOut * USBD_MSC_SPEED_MPS);

  MSC_DataIn = 0;
  MSC_DataOut = 0;
}

void USB_MSC_Init(void)
{
  trace("usb: MSC mode activated\n");

  xShowUsbSpeedTimer = xTimerCreate((signed portCHAR *) "USB Speed Timer",
      USBD_MSC_SPEED_MPS, pdTRUE, (void *) USB_MSC_DisplaySpeed,
      USB_MSC_DisplaySpeed);
  configASSERT(xShowUsbSpeedTimer);

  BSP_USBD_MSC_Init();
}

void USB_CDC_Init(void)
{
#ifdef ENABLE_TRACE
  trace("usb: CDC mode activated\n");
  BSP_USBD_CDC_Init();
#endif
}

void USB_DeInit(void)
{
  trace("usb: deinit\n");

  BSP_USBD_DeInit();

  xTimerDelete(xShowUsbSpeedTimer, configTIMER_API_TIMEOUT_TICKS);
}

#endif
