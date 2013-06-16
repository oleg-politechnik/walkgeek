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
#include "player.h"
#include "audio_if.h"
#include "navigator.h"

#include "opus_decoder.h"
#include "mp3_decoder.h"
#include "minIni.h"
#include "profile.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct
{
//  bool IsSingleDirPlayback;
} PlayerSettings_Typedef;

/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Player_SaveState(void);
static void Player_SyncCommand(void);

/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static Decoder_Typedef
        decoders[] =
                {
#ifdef USE_MP3
                        { .LoadFile = MP3_LoadFile, .MainThread = MP3_MainThread, .Seek = MP3_Seek, .Stop = MP3_Stop},
#endif
                        { .LoadFile = OPUS_LoadFile, .MainThread =
                                OPUS_MainThread, .Seek = OPUS_Seek, .Stop =
                                OPUS_Stop },
                        { .LoadFile = 0, .MainThread = 0, .Seek = 0, .Stop = 0 } };

static char *suffixes_white_list[] =
{
#ifdef USE_MP3
        "mp3",
#endif
        "opus", 0 };

PlayerStatus_Typedef PlayerStatus;
PlayerState_Typedef PlayerState;

static Decoder_Typedef *decoder;

static NavigatorContext_Typedef PlayerContext;

static volatile u32 PlayerCommand = PC_DUMMY;
static volatile s32 PlayerCommandArg;

static char PlayerErrorString[128];

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Player_Init(void)
{
  Navigator_Init();

  long int volume = ini_getl("", "volume", PLAYER_DEFAULT_VOLUME,
          PLAYER_INI_FILE);
  Audio_SetVolume(volume);

  Navigator_InitRoot(&PlayerContext, suffixes_white_list);

#ifndef PROFILING
  char buf[256];

  //todo len???, null-terminated???
  int len;
  len = ini_gets("file", "path", "", buf, sizeof(buf), PLAYER_INI_FILE);
  if (len)
  {
    if (Navigator_Cd(&PlayerContext, buf))
      trace("settings: restored last dir (%s)\n", PlayerContext.dir_path);
  }

  len = ini_gets("file", "name", "", buf, sizeof(buf), PLAYER_INI_FILE);
  if (len)
  {
    if (Navigator_TryFile(&PlayerContext, buf))
      trace("settings: restored last file (%s)\n", PlayerContext.fname);
  }

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
        Player_AsyncCommand(PC_SEEK, mstime);
      }

      if (mstime < PlayerState.metadata.mstime_max)
      {
        Player_AsyncCommand(PC_SEEK, mstime);
        Player_SyncCommand();
        Player_AsyncCommand(PC_SEEK, 0);
        Player_SyncCommand();
      }
    }
  }
  else
#endif
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
  Player_SaveState();

  Player_Stop();

  Navigator_DeInit();
}

void Player_Play(void)
{
  CPU_InitUserHeap();

  PlayerCommand = PC_DUMMY;

  Profiler_Init();
  CPU_RefillStack();

  memset(&PlayerState, 0, sizeof(PlayerState));

  if (PlayerContext.fname)
  {
    assert_param(
            (PlayerContext.suffix_ix >= 0)
                    && ((unsigned) PlayerContext.suffix_ix < SIZE_OF(decoders)
                            - 1));

    decoder = &decoders[PlayerContext.suffix_ix];

    snprintf(PlayerState.metadata.file_name,
            sizeof(PlayerState.metadata.file_name), "%s/%s",
            PlayerContext.dir_path, PlayerContext.fname);

    trace("player: loading %s\n", PlayerState.metadata.file_name);

#ifndef SIMULATOR
    Profiler_EnterFunc(PF_PRELOAD);
    {
      decoder->LoadFile(PlayerState.metadata.file_name);
    }
    Profiler_ExitFunc(PF_PRELOAD);
#endif

    if (PlayerStatus == PS_STOPPED)
    {
      SetVariable(VAR_PlayerState, PlayerStatus, PS_PLAYING);
      Audio_CommandSync(AC_PLAY);
    }
  }
}

void Player_Stop(void)
{
#ifndef SIMULATOR
  if (decoder)
  {
    decoder->Stop();
  }
#endif

  /*
   * todo: call AC_STOP after some idle in the paused state
   *
   */

  //trace("player: stopped\n");

  Audio_CommandSync(AC_STOP);

  SetVariable(VAR_PlayerState, PlayerStatus, PS_STOPPED);
}

