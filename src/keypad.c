/*
 * keypad.c
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
#include "keypad.h"
#include "system.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static bool ppp_while_start;
static KEY_Typedef key_pressed = _KEY_DUMMY;

static bool key_matrix[KEY_MAX];
static u8 _debounce_matrix[KEY_MAX];

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static inline void Key_Released(KEY_Typedef code)
{
  if (key_pressed == code)
  {
    key_pressed = _KEY_DUMMY;

    if (ppp_while_start && code == KEY_PPP)
    {
      ppp_while_start = false;
      return;
    }

    Keypad_KeyReleasedCallback(code);
  }
}

static inline void Key_Pressed(KEY_Typedef code)
{
  if (key_pressed == _KEY_DUMMY)
  {
    key_pressed = code;

    if (ppp_while_start && code == KEY_PPP)
    {
      return;
    }

    Keypad_KeyPressedCallback(code);
  }
}

void Keypad_Init(void)
{
  ppp_while_start = BSP_Keypad_GetKeyStatus(KEY_PPP);

  BSP_Keypad_Init();

  key_pressed = _KEY_DUMMY;

  memset(key_matrix, 0, sizeof(key_matrix));
  memset(_debounce_matrix, 0, sizeof(_debounce_matrix));
}

void RAM_FUNC Keypad_1msScan(void)
{
  u8 key_ix;
  u8 *p_debounce;

  for (key_ix = 0; key_ix < KEY_MAX; key_ix++)
  {
    p_debounce = &_debounce_matrix[key_ix];

    if (BSP_Keypad_GetKeyStatus(key_ix))
    {
      if (key_matrix[key_ix])
      {
        *p_debounce = 0;
      }
      else
      {
        ++*p_debounce;
        if (*p_debounce > KEY_DEBOUNCE_MS)
        {
          *p_debounce = 0;
          key_matrix[key_ix] = true;
          Key_Pressed(key_ix);
        }
      }
    }
    else
    {
      if (key_matrix[key_ix])
      {
        ++*p_debounce;
        if (*p_debounce > KEY_DEBOUNCE_MS)
        {
          *p_debounce = 0;
          key_matrix[key_ix] = false;
          Key_Released(key_ix);
        }
      }
      else
      {
        *p_debounce = 0;
      }
    }
  }
}

KEY_Typedef Keypad_CurrentKey()
{
  return key_pressed;
}
