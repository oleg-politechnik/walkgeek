/*
 * audio_buffer.c
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
#include "audio_buffer.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static u8 length, index_consumer;
static AudioBuffer_Typedef buffers[AUDIO_BUFFER_COUNT];

//static u32 stats_length[AUDIO_BUFFER_COUNT]; //todo -> malloc

void AudioBuffer_Init(void)
{
  length = index_consumer = 0;

  for (int i = 0; i < AUDIO_BUFFER_COUNT; i++)
  {
    buffers[i].size = 0;
  }
}

u8 AudioBuffer_GetFullCount(void)
{
  return length;
}

AudioBuffer_Typedef *AudioBuffer_TryGetProducer(void)
{
  if (length + 1 < AUDIO_BUFFER_COUNT)
  {
    int ix;

    CPU_DisableInterrupts();
    {
      ix = (index_consumer + length) % AUDIO_BUFFER_COUNT;
    }
    CPU_EnableInterrupts();

    return (&buffers[ix]);
  }
  else
  {
    return (0);
  }
}

void AudioBuffer_MoveProducer(void)
{
  assert_param(length + 1 < AUDIO_BUFFER_COUNT);
  CPU_DisableInterrupts();
  {
    length++;
  }
  CPU_EnableInterrupts();
}

AudioBuffer_Typedef *AudioBuffer_TryGetConsumer(void)
{
//  stats_length[length]++;

  return ((length > 0)) ? (&buffers[index_consumer]) : 0;
}

void AudioBuffer_MoveConsumer(void)
{
  assert_param(length > 0);

  CPU_DisableInterrupts();
  {
    length--;
    buffers[index_consumer].size = 0;
    index_consumer = (index_consumer + 1) % AUDIO_BUFFER_COUNT;
  }
  CPU_EnableInterrupts();

  //    iprintf("con_length %i\n", length);
}
