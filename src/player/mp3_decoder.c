/*
 * mp3_decoder.c
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
#include <mp3dec.h>
#include <string.h>
#include "player.h"
#include "mp3_decoder.h"
#include "mediafile.h"
#include "playlist.h"
#include "decoder.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MP3_FRAME_MSTIME            26
#define MP3_TABLE_OF_CONTENTS_SIZE  100

/* Private macro -------------------------------------------------------------*/
#define MP3_CHECK_TAG(file, tag) \
  (strncmp(tag, (char*) &FILE_BUF(file, 0), sizeof(tag) - 1) == 0)

/* Private variables ---------------------------------------------------------*/
HMP3Decoder pMP3Decoder;
MP3FrameInfo mp3FrameInfo;

static bool vbr;
static u8 toc[MP3_TABLE_OF_CONTENTS_SIZE];

//uint16_t MP3_FrameSize; //fixme

static int Frame_sampfreqs[4] =
{ 44100, 48000, 32000, 0 }; // sample rate MPEG1 LAYER3
static int Frame_bitrates[15] =
{ 0, 32000, 40000, 48000, 56000, 64000, 80000, 96000, 112000, 128000, 160000,
        192000, 224000, 256000, 320000 }; // bitrate MPEG1 LAYER3

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

FuncResult MP3_ReadMetadata(MediaFile_Typedef *mfile)
{
  uint32_t offset, frame_size, frame_header_size;
  u16 val; // record the start frame
  u8 version_major/*, extended_header*/;

  vbr = true;

  MF_EXEC(MediaFile_FillFromFile(mfile, 0));

  if (MP3_CHECK_TAG(mfile, "ID3"))
  { /* try ID3v2 */
    mfile->data_start = ((DWORD) FILE_BUF(mfile, 6) << 21)
            | ((DWORD) FILE_BUF(mfile, 7) << 14) | ((WORD) FILE_BUF(mfile, 8)
            << 7) | FILE_BUF(mfile, 9);

    version_major = FILE_BUF(mfile, 3);
    //    version_release = FILE_BUF(mfile, 4);
    //    extended_header = FILE_BUF(mfile, 5) & (1 << 6);

    frame_header_size = (version_major >= 3) ? 10 : 6;

    MF_EXEC(MediaFile_Seek(mfile, 10));

    // iterate through frames
    while (mfile->file.fptr - mfile->bytes_in_buf < mfile->data_start)
    {
      if (version_major >= 3)
      {
        frame_size = ((DWORD) FILE_BUF(mfile, 4) << 24)
                | ((DWORD) FILE_BUF(mfile, 5) << 16)
                | ((WORD) FILE_BUF(mfile, 6) << 8) | FILE_BUF(mfile, 7);
      }
      else
      {
        frame_size = ((DWORD) FILE_BUF(mfile, 3) << 14)
                | ((WORD) FILE_BUF(mfile, 4) << 7) | FILE_BUF(mfile, 5);
      }

      if (frame_size == 0)
        break;

      MF_EXEC(MediaFile_ReFill(mfile));

      if (MP3_CHECK_TAG(mfile, "TT2") || MP3_CHECK_TAG(mfile, "TIT2"))
      {
        strncpy(mfile->meta.title,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(mfile->meta.title) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "TP1") || MP3_CHECK_TAG(mfile, "TPE1"))
      {
        strncpy(mfile->meta.artist,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(mfile->meta.artist) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "TAL"))
      {
        strncpy(mfile->meta.album,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(mfile->meta.album) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "TDRC") || MP3_CHECK_TAG(mfile, "TYER"))
      {
        strncpy(mfile->meta.year,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(mfile->meta.year) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "USLT"))
      {
        char *ptr = (char *) &FILE_BUF(mfile, frame_header_size + 1);
        ptr += strlen(ptr);
        ptr++;

        strncpy(mfile->meta.notes, ptr,
                MIN(frame_size - 1, sizeof(mfile->meta.notes) - 1));
      }

      //      TRCK    Track number
      //      TENC    Encoded By
      //      WXXX    URL
      //      TCOP    Frame identifier
      //      TOPE    Original Artist
      //      TCOM    Composer
      //      TCON    Genre
      //      COMM    Comments
      //          Year
      MF_EXEC(MediaFile_Seek(mfile, frame_size + frame_header_size));
    }
  }
  else
  { /* ID3v1 */

    MF_EXEC(MediaFile_FillFromFile(mfile, mfile->file.fsize - 128));

    if (MP3_CHECK_TAG(mfile, "TAG"))
    {
      MF_EXEC(MediaFile_Seek(mfile, 3));
      strncpy(mfile->meta.title, (char *) mfile->file_buf,
              MIN(30, sizeof(mfile->meta.title) - 1));

      MF_EXEC(MediaFile_Seek(mfile, 30));
      strncpy(mfile->meta.artist, (char *) mfile->file_buf,
              MIN(30, sizeof(mfile->meta.artist) - 1));

      MF_EXEC(MediaFile_Seek(mfile, 30));
      strncpy(mfile->meta.album, (char *) mfile->file_buf,
              MIN(30, sizeof(mfile->meta.album) - 1));
    }
    else
    {
      return FUNC_ERROR;
    }

    mfile->data_start = 0;
  }

  MF_EXEC(MediaFile_FillFromFile(mfile, mfile->data_start));

  //(c) SAM3U_COOS

  u16 i;
  u8 bitrate_index;
  u8 sample_index;
  u8 padding_bit;

  offset = 0;

  val = FILE_BUF(mfile, offset);
  while (((val & 0xfffa) != 0xfffa) && (offset < FILE_BUFFER_SIZE - 2))// if it is head frame
  {
    val <<= 8;
    val |= FILE_BUF(mfile, ++offset);
  }
  //todo ovf
  offset++;

  MF_EXEC(MediaFile_Seek(mfile, offset));
  offset = 0;

  bitrate_index = (FILE_BUF(mfile, offset)) >> 4; // high 4 bits to get bitrate index
  sample_index = ((FILE_BUF(mfile, offset)) >> 2) & 0x03; // the following 2 bits to get sample rate index
  padding_bit = ((FILE_BUF(mfile, offset)) >> 1) & 0x01; // the following 1 bit to get padding bit

  offset = offset + 2;// get the first byte after the head frame

  MF_EXEC(MediaFile_Seek(mfile, offset));
  offset = 0;

  vbr = false; // this MP3 is CBR
  for (i = 0; i < 36; i++)// read the following 36 bytes, find if it has VBR flag
  {
    if (strncmp("Xing", (char *) &FILE_BUF(mfile, i), 4) == 0)
    {
      vbr = true; // this MP3 is VBR
    }
  }

  if (vbr == false) //CBR
  {
    mfile->framesize = (u32) (((144 * Frame_bitrates[bitrate_index])
            / Frame_sampfreqs[sample_index])) + padding_bit; // count the bytes of every frame

    assert_param(mfile->file.fsize > mfile->data_start);

    mfile->maxframe = (mfile->file.fsize - mfile->data_start)
            / mfile->framesize; // the total frames
  }
  else //VBR
  {
    /* http://www.multiweb.cz/twoinches/mp3inside.htm
     * Formula for counting frame length in Bytes:
     *  FrameLen = int((144 * BitRate / SampleRate ) + Padding);
     *  Eg. for Bitrate = 192kbps, SampleRate = 44.1kHz a Padding = Yes
     *  FrameLen = int((144 * 192000 / 44100) + 1) = 627 Bytes
     *  int() means round to bottom. FrameLen includes frame header.
     * */

    offset = offset + 40;
    mfile->maxframe = FILE_BUF(mfile, offset + 3) + FILE_BUF(mfile, offset + 2)
            * 256 + FILE_BUF(mfile, offset + 1) * 256 * 256
            + FILE_BUF(mfile, offset) * 256 * 256 * 256;

    offset += 4;

    //    48-51   Bytes
    //    File length in Bytes

    offset += 4;

    MF_EXEC(MediaFile_Seek(mfile, offset));
    offset = 0;

    memcpy(toc, &FILE_BUF(mfile, offset), sizeof(toc));

    //    52-151    TOC (Table of Contents)
    //    Contains of 100 indexes (one Byte length) for easier lookup in file-> Approximately solves problem with moving inside file->
    //    Each Byte has a value according this formula:
    //    (TOC[i] / 256) * fileLenInBytes
    //    So if song lasts eg. 240 sec. and you want to jump to 60. sec. (and file is 5 000 000 Bytes length) you can use:
    //    TOC[(60/240)*100] = TOC[25]
    //    and corresponding Byte in file is then approximately at:
    //    (TOC[25]/256) * 5000000
  }
  mfile->meta.mstime_curr = 0;
  mfile->meta.mstime_max = mfile->maxframe * MP3_FRAME_MSTIME;

  //

  return FUNC_SUCCESS;
}

