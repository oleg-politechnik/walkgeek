/*
 * diskio_sdio.c
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

/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* by grqd_xp                                                            */
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
#include <string.h>
#include "diskio.h"
#include <stdint.h>
#include <stdio.h>
#include "integer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "system.h"

int fsd;

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define SECTOR_SIZE 512

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define ATA		0
#define MMC   0
#define USB		2

/*-----------------------------------------------------------------------*/
/* Inicializes a Drive                                                    */

DSTATUS disk_initialize(BYTE drv) /* Physical drive number (0..) */
{
//  SD_CARD_FILE

  fsd = open(SD_CARD_FILE, O_RDWR);

  assert_param(fsd != -1);

  return 0;
}

/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status(BYTE drv) /* Physical drive nmuber (0..) */
{
  return 0;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
DRESULT disk_write(BYTE drv, /* Physical drive nmuber (0..) */
const BYTE *buff, /* Data to be written */
DWORD sector, /* Sector address (LBA) */
BYTE count /* Number of sectors to write (1..255) */
)
{
  if (drv != MMC)
    return RES_PARERR;

  if (!count)
    return RES_PARERR;

  if (disk_status(drv) & STA_NOINIT)
    return RES_NOTRDY;

  assert_param(lseek(fsd, sector * SECTOR_SIZE, SEEK_SET) >= 0);
  assert_param(write(fsd, buff, count * SECTOR_SIZE) == count * SECTOR_SIZE);

  return RES_OK;
}
#endif /* _READONLY */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/

DWORD get_fattime()
{
  /* Pack date and time into a DWORD variable */
  return ((DWORD) (2011 - 1980) << 25) | ((DWORD) 1 << 21) | ((DWORD) 1 << 16)
          | ((DWORD) 12 << 11) | ((DWORD) 03 << 5) | ((DWORD) 25 >> 1);
}

/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read(BYTE drv, /* Physical drive nmuber (0..) */
BYTE *buff, /* Data buffer to store read data */
DWORD sector, /* Sector address (LBA) */
BYTE count /* Number of sectors to read (1..255) */
)
{
  if (drv != MMC)
    return RES_PARERR;

  if (drv || !count)
    return RES_PARERR;

  if (disk_status(drv) & STA_NOINIT)
    return RES_NOTRDY;

  assert_param(lseek(fsd, sector * SECTOR_SIZE, SEEK_SET) >= 0);
  assert_param(read(fsd, buff, count * SECTOR_SIZE) == count * SECTOR_SIZE);

  return RES_OK;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

#if _USE_IOCTL != 0
DRESULT disk_ioctl(BYTE drv, /* Physical drive number (0) */
BYTE ctrl, /* Control code */
void *buff) /* Buffer to send/receive control data */
{
  DRESULT res = RES_OK;

  struct stat sb;

  if (drv != MMC)
    return RES_PARERR;

  if (disk_status(drv) & STA_NOINIT)
    return RES_NOTRDY;

  switch (ctrl)
  {
    case CTRL_SYNC: /* Make sure that no pending write process */
      res = RES_OK;
      break;

    case GET_SECTOR_COUNT: /* Get number of sectors on the disk (DWORD) */
      assert_param(!stat(SD_CARD_FILE, &sb));
      *(DWORD*) buff = (DWORD) sb.st_size;
      res = RES_OK;
      break;

    case GET_SECTOR_SIZE: /* Get R/W sector size (WORD) */
      //fixme
      *(WORD*) buff = 512;
      //*(WORD*)buff = SDCardInfo.CardBlockSize;
      res = RES_OK;
      break;

    case GET_BLOCK_SIZE: /* Get erase block size in unit of sector (DWORD) */
      //fixme
      *(DWORD*) buff = 512;

      break;

    default:
      res = RES_PARERR;
  }

  return res;
}
#endif /* _USE_IOCTL != 0 */
