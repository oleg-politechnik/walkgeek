/*
 ** Copied from:
 ** File: opusdec.c
 ** Copyright (c) 2002-2007 Jean-Marc Valin
 ** Copyright (c) 2008 CSIRO
 ** Copyright (c) 2007-2012 Xiph.Org Foundation
 *
 * opus_decoder.c
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
#include "task.h"

#include "opus_decoder.h"
#include "mediafile.h"
#include "audio_buffer.h"
#include <ogg/ogg.h>
#include "opus_types.h"
#include <opus_multistream.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h> /*tolower()*/

#include <opus.h>
#include <opus_multistream.h>
#include <ogg/ogg.h>

#include <math.h>

#include <string.h>
#include "opus_header.h"
#include "audio_buffer.h"
#include "player.h"
#include "audio_if.h"

#include "ff.h"
#include "audio_if.h"
#include "opus_types.h"
#include "opus/config.h"
#include "opus/celt/stack_alloc.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* 20ms at 48000, TODO 120ms */
#define MAX_FRAME_SIZE      960
#define OPUS_STACK_SIZE     31684 /**/

/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct
{
  opus_int16 *output;
  int frame_size;
  OpusDecoder *st;
  opus_int64 packet_count;
  int total_links;
  int stream_init;
  int quiet;
  ogg_int64_t page_granule;
  ogg_int64_t end_granule;
  ogg_int64_t link_out;
  ogg_page og;
  ogg_packet op;
  ogg_stream_state os;
  int eos;
  ogg_int64_t audio_size;
  double last_coded_seconds;
  int channels;
  int rate;
  int preskip;
  int gran_offset;
  int has_opus_stream;
  ogg_int32_t opus_serialno;
  int proceeding_page;
  int seeking;

  opus_int64 maxout;

  FIL file;
  FRESULT res;
} sOpusPrivate;

/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define readint(buf, base) (((buf[base+3]<<24)&0xff000000)| \
                           ((buf[base+2]<<16)&0xff0000)| \
                           ((buf[base+1]<<8)&0xff00)| \
                           (buf[base]&0xff))

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void print_comments(sDecoderContext *psDecoderContext, char *comments, int length);
static OpusDecoder *process_header(sDecoderContext *psDecoderContext, ogg_packet *op, int *rate, int *channels,
        int *preskip, int quiet);

/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int OPUS_LoadFile(sDecoderContext *psDecoderContext)
{
  configASSERT(!psDecoderContext->pDecoderData);

  trace("OPUS started");
  print_user_heap_mallinfo();

  psDecoderContext->pDecoderData = pvPortMalloc(sizeof(sOpusPrivate));
  bzero(psDecoderContext->pDecoderData, sizeof(sOpusPrivate));

  trace("OPUS file buffers allocated");
  print_user_heap_mallinfo();

  sOpusPrivate *p = (sOpusPrivate *) psDecoderContext->pDecoderData;
  p->channels = -1;
  p->rate = 48000;
  p->os.oy.file = &p->file;

  p->res = f_open(&p->file, psDecoderContext->pcFilePath, FA_READ);
  if (p->res != FR_OK)
  {
    assert_param(0);
    //
  }

  return true;
}

int OPUS_LoadMetadata(sDecoderContext *psDecoderContext)
{
  sOpusPrivate *p = (sOpusPrivate *) psDecoderContext->pDecoderData;
  sMetadata *meta = psDecoderContext->psMetadata;

  /* Determine the audio length */
  {
    minogg_sync_init(&p->os.oy, 2048, NULL);

    /* All we need here is to read last page's header granulepos */
    /* Ogg max page size is 65K, so... */
    p->os.oy.nextpage_pos = MIN(minogg_impl_fsize(&p->os.oy), 65536); //todo

    while (minogg_sync_pageout(&p->os.oy, &p->og) == MINOGG_OK)
    {
      p->opus_serialno = ogg_page_serialno(&p->og);
      p->end_granule = ogg_page_granulepos(&p->og);
    }

    // ogg_sync_reset(&oy); todo
  }

  p->os.oy.nextpage_pos = 0; //todo this is ugly

  return true;
}