void Player_AsyncCommand(PlayerCommand_Typedef cmd, s32 arg)
{
  CPU_DisableInterrupts();
  {
    PlayerCommand = cmd;
    PlayerCommandArg = arg;
  }
  CPU_RestoreInterrupts();
}

static void Player_Next(void)
{
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

static void Player_Prev(void)
{
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

static void Player_SyncCommand(void)
{
  u32 PlayerCommand_Cached;
  s32 PlayerCommandArg_Cached;

  while (PlayerCommand != PC_DUMMY)
  {
    CPU_DisableInterrupts();
    {
      PlayerCommand_Cached = PlayerCommand;
      PlayerCommandArg_Cached = PlayerCommandArg;
    }
    CPU_RestoreInterrupts();

    CPU_CompareExchange(&PlayerCommand, PlayerCommand_Cached, PC_DUMMY);

    switch (PlayerCommand_Cached)
    {
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
#ifndef PROFILING
        if (PlayerStatus < PS_PLAYING)
#endif
          break;

        assert_param(decoder->Seek);

        if (PlayerCommandArg_Cached == 0)
        {
          Audio_CommandSync(AC_PLAY);
          PlayerStatus = PS_PLAYING;
          break;
        }

        PlayerStatus = PS_SEEKING;
        Audio_CommandSync(AC_PAUSE);
        Audio_CommandSync(AC_RESET_BUFFERS);

        if (PlayerCommandArg_Cached > 0)
        {
          if (PlayerState.metadata.mstime_curr + PlayerCommandArg_Cached
                  > PlayerState.metadata.mstime_max)
          {
            Player_Next();
            break;
          }
        }
        else if (PlayerCommandArg_Cached < 0)
        {
          if (PlayerState.metadata.mstime_curr < (u32) -PlayerCommandArg_Cached)
          {
            PlayerCommandArg_Cached += (PlayerState.metadata.mstime_curr);

            Player_Prev();

            if (PlayerStatus == PS_PLAYING)
            {
              Player_AsyncCommand(PC_SEEK,
                      PlayerState.metadata.mstime_max + PlayerCommandArg_Cached);
            }

            break;
          }
        }

        decoder->Seek(
                PlayerState.metadata.mstime_curr + PlayerCommandArg_Cached);
        break;

      default:
        break;
    }
  }
}

void Player_MainThread(void)
{
  Player_SyncCommand();

  if (PlayerStatus == PS_PLAYING)
  {
#ifndef SIMULATOR
    Profiler_EnterFunc(PF_CODEC_TOTAL);
    {
      decoder->MainThread();
    }
    Profiler_ExitFunc(PF_CODEC_TOTAL);
#endif

    Audio_PeriodicKick();
  }

  if (PlayerStatus == PS_PLAYING || PlayerStatus == PS_SEEKING)
  {
    if (PlayerState.metadata.time_curr != PlayerState.metadata.mstime_curr
            / 1000)
    {

      SetVariable(VAR_AudioPosition, PlayerState.metadata.time_curr,
              PlayerState.metadata.mstime_curr / 1000);

      /*Display a progress spinner while decoding.*/
//      static const char spinner[] = "|/-\\";
//      static size_t last_spin;
//
//      trace("\r[%c]", spinner[last_spin & 3]);
//
////      trace("\r[%c] %02d:%02d:%02d", spinner[last_spin & 3],
////              (int) (PlayerState.metadata.time_curr / 3600),
////              (int) (PlayerState.metadata.time_curr / 60) % 60,
////              (int) (PlayerState.metadata.time_curr) % 60);
//      fflush(stdout);
//      last_spin++;


#ifdef PROFILING
      if (PlayerState.metadata.time_curr == 60)
      {
        Profiler_SetTotal(60 * 1000000);
        Profiler_Print();

        trace("Stack: free %ub out of %ub (%u%%)\n",
                CPU_GetStackFree(), CPU_GetStackSize(),
                CPU_GetStackFree() * 100 / CPU_GetStackSize());

        PlayerStatus = PS_EOF;
      }
#endif
    }
  }

  if (PlayerStatus == PS_EOF)
  {
    Player_AsyncCommand(PC_NEXT, 0);
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

    f_printf(&f, "path=");
    f_puts(PlayerContext.dir_path, &f);
    f_printf(&f, "\n");

    f_printf(&f, "name=");
    f_puts(PlayerContext.fname, &f);
    f_printf(&f, "\n");

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
