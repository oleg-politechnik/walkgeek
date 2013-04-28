/**
 ******************************************************************************
 * @file    usbd_usr.c
 * @author  MCD Application Team
 * @version V1.1.0
 * @date    19-March-2012
 * @brief   This file includes the user application layer
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_usr.h"

typedef struct {
  uint8_t usbd_speed;
} USBD_State_Typedef;

/** @defgroup USBD_USR
 * @brief    This file includes the user application layer
 * @{
 */

/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBD_Usr_cb_TypeDef USR_cb =
{
        USBD_USR_Init, USBD_USR_DeviceReset, USBD_USR_DeviceConfigured,
        USBD_USR_DeviceSuspended, USBD_USR_DeviceResumed,
        USBD_USR_DeviceConnected, USBD_USR_DeviceDisconnected, };

USBD_State_Typedef USBD_State;

/**
 * @brief  Displays the message on LCD on device lib initialization
 * @param  None
 * @retval None
 */
void USBD_USR_Init(void)
{
}

/**
 * @brief  Displays the message on LCD on device reset event
 * @param  speed : device speed
 * @retval None
 */
void USBD_USR_DeviceReset(uint8_t speed)
{
  switch (speed)
  {
    case USB_OTG_SPEED_HIGH:
      break;

    case USB_OTG_SPEED_FULL:
      break;

    default:
      break;
  }
}

/**
 * @brief  Displays the message on LCD on device config event
 * @param  None
 * @retval Staus
 */
void USBD_USR_DeviceConfigured(void)
{
//  if (App_Mode() != APP_MODE_MSC)
//    App_SetMode(APP_MODE_MSC);
}
/**
 * @brief  Displays the message on LCD on device suspend event
 * @param  None
 * @retval None
 */
void USBD_USR_DeviceSuspended(void)
{
  //  App_SetMode(APP_MODE_PLAYER); //fixme
}

/**
 * @brief  Displays the message on LCD on device resume event
 * @param  None
 * @retval None
 */
void USBD_USR_DeviceResumed(void)
{
//  if (App_Mode() != APP_MODE_MSC)
//    App_SetMode(APP_MODE_MSC);
}

/**
 * @brief  USBD_USR_DeviceConnected
 *         Displays the message on LCD on device connection Event
 * @param  None
 * @retval Status
 */
void USBD_USR_DeviceConnected(void)
{
  //fixme
}

/**
 * @brief  USBD_USR_DeviceDisonnected
 *         Displays the message on LCD on device disconnection Event
 * @param  None
 * @retval Status
 */
void USBD_USR_DeviceDisconnected(void)
{
  //App_SetMode(APP_MODE_PLAYER); //fixme
  //NVIC_SystemReset();
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
