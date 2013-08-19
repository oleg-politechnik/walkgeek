/*
 * usb_ui.c
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

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "ui.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern u32 MSC_RxSpeed, MSC_TxSpeed;

/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void USBScreen_Init(void);
static void USBScreen_DeInit(void);
static void USBScreen_VariableChangedHandler(VAR_Index var);

static void PrintSpeed(char *buf, u32 bytes_per_second);

/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Screen_Typedef UsbScreen = {
        .Init = USBScreen_Init,
        .DeInit = USBScreen_DeInit,
        .UpdateVar = USBScreen_VariableChangedHandler,
        .KeyPressedHandler = NULL,
        .KeyReleasedHandler = NULL
};

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void USBScreen_Init(void)
{
  DISP_ALIGN_CENTER(2, "USB Disk");

  UI_SyncVariable(VAR_MSC_Speed);
}

static void USBScreen_DeInit(void)
{
}

static void USBScreen_VariableChangedHandler(VAR_Index var)
{
  char str_buf[32];

  switch (var)
  {
    case VAR_MSC_Speed:
      sprintf(str_buf, "Rx: ");
      PrintSpeed(str_buf + sizeof("Rx"), MSC_TxSpeed);
      Disp_ClearRow(3);
      DISP_ALIGN_LEFT(3, str_buf);

      sprintf(str_buf, "Wx: ");
      PrintSpeed(str_buf + sizeof("Wx"), MSC_RxSpeed);
      Disp_ClearRow(4);
      DISP_ALIGN_LEFT(4, str_buf);
      break;

    default:
      break;
  }
}

void PrintSpeed(char *buf, u32 bytes_per_second)
{
  if (bytes_per_second < 1024)
  {
    sprintf(buf, "%uB/s", (unsigned int) bytes_per_second);
  }
  else if (bytes_per_second < 1024 * 1024)
  {
    sprintf(buf, "%uKB/s", (unsigned int) bytes_per_second / (1024));
  }
  else
  {
    sprintf(buf, "%uMB/s", (unsigned int) bytes_per_second / (1024 * 1024));
  }
}

