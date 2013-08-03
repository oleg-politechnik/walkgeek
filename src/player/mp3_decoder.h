/*
 * mp3_decoder.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MP3_DECODER_H_
#define MP3_DECODER_H_

/* Includes ------------------------------------------------------------------*/
#include "player.h"
#include "mediafile.h"

/* Exported constants --------------------------------------------------------*/
#define MP3_BUFFER_SAMPLE_SIZE	(AUDIO_BUFFER_SAMPLE_SIZE / 2)

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
FuncResult MP3_LoadFile(sDecoderContext *psDecoderContext);
FuncResult MP3_MainThread(sDecoderContext *psDecoderContext);
FuncResult MP3_Seek(sDecoderContext *psDecoderContext, u32 ms_absolute_offset);
void MP3_Destroy(sDecoderContext *psDecoderContext);

#endif /* MP3_DECODER_H_ */
