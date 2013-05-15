/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE Ogg CONTAINER SOURCE CODE.              *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2010             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: code raw packets into framed OggSquish stream and
           decode Ogg streams back into raw packets
 last mod: $Id: framing.c 18052 2011-08-04 17:57:02Z giles $

 note: The CRC code is directly derived from public domain code by
 Ross Williams (ross@guest.adelaide.edu.au).  See docs/framing.html
 for details.

 ********************************************************************/

#include <stdlib.h>
#include <string.h>
#include "ogg/ogg.h"
#include <stdio.h>

static int minogg_sync_refill(ogg_sync_state *oy)
{
  assert_param(oy->returned <= oy->fill);

  memmove(oy->data, oy->data + oy->returned, oy->fill - oy->returned);

  oy->fill -= oy->returned;
  oy->returned = 0;

  size_t read;

  if (minogg_impl_fsize(oy) - minogg_impl_ftell(oy) == 0)
    return MINOGG_END;

  int res = minogg_impl_fread(oy, oy->data + oy->fill, oy->storage - oy->fill,
      &read);

  if (res == MINOGG_OK)
  {
    oy->fill += read;
  }

  assert_param(oy->returned <= oy->fill);

  return res;
}

static int minogg_sync_fill_from(ogg_sync_state *oy, size_t abs_offset)
{
  int res;
  assert_param(abs_offset <= oy->fsize);

  res = minogg_impl_lseek(oy, abs_offset);
  if (res != MINOGG_OK)
  {
    return res;
  }

  oy->unsynced = 1;

  oy->fill = 0;
  oy->returned = 0;

  return minogg_sync_refill(oy);
}

static int minogg_sync_lseek(ogg_sync_state *oy, long delta)
{
  assert_param(delta >= 0);
  assert_param(oy->returned <= oy->fill);

  size_t offset_to_load = minogg_impl_ftell(oy) - oy->fill + oy->returned + delta;

  assert_param(offset_to_load < oy->fsize);

  if (delta + oy->returned >= oy->fill)
  {
    return minogg_sync_fill_from(oy, offset_to_load);
  }

  memmove(oy->data, oy->data + oy->returned, oy->fill - oy->returned);
  oy->returned -= delta;
  oy->fill -= delta;

  assert_param(oy->returned <= oy->fill);

  return MINOGG_OK;
}



/* A complete description of Ogg framing exists in docs/framing.html */

int ogg_page_version(const ogg_page *og){
  return((int)(og->header[4]));
}

int ogg_page_continued(const ogg_page *og){
  return((int)(og->header[5]&0x01));
}

int ogg_page_bos(const ogg_page *og){
  return((int)(og->header[5]&0x02));
}

int ogg_page_eos(const ogg_page *og){
  return((int)(og->header[5]&0x04));
}

ogg_int64_t ogg_page_granulepos(const ogg_page *og){
  unsigned char *page=((ogg_page *) og)->header;
  ogg_int64_t granulepos=page[13]&(0xff);
  granulepos= (granulepos<<8)|(page[12]&0xff);
  granulepos= (granulepos<<8)|(page[11]&0xff);
  granulepos= (granulepos<<8)|(page[10]&0xff);
  granulepos= (granulepos<<8)|(page[9]&0xff);
  granulepos= (granulepos<<8)|(page[8]&0xff);
  granulepos= (granulepos<<8)|(page[7]&0xff);
  granulepos= (granulepos<<8)|(page[6]&0xff);
  return(granulepos);
}

int ogg_page_serialno(const ogg_page *og){
  return(og->header[14] |
         (og->header[15]<<8) |
         (og->header[16]<<16) |
         (og->header[17]<<24));
}

long ogg_page_pageno(const ogg_page *og){
  return(og->header[18] |
         (og->header[19]<<8) |
         (og->header[20]<<16) |
         (og->header[21]<<24));
}



/* returns the number of packets that are completed on this page (if
   the leading packet is begun on a previous page, but ends on this
   page, it's counted */

/* NOTE:
   If a page consists of a packet begun on a previous page, and a new
   packet begun (but not completed) on this page, the return will be:
     ogg_page_packets(page)   ==1,
     ogg_page_continued(page) !=0

   If a page happens to be a single packet that was begun on a
   previous page, and spans to the next page (in the case of a three or
   more page packet), the return will be:
     ogg_page_packets(page)   ==0,
     ogg_page_continued(page) !=0
*/

int ogg_page_packets(const ogg_page *og){
  int i,n=og->header[26],count=0;
  for(i=0;i<n;i++)
    if(og->header[27+i]<255)count++;
  return(count);
}


