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
/*#include "ff.h"*/
#include "common.h"
#include <unistd.h>
#include "usbd_cdc_core.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern CDC_IF_Prop_TypeDef VCP_fops;

/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define USER_MIN_FILENO 3
#define CNT_FILENO (USER_MIN_FILENO + ((_FS_SHARE) ? (_FS_SHARE) : 1))

/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//static FIL ofiles[CNT_FILENO - USER_MIN_FILENO];

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//static inline int fr_to_result(FRESULT fr)
//{
//  static char conv_table[] =
//  { 0, -EIO, /* (1) A hard error occured in the low level disk I/O layer */
//  -EINVAL, /* (2) Assertion failed */
//  -EAGAIN, /* (3) The physical drive cannot work */
//  -ENOENT, /* (4) Could not find the file */
//  -ENOENT, /* (5) Could not find the path */
//  -ENOENT, /* (6) The path name format is invalid */
//  -EACCES, /* (7) Acces denied due to prohibited access or directory full */
//  -EEXIST, /* (8) Acces denied due to prohibited access */
//  -ENXIO, /* (9) The file/directory object is invalid */
//  -EROFS, /* (10) The physical drive is write protected */
//  -ENODEV, /* (11) The logical drive number is invalid */
//  -ENOBUFS, /* (12) The volume has no work area */
//  -EFAULT, /* (13) There is no valid FAT volume */
//  -EINVAL, /* (14) The f_mkfs() aborted due to any parameter error */
//  -ETIME, /* (15) Could not get a grant to access the volume within defined period */
//  -ENFILE, /* (16) The operation is rejected according to the file shareing policy */
//  -ENOBUFS, /* (17) LFN working buffer could not be allocated */
//  -EMFILE, /* (18) Number of open files > _FS_SHARE */
//  -EINVAL, /* (19) Given parameter is invalid */
//  };
//
//  assert_param(fr < SIZE_OF(conv_table));
//
//  if (!fr)
//  {
//    return 0;
//  }
//
//  errno = conv_table[fr];
//  return -1;
//}

int _open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
//  trace("name: %s flags: 0x%08x mode: 0x%08x\r\n", file, flags, mode);

//#define FA_READ       0x01
//#define FA_OPEN_EXISTING  0x00
//#define FA__ERROR     0x80
//
//#if !_FS_READONLY
//#define FA_WRITE      0x02
//#define FA_CREATE_NEW   0x04
//#define FA_CREATE_ALWAYS  0x08
//#define FA_OPEN_ALWAYS    0x10
//#define FA__WRITTEN     0x20
//#define FA__DIRTY     0x40
//#endif
//
//  //XXX std* files?
//  int f_ix;
//  for (f_ix = 0; f_ix < SIZE_OF(ofiles); f_ix++)
//  {
//    if (!ofiles[f_ix].fs) /* closed */
//    {
//      return fr_to_result(f_open(&ofiles[f_ix], name, ));
//    }
//  }
//
//  return -EMFILE;
//
//
//
  errno = -ENOSYS;
  return -1; /* Always fails */

}

int _lseek(int file, int offset, int whence)
{
  if ((STDOUT_FILENO == file) || (STDERR_FILENO == file))
  {
    return 0;
  }
//  if ((STDIN_FILENO == file) || (file >= CNT_FILENO))
  {
    errno = -EBADF;
    return -1;
  }
//
//  FIL *f = &ofiles[file];
//  DWORD position;
//
//  switch (whence)
//  {
//    case SEEK_SET: /* The offset is set to offset bytes. */
//      position = offset;
//      break;
//
//    case SEEK_CUR: /* The offset is set to its current location plus
//     * offset bytes. */
//
//      position = offset + f_tell(f);
//      break;
//
//    case SEEK_END: /* The offset is set to the size of the file plus
//     * offset bytes. */
//
//      position = offset + f_size(f);
//      break;
//
//    default:
//      return -EINVAL;
//  }
//
//  return /*fr_to_errno(f_lseek(f, position))*/-1;
}

//EFBIG
//ENOSPC

int _write(int file, char *buf, int nbytes)
{
  int i;

  /* We only handle stdout and stderr */
  if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
  {
    errno = EBADF;
    return -1;
  }

  nbytes = MIN(APP_RX_DATA_SIZE - usbd_cdc_GetBufferCount(), nbytes);

  VCP_fops.pIf_DataTx(buf, nbytes);

  return nbytes;
}
