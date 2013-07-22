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
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "player.h"
#include "audio_if.h"
#include "navigator.h"

#include "opus_decoder.h"
#include "mp3_decoder.h"
#include "minIni.h"
#include "../../bsp/stm32f4_discovery/stm324xg_eval_sdio_sd.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void Player_SaveState(void);
static void Player_SyncCommand(ePlayerCommand cmd, s32 arg);
/*static */void Player_Init(void);
static void Player_DeInit(void);
static void Player_Play(void);
static void Player_Stop(void);

/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static Decoder_Typedef decoders[] =
{
#ifdef USE_MP3
    {
	.LoadFile = MP3_LoadFile,
	.MainThread = MP3_MainThread,
	.Seek = MP3_Seek,
	.Stop = MP3_Stop
    },
#endif
//    {
//	.LoadFile = OPUS_LoadFile,
//	.MainThread = OPUS_MainThread,
//	.Seek = OPUS_Seek,
//	.Stop = OPUS_Stop
//    },
    {
	.LoadFile = 0,
	.MainThread = 0,
	.Seek = 0,
	.Stop = 0
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

static PlayerStatus_Typedef PlayerStatus;
PlayerState_Typedef PlayerState;

static Decoder_Typedef *decoder;

static NavigatorContext_Typedef PlayerContext;

static char PlayerErrorString[128];

xQueueHandle xPlayerCommandQueue;

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void prvPlayerTask(void *pvParameters)
{
  xPlayerCommandQueue = xQueueCreate( 10, sizeof( sPlayerCommand ) );
  assert_param(xPlayerCommandQueue);

  while (1)
  {
    sPlayerCommand command;
    if (xQueueReceive(xPlayerCommandQueue, &(command), (portTickType) 1)) //todo give from ISR
    {
      Player_SyncCommand(command.cmd, command.arg);
    }

    if (PlayerStatus == PS_PLAYING)
    {
      decoder->MainThread();

      Audio_PeriodicKick();
    }

    if (PlayerStatus == PS_PLAYING || PlayerStatus == PS_SEEKING)
    {
      if (PlayerState.metadata.time_curr != PlayerState.metadata.mstime_curr
              / 1000)
      {

        SetVariable(VAR_AudioPosition, PlayerState.metadata.time_curr,
                PlayerState.metadata.mstime_curr / 1000);
      }
    }
  }
}

#include <inttypes.h>
#include <stdio.h>

void Player_Init(void)
{
  assert_param(PlayerStatus == PS_DEINITED);

  Navigator_Init();

  long int volume = ini_getl("", "volume", PLAYER_DEFAULT_VOLUME,
          PLAYER_INI_FILE);
  Audio_SetVolume(volume);

  Navigator_InitRoot(&PlayerContext, suffixes_white_list);

  char buf[256];

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

  SetVariable(VAR_PlayerState, PlayerStatus, PS_STOPPED);

  if (PlayerContext.fname)
  {
    Player_Play();

    if (PlayerStatus == PS_PLAYING)
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
  assert_param(PlayerStatus != PS_DEINITED);

  Player_SaveState();

  Player_Stop();

  Navigator_DeInit();
}

void Player_Play(void)
{
  assert_param(PlayerStatus == PS_STOPPED);

  CPU_InitUserHeap();

  memset(&PlayerState, 0, sizeof(PlayerState));

  if (PlayerContext.fname)
  {
    assert_param(PlayerContext.suffix_ix >= 0);
    assert_param((unsigned) PlayerContext.suffix_ix < SIZE_OF(decoders) - 1);

    decoder = &decoders[PlayerContext.suffix_ix];

    snprintf(PlayerState.metadata.file_name,
            sizeof(PlayerState.metadata.file_name), "%s/%s",
            PlayerContext.dir_path, PlayerContext.fname);

    trace("player: loading %s\n", PlayerState.metadata.file_name);

    decoder->LoadFile(PlayerState.metadata.file_name);

    if (PlayerStatus == PS_STOPPED)
    {
      SetVariable(VAR_PlayerState, PlayerStatus, PS_PLAYING);
      Audio_CommandSync(AC_PLAY);
    }
  }
}

void Player_Stop(void)
{
  if (PlayerStatus >= PS_PLAYING)
  {
    if (decoder)
    {
      decoder->Stop();
    }

    trace("player: stopped\n");

    Audio_CommandSync(AC_STOP);

    SetVariable(VAR_PlayerState, PlayerStatus, PS_STOPPED);
  }
}

void Player_AsyncCommand(ePlayerCommand cmd, s32 arg)
{
  sPlayerCommand command;
  command.cmd = cmd;
  command.arg = arg;

  xQueueSend( xPlayerCommandQueue, ( void * ) &command, portMAX_DELAY );
}

void Player_AsyncCommandFromISR(ePlayerCommand cmd, s32 arg)
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
  assert_param(PlayerStatus >= PS_STOPPED);

  Player_Stop();

  trace("\n\nplayer: next\n");

  Navigator_NextFile(&PlayerContext);
  if (PlayerContext.fname)
  {
    Player_Play();
  }
  else
  {
    Audio_CommandSync(AC_PAUSE);
    trace("Player: Cannot switch to the next file\n");
  }
}

void Player_Prev(void)
{
  assert_param(PlayerStatus >= PS_STOPPED);

  Player_Stop();

  trace("player: prev\n");

  Navigator_PrevFile(&PlayerContext);
  if (PlayerContext.fname)
  {
    Player_Play();
  }
  else
  {
    trace("Player: Cannot switch to the previous file\n");
  }
}

void Player_SyncCommand(ePlayerCommand cmd, s32 arg)
{
  switch (cmd)
  {
  case PC_INIT:
    Player_Init();
    break;

  case PC_DEINIT:
    Player_DeInit();
    break;

  case PC_NEXT:
    Player_Next();
    break;

  case PC_PREV:
    Player_Prev();
    break;

  case PC_DIR_START:
    trace("player: first track in current dir\n");
    Navigator_ResetDir(&PlayerContext);
    Player_Next();
    break;

  case PC_DIR_END:
    Player_Stop();
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
    }
    break;

  case PC_SEEK:
    if (PlayerStatus < PS_PLAYING)
      break;

    assert_param(decoder->Seek);

    if (arg == 0)
    {
      Audio_CommandSync(AC_PLAY);
      PlayerStatus = PS_PLAYING;
      break;
    }

    PlayerStatus = PS_SEEKING;
    Audio_CommandSync(AC_PAUSE);
    Audio_CommandSync(AC_RESET_BUFFERS);

    if (arg > 0)
    {
      if (PlayerState.metadata.mstime_curr + arg
	  > PlayerState.metadata.mstime_max)
      {
	Player_Next();
	break;
      }
    }
    else if (arg < 0)
    {
      if (PlayerState.metadata.mstime_curr < (u32) -arg)
      {
	arg += (PlayerState.metadata.mstime_curr);

	Player_Prev();

	if (PlayerStatus == PS_PLAYING)
	{
	  Player_AsyncCommand(PC_SEEK,
	      PlayerState.metadata.mstime_max + arg);
	}

	break;
      }
    }

    decoder->Seek(PlayerState.metadata.mstime_curr + arg);
    break;

  default:
    break;
  }
}

PlayerState_Typedef *Player_GetState(void)
{
  return &PlayerState;
}

PlayerStatus_Typedef Player_GetStatus(void)
{
  return PlayerStatus;
}

/* Utils **********************************************************************/

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

void Player_AudioFileError(char *error)
{
  trace("Player ERROR: %s", error);

  strncpy(PlayerErrorString, error, sizeof(PlayerErrorString));

  SetVariable(VAR_PlayerState, PlayerStatus, PS_ERROR_FILE);
}

char *Player_GetErrorString(void)
{
  return PlayerErrorString;
}
