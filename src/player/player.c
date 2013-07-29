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

#include "player.h"
#include "audio_if.h"
#include "navigator.h"

#include "opus_decoder.h"
#include "mp3_decoder.h"
#include "minIni.h"
#include "decoder.h"

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
                .LoadMetadata = MP3_LoadMetadata,
                .MainThread = MP3_MainThread,
                .Seek = MP3_Seek,
                .InitDecoder = MP3_InitDecoder,
        },
#endif
        //    {
        //	.LoadFile = OPUS_LoadFile,
        //	.Destroy = OPUS_Destroy,
        //	.LoadMetadata = OPUS_LoadMetadata,
        //	.MainThread = OPUS_MainThread,
        //	.Seek = OPUS_Seek,
        //  .InitDecoder = OPUS_InitDecoder
        //    },
        {
                .LoadFile = 0,
                .Destroy = 0,
                .LoadMetadata = 0,
                .MainThread = 0,
                .Seek = 0,
                .InitDecoder = 0
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

static sDecoderContext *pMainDecoderContext;
static sDecoderContext *pNextDecoderContext;

static xTaskHandle pxDecoderTask;

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void prvPlayerTask(void *pvParameters)
{
  xPlayerCommandQueue = xQueueCreate( 10, sizeof( sPlayerCommand ) );
  configASSERT(xPlayerCommandQueue);

  pMainDecoderContext = pvPortMalloc(sizeof(sDecoderContext));
  bzero(pMainDecoderContext, sizeof(sDecoderContext));
  pMainDecoderContext->psMetadata = &PlayerState.metadata;
  pMainDecoderContext->xCommandQueue = xQueueCreate(taskDECODER_COMMAND_QUEUE_LENGTH, sizeof(sDecoderCommand));

  pNextDecoderContext = pvPortMalloc(sizeof(sDecoderContext));
  bzero(pNextDecoderContext, sizeof(sDecoderContext));
  pNextDecoderContext->psMetadata = &PlayerState.metadata;
  pNextDecoderContext->xCommandQueue = xQueueCreate(taskDECODER_COMMAND_QUEUE_LENGTH, sizeof(sDecoderCommand));

  while (1)
  {
    sPlayerCommand command;
    if (xQueueReceive(xPlayerCommandQueue, &(command), portMAX_DELAY))
    {
      Player_SyncCommand(command.cmd, command.arg);
    }
  }
}

void Player_Init(void)
{
  assert_param(PlayerState.status == PS_DEINITED);

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

  SetVariable(VAR_PlayerState, PlayerState.status, PS_STOPPED);

  if (PlayerContext.fname)
  {
    Player_Play();

    if (PlayerState.status == PS_PLAYING)
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

  Player_Stop();

  Navigator_DeInit();

  SetVariable(VAR_PlayerState, PlayerState.status, PS_DEINITED);
}

void Player_Play(void)
{
  assert_param(PlayerState.status >= PS_STOPPED);

  bzero(&PlayerState.metadata, sizeof(PlayerState.metadata));

  if (PlayerContext.fname)
  {
    assert_param(PlayerContext.suffix_ix >= 0);
    assert_param((unsigned) PlayerContext.suffix_ix < SIZE_OF(decoders) - 1);

    snprintf(pMainDecoderContext->pcFilePath,
            sizeof(pMainDecoderContext->pcFilePath), "%s/%s",
            PlayerContext.dir_path, PlayerContext.fname);

    if (pMainDecoderContext->pDecoderData)
    {
      configASSERT(pMainDecoderContext->pDecoder);
      Decoder(pMainDecoderContext)->Destroy(pMainDecoderContext);
    }

    if (pxDecoderTask)
    {
      vTaskDelete(pxDecoderTask);
      pxDecoderTask = NULL;
    }

    if (pNextDecoderContext->pDecoderData && !strcmp(pMainDecoderContext->pcFilePath,
            pNextDecoderContext->pcFilePath))
    {
      trace("player: use cached %s\n", pNextDecoderContext->pcFilePath);
      configASSERT(pNextDecoderContext->pDecoder == &decoders[PlayerContext.suffix_ix]);

      /* Swap contexts */
      sDecoderContext *pTempDecoderContext = pMainDecoderContext;
      pMainDecoderContext = pNextDecoderContext;
      pNextDecoderContext = pTempDecoderContext;
    }
    else
    {
      if (pNextDecoderContext->pDecoderData)
      {
        configASSERT(pNextDecoderContext->pDecoder);
        Decoder(pNextDecoderContext)->Destroy(pNextDecoderContext);
      }

      trace("player: loading %s\n", pMainDecoderContext->pcFilePath);

      pMainDecoderContext->pDecoder = &decoders[PlayerContext.suffix_ix];

      if (Decoder(pMainDecoderContext)->LoadFile(pMainDecoderContext) != FUNC_SUCCESS)
      {
        Player_SyncCommand(PC_AUDIO_FILE_ERROR, 0);
        return;
      }
    }

    signed portBASE_TYPE xReturn;

    /* Start playing current track ASAP */
    if (pMainDecoderContext->pDecoderData)
    {
      SetVariable(VAR_PlayerState, PlayerState.status, PS_PLAYING);

      xReturn = xTaskCreate(prvDecoderTask, (signed portCHAR *) "Decoder", taskDECODER_STACK_SIZE, pMainDecoderContext, taskDECODER_PRIORITY, &pxDecoderTask);
      configASSERT(xReturn == pdPASS);

      Audio_CommandSync(AC_PLAY);
    }

    /* Load metadata for the current track */
    pNextDecoderContext->pDecoder = pMainDecoderContext->pDecoder;
    strncpy(pNextDecoderContext->pcFilePath, pMainDecoderContext->pcFilePath,
            sizeof(pMainDecoderContext->pcFilePath));
    xReturn = Decoder(pNextDecoderContext)->LoadFile(pNextDecoderContext);
    configASSERT(xReturn == FUNC_SUCCESS);

    Decoder(pNextDecoderContext)->LoadMetadata(pNextDecoderContext);

    SyncVariable(VAR_Metadata);

    Decoder(pNextDecoderContext)->Destroy(pNextDecoderContext);

    /* Pre-cache next file */
    Navigator_NextFile(&PlayerContext);

    //todo store max time when pre-caching

    if (PlayerContext.fname)
    {
      assert_param(PlayerContext.suffix_ix >= 0);
      assert_param((unsigned) PlayerContext.suffix_ix < SIZE_OF(decoders) - 1);

      snprintf(pNextDecoderContext->pcFilePath,
              sizeof(pMainDecoderContext->pcFilePath), "%s/%s",
              PlayerContext.dir_path, PlayerContext.fname);

      trace("player: pre-caching %s\n", pNextDecoderContext->pcFilePath);

      pNextDecoderContext->pDecoder = &decoders[PlayerContext.suffix_ix];

      if (Decoder(pNextDecoderContext)->LoadFile(pNextDecoderContext) != FUNC_SUCCESS)
      {
        Decoder(pNextDecoderContext)->Destroy(pNextDecoderContext);
      }
    }

    Navigator_PrevFile(&PlayerContext);
  }
}

void Player_Stop(void)
{
  if (PlayerState.status >= PS_PLAYING)
  {
    Audio_CommandSync(AC_STOP);

    if (pxDecoderTask)
    {
      vTaskDelete(pxDecoderTask);
      pxDecoderTask = NULL;
    }

    SetVariable(VAR_PlayerState, PlayerState.status, PS_STOPPED);
    trace("player: stopped\n");
  }

  configASSERT(!pxDecoderTask);
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
    Audio_CommandSync(AC_PAUSE);
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
    Audio_CommandSync(AC_PAUSE);
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
      if (PlayerState.status < PS_PLAYING)
        break;

      mstime_curr = PlayerState.metadata.mstime_curr;

      if (arg == 0)
      {
        //        Audio_CommandSync(AC_PLAY);
        SetVariable(VAR_PlayerState, PlayerState.status, PS_PLAYING);
        Decoder_AsyncCommand(DC_END_SEEKING, 0);
        break;
      }

      SetVariable(VAR_PlayerState, PlayerState.status, PS_SEEKING);

      if (arg > 0)
      {
        if (mstime_curr + arg
                > PlayerState.metadata.mstime_max)
        {
          Player_Next();
          break;
        }
      }
      else if (arg < 0)
      {
        if (mstime_curr < (u32) -arg)
        {
          arg += (PlayerState.metadata.mstime_curr);

          Player_Prev();

          //          if (PlayerState.status == PS_PLAYING)
          //          {
          //            Player_AsyncCommand(PC_SEEK,
          //                    PlayerState.metadata.mstime_max + arg);
          //          }

          break;
        }
      }

      Decoder_AsyncCommand(DC_SEEK, mstime_curr + arg);
      break;

    case PC_SAVE_CURRENT_DIR:
      Player_SaveState();
      break;

    case PC_AUDIO_FILE_ERROR:
      SetVariable(VAR_PlayerState, PlayerState.status, PS_ERROR_FILE);
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
