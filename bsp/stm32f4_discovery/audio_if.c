/*
 * audio_if.c
 *
 * Copyright (c) 2012, 2013, Oleg Tsaregorodtsev
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
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "audio_if.h"
#include "bsp.h"
#include "stm32f4_discovery_audio_codec.h"
#include "player.h"
#include "../3rd_party/STM32_USB-Host-Device_Lib_V2.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static volatile AudioState_Typedef AudioState = AS_STOPPED;
static uint32_t Volume;
static uint32_t NeglectedDMA_Count;
volatile uint32_t DMA_Starving_Flag;

static Buffer_Typedef Buffers[2];
static Buffer_Typedef *CurrentBuffer = &Buffers[0];
static Buffer_Typedef *NextBuffer = &Buffers[1];
static uint32_t SampleRate;

static xSemaphoreHandle buffer_mutex;

static const u8 log_table[] =
{ 0, 1, 15, 24, 30, 35, 39, 42, 45, 48, 50, 52, 54, 56, 57, 59, 60, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 72, 73, 74, 75, 75, 76, 77, 77, 78, 78,
        79, 80, 80, 81, 81, 82, 82, 83, 83, 84, 84, 85, 85, 85, 86, 86, 87, 87,
        87, 88, 88, 89, 89, 89, 90, 90, 90, 91, 91, 91, 92, 92, 92, 93, 93, 93,
        93, 94, 94, 94, 95, 95, 95, 95, 96, 96, 96, 96, 97, 97, 97, 97, 98, 98,
        98, 98, 99, 99, 99, 99, 100, 100 };

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static FuncResult Audio_Init(void);
static u32 ConvertVolume(u32 NewVolume);
static uint32_t AudioBuffer_CurrentBuffer(void);

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void Audio_Error(void)
{
  SetVariable(VAR_AudioStatus, AudioState, AS_ERROR);
}

FuncResult Audio_Init(void)
{
  /* Call low layer function */
  if (EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, ConvertVolume(Volume))
          != 0)
  {
    Audio_Error();
    return FUNC_ERROR;
  }
  SetVariable(VAR_AudioStatus, AudioState, AS_STOPPED);
  return FUNC_SUCCESS;
}

FuncResult Audio_Pause(void)
{
  if (AudioState == AS_PAUSED)
  {
    return FUNC_SUCCESS;
  }

  if (AudioState != AS_PLAYING)
  {
    return FUNC_NOT_SUCCESS;
  }

  if (EVAL_AUDIO_PauseResume(AUDIO_PAUSE) != 0)
  {
    Audio_Error();
    return FUNC_ERROR;
  }

  SetVariable(VAR_AudioStatus, AudioState, AS_PAUSED);
  return FUNC_SUCCESS;
}

void Audio_Stop(void)
{
  SetVariable(VAR_AudioPosition, SampleRate, 0);
  EVAL_AUDIO_Stop(CODEC_PDWN_SW); //XXX CODEC_PDWN_HW
  bzero(&Buffers, sizeof(Buffers));
  CurrentBuffer = &Buffers[0];
  NextBuffer = &Buffers[1];
  SetVariable(VAR_AudioStatus, AudioState, AS_STOPPED);
}

u32 ConvertVolume(u32 NewVolume)
{
  assert_param(NewVolume <= 100);
  SetVariable(VAR_AudioVolume, Volume, NewVolume);
  return log_table[NewVolume];
}

FuncResult Audio_SetVolume(u8 NewVolume)
{
  if (AudioState == AS_STOPPED)
  {
    SetVariable(VAR_AudioVolume, Volume, NewVolume);
    return FUNC_SUCCESS;
  }

  if (EVAL_AUDIO_VolumeCtl(ConvertVolume(NewVolume)) != 0)
  {
    Audio_Error();
    return FUNC_ERROR;
  }

  return FUNC_SUCCESS;
}

FuncResult Audio_ChangeVolume(s8 delta) //todo async
{
  s16 new_volume = Audio_GetVolume() + delta;

  if (delta > 0)
  {
    if (new_volume > DEFAULT_VOLMAX)
    {
      new_volume = DEFAULT_VOLMAX;
    }
  }
  else
  {
    if (new_volume < DEFAULT_VOLMIN)
    {
      new_volume = DEFAULT_VOLMIN;
    }
  }

  return Audio_SetVolume(new_volume);
}

AudioState_Typedef Audio_GetState(void)
{
  return AudioState;
}

u32 Audio_GetSampleRate(void)
{
  return SampleRate;
}

u8 Audio_GetVolume(void)
{
  return Volume;
}

