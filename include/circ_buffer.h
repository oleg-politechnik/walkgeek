/*
 * circ_buffer.h
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
#ifndef CIRC_BUFFER_H_
#define CIRC_BUFFER_H_

/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/*#define BUF_SIZE                5*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u16 data[BUF_SIZE];
  vu16 index_consumer;
  vu16 count;
} circular_buffer_t;

/* Exported macro ------------------------------------------------------------*/
#define free(buf) (BUF_SIZE - buf->count)
#define has_data_of(buf, len) (len <= buf->count)
#define has_space_for(buf, len) (len <= free(buf))
#define get_offset(buf, offset) ((buf->index_consumer + offset) % BUF_SIZE)
#define get_end(buf) get_offset(buf, buf->count)

#define EXIT_CHECK(buf) check_buffer(buf); //__enable_irq()

/* Exported functions ------------------------------------------------------- */
static inline void circular_fifo_init(circular_buffer_t *fifo)
{
  fifo->index_consumer = fifo->count = 0;
}

static __inline void check_buffer(circular_buffer_t *buf)
{
  //__disable_irq();
  if (buf->count >= BUF_SIZE)
    buf->count = BUF_SIZE - 1;

  if (buf->index_consumer >= BUF_SIZE)
    buf->index_consumer = 0;
}

//static __inline void circular_fifo_fwd_read_ptr(circular_buffer_t *buf,
//        u16 delta)
//{
//  check_buffer(buf);
//  //    STORING_CHECK;
//  if (has_data_of(buf, delta)) {
//    buf->index_consumer = get_offset(buf, delta);
//    buf->count -= delta;
//  }
//  EXIT_CHECK(buf);
//}
//
//static __inline void circular_fifo_fwd_write_ptr(circular_buffer_t *buf,
//        u16 delta)
//{
//  check_buffer(buf);
//  if (has_space_for(buf, delta)) {
//    buf->count += delta;
//  }
//  EXIT_CHECK(buf);
//}

//static __inline u16 *circular_fifo_get_write_ptr(circular_buffer_t *buf,
//        u16 length_req)
//{
//  u16 *ret = 0;
//  u16 abs_end;
//  check_buffer(buf);
//  if (has_space_for(buf, length_req)) {
//    abs_end = buf->index_consumer + buf->count;
//    if ((abs_end < BUF_SIZE) && ((abs_end + length_req) > BUF_SIZE)) {
//      circular_fifo_fwd_write_ptr(buf, BUF_SIZE - abs_end);
//      if (!has_space_for(buf, length_req)) {
//        EXIT_CHECK(buf);
//        return ret;
//      }
//    }
//    ret = (u16*) buf->data + get_end(buf);
//  }
//  EXIT_CHECK(buf);
//  return ret;
//}
//
//static __inline u16 *circular_fifo_get_read_ptr(circular_buffer_t *buf,
//        u16 length_req)
//{
//  u16 *ret = 0;
//  check_buffer(buf);
//  if (has_data_of(buf, length_req)) {
//    if (BUF_SIZE - buf->index_consumer < length_req) {
//      circular_fifo_fwd_read_ptr(buf, BUF_SIZE - buf->index_consumer);
//      if (!has_data_of(buf, length_req)) {
//        EXIT_CHECK(buf);
//        return ret;
//      }
//    }
//    ret = (u16*) buf->data + buf->index_consumer;
//  }
//  EXIT_CHECK(buf);
//  return ret;
//}

static __inline bool circular_fifo_push(circular_buffer_t *buf, u16 word)
{
  bool result = false;
  volatile u16 *data_p;
  check_buffer(buf);

  if (buf->count < BUF_SIZE) {
    data_p = buf->data + get_end(buf);
    *data_p = word;
    buf->count++;
    result = true;
  }

  EXIT_CHECK(buf);

  return result;
}

static __inline bool circular_fifo_pop(circular_buffer_t *buf,
        volatile u16 *word)
{
  bool result = false;
  check_buffer(buf);

  if (buf->count > 0) {
    *(word) = *(buf->data + buf->index_consumer);
    buf->index_consumer = (buf->index_consumer + 1) % BUF_SIZE;
    buf->count--;
    result = true;
  }

  EXIT_CHECK(buf);

  return result;
}

static __inline bool circular_fifo_is_full(circular_buffer_t *buf)
{
  bool ret;  check_buffer(buf);
  ret = (buf->count == BUF_SIZE);
  EXIT_CHECK(buf);
  return ret;
}

static __inline bool circular_fifo_is_empty(circular_buffer_t *buf)
{
  bool ret;
  check_buffer(buf);
  ret = (buf->count == 0);
  EXIT_CHECK(buf);
  return ret;
}

#endif /* CIRC_BUFFER_H_ */
