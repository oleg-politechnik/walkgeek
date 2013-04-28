/*
 * keyboard.c
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
#include "keyboard.h"
#include "system.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define KEY_COL(index) (index % KEYBOARD_COL_COUNT)
#define KEY_ROW(index) (index / KEYBOARD_ROW_COUNT)
#define KEY_INDEX(row, col) ((row)*KEYBOARD_COL_COUNT + col)

/* Private variables ---------------------------------------------------------*/
static u8 key_matrix[KEYBOARD_ROW_COUNT][KEYBOARD_COL_COUNT];
static u8 _debounce_matrix[KEYBOARD_ROW_COUNT][KEYBOARD_COL_COUNT];
static u8 row_ix;
static bool ppp_while_start;

static KEY_Typedef key_pressed = _KEY_DUMMY;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Keyboard_Init(void)
{
  ppp_while_start = BSP_GetPPPButton();

  BSP_Keyboard_Init();
}

KEY_Typedef Keyboard_CurrentKey()
{
  return key_pressed;
}

static inline void Keyboard_KeyPressed(KEY_Typedef code)
{
  if (key_pressed == _KEY_DUMMY)
  {
    key_pressed = code;

    if (ppp_while_start && code == KEY_PPP)
    {
      return;
    }

    Keyboard_KeyPressedCallback(code);
  }
}

static inline void Keyboard_KeyReleased(KEY_Typedef code)
{
  if (key_pressed == code)
  {
    key_pressed = _KEY_DUMMY;

    if (ppp_while_start && code == KEY_PPP)
    {
      ppp_while_start = false;
      return;
    }

    Keyboard_KeyReleasedCallback(code);
  }
}

u8 Keyboard_GetRowValues(u8 row_index)
{
  if (row_index == 0)
  {
    u8 ret_val = 0;

    ret_val |= BSP_GetPPPButton() ? (1 << KEY_PPP) : 0;
    ret_val |= BSP_GetESCButton() ? (1 << KEY_ESC) : 0;

    return ret_val;
  }

  return BSP_KeyboardGetRowValues(row_ix);
}

static inline void Keyboard_ScanRow()
{
  u8 i_col;
  u8 *p_debounce;
  u8 i_row_value, code;

  assert_param(row_ix < KEYBOARD_ROW_COUNT);

  //

  i_row_value = Keyboard_GetRowValues(row_ix);
  // строки нажатых кнопок
  for (i_col = 0; i_col < KEYBOARD_COL_COUNT; i_col++)
  {
    p_debounce = &_debounce_matrix[row_ix][i_col]; // адресация по индексу
    code = KEY_INDEX(row_ix, i_col);

    if (i_row_value & _BV(i_col))
    { // кнопка нажата (индекс)?
      //да
      if (key_matrix[row_ix][i_col])
      {
        *p_debounce = 0;
      }
      else
      {
        ++*p_debounce;
        if (*p_debounce > KEYBOARD_DEBOUNCE_MS)
        {
          *p_debounce = 0; // по такой же схеме будем обрабатывать отжатия
          key_matrix[row_ix][i_col] = true;
          Keyboard_KeyPressed(code);
        }
      }
    }
    else
    {
      //нет
      if (key_matrix[row_ix][i_col])
      { // флаг кнопки взведен (код)?
        ++*p_debounce;
        if (*p_debounce > KEYBOARD_DEBOUNCE_MS)
        {
          *p_debounce = 0;
          key_matrix[row_ix][i_col] = false;
          Keyboard_KeyReleased(code);
        }
      }
      else
      {
        *p_debounce = 0;
      }
    }
  }
}

void Keyboard_Scan()
{
  row_ix = 0;
  do
  {
    Keyboard_ScanRow();
  } while (++row_ix < KEYBOARD_ROW_COUNT);
}
