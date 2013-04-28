/*
 * usbd_desc.h
 *
 *  Created on: 18 Jul 2012
 *      Author: User
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USBD_DESC_H_
#define USBD_DESC_H_

/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05
#define USB_SIZ_DEVICE_DESC                     18
#define USB_SIZ_STRING_LANGID                   4

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern  uint8_t USBD_DeviceDesc  [USB_SIZ_DEVICE_DESC];
extern  uint8_t USBD_StrDesc[USB_MAX_STR_DESC_SIZ];
extern  uint8_t USBD_OtherSpeedCfgDesc[USB_LEN_CFG_DESC];
extern  uint8_t USBD_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];
extern  uint8_t USBD_LangIDDesc[USB_SIZ_STRING_LANGID];

#endif /* USBD_DESC_H_ */
