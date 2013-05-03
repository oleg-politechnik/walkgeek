/*
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
#include "opus_decoder.h"
#include "mediafile.h"
#include "audio_buffer.h"
#include <ogg/ogg.h>
#include "opus_types.h"
#include <opus_multistream.h>

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct shapestate shapestate;
struct shapestate {
  float * b_buf;
  float * a_buf;
  int fs;
  int mute;
};

/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int c;
int option_index = 0;
//char *inFile, *outFile;
//FILE *fin, *fout=NULL, *frange=NULL;
float *output;
int frame_size=0;
OpusDecoder *st=NULL;
opus_int64 packet_count=0;
int total_links=0;
int stream_init;
int quiet = 0;
int forcewav = 0;
ogg_int64_t page_granule=0;
ogg_int64_t link_out=0;
ogg_sync_state oy;
ogg_page       og;
ogg_packet     op;
ogg_stream_state os;
int close_in=0;
int eos=0;
ogg_int64_t audio_size=0;
double last_coded_seconds=0;
float manual_gain=0;
int channels=-1;
int mapping_family;
int rate=0;
int wav_format=0;
int preskip=0;
int gran_offset=0;
int has_opus_stream=0;
ogg_int32_t opus_serialno;
int dither=1;
shapestate shapemem;
//SpeexResamplerState *resampler=NULL;
float gain=1;
int streams=0;
size_t last_spin=0;

#include "opusdec.c"

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void finalize()
{
  /*Did we make it to the end without recovering ANY opus logical streams?*/
//  if(!total_links)fprintf (stderr, "This doesn't look like a Opus file\n");
//
//  if (stream_init)
//     ogg_stream_clear(&os);
//  ogg_sync_clear(&oy);
//
//  if(shapemem.a_buf)free(shapemem.a_buf);
//  if(shapemem.b_buf)free(shapemem.b_buf);
//
//  if(output)free(output);

}

FuncResult Opus_TryFile(MediaFile_Typedef *mfile)
{
  stream_init = 0;

  output=0;
  shapemem.a_buf=0;
  shapemem.b_buf=0;
  shapemem.mute=960;
  shapemem.fs=0;

  /*Output to a file or playback?*/
    /*If playing to audio out, default the rate to 48000
      instead of the original rate. The original rate is
      only important for minimizing surprise about the rate
      of output files and preserving length, which aren't
      relevant for playback. Many audio devices sound
      better at 48kHz and not resampling also saves CPU.*/
    if(rate==0)rate=48000;

  /* .opus files use the Ogg container to provide framing and timekeeping.
   * http://tools.ietf.org/html/draft-terriberry-oggopus
   * The easiest way to decode the Ogg container is to use libogg, so
   *  thats what we do here.
   * Using libogg is fairly straight forward-- you take your stream of bytes
   *  and feed them to ogg_sync_ and it periodically returns Ogg pages, you
   *  check if the pages belong to the stream you're decoding then you give
   *  them to libogg and it gives you packets. You decode the packets. The
   *  pages also provide timing information.*/
  ogg_sync_init(&oy);

  return FUNC_SUCCESS;
}

FuncResult Opus_FastFileCheck(const char *fname)
{
  return MediaFile_CheckExtension(fname, "opus");
}

