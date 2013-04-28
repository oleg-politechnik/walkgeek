/*
 * player.c
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

/* Includes ------------------------------------------------------------------*/
#include <string.h>

#include "player.h"
#include "system.h"
#include "ui.h"
#include "mediafile.h"
#include "audio_if.h"
#include "playlist.h"
#include <stdio.h>
#include "decoder.h"

extern Decoder_TypeDef decoders[];
AudioBuffer_Typedef *AudioBuffer_TryGetProducer(void);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile u32 PlayerCommand = PC_EMPTY;
static volatile s32 PlayerCommandArg;
static PlayerState_Typedef PlayerState = PS_INACTIVE;

static Decoder_TypeDef *decoder = NULL;

static char PlayerErrorString[80];

static FATFS fatfs;

static MediaFile_Typedef mfile;

/* Private function prototypes -----------------------------------------------*/
static void Player_Next(void);
static void Player_Prev(void);
static void Player_ChangeVolume(int8_t delta);
static void Player_SetVolume(u8 vol);

FuncResult Player_TryFile(MediaFile_Typedef *file);
static FuncResult Player_RestoreSettings(void);
static FuncResult Player_StoreSettings(void);

FuncResult Playlist_Init(void);
void Playlist_LoadNext(void);
void Playlist_LoadPrev(void);
FuncResult Playlist_TryLoadCurrentTrack(void);
FuncResult Playlist_SetCurrentTrack(TCHAR *file_name);

/* Private functions ---------------------------------------------------------*/
static void Player_SetState(PlayerState_Typedef state)
{
  SetVariable(VAR_ApplicationState, PlayerState, state);
}

void Player_Init()
{
  if (PlayerState != PS_INACTIVE)
    return;

  Player_SetState(PS_STOPPED);

  if (Playlist_Init() != FUNC_SUCCESS)
  {
    Player_SetState(PS_ERROR);
  }
}

void Player_DeInit()
{
  if (PlayerState == PS_INACTIVE)
    return;

  Audio_Command(AC_STOP);

  Player_StoreSettings();

  MediaFile_Close(&mfile);

  f_mount(0, NULL);

  Player_SetState(PS_INACTIVE);
}

/*
 * Safe to call from an ISR
 */
void Player_AsyncCommand(PlayerCommand_Typedef cmd, s32 arg)
{
  PlayerCommand = cmd;
  PlayerCommandArg = arg;
}

PlayerState_Typedef Player_GetState(void)
{
  return PlayerState;
}

void Player_SyncCommand(void)
{
  u32 PlayerCommand_Cached;

  while (PlayerCommand != PC_EMPTY)
  {
    PlayerCommand_Cached = PlayerCommand;
    CPU_CompareExchange(&PlayerCommand, PlayerCommand_Cached, PC_EMPTY);

    switch (PlayerCommand_Cached)
    {
      case PC_PLAY:
        /* TODO Pick a file, if no */
        Player_SetState(PS_PLAYING);
        Audio_Command(AC_PLAY);
        break;

      case PC_PAUSE:
        Player_SetState(PS_PAUSED);
        Audio_Command(AC_PAUSE);
        break;

      case PC_NEXT:
        Player_Next();
        break;

      case PC_PREV:
        Player_Prev();
        break;

      case PC_SEEK:
        //todo is file->meta loaded
        if (PlayerCommandArg == 0)
        {
          Player_SetState(PS_PLAYING);
          Audio_Command(AC_PLAY);
          break;
        }

        Player_SetState(PS_SEEKING);
        Audio_Command(AC_RESET_BUFFERS);
        assert_param(decoder);
        assert_param(decoder->SeekFunc);
        if ((*decoder->SeekFunc)(&mfile, PlayerCommandArg * 1000) == FUNC_ERROR)
        {
          //          if (PlayerCommandArg < 0)
          //          {
          //            Player_Prev();
          //          }
          //          else
          //          {
          //            Player_Next();
          //          }
        }
        break;

      case PC_CHANGE_VOLUME:
        Player_ChangeVolume(PlayerCommandArg);
        break;

      default:
        break;
    }
  }
}

