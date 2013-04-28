/**
  ******************************************************************************
  * @file    usbd_conf.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    19-March-2012
  * @brief   USB Device configuration file
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
#ifndef __USBD_CONF_MSC__H__
#define __USBD_CONF_MSC__H__

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_CONF
  * @brief This file is the device library configuration file
  * @{
  */

/** @defgroup USBD_CONF_Exported_Defines
  * @{
  */

/* USB MSC ===================================================================*/

#define USBD_CFG_MAX_NUM           1
#define USBD_ITF_MAX_NUM           1
//#define USB_MAX_STR_DESC_SIZ       64

#define USBD_SELF_POWERED

/* Class Layer Parameter */

#define MSC_IN_EP                    0x81
#define MSC_OUT_EP                   0x01
#ifdef USE_USB_OTG_HS
#ifdef USE_ULPI_PHY
#define MSC_MAX_PACKET               512
#else
#define MSC_MAX_PACKET               64
#endif
#else  /*USE_USB_OTG_FS*/
#define MSC_MAX_PACKET                64
#endif


#define MSC_MEDIA_PACKET             4096

/**
  * @}
  */

/** @defgroup USB_CONF_Exported_Defines
  * @{
  */

/* USB AUDIO =================================================================*/

/* Audio frequency in Hz */
#ifndef EXTERNAL_CRYSTAL_25MHz
 #define USBD_AUDIO_FREQ                48000 /* Audio frequency in Hz.
                                                 It is advised to set standard frequencies >= 24KHz to get best quality
                                                 except for STM32F10 devices, when the HSE value is 25MHz, it is advised to
                                                 set audio frequencies reachable with this HSE value (refer to RM0008 for
                                                 more details). ie. it is advised to set 16KHz value in this case.
                                                 Note that maximum allowed audio frequency is 96KHz (this limitation is
                                                 due to the codec used on the Evaluation board. The STM32 I2S cell allows
                                                 to  reach 192KHz frequency).
                                                 @note
                                                    When modifying this value, make sure that the I2S PLL configuration allows
                                                    to get minimum error on audio frequency. This configuration is set in file
                                                    system_stm32f2xx.c or system_stm32f10x.c.*/
#else
 #define USBD_AUDIO_FREQ                48000  /* Audio frequency in Hz for STM32F10x devices family when 25MHz HSE value
                                                  is used. */
#endif /* EXTERNAL_CRYSTAL_25MHz */

//#define DEFAULT_VOLUME                  80    /* Default volume in % (Mute=0%, Max = 100%) in Logarithmic values.
//                                                 To get accurate volume variations, it is possible to use a logarithmic
//                                                 coversion table to convert from percentage to logarithmic law.
//                                                 In order to keep this example code simple, this conversion is not used.*/

/* Use this section to modify the number of supported interfaces and configurations.
   Note that if you modify these parameters, you have to modify the descriptors
   accordingly in usbd_audio_core.c file */
#define AUDIO_TOTAL_IF_NUM              0x02
#define USBD_CFG_MAX_NUM                1
#define USBD_ITF_MAX_NUM                1
#define USB_MAX_STR_DESC_SIZ            200

/**
  * @}
  */

/** @defgroup USB_AUDIO_Class_Layer_Parameter
  * @{
  */
#define AUDIO_OUT_EP                    0x01
#define AUDIO_IN_EP                     0x82
/**
  * @}
  */


/** @defgroup USB_CONF_Exported_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USB_CONF_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup USB_CONF_Exported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup USB_CONF_Exported_FunctionsPrototype
  * @{
  */
/**
  * @}
  */

#endif //__USBD_CONF__H__

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

