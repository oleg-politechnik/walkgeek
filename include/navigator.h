/*
 * navigator.h
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

/* Define to prevent recursive inclusion ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef NAVIGATOR_H_
#define NAVIGATOR_H_

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "common.h"
#include "ff.h"

/* Exported defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct
{
  DIR dir;
  int dir_entry_ix;
  int dir_entry_prev_interesting_ix;
  int dir_entry_ix_count;
} NavigatorDir_Typedef;

typedef struct
{
  NavigatorDir_Typedef dir_[NAVIGATOR_MAX_NESTING_LEVEL];
  int dir_nesting_;

  /* file-related */
  FILINFO file_info_;
  char lfn_buf_[256];

  char **suffixes_white_list_;

  //todo DIR->index;

//  filter
//  u32 total_media_files;
//  u32 current_media_file_index;
  //u32 total_media_files_dir;
  //u32 current_media_file_index_dir;

  char dir_path[256];
  char *fname;
  int suffix_ix;

} NavigatorContext_Typedef;

/* Exported functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Navigator_Init(void);
void Navigator_InitRoot(NavigatorContext_Typedef *ctx,
    char *suffixes_white_list[]);
bool Navigator_Cd(NavigatorContext_Typedef *ctx, char *path);
bool Navigator_CdUp(NavigatorContext_Typedef *ctx);
bool Navigator_TryFile(NavigatorContext_Typedef *ctx, char *filename);
void Navigator_DeInit(void);

bool Navigator_IsOnline(void);

void Navigator_NextFile(NavigatorContext_Typedef *ctx);
void Navigator_PrevFile(NavigatorContext_Typedef *ctx);
void Navigator_LastFileCurrentDir(NavigatorContext_Typedef *ctx);

/* Exported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported static inline functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#endif /* NAVIGATOR_H_ */
