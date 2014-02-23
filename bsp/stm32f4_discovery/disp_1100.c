/*
 * disp_1100.c
 *
 * Copyright (c) 2012, 2013, 2014, Oleg Tsaregorodtsev
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
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "disp_1100.h"
#include "stm32f4xx_conf.h"
#include "misc.h"
#include <string.h>
#include "system.h"

#include "display.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static FunctionalState disp1100_uses_irq;

/* Private function prototypes -----------------------------------------------*/
static void Disp1100_SPI_Init(void);
static void Disp1100_SetIRQ_Enabled(FunctionalState irq_enabled);
static void Disp1100_InitController(void);
void uDelay(const uint32_t usec);
static void Disp1100_SendByte(u16 byte, FunctionalState use_irq);

/* Private functions ---------------------------------------------------------*/
void Disp1100_Init(FunctionalState irq_enabled)
{
	disp1100_uses_irq = irq_enabled;

	Disp1100_SetIRQ_Enabled(DISABLE);
	Disp1100_GPIO_Init();

	Disp1100_SetRST(ENABLE);

	Disp1100_SPI_Init();

  Disp1100_SetRST(DISABLE);

	if (disp1100_uses_irq)
	{
		vTaskDelay(100);
	}
	else
	{
		uDelay(100 * 1000);
	}

	Disp1100_InitController();
}

void Disp1100_SPI_Init(void)
{
  Disp1100_SetCS(DISABLE);

  SPI_InitTypeDef SPI_InitStructure;

  SPI_StructInit(&SPI_InitStructure);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  /* would have been SPI_Direction_1Line_Tx but i need RXNE interrupt
   * in order to catch the end of transmission and manually reset CS in its ISR
   */
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_Init(DISP_1100_SPI, &SPI_InitStructure);

  SPI_Cmd(DISP_1100_SPI, ENABLE);
}

void Disp1100_SendByte(u16 byte, FunctionalState use_irq)
{
  Disp1100_SetCS(true);

  SPI_I2S_ReceiveData(DISP_1100_SPI); /* Reset IRQ */

  if (!use_irq)
  {
  	SPI_I2S_ITConfig(DISP_1100_SPI, SPI_I2S_IT_RXNE, DISABLE);
  }

  SPI_I2S_SendData(DISP_1100_SPI, byte);

  if (!use_irq)
  {
    while (!SPI_GetFlagStatus(DISP_1100_SPI, SPI_FLAG_RXNE))
    {
      /*vTaskDelay(1)*/;
    }

    Disp1100_SetCS(DISABLE);
  }
  else
  {
  	SPI_I2S_ITConfig(DISP_1100_SPI, SPI_I2S_IT_RXNE, ENABLE);
  }
}

void Disp1100_SendData(u8 byte)
{
  Disp1100_SendByte((byte | 0x100) << 7, disp1100_uses_irq);
}

void Disp1100_SendCommand(u8 byte)
{
	/* In order to simplify design, we do not use command queue here */
  Disp1100_SendByte((byte & ~0x100) << 7, DISABLE);
}

void Disp1100_SetXRow(u8 x, u8 row)
{
  Disp1100_SendCommand(0x10 | ((x >> 4) & 0x7));
  Disp1100_SendCommand(x & 0x0f);

  Disp1100_SendCommand(0xB0 | (row & 0x0f));
}

void Disp1100_IRQHandler()
{
  if (SPI_GetITStatus(DISP_1100_SPI, SPI_IT_RXNE))
  {
    SPI_I2S_ReceiveData(DISP_1100_SPI);

    Disp1100_SetCS(DISABLE);

    Display_NextWord_FromISR();
  }
}

void Disp1100_SetIRQ_Enabled(FunctionalState irq_enabled)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DISP_1100_SPI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configIRQ_PRIORITY_DISP;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = irq_enabled;
  NVIC_Init(&NVIC_InitStructure);
}

static void Disp1100_InitController(void)
{
  Disp1100_SendCommand(0x20); // write VOP register
  Disp1100_SendCommand(0x90);
  Disp1100_SendCommand(0xA4); // all on/normal display
  Disp1100_SendCommand(0x2F); // Power control set(charge pump on/off)
  Disp1100_SendCommand(0x40); // set start row address = 0
  Disp1100_SendCommand(0xac); // set initial row (R0) of the display
  Disp1100_SendCommand(0x07);
  Disp1100_SendCommand(0xF9); //
  Disp1100_SendCommand(0xaf); // display ON/OFF
  Disp1100_SendCommand(0xa6); // normal display (non inverted) a6

  Disp1100_SetIRQ_Enabled(disp1100_uses_irq);
}

void uDelay(const uint32_t usec)
{
	//todo: implement platform-dependent wall-clock-based delays

	uint32_t count = 0;
	const uint32_t utime = (120 * usec / 7);
	do
	{
		if (++count > utime)
		{
			return;
		}
	} while (1);
}

