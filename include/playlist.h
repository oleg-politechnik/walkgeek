/*
 * playlist.h
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
#ifndef PLAYLIST_H_
#define PLAYLIST_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
#include "ff.h"

/* Exported constants --------------------------------------------------------*/
#define PLAYER_MAX_DIR_DEPTH  8
//todo stack of opened dirs to traverse through subdirs

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  int f_index; /* number of times ot call f_readdir */
  TCHAR fname[13];
  //todo path
} PlaylistEntry_Typedef;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

//void Playlist_Init(void);
//void Playlist_LoadNext(void);
//void Playlist_LoadPrev(void);
//FuncResult Playlist_TryLoadCurrentTrack(void);
//FuncResult Playlist_SetCurrentTrack(TCHAR *file_path);

#endif /* PLAYLIST_H_ */
