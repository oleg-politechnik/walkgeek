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
#include "stm324xg_eval_sdio_sd.h"
#include "integer.h"
#include "usbd_storage_msd.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define SECTOR_SIZE 512

extern SD_CardInfo SDCardInfo;

u32 buff2[4096];//16384/4

int8_t STORAGE_Init(uint8_t lun);
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num,
        uint32_t *block_size);
int8_t STORAGE_IsReady(uint8_t lun);
int8_t STORAGE_IsWriteProtected(uint8_t lun);
int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
        uint16_t blk_len);
int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr,
        uint16_t blk_len);
int8_t STORAGE_GetMaxLun(void);

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define ATA		0
#define MMC   0
#define USB		2

/*-----------------------------------------------------------------------*/
/* Inicializes a Drive                                                    */

DSTATUS disk_initialize(BYTE drv) /* Physical drive number (0..) */
{
  DSTATUS stat = STA_NOINIT;

  if (drv != MMC)
    return STA_NODISK;

  if (STORAGE_Init(MMC) == 0)
    stat &= ~STA_NOINIT;

  return stat;
}

/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status(BYTE drv) /* Physical drive nmuber (0..) */
{
  DSTATUS stat = 0;

  if (drv != MMC)
    return STA_NODISK;

  if (STORAGE_IsReady(MMC) != 0)
    stat = STA_NOINIT;

  return stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

//DRESULT disk_read(BYTE drv, /* Physical drive number (0) */
//BYTE *buff, /* Pointer to the data buffer to store read data */
//DWORD sector, /* Start sector number (LBA) */
//BYTE count) /* Sector count (1..255) */
//{
//  if (drv != MMC)
//    return RES_PARERR;
//
//  if (drv || !count)
//    return RES_PARERR;
//
//  if (disk_status(drv) & STA_NOINIT)
//    return RES_NOTRDY;
//
//  if (STORAGE_Read(MMC, buff, sector, count) != 0)
//    return RES_ERROR;
//
//  return RES_OK;
//}

static __IO SD_Error SDStatus;
//
//DRESULT disk_read(BYTE drv, /* Physical drive number (0) */
//BYTE *buff, /* Pointer to the data buffer to store read data */
//DWORD sector, /* Start sector number (LBA) */
//BYTE count /* Number of sectors to read (1..128) */
//)
//{
////  if (drv != MMC)
////    return RES_PARERR;
////
////  if (drv || !count)
////    return RES_PARERR;
////
////  if (disk_status(drv) & STA_NOINIT)
////    return RES_NOTRDY;
//
//  //      printf( "disk_read. drv:%d, sector:%d, count:%d\n", (int)drv, (int)sector, (int)count );
//  //TODO обратить внимание на работу с картой SDHC
//  if (count == 1) // read only 1 sector of card
//  {
//    SDStatus = SD_ReadBlock(buff, sector * 512, SD_BLOCK_SIZE);
//    SDStatus = SD_WaitReadOperation();
//    while (SD_GetStatus() != SD_TRANSFER_OK)
//      ;
//  }
//
//  if (count > 1) // read multiblock;
//  {
//    SDStatus = SD_ReadMultiBlocks(buff, sector * 512, SD_BLOCK_SIZE, count);
//    SDStatus = SD_WaitReadOperation();
//    while (SD_GetStatus() != SD_TRANSFER_OK) /*fixme CPU idle*/
//      ;
//  }
//
//  if (SDStatus == SD_OK)
//    return RES_OK;
//  else
//    return RES_ERROR;
//}

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

//  if (STORAGE_Write(drv, (u8*) buff, sector << 9, count) != 0)
//    return RES_ERROR;
  memcpy(buff2, buff, SECTOR_SIZE);

  SD_WriteMultiBlocks((u8*) buff2, sector << 9, SECTOR_SIZE, count);
  SD_WaitWriteOperation();
  while (SD_GetStatus() != SD_TRANSFER_OK) /*fixme CPU idle*/
    ;

  return RES_OK;
}
#endif /* _READONLY */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

//DSTATUS disk_status(BYTE drv /* Physical drive number (0) */
//)
//{
//  __asm__ volatile("nop");
//  //      printf( "disk_status. drv:%d\n", (int)drv );
//  return Stat;
//}
//
//DSTATUS disk_initialize(BYTE drv /* Physical drive number (0) */
//)
//{
//  __asm__ volatile("nop");
//  //      printf( "disk_initialize. drv:%d\n", (int)drv );
//  Stat &= ~STA_NOINIT;
//  return Stat;
//}

/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/

//DRESULT disk_ioctl (
//        BYTE drv,               /* Physical drive number (0) */
//        BYTE ctrl,              /* Control command code */
//        void *buff              /* Pointer to the conrtol data */
//)
//{
//        __asm__ volatile("nop");
////      printf( "disk_ioctl. drv:%d, ctrl:%d\n", (int)drv, (int)ctrl );
//        return RES_OK;
//}

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
  SDTransferState state;

  if (drv != MMC)
    return RES_PARERR;

  if (drv || !count)
    return RES_PARERR;

  if (disk_status(drv) & STA_NOINIT)
    return RES_NOTRDY;

  if (count == 1)
  {
    SD_ReadBlock((u8*) buff2, sector << 9, SECTOR_SIZE);

    SD_WaitReadOperation();
    while ((state = SD_GetStatus()) == SD_TRANSFER_BUSY) /*fixme CPU idle*/
      ;

    memcpy(buff, buff2, SECTOR_SIZE);

    if (state == SD_TRANSFER_ERROR)
    {
      return RES_ERROR;
    }
  }
  else
  {
    assert_param(SECTOR_SIZE*count<=sizeof(buff2));

    SD_ReadMultiBlocks((u8*) buff2, sector << 9, SECTOR_SIZE, count);
    SD_WaitReadOperation();
    while ((state = SD_GetStatus()) == SD_TRANSFER_BUSY) /*fixme CPU idle*/
      ;

    memcpy(buff, buff2, SECTOR_SIZE*count);

    if (state == SD_TRANSFER_ERROR)
    {
      return RES_ERROR;
    }
  }
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

  if (drv != MMC)
    return RES_PARERR;

  if (disk_status(drv) & STA_NOINIT)
    return RES_NOTRDY;

  switch (ctrl)
  {
    case CTRL_SYNC: /* Make sure that no pending write process */
      //fixme
      //    while (SDIO_GetResponse(SDIO_RESP1) == 0)
      //      ;//(SD_WaitReady
      //        {
      res = RES_OK;
      //        }
      //        else
      //        {
      //            res = RES_ERROR;
      //        }
      res = RES_OK;
      break;

    case GET_SECTOR_COUNT: /* Get number of sectors on the disk (DWORD) */
      //  if((SDCardInfo.CardType == SDIO_STD_CAPACITY_SD_CARD_V1_1) || (SDCardInfo.CardType == SDIO_STD_CAPACITY_SD_CARD_V2_0))
      //  *(DWORD*)buff = SDCardInfo.CardCapacity >> 9;
      //  else if(SDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
      //  *(DWORD*)buff = (SDCardInfo.SD_csd.DeviceSize+1)*1024;
      //  //else;////SD_GetCapacity();

      *(DWORD*) buff = (DWORD) SDCardInfo.CardCapacity;
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