void OPUS_Init(sDecoderContext *psDecoderContext)
{
  configASSERT(psDecoderContext->pDecoderData);

  sOpusPrivate *p = (sOpusPrivate *) psDecoderContext->pDecoderData;

  configASSERT(!p->st);
}

int OPUS_MainThread(sDecoderContext *psDecoderContext)
{
  sOpusPrivate *p = (sOpusPrivate *) psDecoderContext->pDecoderData;
  sMetadata *meta = psDecoderContext->psMetadata;

  char *data;
  UINT nb_read;

  if (!p->frame_size) /* already have decoded frame */
  {
    if (p->proceeding_page)
    {
      if (ogg_stream_packetout(&p->os, &p->op) == 1)
      {
	p->proceeding_page = 1;
        /*OggOpus streams are identified by a magic string in the initial
         stream header.*/
        if (p->op.b_o_s && p->op.bytes >= 8 && !memcmp(p->op.packet, "OpusHead", 8))
        {
          if (!p->has_opus_stream)
          {
            p->opus_serialno = p->os.serialno;
            p->has_opus_stream = 1;
            p->link_out = 0;
            p->packet_count = 0;
            p->eos = 0;
            p->total_links++;
          }
          else
          {
            trace("Warning: ignoring opus stream %lld\n",
                    (long long) os->serialno);
          }
        }
        if (!p->has_opus_stream || p->os.serialno != p->opus_serialno)
        {
          trace("!has_opus_stream || os->serialno != opus_serialno");
          exit(1);
          return (-1);
        }

        /*If first packet in a logical stream, process the Opus header*/
        if (p->packet_count == 0)
        {
          p->st = process_header(psDecoderContext, &p->op, &p->rate, &p->channels, &p->preskip, p->quiet);
          if (!p->st)
	  {
	    exit(1);
	    return (-1);
	  }

          trace("Decoder allocated");
          print_user_heap_mallinfo();

          meta->channel_count = p->channels;

          if (ogg_stream_packetout(&p->os, &p->op) != 0 || p->og.header[p->og.header_len
                  - 1] == 255)
          {
            /*The format specifies that the initial header and tags packets are on their
             own pages. To aid implementors in discovering that their files are wrong
             we reject them explicitly here. In some player designs files like this would
             fail even without an explicit test.*/

            Player_AudioFileError(
                    "Extra packets on initial header page. Invalid stream.");
            return -1;
          }

          /*Remember how many samples at the front we were told to skip
           so that we can adjust the timestamp counting.*/
          p->gran_offset = p->preskip;

          if (p->end_granule < p->gran_offset)
            exit(1);

          meta->mstime_max = (p->end_granule - p->gran_offset) / (p->rate
                  / 1000);

          p->output = user_malloc(sizeof(opus_int16) * MAX_FRAME_SIZE * p->channels);
          if (!p->output)
          {
            Player_AudioFileError("Cannot allocate CPU_AllocFromStackBottom");
            return -1;
          }

          trace("Output buffer allocated");
          print_user_heap_mallinfo();

          SyncVariable(VAR_AudioStatus);
        }
        else if (p->packet_count == 1)
        {
          if (!p->quiet)
            print_comments(psDecoderContext, (char*) p->op.packet, p->op.bytes);

#if 0
          if (ogg_stream_packetout(os, &op) != 0 || og.header[og.header_len
                  - 1] == 255)
          {
            Player_AudioFileError(
                    "Extra packets on initial tags page. Invalid stream.");
            return;
          }
#endif
        }
        else
        {
          int ret;

          /*End of stream condition*/
          if (p->op.e_o_s && p->os.serialno == p->opus_serialno)
            p->eos = 1; /* don't care for anything except opus eos */

          ret = opus_decode(p->st, (unsigned char*) p->op.packet, p->op.bytes,
              p->output, MAX_FRAME_SIZE, 0);

          /*If the decoder returned less than zero, we have an error.*/
          if (ret < 0)
          {
            trace("Decoding error: %s\n", opus_strerror(ret));
            exit(1);
          }
          p->frame_size = ret;

          /*This handles making sure that our output duration respects
           the final end-trim by not letting the output sample count
           get ahead of the granpos indicated value.*/
          p->maxout = ((p->page_granule - p->gran_offset) * p->rate / 48000) - p->link_out;
        }
        p->packet_count++;
      }
      else
      {
	p->proceeding_page = 0;
      }
    }

    /*We're done*/
    if (p->eos)
    {
      p->has_opus_stream = 0;
    }
    else
    {
      if (!p->proceeding_page && minogg_sync_pageout(&p->os.oy, &p->og) == MINOGG_OK)
      {
        if (p->stream_init == 0)
        {
          ogg_stream_init(&p->os, ogg_page_serialno(&p->og));
          p->stream_init = 1;
        }
        if (ogg_page_serialno(&p->og) != p->os.serialno)
        {
          /* so all streams are read. */
          ogg_stream_reset_serialno(&p->os, ogg_page_serialno(&p->og));
        }
        /*Add page to the bitstream*/
        ogg_stream_pagein(&p->os, &p->og);

        p->page_granule = ogg_page_granulepos(&p->og);

        p->proceeding_page = 1;
      }
    }
  }

  if (p->frame_size) /* already have decoded frame */
  {
    if (AudioBuffer_TryGetProducer())
    {
//      opus_int64 outsamp;
//
//      outsamp = audio_write(output, channels, frame_size, &preskip,
//              0 > maxout ? 0 : maxout);
//      link_out += outsamp;
//      audio_size += outsamp;
//
//      meta->mstime_curr = audio_size / (rate / 1000);
//
//      frame_size = 0; /* we have consumed that last decoded frame */
//
//      if (f_eof(file))
//      {
//        trace("\rDecoding complete.        \n");
//        /*Did we make it to the end without recovering ANY opus logical streams?*/
//        if (!total_links)
//        {
//          trace("This doesn't look like a Opus file\n");
//        }
//
//        //          if (stream_init)
//        //            ogg_stream_clear(os);
//        //          ogg_sync_clear(&oy);
//
//        f_close(file);
//
//        Player_AsyncCommand(PC_NEXT, 0);
//
////        vTaskDelete(NULL);
//      }
    }
  }

  return 0;//fixme
}