#if 0
/* helper to initialize lookup for direct-table CRC (illustrative; we
   use the static init below) */

static ogg_uint32_t _ogg_crc_entry(unsigned long index){
  int           i;
  unsigned long r;

  r = index << 24;
  for (i=0; i<8; i++)
    if (r & 0x80000000UL)
      r = (r << 1) ^ 0x04c11db7; /* The same as the ethernet generator
                                    polynomial, although we use an
                                    unreflected alg and an init/final
                                    of 0, not 0xffffffff */
    else
       r<<=1;
 return (r & 0xffffffffUL);
}
#endif

/* init the encode/decode logical stream state */

int ogg_stream_init(ogg_stream_state *os,int serialno){
  if(os){

    ogg_sync_state oy = os->oy; //fixme
    memset(os,0,sizeof(*os));
    os->oy = oy;

//    os->body_storage=16*1024;
    os->lacing_storage=1024;

//    os->body_data=_ogg_malloc(os->body_storage*sizeof(*os->body_data));
    os->lacing_vals=_ogg_malloc(os->lacing_storage*sizeof(*os->lacing_vals));
    os->granule_vals=_ogg_malloc(os->lacing_storage*sizeof(*os->granule_vals));

    if(/*!os->body_data || */!os->lacing_vals || !os->granule_vals){
      ogg_stream_clear(os);
      return -1;
    }

    os->serialno=serialno;

    return(0);
  }
  return(-1);
}

/* async/delayed error detection for the ogg_stream_state */
int ogg_stream_check(ogg_stream_state *os){
  if(!os/* || !os->body_data*/) return -1;
  return 0;
}

/* _clear does not free os, only the non-flat storage within */
int ogg_stream_clear(ogg_stream_state *os){
  if(os){
    /*if(os->body_data)_ogg_free(os->body_data);*/
    if(os->lacing_vals)_ogg_free(os->lacing_vals);
    if(os->granule_vals)_ogg_free(os->granule_vals);

    memset(os,0,sizeof(*os));
  }
  return(0);
}

int ogg_stream_destroy(ogg_stream_state *os){
  if(os){
    ogg_stream_clear(os);
    _ogg_free(os);
  }
  return(0);
}

/* Helpers for ogg_stream_encode; this keeps the structure and
   what's happening fairly clear */

//static int _os_body_expand(ogg_stream_state *os,int needed){
//  if(os->body_storage<=os->body_fill+needed){
//    void *ret;
//    ret=_ogg_realloc(os->body_data,(os->body_storage+needed+1024)*
//                     sizeof(*os->body_data));
//    if(!ret){
//      ogg_stream_clear(os);
//      return -1;
//    }
//    os->body_storage+=(needed+1024);
//    os->body_data=ret;
//  }
//  return 0;
//}

static int _os_lacing_expand(ogg_stream_state *os,int needed){
  if(os->lacing_storage<=os->lacing_fill+needed){
    void *ret;
    ret=_ogg_realloc(os->lacing_vals,(os->lacing_storage+needed+32)*
                     sizeof(*os->lacing_vals));
    if(!ret){
      ogg_stream_clear(os);
      return -1;
    }
    os->lacing_vals=ret;
    ret=_ogg_realloc(os->granule_vals,(os->lacing_storage+needed+32)*
                     sizeof(*os->granule_vals));
    if(!ret){
      ogg_stream_clear(os);
      return -1;
    }
    os->granule_vals=ret;
    os->lacing_storage+=(needed+32);
  }
  return 0;
}

int ogg_stream_eos(ogg_stream_state *os){
  if(ogg_stream_check(os)) return 1;
  return os->e_o_s;
}

/* DECODING PRIMITIVES: packet streaming layer **********************/

/* This has two layers to place more of the multi-serialno and paging
   control in the application's hands.  First, we expose a data buffer
   using ogg_sync_buffer().  The app either copies into the
   buffer, or passes it directly to read(), etc.  We then call
   ogg_sync_wrote() to tell how many bytes we just added.

   Pages are returned (pointers into the buffer in ogg_sync_state)
   by ogg_sync_pageout().  The page is then submitted to
   ogg_stream_pagein() along with the appropriate
   ogg_stream_state* (ie, matching serialno).  We then get raw
   packets out calling ogg_stream_packetout() with a
   ogg_stream_state. */

/* initialize the struct to a known state */
int ogg_sync_init(ogg_sync_state *oy){
  if(oy){
    oy->storage = -1; /* used as a readiness flag */
    memset(oy,0,sizeof(*oy));
  }
  return(0);
}

