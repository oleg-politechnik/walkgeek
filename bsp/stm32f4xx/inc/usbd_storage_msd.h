/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USBD_STORAGE_MSD_H_
#define USBD_STORAGE_MSD_H_

/* Includes ------------------------------------------------------------------*/
#include "system.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
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

void STORAGE_DeInit(uint8_t lun);

extern u32 MSC_DataIn;
extern u32 MSC_DataOut;

#endif /* USBD_STORAGE_MSD_H_ */
