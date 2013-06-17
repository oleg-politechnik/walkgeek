/*
 * mediafile.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MEDIAFILE_H_
#define MEDIAFILE_H_

/* Includes ------------------------------------------------------------------*/
#include "ff.h"
#include "metadata.h"
#include "system.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
  MFS_EMPTY,
  MFS_ERROR,
  MFS_OPENED,
  MFS_EOF,
  MFS_PLAYABLE
} MediaFileState_Typedef;

typedef struct
{
  MediaFileState_Typedef state;

  /* global indexes */
  int total_media_files;
  int current_media_file_index;

  /* current dir */
  DIR dir;
  //  u32 path_indexes[PLAYER_MAX_DIR_DEPTH];
  u32 path_depth;

  int total_media_files_dir;
  int current_media_file_index_dir;

  /* current file */
  FIL file;
  int file_index;

  /* decoding */
  u32 data_start;
  u32 framesize;//todo VBR??
  u32 maxframe;

  /* file buffer */
  u32 buf_offset;
  u32 bytes_in_buf;
  u8 file_buf[FILE_BUFFER_SIZE];
} MediaFile_Typedef;

/* Exported macro ------------------------------------------------------------*/
#define FILE_BUF(file, offset) (file->file_buf[file->buf_offset + offset])

#define FS_EXEC(cmd) do { \
        FRESULT res = cmd; if (res != FR_OK) return FUNC_ERROR; } while(0)

#define MF_EXEC(cmd) do { \
        FuncResult fr = cmd; if (fr != FUNC_SUCCESS) return fr; } while(0)

/* Exported functions --------------------------------------------------------*/
FuncResult MediaFile_Open(MediaFile_Typedef *mfile, const TCHAR *path);
void MediaFile_Close(MediaFile_Typedef *mfile);

FuncResult MediaFile_Seek(MediaFile_Typedef *mfile, u32 delta);
FuncResult MediaFile_FillFromFile(MediaFile_Typedef *mfile, u32 file_offset);
FuncResult MediaFile_ReFill(MediaFile_Typedef *mfile);

/* Exported variables --------------------------------------------------------*/

#endif /* MEDIAFILE_H_ */