/* clear non-flat storage within */
int ogg_sync_clear(ogg_sync_state *oy){
  if(oy){
    if(oy->data)_ogg_free(oy->data);
    memset(oy,0,sizeof(*oy));
  }
  return(0);
}

int ogg_sync_destroy(ogg_sync_state *oy){
  if(oy){
    ogg_sync_clear(oy);
    _ogg_free(oy);
  }
  return(0);
}

int ogg_sync_check(ogg_sync_state *oy){
  if(oy->storage<0) return -1;
  return 0;
}

//char *ogg_sync_buffer(ogg_sync_state *oy, long size){
//  if(ogg_sync_check(oy)) return NULL;
//
//  /* first, clear out any space that has been previously returned */
//  if(oy->returned){
//    oy->fill-=oy->returned;
//    if(oy->fill>0)
//      memmove(oy->data,oy->data+oy->returned,oy->fill);
//    oy->returned=0;
//  }
//
//  if(size>oy->storage-oy->fill){
//    /* We need to extend the internal buffer */
//    long newsize=size+oy->fill+4096; /* an extra page to be nice */
//    void *ret;
//
//    if(oy->data)
//      ret=_ogg_realloc(oy->data,newsize);
//    else
//      ret=_ogg_malloc(newsize);
//    if(!ret){
//      ogg_sync_clear(oy);
//      return NULL;
//    }
//    oy->data=ret;
//    oy->storage=newsize;
//  }
//
//  /* expose a segment at least as large as requested at the fill mark */
//  return((char *)oy->data+oy->fill);
//}

int ogg_sync_wrote(ogg_sync_state *oy, long bytes){
  if(ogg_sync_check(oy))return -1;
  if(oy->fill+bytes>oy->storage)return -1;
  oy->fill+=bytes;
  return(0);
}

/* sync the stream.  This is meant to be useful for finding page
   boundaries.

   return values for this:
  -n) skipped n bytes
   0) page not ready; more data (no bytes skipped)
   n) page synced at current location; page length n bytes

*/

long ogg_sync_pageseek(ogg_sync_state *oy, ogg_page *og)
{
  unsigned char *page = (unsigned char *) oy->data + oy->returned;
  unsigned char *next;
  long bytes = oy->fill - oy->returned;

  if (ogg_sync_check(oy))
    return 0;

  if (oy->headerbytes == 0)
  {
    int headerbytes, i;
    if (bytes < 27)
      return (0); /* not enough for a header */

    /* verify capture pattern */
    if (memcmp(page, "OggS", 4))
      goto sync_fail;

    headerbytes = page[26] + 27;
    if (bytes < headerbytes)
      return (0); /* not enough for header + seg table */

    /* count up body length in the segment table */

    for (i = 0; i < page[26]; i++)
      oy->bodybytes += page[27 + i];
    oy->headerbytes = headerbytes;
  }

  oy->nextpage_pos = minogg_impl_ftell(oy) - (oy->fill - oy->returned) +
      oy->bodybytes + oy->headerbytes;
  assert_param(oy->nextpage_pos > 0);

  /* yes, have a whole page all ready to go */
  {
    unsigned char *page = oy->data + oy->returned;
    long bytes;

    if (og)
    {
      assert_param(oy->headerbytes <= (int) sizeof(og->header));

      memcpy(og->header, page, oy->headerbytes);
      og->header_len = oy->headerbytes;
      og->body_len = oy->bodybytes;
    }

    oy->unsynced = 0;

    oy->returned += (bytes = oy->headerbytes);

    oy->headerbytes = 0;
    oy->bodybytes = 0;

    return (bytes);
  }

  sync_fail:
  oy->headerbytes = 0;
  oy->bodybytes = 0;

  /* search for possible capture */
  next = memchr(page + 1, 'O', bytes - 1);
  if (!next)
    next = oy->data + oy->fill;

  oy->returned = (int) (next - oy->data);
  return ((long) -(next - page));
}

/* sync the stream and get a page.  Keep trying until we find a page.
   Suppress 'sync errors' after reporting the first.

   return values:
   -1) recapture (hole in data)
    0) need more data
    1) page returned

   Returns pointers into buffered data; invalidated by next call to
   _stream, _clear, _init, or _buffer */

