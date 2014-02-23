/*
 * player.c
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
#include <inttypes.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "ui.h"
#include "player.h"
#include "audio_if.h"
#include "navigator.h"

#include "opus_decoder.h"
#include "mp3_decoder.h"
#include "minIni.h"
#include "audio_buffer.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct
{
  ePlayerCommand cmd;
  int arg;
} sPlayerCommand;

/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void Player_SaveState(void);
static void Player_SyncCommand(ePlayerCommand cmd, signed portBASE_TYPE arg);
static void Player_Init(void);
static void Player_DeInit(void);
static void Player_Play(void);
static void Player_Stop(void);

/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static sDecoder decoders[] =
{
#ifdef USE_MP3
        {
                .LoadFile = MP3_LoadFile,
                .Destroy = MP3_Destroy,
                .MainThread = MP3_MainThread,
                .Seek = MP3_Seek,
        },
#endif
        {
                .LoadFile = OPUS_LoadFile,
                .Destroy = OPUS_Destroy,
                .MainThread = OPUS_MainThread,
                .Seek = OPUS_Seek,
        },
        {
                .LoadFile = 0,
                .Destroy = 0,
                .MainThread = 0,
                .Seek = 0,
        }
};

static char *suffixes_white_list[] =
{
#ifdef USE_MP3
        "mp3",
#endif
        "opus",
        0
};

static sPlayerState PlayerState;

static NavigatorContext_Typedef PlayerContext;

static xQueueHandle xPlayerCommandQueue;

static sDecoderContext *pDecoderContext;

char PlayerErrorString[128];

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void prvPlayerTask(void *pvParameters)
{
  xPlayerCommandQueue = xQueueCreate( 10 /*fixme*/, sizeof( sPlayerCommand ) );
  configASSERT(xPlayerCommandQueue);

  pDecoderContext = pvPortMalloc(sizeof(sDecoderContext));
  bzero(pDecoderContext, sizeof(sDecoderContext));
  pDecoderContext->psMetadata = &PlayerState.metadata;

  while (1)
  {
    sPlayerCommand command;
    if (xQueueReceive(xPlayerCommandQueue, &(command), configPLAYER_TIMEOUT_MS))
    {
      Player_SyncCommand(command.cmd, command.arg);
    }

    if (PlayerState.status == PS_PLAYING)
    {
      Decoder(pDecoderContext)->MainThread(pDecoderContext);

      Audio_PeriodicKick();
    }

    if (PlayerState.status == PS_PLAYING || PlayerState.status == PS_SEEKING)
    {
      if (PlayerState.metadata.time_curr != PlayerState.metadata.mstime_curr
              / 1000)
      {
        UI_SetVariable(VAR_PlayerPosition, PlayerState.metadata.time_curr,
                PlayerState.metadata.mstime_curr / 1000);
      }
    }
  }
}

static void FinalizeCurrentTrack(void)
{
  bzero(&PlayerState.metadata, sizeof(PlayerState.metadata));

  if (pDecoderContext->pDecoderData)
  {
    configASSERT(pDecoderContext->pDecoder);
    Decoder(pDecoderContext)->Destroy(pDecoderContext);
    configASSERT(!pDecoderContext->pDecoderData);
  }

  CPU_InitUserHeap();
}

