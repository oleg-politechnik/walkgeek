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
#include "audio_if.h"
#include "bsp.h"
#include "audio_buffer.h"
//#include "stm324xg_usb_audio_codec.h"
#include "stm32f4_discovery_audio_codec.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static volatile AudioState_Typedef AudioState = AS_STOPPED;
static uint32_t Volume;
static uint32_t SampleRate;
static uint32_t NeglectedDMA_Count;
static volatile uint32_t DMA_Starving_Flag;

static const u8 log_table[] =
{ 0, 1, 15, 24, 30, 35, 39, 42, 45, 48, 50, 52, 54, 56, 57, 59, 60, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 72, 73, 74, 75, 75, 76, 77, 77, 78, 78,
        79, 80, 80, 81, 81, 82, 82, 83, 83, 84, 84, 85, 85, 85, 86, 86, 87, 87,
        87, 88, 88, 89, 89, 89, 90, 90, 90, 91, 91, 91, 92, 92, 92, 93, 93, 93,
        93, 94, 94, 94, 95, 95, 95, 95, 96, 96, 96, 96, 97, 97, 97, 97, 98, 98,
        98, 98, 99, 99, 99, 99, 100, 100 };

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static FuncResult Audio_Init(u32 AudioFreq);
static u32 ConvertVolume(u32 NewVolume);
static FuncResult FeedDMA(void);
static FuncResult Audio_DoCommand(AudioCommand_Typedef cmd);

void AudioBuffer_Init(void);
u8 AudioBuffer_GetFullCount(void);

AudioBuffer_Typedef *AudioBuffer_TryGetProducer(void);
void AudioBuffer_MoveProducer(void);

AudioBuffer_Typedef *AudioBuffer_TryGetConsumer(void);
void AudioBuffer_MoveConsumer(void);

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void Audio_Error(void)
{
  SetVariable(VAR_AudioStatus, AudioState, AS_ERROR);
}

FuncResult Audio_Init(u32 AudioFreq)
{

  /* Call low layer function */
  if (EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, ConvertVolume(Volume), AudioFreq)
          != 0)
  {
    Audio_Error();
    return FUNC_ERROR;
  }

  /* Codec supports this value AudioFreq */

  SetVariable(VAR_AudioPosition, SampleRate, AudioFreq);
  SetVariable(VAR_AudioStatus, AudioState, AS_STOPPED);

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
          SyncVariable(VAR_AudioStatus);
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
      SetVariable(VAR_AudioPosition, SampleRate, 0);

      EVAL_AUDIO_Stop(CODEC_PDWN_SW); //XXX CODEC_PDWN_HW

      SetVariable(VAR_AudioStatus, AudioState, AS_STOPPED);
      return FUNC_SUCCESS;

      /* Process the PAUSE command ---------------------------*/
    case AC_SUSPEND:
      DMA_Starving_Flag = true;
      SyncVariable(VAR_AudioStatus);
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

      SetVariable(VAR_AudioStatus, AudioState, AS_PAUSED);
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

  CPU_DisableInterrupts();

  fr = Audio_DoCommand(cmd);

  CPU_RestoreInterrupts();

  fr2 = Audio_PeriodicKick();

  return (fr == FUNC_SUCCESS) ? fr2 : fr;
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

FuncResult Audio_PeriodicKick(void)
{
  FuncResult fr = FUNC_SUCCESS;

  if (AudioState == AS_ERROR)
    return FUNC_ERROR;

  CPU_DisableInterrupts();

  if (DMA_Starving_Flag && !AudioBuffer_TryGetProducer())
  {
    fr = FeedDMA();
  }

  CPU_RestoreInterrupts();

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

  CPU_DisableInterrupts();

  if (AudioBuffer_GetFullCount() > 0)
  {
    AudioBuffer_MoveConsumer();
  }

  if (AudioState == AS_PLAYING && FeedDMA() != FUNC_SUCCESS)
  {
    NeglectedDMA_Count++;

    Audio_DoCommand(AC_SUSPEND);
  }

  CPU_RestoreInterrupts();
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
      if (EVAL_AUDIO_PauseResume(AUDIO_RESUME/*, (uint32_t) buffer->data, buffer->size * 2*/) != 0)
      {
        Audio_Error();
        return FUNC_ERROR;
      }
    }
//    else
    {
      Audio_MAL_Play((uint32_t) buffer->data, buffer->size * 2);
//      ();
    }

    DMA_Starving_Flag = false;
    SetVariable(VAR_AudioStatus, AudioState, AS_PLAYING);

    return FUNC_SUCCESS;
  }

  return FUNC_NOT_SUCCESS;
}
