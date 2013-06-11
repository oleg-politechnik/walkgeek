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

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct
{
//  bool IsSingleDirPlayback;
} PlayerSettings_Typedef;

/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static Decoder_Typedef
        decoders[] =
                {
#ifdef USE_MP3
# ifdef SIMULATOR
                        { .LoadFile = 0, .MainThread = 0, .Seek = 0, .Stop = 0 },
# else
                        { .LoadFile = MP3_LoadFile, .MainThread = MP3_MainThread, .Seek = MP3_Seek, .Stop = MP3_Stop},
# endif
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
FuncResult Player_RestoreSettings();
FuncResult Player_StoreSettings();

void Player_Init(void)
{
  Navigator_Init();

//  long int volume = ini_getl("", "volume", PLAYER_DEFAULT_VOLUME,
//          PLAYER_INI_FILE);
//  Audio_SetVolume(volume);

  Navigator_InitRoot(&PlayerContext, suffixes_white_list);
#if 0
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
    }
  }
  else
#endif

  if (Player_RestoreSettings() == FUNC_SUCCESS)
  {
  }
  else
  {
    if (!PlayerContext.fname)
    {
      Navigator_NextFile(&PlayerContext);
    }

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
  Player_Stop();

//  ini_putl("", "volume", Audio_GetVolume(), PLAYER_INI_FILE);
//
//  if (Navigator_IsOnline())
//  {
//#ifdef SIMULATOR
//    ini_puts("file", "path", PlayerContext.dir_path, PLAYER_INI_FILE);
//    if (PlayerStatus == PS_PLAYING && PlayerContext.fname)
//    {
//      ini_puts("file", "name", PlayerContext.fname, PLAYER_INI_FILE);
//      ini_putl("file", "mstime", PlayerState.metadata.mstime_curr,
//              PLAYER_INI_FILE);
//    }
//#endif
//
//  }

  Player_StoreSettings();

  Navigator_DeInit();
}

void Player_Play(void)
{
  CPU_InitUserHeap();

  char filepath[512];

  PlayerCommand = PC_DUMMY;

  if (PlayerContext.fname)
  {
    assert_param(
            (PlayerContext.suffix_ix >= 0)
                    && ((unsigned) PlayerContext.suffix_ix < SIZE_OF(decoders)
                            - 1));

#ifndef SIMULATOR
    decoder = &decoders[PlayerContext.suffix_ix];
#endif

    snprintf(filepath, sizeof(filepath), "%s/%s", PlayerContext.dir_path,
            PlayerContext.fname);

    trace("player: loading %s...\n", filepath);

    PlayerStatus = PS_PLAYING;
    memset(&PlayerState, 0, sizeof(PlayerState));
#ifndef SIMULATOR
    decoder->LoadFile(filepath);
#endif

    if (PlayerStatus == PS_PLAYING)
    {
      Audio_CommandSync(AC_PLAY);
    }
  }
}

void Player_Stop(void)
{
  if (decoder)
  {
    decoder->Stop();
  }

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

  trace("player: next\n");

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
    trace("Player: Trying previous file %s\n", PlayerContext.fname);

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
        Navigator_Cd(&PlayerContext, PlayerContext.dir_path);
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

#ifndef SIMULATOR
  if (PlayerStatus == PS_PLAYING)
  {
    decoder->MainThread();

    Audio_PeriodicKick();
  }

  if (PlayerStatus == PS_EOF)
  {
    Player_AsyncCommand(PC_NEXT, 0);
  }
#endif

  if (PlayerStatus == PS_PLAYING || PlayerStatus == PS_SEEKING)
  {
    if (PlayerState.metadata.time_curr != PlayerState.metadata.mstime_curr
	/ 1000)
    {
      SetVariable(VAR_AudioPosition, PlayerState.metadata.time_curr,
	  PlayerState.metadata.mstime_curr / 1000);

      /*Display a progress spinner while decoding.*/
      static const char spinner[] = "|/-\\";
      static size_t last_spin;

      trace("\r[%c] %02d:%02d:%02d", spinner[last_spin & 3],
	  (int) (PlayerState.metadata.time_curr / 3600),
	  (int) (PlayerState.metadata.time_curr / 60) % 60,
	  (int) (PlayerState.metadata.time_curr) % 60);
      fflush(stdout);
      last_spin++;
    }
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

#define CLOSE(fil) do { FS_EXEC(f_truncate(&fil)); \
  FS_EXEC(f_sync(&fil)); \
  FS_EXEC(f_close(&fil)); } while (0)

#define OPEN_WRITE(fil, name) do { \
  FS_EXEC(f_open(&fil, name, FA_WRITE | FA_CREATE_ALWAYS)); } while (0)