void Player_MainCycle(void)
{
  assert_param(SystemState == SS_PLAYER);

  Player_SyncCommand();

  if (PlayerState != PS_PLAYING && PlayerState != PS_PAUSED && PlayerState
          != PS_SEEKING)
  {
    return;
  }

  while (PlayerState != PS_SEEKING && mfile.state == MFS_PLAYABLE)
  {
    AudioBuffer_Typedef *buffer;
    buffer = AudioBuffer_TryGetProducer();
    if (buffer)
    {
      assert_param(decoder);
      if ((*decoder->DecodeFunc)(&mfile, buffer) != FUNC_SUCCESS)
      {
        if (mfile.state == MFS_ERROR)
        {
          Player_SetState(PS_FILE_ERROR);
          snprintf(PlayerErrorString, sizeof(PlayerErrorString),
                  "Decoding error: %s", mfile.meta.file_name);
          return;
        }
      }

      Audio_PeriodicKick(); /* kick the codec's DMA */
    }
    else
    {
      break;
    }
  }

  if (PlayerState == PS_PLAYING || PlayerState == PS_SEEKING)
  {
    SetVariable(VAR_media_time_curr, mfile.meta.time_curr,
            mfile.meta.mstime_curr / 1000);
  }

  if (PlayerState == PS_PLAYING && mfile.state == MFS_EOF)
  {
    Player_Next();
    return;
  }

  Audio_PeriodicKick(); /* kick the codec's DMA */
}

FuncResult Player_TryFile(MediaFile_Typedef *file)
{
  int i = 0;

  //assert_param(FILE_IS_LOADED);

  decoder = NULL;

  //todo metadata -> for a player
  file->meta.title[0] = 0;
  file->meta.artist[0] = 0;
  file->meta.album[0] = 0;
  file->meta.notes[0] = 0;
  file->meta.year[0] = 0; //todo finite playlist

  while (1)
  {
    decoder = &decoders[i];
    if (!decoder->LoadFileFunc)
      break;

    if ((*decoder->LoadFileFunc)(&mfile) == FUNC_ERROR)
    {
      i++;
      continue;
    }

    SyncVariable(VAR_media_file_name);

    SyncVariable(VAR_media_album);
    SyncVariable(VAR_media_artist);
    SyncVariable(VAR_media_genre);
    SyncVariable(VAR_media_time_curr);
    SyncVariable(VAR_media_mstime_max);
    SyncVariable(VAR_media_title);
    SyncVariable(VAR_media_year);

    mfile.state = MFS_PLAYABLE;

    return FUNC_SUCCESS;
  }

  //  Player_AsyncCommand(PC_NEXT, 0);//SetStatus(PS_PLAYING);
  MediaFile_Close(&mfile); //XXX???never can get there
  return FUNC_ERROR;
}

void Player_Next(void)//
{
  mfile.meta.mstime_curr = 0;//todo =0 -- when???
  Playlist_LoadNext();
}

void Player_Prev(void)//
{
  Playlist_LoadPrev();
}

void Player_SetVolume(u8 vol)
{
  Audio_SetVolume(vol);
}

void Player_ChangeVolume(int8_t delta)
{
  int16_t new_volume = Audio_GetVolume() + delta;

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

  Player_SetVolume(new_volume);
}

/* Utils **********************************************************************/

#define CLOSE(fil) do { FS_EXEC(f_truncate(&fil)); \
  FS_EXEC(f_sync(&fil)); \
  FS_EXEC(f_close(&fil)); } while (0)

#define OPEN_WRITE(fil, name) do { \
  FS_EXEC(f_open(&fil, name, FA_WRITE | FA_CREATE_ALWAYS)); } while (0)

extern PlaylistEntry_Typedef plist[PLAYLIST_MAX_ENTRIES];
extern int plist_curr;

