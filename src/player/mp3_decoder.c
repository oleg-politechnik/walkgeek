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
#include "bsp.h"
#include <malloc.h>
#include <unistd.h>
#include <limits.h>

extern PlayerStatus_Typedef PlayerStatus;

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

static MediaFile_Typedef *mfile;

//uint16_t MP3_FrameSize; //fixme

static int Frame_sampfreqs[4] =
{ 44100, 48000, 32000, 0 }; // sample rate MPEG1 LAYER3
static int Frame_bitrates[15] =
{ 0, 32000, 40000, 48000, 56000, 64000, 80000, 96000, 112000, 128000, 160000,
        192000, 224000, 256000, 320000 }; // bitrate MPEG1 LAYER3

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void MediaFile_Clear(MediaFile_Typedef *mfile)
{
  mfile->buf_offset = mfile->bytes_in_buf = 0;
}

FuncResult MediaFile_Open(MediaFile_Typedef *mfile, const TCHAR *path)
{
  assert_param(mfile->state == MFS_EMPTY);

  if (f_open(&mfile->file, path, FA_READ) != FR_OK)
  {
    mfile->state = MFS_ERROR;
    return FUNC_ERROR;
  }

  MediaFile_Clear(mfile);

  mfile->state = MFS_OPENED;
  return FUNC_SUCCESS;
}

void MediaFile_Close(MediaFile_Typedef *mfile)
{
  if (mfile->state != MFS_EMPTY)
  {
    f_close(&mfile->file);

    mfile->state = MFS_EMPTY;
  }
}

FuncResult MediaFile_Seek(MediaFile_Typedef *mfile, u32 delta)
{
  assert_param(mfile->state >= MFS_OPENED);

  assert_param(mfile->buf_offset < FILE_BUFFER_SIZE);
  assert_param(mfile->bytes_in_buf + mfile->buf_offset <= FILE_BUFFER_SIZE);

  u32 offset_to_load = mfile->file.fptr - mfile->bytes_in_buf + delta;

  assert_param(offset_to_load/* + size_min*/ < mfile->file.fsize);

  if (delta >= mfile->bytes_in_buf)
  {
    return MediaFile_FillFromFile(mfile, offset_to_load);
  }

  mfile->bytes_in_buf -= delta;
  mfile->buf_offset += delta;

  assert_param(mfile->buf_offset < FILE_BUFFER_SIZE);
  assert_param(mfile->bytes_in_buf + mfile->buf_offset <= FILE_BUFFER_SIZE);

//  if (size_min > mfile->bytes_in_buf)
//  {
    return MediaFile_ReFill(mfile);
//  }
//
//  return FUNC_SUCCESS;
}

FuncResult MediaFile_FillFromFile(MediaFile_Typedef *mfile, u32 abs_offset)
{
  assert_param(mfile->state >= MFS_OPENED);

  assert_param(abs_offset <= mfile->file.fsize);

  if (f_lseek(&mfile->file, abs_offset) != FR_OK)
  {
    mfile->state = MFS_ERROR;
    return FUNC_ERROR;
  }

  MediaFile_Clear(mfile);
  return MediaFile_ReFill(mfile);
}

FuncResult MediaFile_ReFill(MediaFile_Typedef *mfile)
{
  assert_param(mfile->state >= MFS_OPENED);

  FRESULT res;
  u32 bytes_returned, bytes_to_read, bytes_avail;

//  if (size_min <= mfile->bytes_in_buf)
//    /* nothing to do here */
//    return FUNC_SUCCESS;

  assert_param(mfile->buf_offset < FILE_BUFFER_SIZE);
  assert_param(mfile->bytes_in_buf + mfile->buf_offset <= FILE_BUFFER_SIZE);

  bytes_avail = mfile->file.fsize - mfile->file.fptr;

  if (bytes_avail == 0)
  {
    mfile->state = MFS_EOF;
    return FUNC_SUCCESS;
  }

//  if (bytes_avail >= FILE_BUFFER_SIZE)
//  {
    bytes_to_read = MIN(FILE_BUFFER_SIZE - mfile->bytes_in_buf, bytes_avail);
//  }
//  else
//  {
//    bytes_to_read = size_min - mfile->bytes_in_buf;
//  }



//  if (bytes_to_read > bytes_avail)
//  {
//    mfile->state = MFS_EOF;
//    return FUNC_NOT_SUCCESS;
//  }

  /*
   * x = free space
   * B = old buffer data
   *
   * file->file_buf
   * |
   * |          file->buf_offset
   * |          |
   * |          <----> - file->bytes_in_buf
   * |          |    |
   * xxxxxxxxxxxBBBBBB
   *                 ^
   *                 file->fptr
   */

  memmove(mfile->file_buf, &mfile->file_buf[mfile->buf_offset], mfile->bytes_in_buf);

  /*
   * x = free space
   * B = old buffer data
   *
   * file->file_buf
   * |
   * file->buf_offset
   * |
   * <----> - file->bytes_in_buf
   * |    |
   * BBBBBBxxxxxxxxxxx
   *      ^
   *      file->fptr
   */

  res = f_read(&mfile->file, &mfile->file_buf[mfile->bytes_in_buf], bytes_to_read,
          (UINT*) &bytes_returned);

  if (res != FR_OK || bytes_to_read != bytes_returned)
  {
    mfile->state = MFS_ERROR;
    return FUNC_ERROR;
  }

  /*
   * B = old buffer data
   * F = new data
   *
   * file->buf_offset
   * |
   * <---------------> - file->bytes_in_buf
   * |               |
   * BBBBBBFFFFFFFFFFF
   *                 ^
   *                 file->fptr
   */

  mfile->buf_offset = 0;
  mfile->bytes_in_buf += bytes_returned;

  assert_param(mfile->buf_offset < FILE_BUFFER_SIZE);
  assert_param(mfile->bytes_in_buf + mfile->buf_offset <= FILE_BUFFER_SIZE);

  return FUNC_SUCCESS;
}