void OPUS_Seek(sDecoderContext *psDecoderContext, u32 ms_absolute_offset)
{
  //todo debug
#if 0
  assert_param(msec < meta->mstime_max);

  trace("Opus: trying to seek to %us... ", msec / 1000);
  fflush(stdout);

  proceeding_page = 0;
  frame_size = 0;

  //opus_decoder_ctl(st, OPUS_RESET_STATE);

  {
    os->oy.nextpage_pos = (double) os->oy.fsize /
	((double) meta->mstime_max / msec);

    if (minogg_sync_pageout(&os->oy, og) != MINOGG_OK)
      return;

    page_granule = ogg_page_granulepos(og);
  }

  meta->mstime_curr = page_granule - gran_offset;

  audio_size = meta->mstime_curr * (rate / 1000);

  trace("got %us\n", meta->mstime_curr / 1000);
#endif
}

void OPUS_Destroy(sDecoderContext *psDecoderContext)
{
  sOpusPrivate *p = (sOpusPrivate *) psDecoderContext->pDecoderData;

#ifdef NONTHREADSAFE_PSEUDOSTACK
  if (global_stack)
  {
    user_free(global_stack);
    global_stack = 0;
  }
#endif

  f_close(&p->file);

  if (p->st)
    opus_decoder_destroy(p->st); //fixme -> move
  p->st = NULL;

  trace("Opus destroyed");
  print_user_heap_mallinfo();

  if (p->output)
  {
    user_free(p->output);
    p->output = 0;
  }

  trace("Opus buffer destroyed");
  print_user_heap_mallinfo();
}

//fixme fatfs semaphore when decoder is halted -> investigate

/* minogg stubs */

