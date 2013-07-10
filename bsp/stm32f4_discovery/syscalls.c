/*
 * syscalls.c
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
#include <errno.h>
#include <assert.h>
#include "common.h"
#include <unistd.h>
#ifdef ENABLE_TRACE
# include "usbd_cdc_core.h"
#endif

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef ENABLE_TRACE
extern CDC_IF_Prop_TypeDef VCP_fops;
#endif

/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int _write(int file, char *buf, int nbytes)
{
//#ifndef ENABLE_TRACE
  return nbytes;
//#else
//  int tx_cnt = 0;
//
//  int room = APP_RX_DATA_SIZE - usbd_cdc_GetBufferCount();
//
//  int i;
//  int cr = 1;
//
//  /* We only handle stdout and stderr */
//  if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
//  {
//    errno = EBADF;
//    return -1;
//  }
//
//  while (nbytes && room && cr)
//  {
//    cr = 0;
//
//    for (i = 0; i < MIN(room - 1, nbytes); i++)
//    {
//      if (buf[i] == '\n')
//      {
//        cr = 1;
//
//        VCP_fops.pIf_DataTx(buf, i);
//        VCP_fops.pIf_DataTx("\r\n", 2);
//        i++;
//
//        nbytes -= i;
//        tx_cnt += i;
//        room -= i + 1;
//        buf += i;
//
//        break;
//      }
//    }
//  }
//
//  i = MIN(room, nbytes);
//  if (i && buf[i - 1] == '\n')
//  {
//    i--;
//  }
//  VCP_fops.pIf_DataTx(buf, i);
//  tx_cnt += i;
//
//  return tx_cnt;
//#endif
}