int ogg_sync_pageout(ogg_sync_state *oy, ogg_page *og){

  if(ogg_sync_check(oy))return 0;

  /* all we need to do is verify a page at the head of the stream
     buffer.  If it doesn't verify, we look for the next potential
     frame */

  for(;;){
    long ret=ogg_sync_pageseek(oy,og);
    if(ret>0){
      /* have a page */
      return(1);
    }
    if(ret==0){
      /* need more data */
      return(0);
    }

    /* head did not start a synced page... skipped some bytes */
    if(!oy->unsynced){
      oy->unsynced=1;
      return(-1);
    }

    /* loop. keep looking */
  }
}

/* add the incoming page to the stream state; we decompose the page
   into packet segments here as well. */

int ogg_stream_pagein(ogg_stream_state *os, ogg_page *og){
  unsigned char *header=og->header;
  /*fixme unsigned char *body=og->body;*/
//  long           bodysize=og->body_len;
  int            segptr=0;

  int version=ogg_page_version(og);
  int continued=ogg_page_continued(og);
  int bos=ogg_page_bos(og);
  int eos=ogg_page_eos(og);
  ogg_int64_t granulepos=ogg_page_granulepos(og);
  int serialno=ogg_page_serialno(og);
  long pageno=ogg_page_pageno(og);
  int segments=header[26];

  if(ogg_stream_check(os)) return -1;

  /* clean up 'returned data' */
  {
    long lr=os->lacing_returned;
//    long br=os->body_returned;

    /* body data */
//    if(br){
//      os->body_fill-=br;
//      if(os->body_fill)
//      {
//        exit(1);
//
//        //memmove(os->body_data,os->body_data+br,os->body_fill);
//      }
//      os->body_returned=0;
//    }

    if(lr){
      /* segment table */
      if(os->lacing_fill-lr){
        exit(1);

//        memmove(os->lacing_vals,os->lacing_vals+lr,
//                (os->lacing_fill-lr)*sizeof(*os->lacing_vals));
//        memmove(os->granule_vals,os->granule_vals+lr,
//                (os->lacing_fill-lr)*sizeof(*os->granule_vals));
      }
      os->lacing_fill-=lr;
      os->lacing_packet-=lr;
      os->lacing_returned=0;
    }
  }

  /* check the serial number */
  if(serialno!=os->serialno)return(-1);
  if(version>0)return(-1);

  if(_os_lacing_expand(os,segments+1)) return -1;

  /* are we in sequence? */
  if(pageno!=os->pageno){
    exit(1); //todo
//    int i;
//
//    /* unroll previous partial packet (if any) */
//    for(i=os->lacing_packet;i<os->lacing_fill;i++)
//      os->body_fill-=os->lacing_vals[i]&0xff;
//    os->lacing_fill=os->lacing_packet;
//
//    /* make a note of dropped data in segment table */
//    if(os->pageno!=-1){
//      os->lacing_vals[os->lacing_fill++]=0x400;
//      os->lacing_packet++;
//    }
  }

  /* are we a 'continued packet' page?  If so, we may need to skip
     some segments */
  if(continued){
    exit(1);
    //todo
//    if(os->lacing_fill<1 ||
//       os->lacing_vals[os->lacing_fill-1]==0x400){
//      bos=0;
//      for(;segptr<segments;segptr++){
//        int val=header[27+segptr];
//        body+=val;
//        bodysize-=val;
//        if(val<255){
//          segptr++;
//          break;
//        }
//      }
//    }
  }

  /*fixme if(bodysize){
    if(_os_body_expand(os,bodysize)) return -1;
    memcpy(os->body_data+os->body_fill,body,bodysize);
    os->body_fill+=bodysize;
  }*/

  {
    int saved=-1;
    while(segptr<segments){
      int val=header[27+segptr];
      os->lacing_vals[os->lacing_fill]=val;
      os->granule_vals[os->lacing_fill]=-1;

      if(bos){
        os->lacing_vals[os->lacing_fill]|=0x100;
        bos=0;
      }

      if(val<255)saved=os->lacing_fill;

      os->lacing_fill++;
      segptr++;

      if(val<255)os->lacing_packet=os->lacing_fill;
    }

    /* set the granulepos on the last granuleval of the last full packet */
    if(saved!=-1){
      os->granule_vals[saved]=granulepos;
    }

  }

  if(eos){
    os->e_o_s=1;
    if(os->lacing_fill>0)
      os->lacing_vals[os->lacing_fill-1]|=0x200;
  }

  os->pageno=pageno+1;

  return(0);
}

/* clear things to an initial state.  Good to call, eg, before seeking */
int ogg_sync_reset(ogg_sync_state *oy){
  if(ogg_sync_check(oy))return -1;

  oy->fill=0;
  oy->returned=0;
  oy->unsynced=0;
  oy->headerbytes=0;
  oy->bodybytes=0;
  return(0);
}