FuncResult MP3_TryFile(MediaFile_Typedef *mfile)
{
  //  EXEC_ERROR_STATUS(Play
  if (MP3_ReadMetadata(mfile) == FUNC_ERROR)
    return FUNC_ERROR;

  MP3_Init();

  return FUNC_SUCCESS;
}

FuncResult MP3_FastFileCheck(const char *fname)
{
  return MediaFile_CheckExtension(fname, "mp3");
}

FuncResult MP3_Decode(MediaFile_Typedef *mfile, AudioBuffer_Typedef *audio_buf)
{
  int offset, bytesLeft, err;
  u8 *f_buffer;

  assert_param(audio_buf->size == 0);

  MF_EXEC(MediaFile_ReFill(mfile));

  offset = MP3FindSyncWord(&FILE_BUF(mfile, 0), mfile->bytes_in_buf);
  if (offset < 0)
  {
    /* 2-byte sync word */

    MF_EXEC(MediaFile_Seek(mfile, mfile->bytes_in_buf - 2));

    return FUNC_ERROR;
  }

  if (offset > 0)
  {
    MF_EXEC(MediaFile_Seek(mfile, offset));
  }

  memset(&mp3FrameInfo, 0, sizeof(mp3FrameInfo));
  err = MP3GetNextFrameInfo(pMP3Decoder, &mp3FrameInfo, &FILE_BUF(mfile, 0));
  if (!(err == ERR_MP3_NONE && mp3FrameInfo.bitrate && mp3FrameInfo.nChans
          && mp3FrameInfo.outputSamps && mp3FrameInfo.samprate
          && mp3FrameInfo.bitsPerSample))
  {
    // advance data pointer
    MF_EXEC(MediaFile_Seek(mfile, 1));
    return FUNC_ERROR;
  }

  bytesLeft = mfile->bytes_in_buf;
  f_buffer = &FILE_BUF(mfile, 0);

  //PROFILE_START("MP3Decode");
  err
          = MP3Decode(pMP3Decoder, &f_buffer, &bytesLeft,
                  (s16*) audio_buf->data, 0);
  //PROFILE_END();

  if (err != ERR_MP3_NONE)
  {
    switch (err)
    {
      case ERR_MP3_INDATA_UNDERFLOW:
      case ERR_MP3_MAINDATA_UNDERFLOW:
        if (mfile->state == MFS_EOF) /*XXX ???*/
        {
          return FUNC_ERROR;
        }
        else
        {
          /*XXX ???*/

          MF_EXEC(MediaFile_Seek(mfile, MAX(1, mfile->bytes_in_buf - bytesLeft)));
        }
        break;

      default:
        MF_EXEC(MediaFile_Seek(mfile, MAX(1, mfile->bytes_in_buf - bytesLeft)));
        break;
    }

    return FUNC_ERROR;
  }

  MF_EXEC(MediaFile_Seek(mfile, mfile->bytes_in_buf - bytesLeft));
  /* no error */

  memset(&mp3FrameInfo, 0, sizeof(mp3FrameInfo));
  MP3GetLastFrameInfo(pMP3Decoder, &mp3FrameInfo);
  if (!(mp3FrameInfo.bitrate && mp3FrameInfo.nChans && mp3FrameInfo.outputSamps
          && mp3FrameInfo.samprate && mp3FrameInfo.bitsPerSample))
  {
    // advance data pointer
    MF_EXEC(MediaFile_Seek(mfile, 1));
    return FUNC_ERROR;
  }

  assert_param(mp3FrameInfo.outputSamps <= AUDIO_BUFFER_MAX_SIZE);
  assert_param(mp3FrameInfo.nChans <= 2);

  audio_buf->size = mp3FrameInfo.outputSamps;
  audio_buf->sampling_freq = mp3FrameInfo.samprate;

  SetVariable(VAR_media_channel_count, mfile->meta.channel_count, mp3FrameInfo.nChans);
  SetVariable(VAR_media_bitrate, mfile->meta.bitrate, mp3FrameInfo.bitrate);

  if (mp3FrameInfo.nChans == 1)
  {
    assert_param(audio_buf->size * 2 <= AUDIO_BUFFER_MAX_SIZE);
    for (s32 i = audio_buf->size - 1; i >= 0; i--)
    {
      audio_buf->data[2 * i] = audio_buf->data[i];
      audio_buf->data[2 * i + 1] = audio_buf->data[i];
    }
    audio_buf->size *= 2;
  }

  mfile->meta.mstime_curr += MP3_FRAME_MSTIME;

  AudioBuffer_MoveProducer();

  return FUNC_SUCCESS;
}