FuncResult Player_StoreSettings()
{
  FIL fil;
  UINT bytes_to_write, bytes_written;

  //  TCHAR file_name[255];
  u8 volume;

  if (PlayerState <= PS_STOPPED)
  {
    return FUNC_ERROR;
  }

  if (mfile.state != MFS_PLAYABLE)
  {
    return FUNC_ERROR;
  }

  //  if (!MEDIA_FILE_IS_LOADED) //todo error + is mounted
  //    return;
  OPEN_WRITE(fil, "volume");
  bytes_to_write = sizeof(u8);
  volume = Audio_GetVolume();
  FS_EXEC(f_write(&fil, &volume, bytes_to_write, &bytes_written));
  CLOSE(fil);

  OPEN_WRITE(fil, "file.fname");
  f_puts(plist[plist_curr].fname, &fil);
  CLOSE(fil);

  //
  OPEN_WRITE(fil, "file.fptr");
  bytes_to_write = sizeof(mfile.file.fptr);
  FS_EXEC(f_write(&fil, &mfile.file.fptr, bytes_to_write, &bytes_written));
  CLOSE(fil);

  OPEN_WRITE(fil, "file.meta.mstime_curr");
  bytes_to_write = sizeof(mfile.meta.mstime_curr);
  FS_EXEC(f_write(&fil, &mfile.meta.mstime_curr, bytes_to_write, &bytes_written));
  CLOSE(fil);

  MediaFile_Close(&mfile);//todo playlist

  return FUNC_SUCCESS;
}

FuncResult Player_RestoreSettings()
{
  FRESULT res;
  FIL fil;
  UINT bytes_to_read, bytes_read;
  u8 volume;
  u32 fptr, mstime_curr;
  TCHAR file_name[100];

  res = f_open(&fil, "volume", FA_READ);
  if (res == FR_OK)
  {
    bytes_to_read = sizeof(volume);
    FS_EXEC(f_read(&fil, &volume, bytes_to_read, &bytes_read));
    FS_EXEC(f_close(&fil));

    //

    if (bytes_to_read == bytes_read)
    {
      Player_SetVolume(volume);
    }
  }

  //

  res = f_open(&fil, "file.fname", FA_READ);
  if (res != FR_OK)
    return FUNC_ERROR;

  f_gets(file_name, SIZE_OF(file_name), &fil);
  FS_EXEC(f_close(&fil));

  //

  if (Playlist_SetCurrentTrack(file_name) != FUNC_SUCCESS)
  {
    return FUNC_ERROR;
  }

  //

  res = f_open(&fil, "file.fptr", FA_READ);
  if (res != FR_OK)
    return FUNC_ERROR;

  bytes_to_read = sizeof(fptr);
  FS_EXEC(f_read(&fil, &fptr, bytes_to_read, &bytes_read));
  FS_EXEC(f_close(&fil));

  if (!(bytes_to_read == bytes_read && fptr < mfile.file.fsize))
  {
    return FUNC_SUCCESS;
  }

  //

  res = f_open(&fil, "file.meta.mstime_curr", FA_READ);
  if (res != FR_OK)
    return FUNC_ERROR;

  bytes_to_read = sizeof(mstime_curr);
  FS_EXEC(f_read(&fil, &mstime_curr, bytes_to_read, &bytes_read));
  FS_EXEC(f_close(&fil));

  if (!(bytes_to_read == bytes_read && mstime_curr < mfile.meta.mstime_max))
  {
    return FUNC_SUCCESS;
  }

  //
  MF_EXEC(MediaFile_FillFromFile(&mfile, fptr));
  mfile.meta.mstime_curr = mstime_curr;

  return FUNC_SUCCESS;
}

FuncResult MediaFile_CheckExtension(const char *fname, const char *ext)
{
  assert_param(fname);

  int len = strlen(fname);
  int ext_len = strlen(ext) + 1;
  const char *ext_begin = &fname[len - ext_len];
  int ret;

  if (len < ext_len)
  {
    return FUNC_ERROR;
  }

  if (ext_begin[0] != '.')
  {
    return FUNC_ERROR;
  }

  ret = strcasecmp(&ext_begin[1], ext);
  if (ret != 0)
  {
    return FUNC_ERROR;
  }

  return FUNC_SUCCESS;
}

/* Includes ------------------------------------------------------------------*/
#include "player.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PlaylistEntry_Typedef plist[PLAYLIST_MAX_ENTRIES];
int plist_cnt;
int plist_curr;