FuncResult MP3_ReadMetadata(MediaFile_Typedef *mfile)
{
  uint32_t offset, frame_size, frame_header_size;
  u16 val; // record the start frame
  u8 version_major/*, extended_header*/;

  Metadata_TypeDef *meta = &(Player_GetState()->metadata);

  vbr = true;














  MF_EXEC(MediaFile_FillFromFile(mfile, 0));

  if (MP3_CHECK_TAG(mfile, "ID3"))
  { /* try ID3v2 */
    mfile->data_start = ((DWORD) FILE_BUF(mfile, 6) << 21)
            | ((DWORD) FILE_BUF(mfile, 7) << 14) | ((WORD) FILE_BUF(mfile, 8)
            << 7) | FILE_BUF(mfile, 9)/*XXX??? + 10*/;

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
        strncpy(meta->title,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(meta->title) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "TP1") || MP3_CHECK_TAG(mfile, "TPE1"))
      {
        strncpy(meta->artist,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(meta->artist) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "TAL"))
      {
        strncpy(meta->album,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(meta->album) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "TDRC") || MP3_CHECK_TAG(mfile, "TYER"))
      {
        strncpy(meta->year,
                (char *) &FILE_BUF(mfile, frame_header_size + 1),
                MIN(frame_size - 1, sizeof(meta->year) - 1));
      }
      else if (MP3_CHECK_TAG(mfile, "USLT"))
      {
        char *ptr = (char *) &FILE_BUF(mfile, frame_header_size + 1);
        ptr += strlen(ptr);
        ptr++;

        strncpy(meta->notes, ptr,
                MIN(frame_size - 1, sizeof(meta->notes) - 1));
      }

      MF_EXEC(MediaFile_Seek(mfile, frame_size + frame_header_size));
    }
  }
  else
  { /* ID3v1 */

    MF_EXEC(MediaFile_FillFromFile(mfile, mfile->file.fsize - 128));

    if (MP3_CHECK_TAG(mfile, "TAG"))
    {
      MF_EXEC(MediaFile_Seek(mfile, 3));
      strncpy(meta->title, (char *) mfile->file_buf,
              MIN(30, sizeof(meta->title) - 1));

      MF_EXEC(MediaFile_Seek(mfile, 30));
      strncpy(meta->artist, (char *) mfile->file_buf,
              MIN(30, sizeof(meta->artist) - 1));

      MF_EXEC(MediaFile_Seek(mfile, 30));
      strncpy(meta->album, (char *) mfile->file_buf,
              MIN(30, sizeof(meta->album) - 1));
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
  meta->mstime_curr = 0;
  meta->mstime_max = mfile->maxframe * MP3_FRAME_MSTIME;












//  if (entry->id3v2len)
//      setid3v2title(fd, entry);
//  int len = getsonglength(fd, entry);
//  if (len < 0)
//      return false;
//  entry->length = len;
//
//  /* Subtract the meta information from the file size to get
//     the true size of the MP3 stream */
//  entry->filesize -= entry->first_frame_offset;
//
//  /* only seek to end of file if no id3v2 tags were found */
//  if (!entry->id3v2len) {
//      setid3v1title(fd, entry);
//  }
//
//  if(!entry->length || (entry->filesize < 8 ))
//      /* no song length or less than 8 bytes is hereby considered to be an
//         invalid mp3 and won't be played by us! */
//      return false;
//
//  return true;




















  SyncVariable(VAR_PlayerState);

  return FUNC_SUCCESS;
}

void MP3_LoadFile(char *filepath)
{
  trace("MP3 started");
  print_user_heap_mallinfo();

  mfile = (MediaFile_Typedef *) malloc(sizeof(MediaFile_Typedef));
  memset(mfile, 0, sizeof(MediaFile_Typedef));

  trace("MP3 file buffers allocated");
  print_user_heap_mallinfo();

  MediaFile_Open(mfile, filepath);

  if (MP3_ReadMetadata(mfile) == FUNC_ERROR)
  {
    return Player_AudioFileError("Invalid MP3 metadata format");
  }

  pMP3Decoder = MP3InitDecoder();
  assert_param(pMP3Decoder);

  trace("MP3 decoder allocated");
  print_user_heap_mallinfo();
}

void MP3_MainThread(void)
{
  int offset, bytesLeft, err;
  u8 *f_buffer;

  if (mfile->state == MFS_EOF) /*XXX ???*/
  {
    Player_AsyncCommand(PC_NEXT, 0);
    return;
  }

  AudioBuffer_Typedef *audio_buf;
  if (!(audio_buf = AudioBuffer_TryGetProducer()))
  {
    return;
  }

  Metadata_TypeDef *meta = &(Player_GetState()->metadata);

  assert_param(audio_buf->size == 0);

  if (MediaFile_ReFill(mfile) != FUNC_SUCCESS)
    return;

  offset = MP3FindSyncWord(&FILE_BUF(mfile, 0), mfile->bytes_in_buf);
  if (offset < 0)
  {
    /* 2-byte sync word */

    MediaFile_Seek(mfile, mfile->bytes_in_buf - 2);
    return;
  }

  if (offset > 0)
  {
    if (MediaFile_Seek(mfile, offset) != FUNC_SUCCESS)
	    return;
  }

  memset(&mp3FrameInfo, 0, sizeof(mp3FrameInfo));
  err = MP3GetNextFrameInfo(pMP3Decoder, &mp3FrameInfo, &FILE_BUF(mfile, 0));
  if (!(err == ERR_MP3_NONE && mp3FrameInfo.bitrate && mp3FrameInfo.nChans
          && mp3FrameInfo.outputSamps && mp3FrameInfo.samprate
          && mp3FrameInfo.bitsPerSample))
  {
    // advance data pointer
    MediaFile_Seek(mfile, 1);
    return;
  }

  bytesLeft = mfile->bytes_in_buf;
  f_buffer = &FILE_BUF(mfile, 0);

  err = MP3Decode(pMP3Decoder, &f_buffer, &bytesLeft, (s16*) audio_buf->data,
      0);

  if (err != ERR_MP3_NONE)
  {
    switch (err)
    {
      case ERR_MP3_INDATA_UNDERFLOW:
      case ERR_MP3_MAINDATA_UNDERFLOW:
        if (mfile->state == MFS_EOF) /*XXX ???*/
        {
          return;
        }
        else
        {
          /*XXX ???*/

          MediaFile_Seek(mfile, MAX(1, mfile->bytes_in_buf - bytesLeft));
        }
        break;

      default:
        MediaFile_Seek(mfile, MAX(1, mfile->bytes_in_buf - bytesLeft));
        break;
    }

    return;
  }

  MediaFile_Seek(mfile, mfile->bytes_in_buf - bytesLeft);

  /* no error */

  memset(&mp3FrameInfo, 0, sizeof(mp3FrameInfo));
  MP3GetLastFrameInfo(pMP3Decoder, &mp3FrameInfo);
  if (!(mp3FrameInfo.bitrate && mp3FrameInfo.nChans && mp3FrameInfo.outputSamps
          && mp3FrameInfo.samprate && mp3FrameInfo.bitsPerSample))
  {
    // advance data pointer
    MediaFile_Seek(mfile, 1);
    return;
  }

  assert_param(mp3FrameInfo.outputSamps <= AUDIO_BUFFER_MAX_SIZE);
  assert_param(mp3FrameInfo.nChans <= 2);

  audio_buf->size = mp3FrameInfo.outputSamps;
  audio_buf->sampling_freq = mp3FrameInfo.samprate;

  SetVariable(VAR_AudioStatus, meta->channel_count, mp3FrameInfo.nChans);
  SetVariable(VAR_AudioStatus, meta->bitrate, mp3FrameInfo.bitrate);

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

  meta->mstime_curr += MP3_FRAME_MSTIME;

  AudioBuffer_MoveProducer();

  return;
}

void MP3_Seek(u32 msec)
{
  Metadata_TypeDef *meta = &(Player_GetState()->metadata);

  if (msec > meta->mstime_max)
    return;

  if (vbr) //todo
    return;

  u32 delta_data = msec / MP3_FRAME_MSTIME;
  u32 delta_time = delta_data * MP3_FRAME_MSTIME;

  meta->mstime_curr = delta_time;

  delta_data *= mfile->framesize;
  MediaFile_FillFromFile(mfile, delta_data);

  return;
}

void MP3_Stop(void)
{
  trace("MP3 deallocated");
  print_user_heap_mallinfo();

  MediaFile_Close(mfile);

  free(mfile);
}

#if 0

#define MAX_PATH 260

#define ID3V2_BUF_SIZE 900
#define ID3V2_MAX_ITEM_SIZE 240

struct mp3entry {
    char path[MAX_PATH];
    char* title;
    char* artist;
    char* album;
    char* genre_string;
    char* disc_string;
    char* track_string;
    char* year_string;
    char* composer;
    char* comment;
    char* albumartist;
    char* grouping;
    int discnum;
    int tracknum;
    int layer;
    int year;
    unsigned char id3version;
    unsigned int codectype;
    unsigned int bitrate;
    unsigned long frequency;
    unsigned long id3v2len;
    unsigned long id3v1len;
    unsigned long first_frame_offset; /* Byte offset to first real MP3 frame.
                                         Used for skipping leading garbage to
                                         avoid gaps between tracks. */
    unsigned long filesize; /* without headers; in bytes */
    unsigned long length;   /* song length in ms */
    unsigned long elapsed;  /* ms played */

    int lead_trim;          /* Number of samples to skip at the beginning */
    int tail_trim;          /* Number of samples to remove from the end */

    /* Added for Vorbis, used by mp4 parser as well. */
    unsigned long samples;  /* number of samples in track */

    /* MP3 stream specific info */
    unsigned long frame_count; /* number of frames in the file (if VBR) */

    /* Xing VBR fields */
    bool vbr;
    bool has_toc;           /* True if there is a VBR header in the file */
    unsigned char toc[100]; /* table of contents */

    /* these following two fields are used for local buffering */
    char id3v2buf[ID3V2_BUF_SIZE];
    char id3v1buf[4][92];
};


static unsigned long unsync(unsigned long b0,
                            unsigned long b1,
                            unsigned long b2,
                            unsigned long b3)
{
   return (((long)(b0 & 0x7F) << (3*7)) |
           ((long)(b1 & 0x7F) << (2*7)) |
           ((long)(b2 & 0x7F) << (1*7)) |
           ((long)(b3 & 0x7F) << (0*7)));
}

enum {
    ID3_VER_1_0 = 1,
    ID3_VER_1_1,
    ID3_VER_2_2,
    ID3_VER_2_3,
    ID3_VER_2_4
};

static bool global_ff_found;


unsigned long bytes2int(unsigned long b0, unsigned long b1,
                        unsigned long b2, unsigned long b3)
{
   return (b0 & 0xFF) << (3*8) |
          (b1 & 0xFF) << (2*8) |
          (b2 & 0xFF) << (1*8) |
          (b3 & 0xFF) << (0*8);
}


struct tag_resolver {
    const char* tag;
    int tag_length;
    size_t offset;
    int (*ppFunc)(struct mp3entry*, char* tag, int bufferpos);
    bool binary;
};

static const struct tag_resolver taglist[] = {
    { "TPE1", 4, offsetof(struct mp3entry, artist), NULL, false },
    { "TP1",  3, offsetof(struct mp3entry, artist), NULL, false },
    { "TIT2", 4, offsetof(struct mp3entry, title), NULL, false },
    { "TT2",  3, offsetof(struct mp3entry, title), NULL, false },
    { "TALB", 4, offsetof(struct mp3entry, album), NULL, false },
    { "TAL",  3, offsetof(struct mp3entry, album), NULL, false },
    { "TCOM", 4, offsetof(struct mp3entry, composer), NULL, false },
    { "TCM",  3, offsetof(struct mp3entry, composer), NULL, false },
    { "TPE2", 4, offsetof(struct mp3entry, albumartist), NULL, false },
    { "TP2",  3, offsetof(struct mp3entry, albumartist), NULL, false },
    { "TIT1", 4, offsetof(struct mp3entry, grouping), NULL, false },
    { "TT1",  3, offsetof(struct mp3entry, grouping), NULL, false },
    { "COMM", 4, offsetof(struct mp3entry, comment), NULL, false },
    { "COM",  3, offsetof(struct mp3entry, comment), NULL, false },
};

#define TAGLIST_SIZE ((int)SIZE_OF(taglist))

static int unicode_len(char encoding, const void* string)
{
    int len = 0;

    if (encoding == 0x01 || encoding == 0x02) {
        char first;
        const char *s = string;
        /* string might be unaligned, so using short* can crash on ARM and SH1 */
        do {
            first = *s++;
        } while ((first | *s++) != 0);

        len = s - (const char*) string;
    } else {
        len = strlen((char*) string) + 1;
    }

    return len;
}

/*
 * Sets the title of an MP3 entry based on its ID3v2 tag.
 *
 * Arguments: file - the MP3 file to scan for a ID3v2 tag
 *            entry - the entry to set the title in
 *
 * Returns: true if a title was found and created, else false
 */
void setid3v2title(int fd, struct mp3entry *entry)
{
    int minframesize;
    int size;
    long bufferpos = 0, totframelen, framelen;
    char header[10];
    char tmp[4];
    unsigned char version;
    char *buffer = entry->id3v2buf;
    int bytesread = 0;
    int buffersize = sizeof(entry->id3v2buf);
    unsigned char global_flags;
    int flags;
    bool global_unsynch = false;
    bool unsynch = false;
    int i, j;
    int rc;


    global_ff_found = false;

    /* Bail out if the tag is shorter than 10 bytes */
    if(entry->id3v2len < 10)
        return;

    /* Read the ID3 tag version from the header */
    lseek(fd, 0, SEEK_SET);
    if(10 != read(fd, header, 10))
        return;

    /* Get the total ID3 tag size */
    size = entry->id3v2len - 10;

    version = header[3];
    switch ( version ) {
        case 2:
            version = ID3_VER_2_2;
            minframesize = 8;
            break;

        case 3:
            version = ID3_VER_2_3;
            minframesize = 12;
            break;

        case 4:
            version = ID3_VER_2_4;
            minframesize = 12;
            break;

        default:
            /* unsupported id3 version */
            return;
    }
    entry->id3version = version;
    entry->tracknum = entry->year = entry->discnum = 0;
    entry->title = entry->artist = entry->album = NULL; /* FIXME incomplete */

    global_flags = header[5];

    /* Skip the extended header if it is present */
    if(global_flags & 0x40) {
        if(version == ID3_VER_2_3) {
            if(10 != read(fd, header, 10))
                return;
            /* The 2.3 extended header size doesn't include the header size
               field itself. Also, it is not unsynched. */
            framelen =
                bytes2int(header[0], header[1], header[2], header[3]) + 4;

            /* Skip the rest of the header */
            lseek(fd, framelen - 10, SEEK_CUR);
        }

        if(version >= ID3_VER_2_4) {
            if(4 != read(fd, header, 4))
                return;

            /* The 2.4 extended header size does include the entire header,
               so here we can just skip it. This header is unsynched. */
            framelen = unsync(header[0], header[1],
                              header[2], header[3]);

            lseek(fd, framelen - 4, SEEK_CUR);
        }
    }

    /* Is unsynchronization applied? */
    if(global_flags & 0x80) {
        global_unsynch = true;
    }

    /*
     * We must have at least minframesize bytes left for the
     * remaining frames to be interesting
     */
    while (size >= minframesize && bufferpos < buffersize - 1) {
        flags = 0;

        /* Read frame header and check length */
        if(version >= ID3_VER_2_3) {
            if(global_unsynch && version <= ID3_VER_2_3)
                rc = read_unsynched(fd, header, 10);
            else
                rc = read(fd, header, 10);
            if(rc != 10)
                return;
            /* Adjust for the 10 bytes we read */
            size -= 10;

            flags = bytes2int(0, 0, header[8], header[9]);

            if (version >= ID3_VER_2_4) {
                framelen = unsync(header[4], header[5],
                                  header[6], header[7]);
            } else {
                /* version .3 files don't use synchsafe ints for
                 * size */
                framelen = bytes2int(header[4], header[5],
                                     header[6], header[7]);
            }
        } else {
            if(6 != read(fd, header, 6))
                return;
            /* Adjust for the 6 bytes we read */
            size -= 6;

            framelen = bytes2int(0, header[3], header[4], header[5]);
        }

//        logf("framelen = %ld, flags = 0x%04x", framelen, flags);
        if(framelen == 0){
            if (header[0] == 0 && header[1] == 0 && header[2] == 0)
                return;
            else
                continue;
        }

        unsynch = false;

        if(flags)
        {
            if (version >= ID3_VER_2_4) {
                if(flags & 0x0040) { /* Grouping identity */
                    lseek(fd, 1, SEEK_CUR); /* Skip 1 byte */
                    framelen--;
                }
            } else {
                if(flags & 0x0020) { /* Grouping identity */
                    lseek(fd, 1, SEEK_CUR); /* Skip 1 byte */
                    framelen--;
                }
            }

            if(flags & 0x000c) /* Compression or encryption */
            {
                /* Skip it */
                size -= framelen;
                lseek(fd, framelen, SEEK_CUR);
                continue;
            }

            if(flags & 0x0002) /* Unsynchronization */
                unsynch = true;

            if (version >= ID3_VER_2_4) {
                if(flags & 0x0001) { /* Data length indicator */
                    if(4 != read(fd, tmp, 4))
                        return;

                    /* We don't need the data length */
                    framelen -= 4;
                }
            }
        }
    }
}


struct mp3info {
    /* Standard MP3 frame header fields */
    int version;
    int layer;
    int bitrate;
    long frequency;
    int padding;
    int channel_mode;
    int frame_size;   /* Frame size in bytes */
    int frame_samples;/* Samples per frame */
    int ft_num;       /* Numerator of frametime in milliseconds */
    int ft_den;       /* Denominator of frametime in milliseconds */

    bool is_vbr;      /* True if the file is VBR */
    bool has_toc;     /* True if there is a VBR header in the file */
    unsigned char toc[100];
    unsigned long frame_count; /* Number of frames in the file (if VBR) */
    unsigned long byte_count;  /* File size in bytes */
    unsigned long file_time;   /* Length of the whole file in milliseconds */
    int enc_delay;    /* Encoder delay, fetched from LAME header */
    int enc_padding;  /* Padded samples added to last frame. LAME header */
};

#define VBR_HEADER_MAX_SIZE (180)

#define MPEG_VERSION1   0
#define MPEG_VERSION2   1
#define MPEG_VERSION2_5 2

static bool mp3headerinfo(struct mp3info *info, unsigned long header)
{
//    int bitindex, freqindex;
//
//    /* MPEG Audio Version */
//    if ((header & VERSION_MASK) >> 19 >= sizeof(version_table))
//        return false;
//
//    info->version = version_table[(header & VERSION_MASK) >> 19];
//    if (info->version < 0)
//        return false;
//
//    /* Layer */
//    info->layer = 3 - ((header & LAYER_MASK) >> 17);
//    if (info->layer == 3)
//        return false;
//
//
//    /* Calculate number of bytes, calculation depends on layer */
//    if (info->layer == 0) {
//        info->frame_samples = 384;
//        info->frame_size = (12000 * info->bitrate / info->frequency
//                            + info->padding) * 4;
//    }
//    else {
//        if ((info->version > MPEG_VERSION1) && (info->layer == 2))
//            info->frame_samples = 576;
//        else
//            info->frame_samples = 1152;
//        info->frame_size = (1000/8) * info->frame_samples * info->bitrate
//                           / info->frequency + info->padding;
//    }
//
//    /* Frametime fraction denominator */
//    if (freqindex != 0) {      /* 48/32/24/16/12/8 kHz */
//        info->ft_den = 1;      /* integer number of milliseconds */
//    }
//    else {                     /* 44.1/22.05/11.025 kHz */
//        if (info->layer == 0)     /* layer 1 */
//            info->ft_den = 147;
//        else                      /* layer 2+3 */
//            info->ft_den = 49;
//    }
//    /* Frametime fraction numerator */
//    info->ft_num = 1000 * info->ft_den * info->frame_samples / info->frequency;
//
//    info->channel_mode = (header & CHANNELMODE_MASK) >> 6;
///* Rockbox: not used
//    info->mode_extension = (header & MODE_EXT_MASK) >> 4;
//    info->emphasis = header & EMPHASIS_MASK;
//*/
//    VDEBUGF( "Header: %08lx, Ver %d, lay %d, bitr %d, freq %ld, "
//            "chmode %d, bytes: %d time: %d/%d\n",
//            header, info->version, info->layer+1, info->bitrate,
//            info->frequency, info->channel_mode,
//            info->frame_size, info->ft_num, info->ft_den);
    return true;
}

/* Seek to next mpeg header and extract relevant information. */
static int get_next_header_info(int fd, long *bytecount, struct mp3info *info,
                                bool single_header)
{
    long tmp;
    unsigned long header = 0;

//    header = __find_next_frame(fd, &tmp, 0x20000, 0, fileread, single_header);
    if(header == 0)
        return -1;

    if(!mp3headerinfo(info, header))
        return -2;

    /* Next frame header is tmp bytes away. */
//    *bytecount += tmp;

    return 0;
}

#define VBR_FRAMES_FLAG  0x01
#define VBR_BYTES_FLAG   0x02
#define VBR_TOC_FLAG     0x04
#define VBR_QUALITY_FLAG 0x08

#define MAX_XING_HEADER_SIZE 576

/* Extract information from a 'Xing' or 'Info' header. */
static void get_xing_info(struct mp3info *info, unsigned char *buf)
{
    int i = 8;

    /* Is it a VBR file? */
    info->is_vbr = !memcmp(buf, "Xing", 4);

    if (buf[7] & VBR_FRAMES_FLAG) /* Is the frame count there? */
    {
        info->frame_count = bytes2int(buf[i], buf[i+1], buf[i+2], buf[i+3]);
        if (info->frame_count <= ULONG_MAX / info->ft_num)
            info->file_time = info->frame_count * info->ft_num / info->ft_den;
        else
            info->file_time = info->frame_count / info->ft_den * info->ft_num;
        i += 4;
    }

    if (buf[7] & VBR_BYTES_FLAG) /* Is byte count there? */
    {
        info->byte_count = bytes2int(buf[i], buf[i+1], buf[i+2], buf[i+3]);
        i += 4;
    }

    if (info->file_time && info->byte_count)
    {
        if (info->byte_count <= (ULONG_MAX/8))
            info->bitrate = info->byte_count * 8 / info->file_time;
        else
            info->bitrate = info->byte_count / (info->file_time >> 3);
    }

    if (buf[7] & VBR_TOC_FLAG) /* Is table-of-contents there? */
    {
        info->has_toc = true;
        memcpy( info->toc, buf+i, 100 );
        i += 100;
    }
    if (buf[7] & VBR_QUALITY_FLAG)
    {
        /* We don't care about this, but need to skip it */
        i += 4;
    }
#if CONFIG_CODEC==SWCODEC
    i += 21;
    info->enc_delay   = ((int)buf[i  ] << 4) | (buf[i+1] >> 4);
    info->enc_padding = ((int)(buf[i+1]&0xF) << 8) |  buf[i+2];
    /* TODO: This sanity checking is rather silly, seeing as how the LAME
       header contains a CRC field that can be used to verify integrity. */
    if (!(info->enc_delay   >= 0 && info->enc_delay   <= 2880 &&
          info->enc_padding >= 0 && info->enc_padding <= 2*1152))
    {
       /* Invalid data */
       info->enc_delay   = -1;
       info->enc_padding = -1;
    }
#endif
}

/* Extract information from a 'VBRI' header. */
static void get_vbri_info(struct mp3info *info, unsigned char *buf)
{
    /* We don't parse the TOC, since we don't yet know how to (FIXME) */
    /*
    int i, num_offsets, offset = 0;
    */

    info->is_vbr  = true;  /* Yes, it is a FhG VBR file */
    info->has_toc = false; /* We don't parse the TOC (yet) */

    info->byte_count  = bytes2int(buf[10], buf[11], buf[12], buf[13]);
    info->frame_count = bytes2int(buf[14], buf[15], buf[16], buf[17]);
    if (info->frame_count <= ULONG_MAX / info->ft_num)
        info->file_time = info->frame_count * info->ft_num / info->ft_den;
    else
        info->file_time = info->frame_count / info->ft_den * info->ft_num;

    if (info->byte_count <= (ULONG_MAX/8))
        info->bitrate = info->byte_count * 8 / info->file_time;
    else
        info->bitrate = info->byte_count / (info->file_time >> 3);

//    VDEBUGF("Frame size (%dkpbs): %d bytes (0x%x)\n",
//           info->bitrate, info->frame_size, info->frame_size);
//    VDEBUGF("Frame count: %lx\n", info->frame_count);
//    VDEBUGF("Byte count: %lx\n", info->byte_count);

    /* We don't parse the TOC, since we don't yet know how to (FIXME) */
    /*
    num_offsets = bytes2int(0, 0, buf[18], buf[19]);
    VDEBUGF("Offsets: %d\n", num_offsets);
    VDEBUGF("Frames/entry: %ld\n", bytes2int(0, 0, buf[24], buf[25]));

    for(i = 0; i < num_offsets; i++)
    {
       offset += bytes2int(0, 0, buf[26+i*2], buf[27+i*2]);;
       VDEBUGF("%03d: %lx\n", i, offset - bytecount,);
    }
    */
}


int get_mp3file_info(int fd, struct mp3info *info)
{
    unsigned char frame[VBR_HEADER_MAX_SIZE], *vbrheader;
    long bytecount = 0;
    int result, buf_size;

    /* Initialize info and frame */
    memset(info,  0, sizeof(struct mp3info));
    memset(frame, 0, sizeof(frame));

#if CONFIG_CODEC==SWCODEC
    /* These two are needed for proper LAME gapless MP3 playback */
    info->enc_delay   = -1;
    info->enc_padding = -1;
#endif

    /* Get the very first single MPEG frame. */
    result = get_next_header_info(fd, &bytecount, info, true);
    if(result)
        return result;

    /* Read the amount of frame data to the buffer that is required for the
     * vbr tag parsing. Skip the rest. */
    buf_size = MIN(info->frame_size-4, (int)sizeof(frame));
    if(read(fd, frame, buf_size) < 0)
        return -3;
    lseek(fd, info->frame_size - 4 - buf_size, SEEK_CUR);

    /* Calculate position of a possible VBR header */
    if (info->version == 1) {
        if (info->channel_mode == 3) /* mono */
            vbrheader = frame + 17;
        else
            vbrheader = frame + 32;
    } else {
        if (info->channel_mode == 3) /* mono */
            vbrheader = frame + 9;
        else
            vbrheader = frame + 17;
    }

    if (!memcmp(vbrheader, "Xing", 4) || !memcmp(vbrheader, "Info", 4))
    {
//        VDEBUGF("-- XING header --\n");

        /* We want to skip the Xing frame when playing the stream */
        bytecount += info->frame_size;

        /* Now get the next frame to read the real info about the mp3 stream */
        result = get_next_header_info(fd, &bytecount, info, false);
        if(result)
            return result;

        get_xing_info(info, vbrheader);
    }
    else if (!memcmp(vbrheader, "VBRI", 4))
    {
//        VDEBUGF("-- VBRI header --\n");

        /* We want to skip the VBRI frame when playing the stream */
        bytecount += info->frame_size;

        /* Now get the next frame to read the real info about the mp3 stream */
        result = get_next_header_info(fd, &bytecount, info, false);
        if(result)
            return result;

        get_vbri_info(info, vbrheader);
    }
    else
    {
//        VDEBUGF("-- No VBR header --\n");

        /* There was no VBR header found. So, we seek back to beginning and
         * search for the first MPEG frame header of the mp3 stream. */
        lseek(fd, -info->frame_size, SEEK_CUR);
        result = get_next_header_info(fd, &bytecount, info, false);
        if(result)
            return result;
    }

    return bytecount;
}

/*
 * Calculates the length (in milliseconds) of an MP3 file.
 *
 * Modified to only use integers.
 *
 * Arguments: file - the file to calculate the length upon
 *            entry - the entry to update with the length
 *
 * Returns: the song length in milliseconds,
 *          0 means that it couldn't be calculated
 */
static int getsonglength(int fd, struct mp3entry *entry)
{
    unsigned long filetime = 0;
    struct mp3info info;
    long bytecount;

    /* Start searching after ID3v2 header */
    if(-1 == lseek(fd, entry->id3v2len, SEEK_SET))
        return 0;

    bytecount = get_mp3file_info(fd, &info);

//    logf("Space between ID3V2 tag and first audio frame: 0x%lx bytes",
//           bytecount);

    if(bytecount < 0)
        return -1;

    bytecount += entry->id3v2len;

    /* Validate byte count, in case the file has been edited without
     * updating the header.
     */
    if (info.byte_count)
    {
        const unsigned long expected = entry->filesize - entry->id3v1len
            - entry->id3v2len;
        const unsigned long diff = MAX(10240, info.byte_count / 20);

        if ((info.byte_count > expected + diff)
            || (info.byte_count < expected - diff))
        {
//            logf("Note: info.byte_count differs from expected value by "
//                 "%ld bytes", labs((long) (expected - info.byte_count)));
            info.byte_count = 0;
            info.frame_count = 0;
            info.file_time = 0;
            info.enc_padding = 0;

            /* Even if the bitrate was based on "known bad" values, it
             * should still be better for VBR files than using the bitrate
             * of the first audio frame.
             */
        }
    }

    entry->bitrate   = info.bitrate;
    entry->frequency = info.frequency;
    entry->layer     = info.layer;
    switch(entry->layer) {
#if CONFIG_CODEC==SWCODEC
        case 0:
            entry->codectype=1;
            break;
#endif
        case 1:
            entry->codectype=2;
            break;
        case 2:
            entry->codectype=3;
            break;
    }

    /* If the file time hasn't been established, this may be a fixed
       rate MP3, so just use the default formula */

    filetime = info.file_time;

    if(filetime == 0)
    {
        /* Prevent a division by zero */
        if (info.bitrate < 8)
            filetime = 0;
        else
            filetime = (entry->filesize - bytecount) / (info.bitrate / 8);
        /* bitrate is in kbps so this delivers milliseconds. Doing bitrate / 8
         * instead of filesize * 8 is exact, because mpeg audio bitrates are
         * always multiples of 8, and it avoids overflows. */
    }

    entry->frame_count = info.frame_count;

    entry->vbr = info.is_vbr;
    entry->has_toc = info.has_toc;

#if CONFIG_CODEC==SWCODEC
    if (!entry->lead_trim)
        entry->lead_trim = info.enc_delay;
    if (!entry->tail_trim)
        entry->tail_trim = info.enc_padding;
#endif

    memcpy(entry->toc, info.toc, sizeof(info.toc));

    /* Update the seek point for the first playable frame */
    entry->first_frame_offset = bytecount;
//    logf("First frame is at %lx", entry->first_frame_offset);

    return filetime;
}

/*
 * Sets the title of an MP3 entry based on its ID3v1 tag.
 *
 * Arguments: file - the MP3 file to scen for a ID3v1 tag
 *            entry - the entry to set the title in
 *
 * Returns: true if a title was found and created, else false
 */
bool setid3v1title(int fd, struct mp3entry *entry)
{
    unsigned char buffer[128];
    static const char offsets[] = {3, 33, 63, 97, 93, 125, 127};
    int i, j;
    unsigned char* utf8;

    if (-1 == lseek(fd, -128, SEEK_END))
        return false;

    if (read(fd, buffer, sizeof buffer) != sizeof buffer)
        return false;

    if (strncmp((char *)buffer, "TAG", 3))
        return false;

    entry->id3v1len = 128;
    entry->id3version = ID3_VER_1_0;

    for (i=0; i < (int)sizeof offsets; i++) {
        unsigned char* ptr = (unsigned char *)buffer + offsets[i];

        switch(i) {
            case 0:
            case 1:
            case 2:
                /* kill trailing space in strings */
                for (j=29; j && (ptr[j]==0 || ptr[j]==' '); j--)
                    ptr[j] = 0;
                /* convert string to utf8 */
                utf8 = (unsigned char *)entry->id3v1buf[i];
//                utf8 = iso_decode(ptr, utf8, -1, 30);
                /* make sure string is terminated */
                *utf8 = 0;
                break;

            case 3:
                /* kill trailing space in strings */
                for (j=27; j && (ptr[j]==0 || ptr[j]==' '); j--)
                    ptr[j] = 0;
                /* convert string to utf8 */
//                utf8 = (unsigned char *)entry->id3v1buf[3];
//                utf8 = iso_decode(ptr, utf8, -1, 28);
                /* make sure string is terminated */
                *utf8 = 0;
                break;

            case 4:
                ptr[4] = 0;
//                entry->year = atoi((char *)ptr);
                break;

            case 5:
                /* id3v1.1 uses last two bytes of comment field for track
                   number: first must be 0 and second is track num */
                if (!ptr[0] && ptr[1]) {
                    entry->tracknum = ptr[1];
                    entry->id3version = ID3_VER_1_1;
                }
                break;

            case 6:
                /* genre */
//                entry->genre_string = id3_get_num_genre(ptr[0]);
                break;
        }
    }

    entry->title = entry->id3v1buf[0];
    entry->artist = entry->id3v1buf[1];
    entry->album = entry->id3v1buf[2];
    entry->comment = entry->id3v1buf[3];

    return true;
}
#endif