//
//extern PlaylistEntry_Typedef plist[PLAYLIST_MAX_ENTRIES];
//extern int plist_curr;

FIL fil;

FuncResult Player_StoreSettings()
{
  UINT bytes_to_write, bytes_written;

  TCHAR f_name_buf[255];

  //  TCHAR file_name[255];
  u8 volume;

  //  if (!MEDIA_FILE_IS_LOADED) //todo error + is mounted
  //    return;
  OPEN_WRITE(fil, "volume");
  bytes_to_write = sizeof(u8);
  volume = Audio_GetVolume();
  FS_EXEC(f_write(&fil, &volume, bytes_to_write, &bytes_written));
  CLOSE(fil);

  if (PlayerContext.fname)
  {
    OPEN_WRITE(fil, "file.dir_path");
    f_puts(PlayerContext.dir_path, &fil);
    CLOSE(fil);

    OPEN_WRITE(fil, "file.fname");
    f_puts(PlayerContext.fname, &fil);
    CLOSE(fil);

    OPEN_WRITE(fil, "file.mstime_curr");
    bytes_to_write = sizeof(PlayerState.metadata.mstime_curr);
    FS_EXEC(f_write(&fil, &PlayerState.metadata.mstime_curr, bytes_to_write, &bytes_written));
    CLOSE(fil);
  }

  return FUNC_SUCCESS;
}

FuncResult Player_RestoreSettings()
{
  FRESULT res;
  UINT bytes_to_read, bytes_read;
  u8 volume;
  u32 fptr, mstime_curr;
  TCHAR file_name[100];
  TCHAR f_name_buf[100];

  Audio_SetVolume(PLAYER_DEFAULT_VOLUME);

  res = f_open(&fil, "volume", FA_READ);
  if (res == FR_OK)
  {
    bytes_to_read = sizeof(volume);
    FS_EXEC(f_read(&fil, &volume, bytes_to_read, &bytes_read));
    FS_EXEC(f_close(&fil));

    //

    if (bytes_to_read == bytes_read)
    {
      Audio_SetVolume(volume);
    }
  }

  //

  char buf[256];

  res = f_open(&fil, "file.dir_path", FA_READ);
  if (res != FR_OK)
    return FUNC_ERROR;

  f_gets(buf, SIZE_OF(buf), &fil);
  FS_EXEC(f_close(&fil));

  {
    if (Navigator_Cd(&PlayerContext, buf))
    {
      trace("settings: restored last dir (%s)\n", PlayerContext.dir_path);
    }
  }

  //

  res = f_open(&fil, "file.fname", FA_READ);
  if (res != FR_OK)
    return FUNC_ERROR;

  f_gets(buf, SIZE_OF(buf), &fil);
  FS_EXEC(f_close(&fil));

  {
    if (Navigator_TryFile(&PlayerContext, buf))
    {
      trace("settings: restored last file (%s)\n", PlayerContext.fname);
    }
  }

  //

  if (PlayerContext.fname)
  {
    Player_Play();

    if (PlayerStatus == PS_PLAYING)
    {
      res = f_open(&fil, "file.mstime_curr", FA_READ);
      if (res != FR_OK)
        return FUNC_SUCCESS;

      unsigned int mstime;

      bytes_to_read = sizeof(mstime);
      FS_EXEC(f_read(&fil, &mstime, bytes_to_read, &bytes_read));
      FS_EXEC(f_close(&fil));

      if (!(bytes_to_read == bytes_read))
      {
        return FUNC_SUCCESS;
      }

      trace("settings: read last file position (%u:%02u:%02u.%03u)\n",
              (mstime / 1000 / 60 / 60), (mstime / 1000 / 60) % 60,
              (mstime / 1000) % 60, mstime % 1000);

      if (mstime < PlayerState.metadata.mstime_max)
      {
        Player_AsyncCommand(PC_SEEK, mstime);
        Player_SyncCommand();
        Player_AsyncCommand(PC_SEEK, 0);
        Player_SyncCommand();
      }
    }
    return FUNC_SUCCESS;
  }

  return FUNC_ERROR;
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
