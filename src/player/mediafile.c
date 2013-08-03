/*
 * mediafile.c
 *
 * Copyright (c) 2012, 2013, Oleg Tsaregorodtsev
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
#include "mediafile.h"

/* Private defines -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions -------------------------------------------------------- */
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
