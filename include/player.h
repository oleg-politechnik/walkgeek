/*
 * player.h
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
#ifndef __PLAYER_H
#define __PLAYER_H

/* Includes ------------------------------------------------------------------*/
#include "ff.h"
#include "software_conf.h"
#include "audio_if.h"
#include "mediafile.h"
#include "metadata.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  PS_INACTIVE,  /* fs not mounted */
  PS_ERROR,
  PS_STOPPED,   /* fs mounted, no file loaded */
  PS_FILE_ERROR,/* non-fatal error related to the current file being played */
  PS_PLAYING,
  PS_PAUSED,
  PS_SEEKING    /* fast forward or rewind */
} PlayerState_Typedef;

typedef enum
{
  PC_EMPTY,

  PC_PLAY,
  PC_PAUSE,
  PC_NEXT,
  PC_PREV,
  PC_SEEK, /* arg = secs +- */

  PC_CHANGE_VOLUME,
/* arg = steps +- */
} PlayerCommand_Typedef;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Player_Init(void);
void Player_DeInit(void);

/* Playback is async, managed through Player_MainCycle */
void Player_AsyncCommand(PlayerCommand_Typedef cmd, s32 arg);
void Player_MainCycle(void);

MediaFile_Typedef *Player_CurrentFile(void);

PlayerState_Typedef Player_GetState(void);

/* Exported variables ------------------------------------------------------- */

#endif /* __PLAYER_H */