int minogg_impl_lseek(ogg_sync_state *oy, size_t pos)
{
  if (pos >= (size_t) minogg_impl_fsize(oy))
    return MINOGG_E_PARAM;

  configASSERT(oy->file);
  assert_param(f_lseek((FIL *) oy->file, pos) == FR_OK);

  return MINOGG_OK;
}

long minogg_impl_ftell(ogg_sync_state *oy)
{
  configASSERT(oy->file);
  return (long)(f_tell((FIL *) oy->file));
}

long minogg_impl_fsize(ogg_sync_state *oy)
{
  configASSERT(oy->file);
  return (long)(f_size((FIL *) oy->file));
}

int minogg_impl_fread(ogg_sync_state *oy, unsigned char *buffer, size_t size, size_t *read)
{
  configASSERT(oy->file);
  size = MIN(size, (size_t) minogg_impl_fsize(oy) - minogg_impl_ftell(oy));

  UINT nb_read;

  assert_param(f_read((FIL *) oy->file, buffer, size, &nb_read) == FR_OK);

  *read = nb_read;

  return MINOGG_OK;
}

void print_comments(sDecoderContext *psDecoderContext, char *comments, int length)
{
  sMetadata *meta = psDecoderContext->psMetadata;

  char *c = comments;
  int len, i, nb_fields, err = 0;

  if (length < (8 + 4 + 4))
  {
    fprintf(stderr, "Invalid/corrupted comments\n");
    return;
  }
  if (strncmp(c, "OpusTags", 8) != 0)
  {
    fprintf(stderr, "Invalid/corrupted comments\n");
    return;
  }
  c += 8;
  trace("Encoded with ");
  len = readint(c, 0);
  c += 4;
  if (len < 0 || len > (length - 16))
  {
    fprintf(stderr, "Invalid/corrupted comments\n");
    return;
  }
  err &= fwrite(c, 1, len, stderr) != (unsigned) len;
  c += len;
  fprintf(stderr, "\n");
  /*The -16 check above makes sure we can read this.*/
  nb_fields = readint(c, 0);
  c += 4;
  length -= 16 + len;
  if (nb_fields < 0 || nb_fields > (length >> 2))
  {
    fprintf(stderr, "Invalid/corrupted comments\n");
    return;
  }
  for (i = 0; i < nb_fields; i++)
  {
    if (length < 4)
    {
      fprintf(stderr, "Invalid/corrupted comments\n");
      return;
    }
    len = readint(c, 0);
    c += 4;
    length -= 4;
    if (len < 0 || len > length)
    {
      fprintf(stderr, "Invalid/corrupted comments\n");
      return;
    }

    if (!strncmp(c, "artist=", sizeof("artist")))
    {
      strncpy(
	  meta->artist,
	  c + sizeof("artist"),
	  MIN((int) sizeof(meta->artist),
	      MAX(len - (int) sizeof("artist"), (int) 0)));
    }
    else if (!strncmp(c, "title=", sizeof("title")))
    {
      strncpy(
	  meta->title,
	  c + sizeof("title"),
	  MIN((int) sizeof(meta->title),
	      MAX(len - (int) sizeof("title"), (int) 0)));
    }
    else
    {
      err &= fwrite(c, 1, len, stderr) != (unsigned) len;
    }

    c += len;
    length -= len;
  }
}

/*Process an Opus header and setup the opus decoder based on it.
  It takes several pointers for header values which are needed
  elsewhere in the code.*/
