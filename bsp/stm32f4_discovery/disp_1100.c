/*
 * disp_1100.c
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
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "disp_1100.h"
#include "stm32f4xx_conf.h"
#include "misc.h"
#include <string.h>
#include "system.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define DISP_INDEX_COUNT            (DISP_X_COUNT * DISP_ROW_COUNT)

#define DISP_IS_VALID_ROW(row)      (row < DISP_ROW_COUNT)
#define DISP_IS_VALID_X(x)          (x < DISP_X_COUNT)
#define DISP_IS_VALID_Y(y)          (y < DISP_Y_COUNT)
#define DISP_IS_VALID_INDEX(ix)     (ix < DISP_INDEX_COUNT)

#define DISP_INDEX(x, row)          (x + row * DISP_X_COUNT)

#define ALL_DISP_DIRTY              DISP_ROW_COUNT

/* Private variables ---------------------------------------------------------*/
static uint8_t dispRAM[DISP_ROW_COUNT][DISP_X_COUNT];
static __IO uint32_t dirty_row_flags;
static __IO uint32_t busy;
static u16 ram_x;
static u8 ram_row;
static bool irq;

static const uint8_t FontLookup[][5] =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // sp
        { 0x00, 0x00, 0x2f, 0x00, 0x00 }, // !
        { 0x00, 0x07, 0x00, 0x07, 0x00 }, // "
        { 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // #
        { 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // $
        { 0xc4, 0xc8, 0x10, 0x26, 0x46 }, // %
        { 0x36, 0x49, 0x55, 0x22, 0x50 }, // &
        { 0x00, 0x05, 0x03, 0x00, 0x00 }, // '
        { 0x00, 0x1c, 0x22, 0x41, 0x00 }, // (
        { 0x00, 0x41, 0x22, 0x1c, 0x00 }, // )
        { 0x14, 0x08, 0x3E, 0x08, 0x14 }, // *
        { 0x08, 0x08, 0x3E, 0x08, 0x08 }, // +
        { 0x00, 0x00, 0x50, 0x30, 0x00 }, // ,
        { 0x10, 0x10, 0x10, 0x10, 0x10 }, // -
        { 0x00, 0x60, 0x60, 0x00, 0x00 }, // .
        { 0x20, 0x10, 0x08, 0x04, 0x02 }, // /
        { 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0
        { 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 1
        { 0x42, 0x61, 0x51, 0x49, 0x46 }, // 2
        { 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 3
        { 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 4
        { 0x27, 0x45, 0x45, 0x45, 0x39 }, // 5
        { 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 6
        { 0x01, 0x71, 0x09, 0x05, 0x03 }, // 7
        { 0x36, 0x49, 0x49, 0x49, 0x36 }, // 8
        { 0x06, 0x49, 0x49, 0x29, 0x1E }, // 9
        { 0x00, 0x36, 0x36, 0x00, 0x00 }, // :
        { 0x00, 0x56, 0x36, 0x00, 0x00 }, // ;
        { 0x08, 0x14, 0x22, 0x41, 0x00 }, // <
        { 0x14, 0x14, 0x14, 0x14, 0x14 }, // =
        { 0x00, 0x41, 0x22, 0x14, 0x08 }, // >
        { 0x02, 0x01, 0x51, 0x09, 0x06 }, // ?
        { 0x32, 0x49, 0x59, 0x51, 0x3E }, // @
        { 0x7E, 0x11, 0x11, 0x11, 0x7E }, // A
        { 0x7F, 0x49, 0x49, 0x49, 0x36 }, // B
        { 0x3E, 0x41, 0x41, 0x41, 0x22 }, // C
        { 0x7F, 0x41, 0x41, 0x22, 0x1C }, // D
        { 0x7F, 0x49, 0x49, 0x49, 0x41 }, // E
        { 0x7F, 0x09, 0x09, 0x09, 0x01 }, // F
        { 0x3E, 0x41, 0x49, 0x49, 0x7A }, // G
        { 0x7F, 0x08, 0x08, 0x08, 0x7F }, // H
        { 0x00, 0x41, 0x7F, 0x41, 0x00 }, // I
        { 0x20, 0x40, 0x41, 0x3F, 0x01 }, // J
        { 0x7F, 0x08, 0x14, 0x22, 0x41 }, // K
        { 0x7F, 0x40, 0x40, 0x40, 0x40 }, // L
        { 0x7F, 0x02, 0x0C, 0x02, 0x7F }, // M
        { 0x7F, 0x04, 0x08, 0x10, 0x7F }, // N
        { 0x3E, 0x41, 0x41, 0x41, 0x3E }, // O
        { 0x7F, 0x09, 0x09, 0x09, 0x06 }, // P
        { 0x3E, 0x41, 0x51, 0x21, 0x5E }, // Q
        { 0x7F, 0x09, 0x19, 0x29, 0x46 }, // R
        { 0x46, 0x49, 0x49, 0x49, 0x31 }, // S
        { 0x01, 0x01, 0x7F, 0x01, 0x01 }, // T
        { 0x3F, 0x40, 0x40, 0x40, 0x3F }, // U
        { 0x1F, 0x20, 0x40, 0x20, 0x1F }, // V
        { 0x3F, 0x40, 0x38, 0x40, 0x3F }, // W
        { 0x63, 0x14, 0x08, 0x14, 0x63 }, // X
        { 0x07, 0x08, 0x70, 0x08, 0x07 }, // Y
        { 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z
        { 0x00, 0x7F, 0x41, 0x41, 0x00 }, // [
        { 0x55, 0x2A, 0x55, 0x2A, 0x55 }, // 55
        { 0x00, 0x41, 0x41, 0x7F, 0x00 }, // ]
        { 0x04, 0x02, 0x01, 0x02, 0x04 }, // ^
        { 0x40, 0x40, 0x40, 0x40, 0x40 }, // _
        { 0x00, 0x01, 0x02, 0x04, 0x00 }, // '
        { 0x20, 0x54, 0x54, 0x54, 0x78 }, // a
        { 0x7F, 0x48, 0x44, 0x44, 0x38 }, // b
        { 0x38, 0x44, 0x44, 0x44, 0x20 }, // c
        { 0x38, 0x44, 0x44, 0x48, 0x7F }, // d
        { 0x38, 0x54, 0x54, 0x54, 0x18 }, // e
        { 0x08, 0x7E, 0x09, 0x01, 0x02 }, // f
        { 0x0C, 0x52, 0x52, 0x52, 0x3E }, // g
        { 0x7F, 0x08, 0x04, 0x04, 0x78 }, // h
        { 0x00, 0x44, 0x7D, 0x40, 0x00 }, // i
        { 0x20, 0x40, 0x44, 0x3D, 0x00 }, // j
        { 0x7F, 0x10, 0x28, 0x44, 0x00 }, // k
        { 0x00, 0x41, 0x7F, 0x40, 0x00 }, // l
        { 0x7C, 0x04, 0x18, 0x04, 0x78 }, // m
        { 0x7C, 0x08, 0x04, 0x04, 0x78 }, // n
        { 0x38, 0x44, 0x44, 0x44, 0x38 }, // o
        { 0x7C, 0x14, 0x14, 0x14, 0x08 }, // p
        { 0x08, 0x14, 0x14, 0x18, 0x7C }, // q
        { 0x7C, 0x08, 0x04, 0x04, 0x08 }, // r
        { 0x48, 0x54, 0x54, 0x54, 0x20 }, // s
        { 0x04, 0x3F, 0x44, 0x40, 0x20 }, // t
        { 0x3C, 0x40, 0x40, 0x20, 0x7C }, // u
        { 0x1C, 0x20, 0x40, 0x20, 0x1C }, // v
        { 0x3C, 0x40, 0x30, 0x40, 0x3C }, // w
        { 0x44, 0x28, 0x10, 0x28, 0x44 }, // x
        { 0x0C, 0x50, 0x50, 0x50, 0x3C }, // y
        { 0x44, 0x64, 0x54, 0x4C, 0x44 } // z
};

/* Private function prototypes -----------------------------------------------*/
//static inline FuncResult Disp_NextColRow(u16 *x, u8 *row);

/* Private functions ---------------------------------------------------------*/
static inline void Disp_SendData(u8 byte);
static inline void Disp_SendCommand(u8 byte);
static inline void FeedDisp();
static inline void Disp_SendByte(u16 byte);

/* Private low-level functions -----------------------------------------------*/

static void Disp_Interface_Init()
{
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
  SPI_Init(DISP_SPI, &SPI_InitStructure);

  SPI_Cmd(DISP_SPI, ENABLE);
}

static inline void Disp_SendData(u8 byte)
{
  Disp_SendByte((byte | 0x100) << 7);
}

static inline void Disp_SendCommand(u8 byte)
{
  Disp_SendByte((byte & ~0x100) << 7);
}

static inline void FeedDisp()
{
  if (DISP_IS_VALID_X(ram_x))
  {
    assert_param(DISP_IS_VALID_ROW(ram_row));

    Disp_SendData(dispRAM[ram_row][ram_x]);
    ram_x++;
  }
}

static inline void Disp_SendByte(u16 byte)
{
  if (irq)
  {
    while (busy)
      ;
  }

  busy = true;
  Disp_SetCS(true);

  SPI_I2S_SendData(DISP_SPI, byte);

  /* XXX clear? */
  SPI_I2S_ITConfig(DISP_SPI, SPI_I2S_IT_RXNE, ENABLE);

  if (!irq)
  {
    while (!SPI_GetITStatus(DISP_SPI, SPI_IT_RXNE))
      ;

    SPI_I2S_ReceiveData(DISP_SPI);

    Disp_SetCS(DISABLE);
  }
}

static void Disp_SetXRow(u8 x, u8 row)
{
  Disp_SendCommand(0x10 | ((x >> 4) & 0x7));
  Disp_SendCommand(x & 0x0f);

  Disp_SendCommand(0xB0 | (row & 0x0f));
}

static inline void Disp_SetRowDirty(uint8_t row, bool dirty)
{
  assert_param(DISP_IS_VALID_ROW(row) || row == ALL_DISP_DIRTY);

  vPortEnterCritical();
  {
    if (dirty)
      dirty_row_flags |= _BV(row);
    else
      dirty_row_flags &= ~_BV(row);
  }
  vPortExitCritical();
}

void Disp_MainThread()
{
  u32 temp;
  u16 i;

  if (busy)
  {
    if (!irq)
    {
      FeedDisp();
    }
    return;
  }

  if (DISP_IS_VALID_X(ram_x))
  {
    return;
  }

  if (dirty_row_flags)
  {
    if (dirty_row_flags == _BV(ALL_DISP_DIRTY))
    {
      dirty_row_flags = 0;
      return;
    }

    for (i = 0; i <= DISP_ROW_COUNT; i++, ram_row++)
    {
      if (!DISP_IS_VALID_ROW(ram_row))
        ram_row = 0;

      temp = _BV(ram_row);
      if (temp & dirty_row_flags)
        break;
    }

    assert_param(DISP_IS_VALID_ROW(ram_row));

    Disp_SetXRow(0, ram_row);
    Disp_SetRowDirty(ram_row, false);
    ram_x = 0;

    FeedDisp();
    return;
  }
}

void Disp_IRQHandler()
{
  if (SPI_GetITStatus(DISP_SPI, SPI_IT_RXNE))
  {
    SPI_I2S_ReceiveData(DISP_SPI);

    Disp_SetCS(DISABLE);

    busy = false;

    FeedDisp();
  }
}

void Disp_SetData(u8 x, u8 row, u8 byte)
{
  assert_param(DISP_IS_VALID_X(x));
  assert_param(DISP_IS_VALID_ROW(row));

  if (dispRAM[row][x] != byte)
  {
    dispRAM[row][x] = byte;
    Disp_SetRowDirty(row, true);
  }
}

void Disp_Clear(void)
{
  u16 x, row;

  for (row = 0; row < DISP_ROW_COUNT; ++row)
  {
    Disp_ClearRow(row);
  }
}

void Disp_String(uint8_t col, uint8_t row, const char *ptr, bool new_line)
{
  u8 chr, i, i_row = row;
  u16 i_col = col;
  u8 *p_str = (u8 *) ptr;

  assert_param(DISP_IS_VALID_X(col));
  assert_param(DISP_IS_VALID_ROW(row));

  while (1)
  {
    chr = *p_str++;

    if (!chr)
      break;

    if (!DISP_IS_VALID_X(i_col + 5))
    {
      if (new_line)
      {
        i_col = 0;
        i_row++;
      }
      else
        break;
    }

    if (i_row > DISP_ROW_COUNT - 2)
      break;

    //todo: unicode
    //todo: line break
    if ((chr < 0x20) || ((chr -= 0x20) && (chr >= sizeof(FontLookup) / 5)))
    {
      //  Convert to a printable character.
      chr = '[' + 1 - 0x20;
    }

    for (i = 0; i < 5; i++)
    {
      assert_param(chr < sizeof(FontLookup) / 5);
      Disp_SetData(i_col, i_row, FontLookup[chr][i]);
      i_col++;
    }

    //  Horizontal gap between characters.
    Disp_SetData(i_col, i_row, 0);
    i_col++;
  }
}

void Disp_ClearRow(uint8_t row)
{
  assert_param(DISP_IS_VALID_ROW(row));

  bzero(dispRAM[row], sizeof(dispRAM[row]));

  Disp_SetRowDirty(row, true);
}

/* Private functions ---------------------------------------------------------*/
static void Disp_InitFinally()
{
  Disp_SetRST(DISABLE);

  if (irq)
  {
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = DISP_SPI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configIRQ_PRIORITY_DISP;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  }

  Disp_SendCommand(0x20); // write VOP register
  Disp_SendCommand(0x90);
  Disp_SendCommand(0xA4); // all on/normal display
  Disp_SendCommand(0x2F); // Power control set(charge pump on/off)
  Disp_SendCommand(0x40); // set start row address = 0
  Disp_SendCommand(0xac); // set initial row (R0) of the display
  Disp_SendCommand(0x07);
  Disp_SendCommand(0xF9); //
  Disp_SendCommand(0xaf); // display ON/OFF
  Disp_SendCommand(0xa6); // normal display (non inverted) a6

  //

  dirty_row_flags = _BV(DISP_ROW_COUNT) - 1;
  Disp_SetRowDirty(ALL_DISP_DIRTY, true);
}

void Disp_Init()
{
  ram_x = DISP_X_COUNT;
  dirty_row_flags = 0;

  Disp_GPIO_Init();
  Disp_SetRST(ENABLE);
  Disp_SetCS(DISABLE);
  busy = false;
  irq = true;

  Disp_Interface_Init();

  vTaskDelay(100);

  Disp_InitFinally();
}


void uDelay (const uint32_t usec)
{
  uint32_t count = 0;
  const uint32_t utime = (120 * usec / 7);
  do
  {
    if ( ++count > utime )
    {
      return ;
    }
  }
  while (1);
}


void mDelay (const uint32_t msec)
{
    uDelay(msec * 1000);
}

void Disp_InitIRQ_Less(void)
{
  ram_x = DISP_X_COUNT;
  dirty_row_flags = 0;

  Disp_Clear();

  Disp_GPIO_Init();
  Disp_SetRST(ENABLE);
  Disp_SetCS(DISABLE);
  busy = false;
  irq = false;

  Disp_Interface_Init();

  mDelay(100);

  Disp_InitFinally();
}
