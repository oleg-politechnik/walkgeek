/*
 * audio_if.c
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
#include "FreeRTOS.h"
#include "semphr.h"

#include "audio_if.h"
#include "bsp.h"
#include "audio_buffer.h"
//#include "stm324xg_usb_audio_codec.h"
#include "stm32f4_discovery_audio_codec.h"
#include "player.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static volatile AudioState_Typedef AudioState = AS_STOPPED;
static int Volume;
static uint32_t SampleRate;
static uint32_t NeglectedDMA_Count;
static volatile uint32_t DMA_Starving_Flag;

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static FuncResult Audio_Init(u32 AudioFreq);
static FuncResult FeedDMA(void);
static FuncResult Audio_DoCommand(AudioCommand_Typedef cmd);

void AudioBuffer_Init(void);
u8 AudioBuffer_GetFullCount(void);

AudioBuffer_Typedef *AudioBuffer_TryGetProducer(void);

AudioBuffer_Typedef *AudioBuffer_TryGetConsumer(void);
void AudioBuffer_MoveConsumer(void);

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void Audio_Error(void)
{
  UI_SetVariable(VAR_AudioStatus, AudioState, AS_ERROR);
}

FuncResult Audio_Init(u32 AudioFreq)
{

  /* Call low layer function */
  if (EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, Volume, AudioFreq)
          != 0)
  {
    Audio_Error();
    return FUNC_ERROR;
  }

  /* Codec supports this value AudioFreq */

  SampleRate = AudioFreq;
  UI_SetVariable(VAR_AudioStatus, AudioState, AS_STOPPED);

  return FUNC_SUCCESS;
}

void Audio_DeInit(void)
{
  if (AudioState == AS_STOPPED)
    return;

  /* TODO: take a look at the correct codec shutdown sequence in the datasheet */

  Audio_CommandSync(AC_STOP);
}

static FuncResult Audio_DoCommand(AudioCommand_Typedef cmd)
{
  if (AudioState == AS_ERROR && cmd != AC_STOP)
    return FUNC_ERROR;

  FuncResult fr;

  switch (cmd)
  {
    /* Process the PLAY command ----------------------------*/
    case AC_PLAY:
      switch (AudioState)
      {
        case AS_PAUSED:
        case AS_PLAYING:
        case AS_STOPPED:
          DMA_Starving_Flag = true;
          UI_SyncVariable(VAR_AudioStatus);
          return FUNC_SUCCESS;

        case AS_ERROR:
          return FUNC_ERROR;
      }
      break;

    case AC_PLAY_PAUSE:
      if (AudioState == AS_PAUSED || AudioState == AS_STOPPED)
      {
        return Audio_DoCommand(AC_PLAY);
      }
      else if (AudioState == AS_PLAYING)
      {
        return Audio_DoCommand(AC_PAUSE);
      }
      return FUNC_NOT_SUCCESS;

      /* Process the STOP command ----------------------------*/
    case AC_STOP:
      SampleRate = 0;

      EVAL_AUDIO_Stop(CODEC_PDWN_SW); //XXX CODEC_PDWN_HW

      UI_SetVariable(VAR_AudioStatus, AudioState, AS_STOPPED);
      return FUNC_SUCCESS;

      /* Process the PAUSE command ---------------------------*/
    case AC_SUSPEND:
      DMA_Starving_Flag = true;
      UI_SyncVariable(VAR_AudioStatus);
      if (AudioState == AS_PLAYING)
      {
        fr = Audio_DoCommand(AC_PAUSE);
      }
      else
      {
        fr = Audio_DoCommand(AC_STOP);
      }
      return fr;

    case AC_PAUSE:
      if (AudioState == AS_PAUSED)
      {
        return FUNC_SUCCESS;
      }

      if (AudioState != AS_PLAYING)
      {
        return FUNC_NOT_SUCCESS;
      }

      if (EVAL_AUDIO_PauseResume(AUDIO_PAUSE/*, 0, 0*/) != 0)
      {
        Audio_Error();
        return FUNC_ERROR;
      }

      UI_SetVariable(VAR_AudioStatus, AudioState, AS_PAUSED);
      return FUNC_SUCCESS;

      /* Process the PAUSE command ---------------------------*/
    case AC_RESET_BUFFERS:
      fr = Audio_DoCommand(AC_PAUSE);

      AudioBuffer_Init();
      return fr;

      /* Unsupported command ---------------------------------*/
    default:
      return FUNC_NOT_SUCCESS;
  }

  return FUNC_NOT_SUCCESS;
}