int ogg_stream_reset(ogg_stream_state *os){
  if(ogg_stream_check(os)) return -1;

//  os->body_fill=0;
//  os->body_returned=0;

  os->lacing_fill=0;
  os->lacing_packet=0;
  os->lacing_returned=0;

  os->e_o_s=0;
  os->b_o_s=0;
  os->pageno=-1;
  os->packetno=0;
  os->granulepos=0;

  return(0);
}

int ogg_stream_reset_serialno(ogg_stream_state *os,int serialno){
  if(ogg_stream_check(os)) return -1;
  ogg_stream_reset(os);
  os->serialno=serialno;
  return(0);
}

static int _packetout(ogg_stream_state *os,ogg_packet *op,int adv){

  /* The last part of decode. We have the stream broken into packet
     segments.  Now we need to group them into packets (or return the
     out of sync markers) */

  int ptr=os->lacing_returned;

  if(os->lacing_packet<=ptr)return(0);

  if(os->lacing_vals[ptr]&0x400){
    /* we need to tell the codec there's a gap; it might need to
       handle previous packet dependencies. */
    os->lacing_returned++;
    os->packetno++;
    return(-1);
  }

  if(!op && !adv)
    return(1); /* just using peek as an inexpensive way
                               to ask if there's a whole packet
                               waiting */

  /* Gather the whole packet. We'll have no holes or a partial packet */
  {
    int size=os->lacing_vals[ptr]&0xff;
    long bytes=size;
    int eos=os->lacing_vals[ptr]&0x200; /* last packet of the stream? */
    int bos=os->lacing_vals[ptr]&0x100; /* first packet of the stream? */

    while(size==255){
      int val=os->lacing_vals[++ptr];
      size=val&0xff;
      if(val&0x200)eos=0x200;
      bytes+=size;
    }

    if(op){
      op->e_o_s=eos;
      op->b_o_s=bos;
      op->packetno=os->packetno;
      op->granulepos=os->granule_vals[ptr];
      op->bytes=bytes;

      assert_param(op->bytes <= os->oy.storage); //fixme
      if (op->bytes > os->oy.fill - os->oy.returned)
      {
        minogg_sync_refill(&os->oy);
      }

      op->packet=os->oy.data + os->oy.returned;
    }

    if(adv){
//      os->body_returned+=bytes;
      os->lacing_returned=ptr+1;
      os->packetno++;

      os->oy.returned += bytes;
    }

    //printf("%ldb\n", bytes);
  }
  return(1);
}

int ogg_stream_packetout(ogg_stream_state *os,ogg_packet *op){
  if(ogg_stream_check(os)) return 0;
  return _packetout(os,op,1);
}

int ogg_stream_packetpeek(ogg_stream_state *os,ogg_packet *op){
  if(ogg_stream_check(os)) return 0;
  return _packetout(os,op,0);
}

void ogg_packet_clear(ogg_packet *op) {
  _ogg_free(op->packet);
  memset(op, 0, sizeof(*op));
}



int minogg_sync_init(ogg_sync_state *oy, size_t buffer_size, unsigned char *buffer)
{
  if (!buffer_size)
    return MINOGG_E_PARAM;

  if (!oy)
    return MINOGG_E_PARAM;

  if (!buffer)
  {
    buffer = _ogg_malloc(buffer_size);
    if (!buffer)
      return MINOGG_E_NO_MEM;
  }

  memset(oy, 0, sizeof(*oy));

  oy->data = buffer;
  oy->storage = buffer_size;

  oy->fsize = minogg_impl_fsize(oy);

  return MINOGG_OK;
}

int minogg_sync_pageout(ogg_sync_state *oy, ogg_page *og)
{
  int res = MINOGG_NEED_REFILL;

  /* all we need to do is verify a page at the head of the stream
     buffer.  If it doesn't verify, we look for the next potential
     frame */

  res = minogg_sync_fill_from(oy, oy->nextpage_pos); //todo if synced

  for (;res >= MINOGG_OK;)
  {
    long ret = ogg_sync_pageseek(oy, og);
    if (ret > 0)
    {
      /* have a page */
      return MINOGG_OK;
    }
    if (ret == 0)
    {
      /* need more data */
      res = minogg_sync_refill(oy);
      continue;
    }

    /* head did not start a synced page... skipped some bytes */
    if (oy->unsynced) //XXX was !oy->unsynced
    {
      /*discard data*/
      res = minogg_sync_lseek(oy, -ret);
    }

    /* loop. keep looking */
  }

  return res;
}