FuncResult MP3_Seek(MediaFile_Typedef *mfile, s32 msec)
{
  //fixme file pos <-> audio stream pos relation

  if (vbr) //todo
    return FUNC_SUCCESS;

  s32 delta_data = msec / MP3_FRAME_MSTIME;
  s32 delta_time = delta_data * MP3_FRAME_MSTIME;

  if (mfile->meta.mstime_curr + delta_time > mfile->meta.mstime_max)
  {
    Playlist_LoadNext(); //fixme
    return FUNC_SUCCESS;
  }

  if ((s32) mfile->meta.mstime_curr + delta_time < 0)
  {
    Playlist_LoadPrev();
    return FUNC_SUCCESS;
  }

  mfile->meta.mstime_curr += delta_time;

  delta_data *= mfile->framesize;
  MF_EXEC(MediaFile_Seek(mfile, delta_data));

  return FUNC_SUCCESS;
}

void MP3_Init()
{
  if (!pMP3Decoder)
  {
    pMP3Decoder = MP3InitDecoder();
    assert_param(pMP3Decoder);
  }
}

void MP3_DeInit()
{
  /* todo: call me! */

  if (pMP3Decoder)
  {
    MP3FreeDecoder(pMP3Decoder);
    pMP3Decoder = 0;
  }
}
