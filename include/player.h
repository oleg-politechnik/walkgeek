/*
 * player.h
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

#ifndef PLAYER_H_
#define PLAYER_H_

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "metadata.h"

/* Exported defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum
{
  PS_DEINITED,
  PS_STOPPED,

  PS_ERROR_FILE,

  PS_PLAYING,
  PS_SEEKING,

  PS_MAX
} PlayerStatus_Typedef;

typedef enum
{
  PC_NEED_MORE_DATA,

  PC_INIT,
  PC_DEINIT,

  PC_NEXT,
  PC_PREV,

  PC_DIR_START,
  PC_DIR_END,

  PC_SAVE_CURRENT_DIR,

  PC_SEEK,

  PC_AUDIO_FILE_ERROR
} ePlayerCommand;

typedef struct
{
  ePlayerCommand cmd;
  s32 arg;
} sPlayerCommand;

typedef struct
{
  void (*LoadFile)(char *filepath);
  void (*MainThread)(void);
  void (*Seek)(u32 msec);
  void (*Stop)(void);
} Decoder_Typedef;

typedef struct
{
  Metadata_TypeDef metadata;
} PlayerState_Typedef;

/* Exported functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Player_AsyncCommand(ePlayerCommand cmd, s32 arg);
void Player_AsyncCommandFromISR(ePlayerCommand cmd, s32 arg);

PlayerState_Typedef *Player_GetState(void);
PlayerStatus_Typedef Player_GetStatus(void);

char *Player_GetErrorString(void);

void Player_AudioFileError(char *error); //fixme

/* Exported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported static inline functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif /* PLAYER_H_ */
