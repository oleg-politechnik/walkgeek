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
#include "disp_1100.h"
#include "stm32f4xx_conf.h"
#include "misc.h"

#define BUF_SIZE DISP_CMD_STACK_SIZE
#include "circ_buffer.h"
#include <string.h>
#include "scheduler.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define DISP_INDEX_COUNT            (DISP_X_COUNT * DISP_ROW_COUNT)

#define DISP_IS_VALID_ROW(row)      (row < DISP_ROW_COUNT)
#define DISP_IS_VALID_X(x)          (x < DISP_X_COUNT)
#define DISP_IS_VALID_Y(y)          (y < DISP_Y_COUNT)
#define DISP_IS_VALID_INDEX(ix)     (ix < DISP_INDEX_COUNT)

#define DISP_INDEX(x, row)          (x + row * DISP_X_COUNT)
#define DISP_IS_VALID_STACK_PTR(ptr)(ptr < DISP_CMD_STACK_SIZE)

#define ALL_DISP_DIRTY              DISP_ROW_COUNT

/* Private variables ---------------------------------------------------------*/
static uint8_t dispBUF[DISP_ROW_COUNT][DISP_X_COUNT];
static uint8_t dispRAM[DISP_ROW_COUNT][DISP_X_COUNT];
circular_buffer_t cmd_buf;
static __IO uint32_t dirty_row_flags;
static u16 ram_x;
static u8 ram_row;
static u16 flush_spi_x;
static u8 flush_spi_row;

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
/* Private low-level functions -----------------------------------------------*/