FuncResult Opus_Decode(MediaFile_Typedef *mfile, AudioBuffer_Typedef *audio_buf)
{
  char *data;
  int i, nb_read;
  /*Get the ogg buffer for writing*/
  data = ogg_sync_buffer(&oy, 200);

  /*Read bitstream from input file*/
  if (f_read(&mfile->file, &mfile->file_buf[mfile->bytes_in_buf],
          200, &nb_read) != FR_OK)
    return FUNC_ERROR;

  ogg_sync_wrote(&oy, nb_read);

  /*Loop for all complete pages we got (most likely only one)*/
  while (ogg_sync_pageout(&oy, &og)==1)
  {
     if (stream_init == 0) {
        ogg_stream_init(&os, ogg_page_serialno(&og));
        stream_init = 1;
     }
     if (ogg_page_serialno(&og) != os.serialno) {
        /* so all streams are read. */
        ogg_stream_reset_serialno(&os, ogg_page_serialno(&og));
     }
     /*Add page to the bitstream*/
     ogg_stream_pagein(&os, &og);
     page_granule = ogg_page_granulepos(&og);
     /*Extract all available packets*/
     while (ogg_stream_packetout(&os, &op) == 1)
     {
        /*OggOpus streams are identified by a magic string in the initial
          stream header.*/
        if (op.b_o_s && op.bytes>=8 && !memcmp(op.packet, "OpusHead", 8)) {
           if(!has_opus_stream)
           {
             opus_serialno = os.serialno;
             has_opus_stream = 1;
             link_out = 0;
             packet_count = 0;
             eos = 0;
             total_links++;
           } else {
             fprintf(stderr,"Warning: ignoring opus stream %" I64FORMAT "\n",(long long)os.serialno);
           }
        }
        if (!has_opus_stream || os.serialno != opus_serialno)
           break;
        /*If first packet in a logical stream, process the Opus header*/
        if (packet_count==0)
        {
           st = process_header(&op, &rate, &mapping_family, &channels, &preskip, &gain, manual_gain, &streams, wav_format, quiet);
           assert_param(st); /* FIXME */

           if(ogg_stream_packetout(&os, &op)!=0 || og.header[og.header_len-1]==255)
           {
              /*The format specifies that the initial header and tags packets are on their
                own pages. To aid implementors in discovering that their files are wrong
                we reject them explicitly here. In some player designs files like this would
                fail even without an explicit test.*/
              fprintf(stderr, "Extra packets on initial header page. Invalid stream.\n");
              assert_param(0); /* FIXME */
           }

           /*Remember how many samples at the front we were told to skip
             so that we can adjust the timestamp counting.*/
           gran_offset=preskip;

           /*Setup the memory for the dithered output*/
           if(!shapemem.a_buf)
           {
              shapemem.a_buf=calloc(channels,sizeof(float)*4);
              shapemem.b_buf=calloc(channels,sizeof(float)*4);
              shapemem.fs=rate;
           }
           if(!output)output=malloc(sizeof(float)*MAX_FRAME_SIZE*channels);

           /*Normal players should just play at 48000 or their maximum rate,
             as described in the OggOpus spec.  But for commandline tools
             like opusdec it can be desirable to exactly preserve the original
             sampling rate and duration, so we have a resampler here.*/
           assert_param(rate == 48000); /* FIXME */
//           if (rate != 48000)
//           {
//              int err;
//              resampler = speex_resampler_init(channels, 48000, rate, 5, &err);
//              if (err!=0)
//                 fprintf(stderr, "resampler error: %s\n", speex_resampler_strerror(err));
//              speex_resampler_skip_zeros(resampler);
//           }
           /*if(!fout)fout=out_file_open(outFile, &wav_format, rate, mapping_family, &channels);*/
        } else if (packet_count==1)
        {
           if (!quiet)
              print_comments((char*)op.packet, op.bytes);
           if(ogg_stream_packetout(&os, &op)!=0 || og.header[og.header_len-1]==255)
           {
              fprintf(stderr, "Extra packets on initial tags page. Invalid stream.\n");
              assert_param(0); /* FIXME */
           }
        } else {
           int ret;
           opus_int64 maxout;
           opus_int64 outsamp;

           /*End of stream condition*/
           if (op.e_o_s && os.serialno == opus_serialno)eos=1; /* don't care for anything except opus eos */

           /*Decode Opus packet*/
           ret = opus_decode_float(st, (unsigned char*)op.packet, op.bytes, output, MAX_FRAME_SIZE, 0);

           if(!quiet){
              /*Display a progress spinner while decoding.*/
              static const char spinner[]="|/-\\";
              double coded_seconds = (double)audio_size/(channels*rate*sizeof(short));
              if(coded_seconds>=last_coded_seconds+1){
                 fprintf(stderr,"\r[%c] %02d:%02d:%02d", spinner[last_spin&3],
                         (int)(coded_seconds/3600),(int)(coded_seconds/60)%60,
                         (int)(coded_seconds)%60);
                 fflush(stderr);
                 last_spin++;
                 last_coded_seconds=coded_seconds;
              }
           }

           /*If the decoder returned less than zero, we have an error.*/
           if (ret<0)
           {
              fprintf (stderr, "Decoding error: %s\n", opus_strerror(ret));
              break;
           }
           frame_size = ret;

           /*If we're collecting --save-range debugging data, collect it now.*/
//               if(frange!=NULL){
//                 OpusDecoder *od;
//                 opus_uint32 rngs[256];
//                 for(i=0;i<streams;i++){
//                   ret=opus_multistream_decoder_ctl(st,OPUS_MULTISTREAM_GET_DECODER_STATE(i,&od));
//                   ret=opus_decoder_ctl(od,OPUS_GET_FINAL_RANGE(&rngs[i]));
//                 }
//                 save_range(frange,frame_size*(48000/48000/*decoding_rate*/),op.packet,op.bytes,
//                            rngs,streams);
//               }

           /*Apply header gain, if we're not using an opus library new
             enough to do this internally.*/
           if (gain!=0){
             for (i=0;i<frame_size*channels;i++)
                output[i] *= gain;
           }

           /*This handles making sure that our output duration respects
             the final end-trim by not letting the output sample count
             get ahead of the granpos indicated value.*/
           maxout=((page_granule-gran_offset)*rate/48000)-link_out;
           outsamp=audio_write(output, channels, rate, frame_size, /*resampler, */&preskip, dither?&shapemem:0, 0>maxout?0:maxout);

           link_out+=outsamp;
           audio_size+=sizeof(short)*outsamp*channels;
        }
        packet_count++;
     }
     /*We're done, drain the resampler if we were using it.*/
//     if(eos && resampler)
//     {
//        float *zeros;
//        int drain;
//
//        zeros=(float *)calloc(100*channels,sizeof(float));
//        drain = speex_resampler_get_input_latency(resampler);
//        do {
//           opus_int64 outsamp;
//           int tmp = drain;
//           if (tmp > 100)
//              tmp = 100;
//           outsamp=audio_write(zeros, channels, tmp, fout, resampler, NULL, &shapemem, strlen(outFile)!=0, ((page_granule-gran_offset)*rate/48000)-link_out);
//           link_out+=outsamp;
//           audio_size+=sizeof(short)*outsamp*channels;
//           drain -= tmp;
//        } while (drain>0);
//        free(zeros);
//        //speex_resampler_destroy(resampler);
//        resampler=NULL;
//     }
     if(eos)
     {
        has_opus_stream=0;
        if(st)opus_decoder_destroy(st);
        st=NULL;
     }
  }

  if (mfile->state == MFS_EOF) /*XXX ???*/
  {
    trace("\rDecoding complete.        \n");
    finalize();
  }

  return FUNC_SUCCESS;
}

FuncResult Opus_Seek(MediaFile_Typedef *mfile, s32 msec)
{
  return FUNC_SUCCESS;
}

void Opus_Init()
{
//  if (!pOpusDecoder)
//  {
//    pOpusDecoder = OpusInitDecoder();
//    assert_param(pOpusDecoder);
//  }
}

void Opus_DeInit()
{
  /* todo: call me! */

//  if (pOpusDecoder)
//  {
//    OpusFreeDecoder(pOpusDecoder);
//    pOpusDecoder = 0;
//  }
}