void EVAL_AUDIO_TransferComplete_CallBack(void)
{
  Buffer_Typedef *TempBuffer;

  configASSERT(CurrentBuffer->full);
  configASSERT(CurrentBuffer->size);
  configASSERT(CurrentBuffer->sampling_freq);

  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

  if (AudioState == AS_PLAYING)
  {
    if (!NextBuffer->full)
    {
      NeglectedDMA_Count++;
      DMA_Starving_Flag = true; /* todo -> handle this situation */
    }
    else
    {
      TempBuffer = CurrentBuffer;
      CurrentBuffer = NextBuffer;
      NextBuffer = TempBuffer;

      if (CurrentBuffer->sampling_freq != SampleRate)
      {
        trace("New sampling freq: %u (was %u)\n",
                (unsigned int) CurrentBuffer->sampling_freq,
                (unsigned int) SampleRate);

        Codec_AudioInterface_Init(CurrentBuffer->sampling_freq);
        SetVariable(VAR_AudioPosition, SampleRate, CurrentBuffer->sampling_freq);
        SampleRate = CurrentBuffer->sampling_freq;
      }

      if (CurrentBuffer->size != NextBuffer->size)
      {
        Audio_MAL_Play((uint32_t) CurrentBuffer->data,
                (uint32_t) NextBuffer->data, CurrentBuffer->size * sizeof(u16));
      }
    }

    NextBuffer->full = false;

    configASSERT(buffer_mutex);
    xSemaphoreGiveFromISR(buffer_mutex, &xHigherPriorityTaskWoken);

    /* Switch context if necessary. */
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
  }
}

Buffer_Typedef *Audio_GetBuffer(u16 size, u32 sampling_freq)
{
  /*
   * First function to call from Decoder, sort of entry point
   */

  if (!buffer_mutex)
  {
    buffer_mutex = xSemaphoreCreateMutex();
    configASSERT(buffer_mutex);
  }

  Buffer_Typedef *ReturnBuffer;

  if (AudioState == AS_STOPPED)
  {
    configASSERT(!CurrentBuffer->full);
    ReturnBuffer = CurrentBuffer;
  }
  else
  {
    configASSERT(CurrentBuffer->full);
    ReturnBuffer = NextBuffer;
  }

  if (ReturnBuffer->full)
  {
    signed portBASE_TYPE xReturn;
    xReturn = xSemaphoreTake(buffer_mutex, portMAX_DELAY);
    if (!xReturn)
    {
      return NULL;
    }
  }

  configASSERT(!ReturnBuffer->full);

  if (ReturnBuffer->size != size)
  {
    if (ReturnBuffer->data)
    {
      vPortFree(ReturnBuffer->data);
    }
    ReturnBuffer->data = pvPortMalloc(size * sizeof(u16));
    DMA_MemoryTargetConfig(AUDIO_MAL_DMA_STREAM,
            (uint32_t) ReturnBuffer->data, ReturnBuffer == &Buffers[1] ? DMA_Memory_1 : DMA_Memory_0);

    /*TODO */
    /*
     * if (DMA error)
     * {
     * Audio_Error();
     * return NULL;
     * }
     *
     * */

    ReturnBuffer->size = size;
  }

  ReturnBuffer->sampling_freq = sampling_freq;

  return ReturnBuffer;
}

FuncResult Audio_AppendBuffer(Buffer_Typedef *AppendableBuffer)
{
  configASSERT(!AppendableBuffer->full);
  configASSERT(AppendableBuffer->sampling_freq);
  configASSERT(AppendableBuffer->size);

  AppendableBuffer->full = true;

  if (AudioState == AS_PAUSED)
  {
    if (EVAL_AUDIO_PauseResume(AUDIO_RESUME) != 0)
    {
      Audio_Error();
      return FUNC_ERROR;
    }
  }

  if (AudioState == AS_STOPPED)
  {
    configASSERT(AppendableBuffer == CurrentBuffer);

    FuncResult fr = Audio_Init();
    if (fr != FUNC_SUCCESS)
    {
      return fr;
    }

    Codec_AudioInterface_Init(AppendableBuffer->sampling_freq);
    SetVariable(VAR_AudioPosition, SampleRate, AppendableBuffer->sampling_freq);
    Audio_MAL_Play((uint32_t) CurrentBuffer->data, (uint32_t) NextBuffer->data,
            CurrentBuffer->size * sizeof(u16));
  }

  SetVariable(VAR_AudioStatus, AudioState, AS_PLAYING);
  return FUNC_SUCCESS;
}

void EVAL_AUDIO_Error_CallBack()
{
  configASSERT(!"DMA ERROR");
}