static char root[] = "0:/";

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
FuncResult Playlist_Init(void)
{
  DIR dir;
  FILINFO file_info;
  int f_index = 0;

  plist_cnt = 0;
  plist_curr = 0;

  file_info.lfname = 0;
  file_info.lfsize = 0;

  //
  FS_EXEC(f_mount(0, &fatfs));

  FS_EXEC(f_opendir(&dir, root));
  FS_EXEC(f_readdir(&dir, 0));

  while (plist_cnt < PLAYLIST_MAX_ENTRIES)
  {
    FS_EXEC(f_readdir(&dir, &file_info));
    f_index++;

    if (file_info.fname[0] == 0)
    {
      //ret next dir
      break;
    }

    if (file_info.fname[0] == '.')
      continue; /* Ignore dot entry */

    if (file_info.fattrib & AM_DIR)
      continue; /* It is a directory */

    if (MediaFile_CheckExtension(file_info.fname, "mp3") == FUNC_SUCCESS
            || MediaFile_CheckExtension(file_info.fname, "wav") == FUNC_SUCCESS)//fixme
    {
      memcpy(plist[plist_cnt].fname, file_info.fname,
              sizeof(plist[plist_cnt].fname));
      plist[plist_cnt].f_index = f_index;
      plist_cnt++;
    }
  }

  if (Player_RestoreSettings() != FUNC_SUCCESS)
  {
    Player_Next(); //first
    //Player_Pause(); //fixme 1st entry -> play?
  }

  if (mfile.state == MFS_PLAYABLE)
  {
    Player_AsyncCommand(PC_PLAY, 0);
    return FUNC_SUCCESS;
  }

  return FUNC_NOT_SUCCESS;
}

void Playlist_LoadNext()
{
  do
  {
    plist_curr = (plist_curr + 1) % plist_cnt;
  } while (Playlist_TryLoadCurrentTrack() == FUNC_ERROR);
}

void Playlist_LoadPrev()
{
  do
  {
    plist_curr = (plist_curr - 1 < 0) ? (plist_cnt - 1) : (plist_curr - 1);
  } while (Playlist_TryLoadCurrentTrack() == FUNC_ERROR);
}

FuncResult Playlist_SetCurrentTrack(TCHAR *file_name) //fixme+dir
{
  assert_param(file_name);

  MediaFile_Close(&mfile);

  for (int i = 0; i < plist_cnt; ++i)
  {
    if (strcmp(plist[i].fname, file_name) == 0) //fixme store settings inside the playlist
    {
      plist_curr = i;

      if (Playlist_TryLoadCurrentTrack() == FUNC_SUCCESS)
      {
        return FUNC_SUCCESS;
      }

      return FUNC_ERROR;
    }
  }
  //todo if not in the plist -> load

  return FUNC_ERROR;
}

FuncResult Playlist_TryLoadCurrentTrack()
{
  int f_index;
  DIR dir;
  FILINFO file_info;

  TCHAR lfn_buf[255];
  file_info.lfname = lfn_buf;
  file_info.lfsize = SIZE_OF(lfn_buf);

  if (plist_cnt < 1)
    return FUNC_ERROR;

  assert_param(plist_curr < plist_cnt);

  f_index = plist[plist_curr].f_index;

  //

  //#if _LFN_UNICODE == 1
  //  char file_name_u8_buf[512];
  //#else
  //  char *file_name_u8_buf;
  //#endif

  MediaFile_Close(&mfile);

  //
  FS_EXEC(f_opendir(&dir, root)); //todo dir
  FS_EXEC(f_readdir(&dir, 0));

  while (f_index--)
  {
    FS_EXEC(f_readdir(&dir, &file_info));
  }

  assert_param(strcmp(file_info.fname, plist[plist_curr].fname) == 0);

  MF_EXEC(MediaFile_Open(&mfile, plist[plist_curr].fname));

  snprintf(mfile.meta.file_name, SIZE_OF(mfile.meta.file_name),
          file_info.lfname[0] ? file_info.lfname : file_info.fname);

  return Player_TryFile(&mfile);
}

MediaFile_Typedef *Player_CurrentFile(void)
{
  return &mfile;
}
