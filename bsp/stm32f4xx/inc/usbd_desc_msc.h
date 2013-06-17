/**
  ******************************************************************************
  * @file    usbd_desc.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    19-March-2012
  * @brief   header file for the usbd_desc.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef USBD_DESC_MSC_H_
#define USBD_DESC_MSC_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"
#include "usbd_desc.h"

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USB_DESC
  * @brief general defines for the usb device library file
  * @{
  */

/** @defgroup USB_DESC_Exported_Defines
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_DESC_Exported_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup USBD_DESC_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup USBD_DESC_Exported_Variables
  * @{
  */
extern  USBD_DEVICE USR_MSC_desc;
/**
  * @}
  */

/** @defgroup USBD_DESC_Exported_FunctionsPrototype
  * @{
  */


uint8_t *     USBD_MSC_DeviceDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_MSC_LangIDStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_MSC_ManufacturerStrDescriptor ( uint8_t speed , uint16_t *length);
uint8_t *     USBD_MSC_ProductStrDescriptor ( uint8_t speed , uint16_t *length);
uint8_t *     USBD_MSC_SerialStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_MSC_ConfigStrDescriptor( uint8_t speed , uint16_t *length);
uint8_t *     USBD_MSC_InterfaceStrDescriptor( uint8_t speed , uint16_t *length);

#ifdef USB_SUPPORT_USER_STRING_DESC
uint8_t *     USBD_MSC_USRStringDesc (uint8_t speed, uint8_t idx , uint16_t *length);
#endif /* USB_SUPPORT_USER_STRING_DESC */

/**
  * @}
  */

#endif /* USBD_DESC_MSC_H_ */

/**
  * @}
  */

/**
* @}
*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