void Player_Init(void)
{
  assert_param(PlayerState.status == PS_DEINITED);

  AudioBuffer_Init();

  Navigator_Init();

  long int volume = ini_getl("", "volume", PLAYER_DEFAULT_VOLUME,
          PLAYER_INI_FILE);
  Audio_SetVolume(volume);

  Navigator_InitRoot(&PlayerContext, suffixes_white_list);

  char buf[MAX_FILE_PATH];

  int len;
  len = ini_gets("file", "path", "", buf, sizeof(buf), PLAYER_INI_FILE);
  if (len)
  {
    if (Navigator_Cd(&PlayerContext, buf))
    {
      trace("settings: restored last dir (%s)\n", PlayerContext.dir_path);
    }
  }

  len = ini_gets("file", "name", "", buf, sizeof(buf), PLAYER_INI_FILE);
  if (len)
  {
    if (Navigator_TryFile(&PlayerContext, buf))
    {
      trace("settings: restored last file (%s)\n", PlayerContext.fname);
    }
  }

  PlayerState.status = PS_STOPPED;
  UI_SyncVariable(VAR_PlayerTrack);

  if (PlayerContext.fname)
  {
    Player_Play();

    if (PlayerState.status >= PS_PLAYING)
    {
      unsigned int mstime = ini_getl("file", "mstime", 0, PLAYER_INI_FILE);

      trace("settings: read last file position (%u:%02u:%02u.%03u)\n",
              (mstime / 1000 / 60 / 60), (mstime / 1000 / 60) % 60,
              (mstime / 1000) % 60, mstime % 1000);

      if (mstime < PlayerState.metadata.mstime_max)
      {
        Player_SyncCommand(PC_SEEK, mstime);
        Player_SyncCommand(PC_SEEK, 0);
      }
    }
  }
  else
  {
    Navigator_NextFile(&PlayerContext);

    if (PlayerContext.fname)
    {
      Player_Play();
    }
    else
    {
      Player_AudioFileError("player: no file to play"); /*todo stderr */
    }
  }
}

void Player_DeInit(void)
{
  assert_param(PlayerState.status != PS_DEINITED);

  Navigator_DeInit();

  PlayerState.status = PS_DEINITED;
  UI_SyncVariable(VAR_PlayerTrack);

  vTaskDelay(10); /* Let screen repaint */
}

void Player_Play(void)
{
  assert_param(PlayerState.status >= PS_STOPPED);

  FinalizeCurrentTrack();

  if (PlayerContext.fname)
  {
    assert_param(PlayerContext.suffix_ix >= 0);
    assert_param((unsigned) PlayerContext.suffix_ix < SIZE_OF(decoders) - 1);

    snprintf(pDecoderContext->pcFilePath, sizeof(pDecoderContext->pcFilePath),
            "%s/%s", PlayerContext.dir_path, PlayerContext.fname);

    trace("player: loading %s\n", pMainDecoderContext->pcFilePath);

    pDecoderContext->pDecoder = &decoders[PlayerContext.suffix_ix];

    if (Decoder(pDecoderContext)->LoadFile(pDecoderContext) != FUNC_SUCCESS)
    {
      Player_SyncCommand(PC_AUDIO_FILE_ERROR, 0);
      return;
    }

    pDecoderContext->psMetadata->file_path = pDecoderContext->pcFilePath;

    PlayerState.status = PS_PLAYING;
    Audio_CommandSync(AC_PLAY);

    Player_AsyncCommand(PC_NEED_MORE_DATA, 0);

    UI_SyncVariable(VAR_PlayerTrack);
  }
}

void Player_Stop(void)
{
  if (PlayerState.status >= PS_PLAYING)
  {
    Audio_CommandSync(AC_STOP);

    PlayerState.status = PS_STOPPED;
    UI_SyncVariable(VAR_PlayerTrack);
    trace("player: stopped\n");
  }
}

void Player_AsyncCommand(ePlayerCommand cmd, int arg)
{
  sPlayerCommand command;
  command.cmd = cmd;
  command.arg = arg;

  xQueueSend( xPlayerCommandQueue, ( void * ) &command, portMAX_DELAY );
}

