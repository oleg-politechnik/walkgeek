/*
 * decoder.c
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

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "decoder.h"
#include "player.h"
#include "audio_if.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static sDecoderContext *ctx;

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void prvDecoderTask(void *pDecoderContext)
{
  u32 last_mstime_curr = 0;
  int mstime_delta;
  bool enter_seeking;

  ctx = (sDecoderContext *) pDecoderContext;
  sDecoderCommand command;
  sPlayerState *state;

  CPU_InitUserHeap();

  Decoder(ctx)->InitDecoder(ctx);

  while (1)
  {
    Decoder(ctx)->MainThread(ctx);

//    Audio_CommandSync(AC_PLAY);

    if (xQueueReceive(ctx->xCommandQueue, &(command), 0))
    {
      while (1)
      {
        if (command.cmd == DC_END_SEEKING)
        {
          Audio_CommandSync(AC_RESET_BUFFERS);
          Decoder(ctx)->Seek(ctx, ctx->psMetadata->mstime_curr);
          break;
        }
        else if (command.cmd == DC_SEEK)
        {
          Audio_CommandSync(AC_PAUSE);
          configASSERT(command.cmd <= ctx->psMetadata->mstime_max);
          ctx->psMetadata->mstime_curr = command.cmd;
        }

        command.cmd = DC_MAX;
        xQueueReceive(ctx->xCommandQueue, &(command), portMAX_DELAY);
      }
    }

    vTaskDelay(10); //todo rework async buffer
/*
    state = Player_GetState();

    if (state->status == PS_PLAYING || state->status == PS_SEEKING)
    {
      if (state->metadata.time_curr != state->metadata.mstime_curr / 1000)
      {
        SetVariable(VAR_AudioPosition, state->metadata.time_curr,
                state->metadata.mstime_curr / 1000);
      }
    }

    Audio_PeriodicKick();*/
  }
}

void Decoder_AsyncCommand(eDecoderCommand cmd, u32 ms_absolute_offset)
{
  sDecoderCommand command;
  command.cmd = cmd;
  command.ms_absolute_offset = ms_absolute_offset;

  xQueueSend( ctx->xCommandQueue, ( void * ) &command, taskDECODER_COMMAND_QUEUE_TIMEOUT );
}