static void Disp_Interface_Init()
{
  SPI_InitTypeDef SPI_InitStructure;

  SPI_StructInit(&SPI_InitStructure);
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
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

bool Disp_IsBusy()
{
  uint16_t itmask = 0;

  itmask = (uint16_t) 1 << (uint16_t) (SPI_I2S_IT_TXE >> 4);

  return ((DISP_SPI->CR2 & itmask) == itmask) ? (true) : (false);
}

static inline void Disp_SetBusy(bool enable)
{
  SPI_I2S_ITConfig(DISP_SPI, SPI_I2S_IT_TXE, enable);
}

void Disp_Sync()
{
  //  Disp_SetBusy(ENABLE);
}

static inline void Disp_SendByte(u16 byte)
{
  while (SPI_I2S_GetFlagStatus(DISP_SPI, SPI_I2S_FLAG_BSY) == SET)
    ;

  Disp_SetCS(true);

  SPI_I2S_GetITStatus(DISP_SPI, SPI_I2S_IT_TXE); //ClearIRQ
  Disp_SetBusy(ENABLE);

  SPI_I2S_SendData(DISP_SPI, byte);
}

static inline void Disp_SendData(u8 byte)
{
  Disp_SendByte((byte | 0x100) << 7);

  flush_spi_x++;
}

static inline void Disp_QueueCommand(uint8_t c)
{
  while (circular_fifo_is_full(&cmd_buf))
  {
    Disp_Sync();
  }

  CPU_DisableInterrupts();
  {
    circular_fifo_push(&cmd_buf, (c & ~0x100) << 7);
  }
  CPU_EnableInterrupts();

  Disp_Sync();
}

static inline void Disp_SetRowDirty(uint8_t row, bool dirty)
{
  assert_param(DISP_IS_VALID_ROW(row) || row == ALL_DISP_DIRTY);

  CPU_DisableInterrupts();
  {
    //dirty_row_flags &= (1 << DISP_ROW_COUNT) - 1;

    if (dirty)
      dirty_row_flags |= _BV(row);
    else
      dirty_row_flags &= ~_BV(row);
  }
  CPU_EnableInterrupts();
}

static inline FuncResult Disp_SyncColRow(u16 x, u8 row)
{
  FuncResult res = FUNC_SUCCESS;

  assert_param(DISP_IS_VALID_X(x));
  assert_param(DISP_IS_VALID_ROW(row));

  if (flush_spi_x != x)
  {
    Disp_QueueCommand(0x10 | ((x >> 4) & 0x7));
    Disp_QueueCommand(x & 0x0f);
    flush_spi_x = x;

    res = FUNC_ERROR;
  }

  if (flush_spi_row != row)
  {
    Disp_QueueCommand(0xB0 | (row & 0x0f));
    flush_spi_row = row;

    res = FUNC_ERROR;
  }

  return res;
}

//static inline FuncResult Disp_NextColRow(u16 *x, u8 *row)
//{
//  (*x)++;
//
//  if (!DISP_IS_VALID_X(*x))
//  {
//    (*x) = 0;
//    (*row)++;
//  }
//
//  if (!DISP_IS_VALID_ROW(*row))
//  {
//    (*row) = 0;
//    return FR_ERROR;
//  }
//
//  return FR_SUCCESS;
//}

void Disp_Manager()
{
  u32 temp;
  u16 i;

  if (Disp_IsBusy())
  {
    return;
  }

  if (!circular_fifo_is_empty(&cmd_buf))
  {
    Disp_SetBusy(ENABLE);
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

    ram_x = 0;
    Disp_SetRowDirty(ram_row, false);
    Disp_SetBusy(ENABLE);

    flush_spi_x = DISP_X_COUNT;
    flush_spi_row = DISP_ROW_COUNT;
    return;
  }
}

void Disp_IRQHandler()
{
  u16 x, word;

  Disp_SetCS(DISABLE);

  assert_param(DISP_IS_VALID_ROW(ram_row));

  //  if (SPI_I2S_GetFlagStatus(DISP_SPI, SPI_I2S_FLAG_BSY) == SET)
  //    return;

  if (!circular_fifo_is_empty(&cmd_buf))
  {
    CPU_DisableInterrupts();
    {
      circular_fifo_pop(&cmd_buf, &word);
    }
    CPU_EnableInterrupts();
    Disp_SendByte(word);
    return;
  }
  else if (DISP_IS_VALID_X(ram_x))
  {
    for (x = ram_x; x < DISP_X_COUNT; x++)
    {
      if (dispRAM[ram_row][x] != dispBUF[ram_row][x] || (dirty_row_flags
              & _BV(ALL_DISP_DIRTY)))
      {
        //        if (offset != 0 && offset <= 3)
        //        {
        //          for (i = 1; i <= offset; i++)//fixme?i=1
        //            dispBUF[ram_ix + i] = dispRAM[ram_ix + i] + 1;
        //        }
        //        ix = ram_ix;

        ram_x = x;

        if (Disp_SyncColRow(ram_x, ram_row) == FUNC_ERROR)
          return;

        dispBUF[ram_row][ram_x] = dispRAM[ram_row][ram_x];
        Disp_SendData(dispBUF[ram_row][ram_x]);
        ram_x++;

        flush_spi_x = DISP_X_COUNT;
        flush_spi_row = DISP_ROW_COUNT;

        return;
      }
    }

    ram_x = DISP_X_COUNT;
  }

  Disp_SetBusy(DISABLE);
}

void Disp_SetContrast(uint8_t contrast)
{
  Disp_QueueCommand(0x21); // LCD Extended Commands.
  Disp_QueueCommand(0x80 | contrast); // Set LCD Vop (Contrast).
  Disp_QueueCommand(0x20); // LCD Standard Commands, Horizontal addressing mode.
}

//static inline FuncResult Disp_NextXY(u16 *x, u16 *y, u8 row_size)
//{
//  row_size = 8;
//
//  (*x)++;
//
//  if (!DISP_IS_VALID_X(*x)) {
//    (*x) = 0;
//    (*y) += row_size;
//  }
//
//  if (!DISP_IS_VALID_Y(*y)) {
//    return FR_ERROR;
//  }
//
//  return FR_SUCCESS;
//}


void Disp_SetData(u8 x, u8 row, u8 byte)
{
  //  u8 row = y / 8;
  //  u8 byte0 = CTRL_ROW(offset_code);
  //  u8 bit0, mask;
  assert_param(DISP_IS_VALID_X(x));
  assert_param(DISP_IS_VALID_ROW(row));

  //#if (col_count != 8)
  //  row &= _BV(col_count) - 1;
  //#endif

  //  bit0 = CTRL_COL(offset_code);
  //
  //  mask = _BV(bit0) - 1;
  //
  //  disp_RAM[DISP_INDEX(col, row)] &= mask;
  //  disp_RAM[DISP_INDEX(col, row)] |= row << bit0;
  //
  //  disp_RAM[DISP_INDEX(col, row + 1)] &= ~mask;
  //  disp_RAM[DISP_INDEX(col, row + 1)] |= row >> (8 - bit0);

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
    for (x = 0; x < DISP_X_COUNT; ++x)
    {
      Disp_SetData(x, row, /*(x + row * DISP_X_COUNT) % 0xFF*/0);
    }
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

  Disp_Sync();
}

/* Private functions ---------------------------------------------------------*/
static void Disp_InitFinally()
{
  Disp_SetRST(DISABLE);

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DISP_SPI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  Disp_QueueCommand(0x20); // write VOP register
  Disp_QueueCommand(0x90);
  Disp_QueueCommand(0xA4); // all on/normal display
  Disp_QueueCommand(0x2F); // Power control set(charge pump on/off)
  Disp_QueueCommand(0x40); // set start row address = 0

  //  Disp_QueueCommand(0xb0); // set Y-address = 0
  //  Disp_QueueCommand(0x10); // set X-address, upper 3 bits
  //  Disp_QueueCommand(0x0); // set X-address, lower 4 bits

  //  Disp_Cmd(0xC8); // mirror Y axis (about X axis)
  //  Disp_Cmd(0xa1); // Invert screen in horizontal axis
  Disp_QueueCommand(0xac); // set initial row (R0) of the display
  Disp_QueueCommand(0x07);
  Disp_QueueCommand(0xF9); //
  Disp_QueueCommand(0xaf); // display ON/OFF
  Disp_QueueCommand(0xa6); // normal display (non inverted)

  //

  flush_spi_x = DISP_X_COUNT;
  flush_spi_row = DISP_ROW_COUNT;

  dirty_row_flags = _BV(DISP_ROW_COUNT) - 1;
  Disp_SetRowDirty(ALL_DISP_DIRTY, true);

  Scheduler_PutTask(10, &Disp_Manager, REPEAT);
}

void Disp_Init()
{
  ram_x = DISP_X_COUNT;
  dirty_row_flags = 0;

  circular_fifo_init(&cmd_buf);

  memset(dispRAM, 0, sizeof(dispRAM));

  Disp_GPIO_Init();
  Disp_SetRST(ENABLE);
  Disp_SetCS(DISABLE);

  Disp_Interface_Init();

  Scheduler_PutTask(100, &Disp_InitFinally, NO_REPEAT);
}

//
///*******************************************************************************
// * Function Name  : LCD_DrawRect
// * Description    : Displays a rectangle.
// * Input          : - Xpos: specifies the X position.
// *                  - Ypos: specifies the Y position.
// *                  - Height: display rectangle height.
// *                  - Width: display rectangle width.
// * Output         : None
// * Return         : None
// *******************************************************************************/
//void LCD_DrawRect(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
//{
//    //  LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
//    //  LCD_DrawLine((Xpos + Height), Ypos, Width, Horizontal);
//    //
//    //  LCD_DrawLine(Xpos, Ypos, Height, Vertical);
//    //  LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, Vertical);
//}
//
///*******************************************************************************
// * Function Name  : LCD_DrawMonoPict
// * Description    : Displays a monocolor picture.
// * Input          : - Pict: pointer to the picture array.
// * Output         : None
// * Return         : None
// *******************************************************************************/
//void LCD_DrawMonoPict(const uint32_t *Pict)
//{
//    //  uint32_t index = 0, i = 0;
//    //
//    //  LCD_SetCursor(0, 319);
//    //
//    //  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
//    //  for(index = 0; index < 2400; index++)
//    //  {
//    //    for(i = 0; i < 32; i++)
//    //    {
//    //      if((Pict[index] & (1 << i)) == 0x00)
//    //      {
//    //        LCD_WriteRAM(BackColor);
//    //      }
//    //      else
//    //      {
//    //        LCD_WriteRAM(TextColor);
//    //      }
//    //    }
//    //  }
//}

//#define col_count 8
//
//u8 ctrl_mx_get_row(const u8 *matrix, ctrl_t offset_code)
//{
//  u8 byte0 = CTRL_ROW(offset_code);
//  u8 bit0, row;
//  if (byte0 > SYS_MATRIX_SIZE - 1) {
//    return 0;
//  }
//
//  bit0 = CTRL_COL(offset_code);
//  row = 0;
//
//  row |= matrix[byte0] >> bit0;
//  row |= (matrix[byte0 + 1] << (8 - bit0));
//
//#if (col_count != 8)
//  row &= _BV(col_count) - 1;
//#endif
//
//  return row;
//}


//u8 ctrl_mx_get_row(const u8 *matrix, ctrl_t offset_code);
//void ctrl_mx_set_row(u8 *matrix, ctrl_t offset_code, u8 row/*, u8 mask*/);
//
//static __inline void Disp_SetPixel(u16 x, u16 y, boolbool)
//{
//    assert_param()
//
//    if (value) {
//        matrix[CTRL_ROW(code)] |= _BV(CTRL_COL(code));
//    } else {
//        matrix[CTRL_ROW(code)] &= ~_BV(CTRL_COL(code));
//    }
//
//    return;
//}
//
//static __inline void Disp_TogglePixel(u16 x, u16 y)
//{
//    if (code > CTRL_MAX) {
//        return;
//    }
//
//    matrix[CTRL_ROW(code)] ^= _BV(CTRL_COL(code));
//
//    return;
//}