void Player_AsyncCommandFromISR(ePlayerCommand cmd, int arg)
{
  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
  sPlayerCommand command;

  command.cmd = cmd;
  command.arg = arg;

  xQueueSendFromISR( xPlayerCommandQueue, ( void * ) &command, &xHigherPriorityTaskWoken );

  /* Switch context if necessary. */
  portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

void Player_Next(void)
{
  assert_param(PlayerState.status >= PS_STOPPED);

  trace("\n\nplayer: next\n");

  Navigator_NextFile(&PlayerContext);
  if (PlayerContext.fname)
  {
    Player_Play();
  }
  else
  {
    Player_Stop();
    trace("Player: Cannot switch to the next file\n");
  }
}

void Player_Prev(void)
{
  assert_param(PlayerState.status >= PS_STOPPED);

  trace("player: prev\n");

  Navigator_PrevFile(&PlayerContext);
  if (PlayerContext.fname)
  {
    Player_Play();
  }
  else
  {
  	Player_Stop();
    trace("Player: Cannot switch to the previous file\n");
  }
}

void Player_SyncCommand(ePlayerCommand cmd, signed portBASE_TYPE arg)
{
  u32 mstime_curr;

  switch (cmd)
  {
    case PC_INIT:
      Player_Init();
      break;

    case PC_DEINIT:
      FinalizeCurrentTrack();
      Player_Stop();
      Player_DeInit();
      break;

    case PC_NEXT:
      FinalizeCurrentTrack();
      Player_Next();
      break;

    case PC_PREV:
      FinalizeCurrentTrack();
      Player_Prev();
      break;

    case PC_DIR_START:
      FinalizeCurrentTrack();
      trace("player: first track in current dir\n");
      Navigator_ResetDir(&PlayerContext);
      Player_Next();
      break;

    case PC_DIR_END:
      FinalizeCurrentTrack();
      trace("player: last track in current dir\n");
      Navigator_LastFileCurrentDir(&PlayerContext);

      if (PlayerContext.fname)
      {
        trace("Player: Trying file %s\n", PlayerContext.fname);

        Player_Play();
      }
      else
      {
        trace("Player: Cannot switch to the last file\n");
        Player_Stop();
      }
      break;

    case PC_SEEK:
      if (PlayerState.status < PS_PLAYING)
        break;

      if (arg == 0)
      {
        PlayerState.status = PS_PLAYING;
        Audio_CommandSync(AC_PLAY);
        break;
      }

      PlayerState.status = PS_SEEKING;
      Audio_CommandSync(AC_PAUSE);
      Audio_CommandSync(AC_RESET_BUFFERS);

      if (arg > 0)
      {
        if (PlayerState.metadata.mstime_curr + arg
                > PlayerState.metadata.mstime_max)
        {
          Player_AsyncCommand(PC_NEXT, 0);
          break;
        }
      }
      else if (arg < 0)
      {
        if (PlayerState.metadata.mstime_curr < (u32) -arg)
        {
          arg += (PlayerState.metadata.mstime_curr);

          Player_SyncCommand(PC_PREV, 0);
          Player_AsyncCommand(PC_SEEK, PlayerState.metadata.mstime_max - PlayerState.metadata.mstime_curr + arg);
          break;
        }
      }

      Decoder(pDecoderContext)->Seek(pDecoderContext, PlayerState.metadata.mstime_curr + arg);
      break;

    case PC_SAVE_CURRENT_DIR:
      Player_SaveState();
      break;

    case PC_AUDIO_FILE_ERROR: //XXX too synchronous
      UI_SetVariable(VAR_PlayerTrack, PlayerState.status, PS_ERROR_FILE);
      break;

    default:
      break;
  }
}

bool Player_IsSeekable(void)
{
  return (PlayerState.status > PS_STOPPED && PlayerState.metadata.mstime_max > 0);
}

sPlayerState *Player_GetState(void)
{
  return &PlayerState;
}

void Player_SaveState(void)
{
  static FIL f;

  if (f_open(&f, PLAYER_INI_FILE, FA_WRITE | FA_CREATE_ALWAYS) != FR_OK)
    return;

  f_printf(&f, "volume=%u\n", Audio_GetVolume());

  if (PlayerContext.fname)
  {
    f_puts("[file]\n", &f);

    f_printf(&f, "path=\"");
    f_puts(PlayerContext.dir_path, &f);
    f_printf(&f, "\"\n");

    f_printf(&f, "name=\"");
    f_puts(PlayerContext.fname, &f);
    f_printf(&f, "\"\n");

    f_printf(&f, "mstime=%u\n", PlayerState.metadata.mstime_curr);
  }

  f_truncate(&f);
  f_sync(&f);
  f_close(&f);
}
#if 0
void Player_AudioFileError(char *error)
{
  trace("Player ERROR: %s", error);

  strncpy(PlayerErrorString, error, sizeof(PlayerErrorString));

  SetVariable(VAR_PlayerTrack, PlayerState.status, PS_ERROR_FILE);
}

char *Player_GetErrorString(void)
{
  return PlayerErrorString;
}
#endif