static OpusDecoder *process_header(sDecoderContext *psDecoderContext, ogg_packet *op, int *rate, int *channels,
        int *preskip, int quiet)
{
  int err;
  OpusDecoder *st;
  OpusHeader header;

#ifdef NONTHREADSAFE_PSEUDOSTACK
  global_stack = user_malloc(OPUS_STACK_SIZE);
#endif

  if (opus_header_parse(op->packet, op->bytes, &header) == 0)
  {
    trace("Cannot parse header\n");
    return NULL;
  }

  *channels = header.channels;

  if (!*rate)
    *rate = header.input_sample_rate;
  /*If the rate is unspecified we decode to 48000*/
  if (*rate == 0)
    *rate = 48000;
  if (*rate < 8000 || *rate > 192000)
  {
    trace("Warning: Crazy input_rate %d, decoding to 48000 instead.\n",*rate);
    *rate = 48000;
  }

  *preskip = header.preskip;
  st = opus_decoder_create(48000, header.channels, &err);
  if (err != OPUS_OK)
  {
    trace("Cannot create decoder: %s\n", opus_strerror(err));
    return NULL;
  }
  if (!st)
  {
    fprintf(stderr, "Decoder initialization failed: %s\n", opus_strerror(err));
    return NULL;
  }

  if (header.gain != 0)
  {
    /*Gain API added in a newer libopus version, if we don't have it
     we apply the gain ourselves. We also add in a user provided
     manual gain at the same time.*/
    int gainadj = (int) header.gain;
    err = opus_decoder_ctl(st, OPUS_SET_GAIN(gainadj));
    if (err != OPUS_OK)
    {
      fprintf(stderr, "Error setting gain: %s\n", opus_strerror(err));
      return NULL;
    }
  }

  if (!quiet)
  {
    trace("Decoding to %d Hz (%d channel%s)", *rate,
            *channels, *channels>1?"s":"");
    if (header.version != 1)
    {
      trace(", Header v%d",header.version);
      trace("\n");
    }
    if (header.gain != 0)
    {
      trace("Playback gain: %f dB\n", header.gain / 256.);
    }
  }

  return st;
}

//      to_write = (out_len < maxout ? out_len : maxout);
//
//#if !PROFILING
//      AudioBuffer_Typedef *buffer = AudioBuffer_TryGetProducer();
//
//      while (!(buffer = AudioBuffer_TryGetProducer()))
//        Audio_PeriodicKick();
//
//      bufs_temp++;
//
////      assert_param(buffer); //todo replace -> audio_file_assert
//      assert_param(AUDIO_BUFFER_MAX_SIZE / 2 /* stereo */>= to_write);
//      assert_param(to_write);
//      assert_param(channels == 1 || channels == 2);
//
//      buffer->size = to_write;
//      buffer->sampling_freq = rate;
//
//      if (channels == 1)
//      {
//        for (i = buffer->size - 1; i >= 0; i--)
//        {
//          buffer->data[2 * i] = buffer->data[i];
//          buffer->data[2 * i + 1] = buffer->data[i];
//        }
//        buffer->size *= 2;
//      }
//      else
//      {
//        memcpy(buffer->data, output, to_write * 2 * 2);
//      }
//
//      AudioBuffer_MoveProducer();
//#endif


//opus_int64 audio_write(opus_int16 *pcm, int channels, int frame_size,
//        int *skip, opus_int64 maxout)
//{
//  opus_int64 sampout = 0;
//  int ret, tmp_skip;
//  unsigned out_len;
//
//  opus_int16 *output;
//
//  maxout = maxout < 0 ? 0 : maxout;
//
//  if (skip)
//  {
//    tmp_skip = (*skip > frame_size) ? (int) frame_size : *skip;
//    *skip -= tmp_skip;
//  }
//  else
//  {
//    tmp_skip = 0;
//  }
//
//  output = pcm + channels * tmp_skip;
//  out_len = frame_size - tmp_skip;
//  frame_size = 0;
//
//  if ((maxout > 0))
//  {
//    //todo: mono -> stereo
//
//    ret = (out_len < maxout ? out_len : maxout);
//    int to_out = ret;
//
//    AudioBuffer_Typedef *buffer;
//    while (!(buffer = AudioBuffer_TryGetProducer()))
//      Audio_PeriodicKick();
//
//    int to_write = MIN(ret, AUDIO_BUFFER_MAX_SIZE / channels);
//
//    memcpy(buffer->data, output, to_write * 2 * 2);
//    buffer->sampling_freq = rate;
//    buffer->size = to_write * channels;
//
//    AudioBuffer_MoveProducer();
//
//    sampout += ret;
//    maxout -= ret;
//  }
//
//  return sampout;
//}