FuncResult Audio_CommandSync(AudioCommand_Typedef cmd)
{
  bool main_thread_in_do_command_old;
  FuncResult fr, fr2;

  vPortEnterCritical();

  fr = Audio_DoCommand(cmd);

  vPortExitCritical();

  fr2 = Audio_PeriodicKick();

  return (fr == FUNC_SUCCESS) ? fr2 : fr;
}

FuncResult Audio_SetVolume(int new_volume)
{
  if (new_volume > EVAL_AUDIO_GetMaxVolume())
  {
  	new_volume = EVAL_AUDIO_GetMaxVolume();
  }
  if (new_volume < EVAL_AUDIO_GetMinVolume())
  {
  	new_volume = EVAL_AUDIO_GetMinVolume();
  }

	UI_SetVariable(VAR_AudioVolume, Volume, new_volume);

  if (AudioState == AS_STOPPED)
  {
    UI_SetVariable(VAR_AudioVolume, Volume, new_volume);
    return FUNC_SUCCESS;
  }

  if (EVAL_AUDIO_VolumeCtl(new_volume) != 0)
  {
    Audio_Error();
    return FUNC_ERROR;
  }

  UI_SetVariable(VAR_AudioVolume, Volume, new_volume);
  return FUNC_SUCCESS;
}

FuncResult Audio_ChangeVolume(int delta) //todo async
{
  return Audio_SetVolume(Audio_GetVolume() + delta);
}

FuncResult Audio_PeriodicKick(void)
{
  FuncResult fr = FUNC_SUCCESS;

  if (AudioState == AS_ERROR)
    return FUNC_ERROR;

  vPortEnterCritical();

  if (DMA_Starving_Flag && !AudioBuffer_TryGetProducer())
  {
    fr = FeedDMA();
  }

  vPortExitCritical();

  return fr;
}

AudioState_Typedef Audio_GetState(void)
{
  return AudioState;
}

int Audio_GetSampleRate(void)
{
  return SampleRate;
}

int Audio_GetVolume(void)
{
  return Volume;
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* assumes uninterruptible execution */

  UNUSED(pBuffer);
  UNUSED(Size);

  vPortEnterCritical();

  if (AudioBuffer_GetFullCount() > 0)
  {
    AudioBuffer_MoveConsumer();
  }

  if (AudioState == AS_PLAYING && FeedDMA() != FUNC_SUCCESS)
  {
    NeglectedDMA_Count++;
    SampleRate = 0;
    EVAL_AUDIO_Stop(CODEC_PDWN_SW); //XXX CODEC_PDWN_HW
    AudioState = AS_STOPPED;
  }

  vPortExitCritical();

  Player_AsyncCommandFromISR(PC_NEED_MORE_DATA, 0);
}

FuncResult FeedDMA(void) //todo
{
  AudioBuffer_Typedef *buffer;

#ifdef PROFILING
  return FUNC_SUCCESS;
#endif

  buffer = AudioBuffer_TryGetConsumer();
  if (buffer)
  {
    if (buffer->sampling_freq != SampleRate)
    {
      trace("New sampling freq: %u (was %u)\n",
              (unsigned int) buffer->sampling_freq,
              (unsigned int) SampleRate);

      FuncResult fr = Audio_Init(buffer->sampling_freq);

      if (fr != FUNC_SUCCESS)
        return fr;
    }

    if (AudioState == AS_PAUSED)
    {
      if (EVAL_AUDIO_PauseResume(AUDIO_RESUME) != 0)
      {
        Audio_Error();
        return FUNC_ERROR;
      }
    }
    //else XXX
    {
    Audio_MAL_Play((uint32_t) buffer->data, buffer->size * 2);
    }

    DMA_Starving_Flag = false;
    UI_SetVariable(VAR_AudioStatus, AudioState, AS_PLAYING);

    return FUNC_SUCCESS;
  }

  return FUNC_NOT_SUCCESS;
}
