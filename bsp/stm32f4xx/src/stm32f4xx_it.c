/**
 ******************************************************************************
 * @file    Audio_playback_and_record/src/stm32f4xx_it.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    28-October-2011
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "system.h"
#include "usb_core.h"
#include "usb_hcd_int.h"
#include "usb_dcd_int.h"
#include "stm324xg_eval_sdio_sd.h"
#include "disp_1100.h"
#include "stm32f4xx_it.h"

extern uint32_t USBD_OTG_ISR_Handler(USB_OTG_CORE_HANDLE *pdev);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern USB_OTG_CORE_HANDLE USB_OTG_Core;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
  while(1)
    ;
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */

void HardFault_TopHandler(unsigned int * hardfault_args)
{
  // From Joseph Yiu, minor edits by FVH
  // hard fault handler in C,
  // with stack frame location as input parameter
  // called from HardFault_Handler in file xxx.s

  unsigned int stacked_r0;
  unsigned int stacked_r1;
  unsigned int stacked_r2;
  unsigned int stacked_r3;
  unsigned int stacked_r12;
  unsigned int stacked_lr;
  unsigned int stacked_pc;
  unsigned int stacked_psr;

  stacked_r0 = ((unsigned long) hardfault_args[0]);
  stacked_r1 = ((unsigned long) hardfault_args[1]);
  stacked_r2 = ((unsigned long) hardfault_args[2]);
  stacked_r3 = ((unsigned long) hardfault_args[3]);

  stacked_r12 = ((unsigned long) hardfault_args[4]);
  stacked_lr = ((unsigned long) hardfault_args[5]);
  stacked_pc = ((unsigned long) hardfault_args[6]);
  stacked_psr = ((unsigned long) hardfault_args[7]);

//  printf ("\n\n[Hard fault handler - all numbers in hex]\n");
//  printf ("R0 = %x\n", stacked_r0);
//  printf ("R1 = %x\n", stacked_r1);
//  printf ("R2 = %x\n", stacked_r2);
//  printf ("R3 = %x\n", stacked_r3);
//  printf ("R12 = %x\n", stacked_r12);
//  printf ("LR [R14] = %x  subroutine call return address\n", stacked_lr);
//  printf ("PC [R15] = %x  program counter\n", stacked_pc);
//  printf ("PSR = %x\n", stacked_psr);
//  printf ("BFAR = %x\n", (*((volatile unsigned long *)(0xE000ED38))));
//  printf ("CFSR = %x\n", (*((volatile unsigned long *)(0xE000ED28))));
//  printf ("HFSR = %x\n", (*((volatile unsigned long *)(0xE000ED2C))));
//  printf ("DFSR = %x\n", (*((volatile unsigned long *)(0xE000ED30))));
//  printf ("AFSR = %x\n", (*((volatile unsigned long *)(0xE000ED3C))));
//  printf ("SCB_SHCSR = %x\n", SCB->SHCSR);

  while (1);
}

void HardFault_Handler(void) __attribute__ ((naked));
void HardFault_Handler(void)
{
  asm volatile (
          "TST LR, #4 \n"
          "ITE EQ \n"
          "MRSEQ R0, MSP \n"
          "MRSNE R0, PSP \n"
          "B HardFault_TopHandler"
  );
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while(1)
      ;
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while(1)
      ;
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while(1)
      ;
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/
/**
 * @brief  This function handles External line 1 interrupt request.
 * @param  None
 * @retval None
 */
//void EXTI1_IRQHandler(void)
//{
//  /* Check the clic on the accelerometer to Pause/Resume Playing */
//  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
//  {
//    //        if (Count == 1) {
//    //            PauseResumeStatus = 1;
//    //            Count = 0;
//    //        } else {
//    //            PauseResumeStatus = 0;
//    //            Count = 1;
//    //        }
//    //        /* Clear the EXTI line 1 pending bit */
//    EXTI_ClearITPendingBit(EXTI_Line1);
//  }
//}

/* Private function prototypes -----------------------------------------------*/
#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
extern uint32_t USBD_OTG_EP1IN_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
extern uint32_t USBD_OTG_EP1OUT_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
#endif

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/******************************************************************************/
#ifdef HAS_SDIO
/**
 * @brief  This function handles SDIO global interrupt request.
 * @param  None
 * @retval None
 */
void SDIO_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
  SD_ProcessIRQSrc();
}

/**
 * @brief  This function handles DMA2 Stream3 or DMA2 Stream6 global interrupts
 *         requests.
 * @param  None
 * @retval None
 */
void SD_SDIO_DMA_IRQHANDLER(void)
{
  /* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
  SD_ProcessDMAIRQ();
}
#endif

#ifdef USE_USB_OTG_FS
/**
 * @brief  This function handles OTG_FS_WKUP Handler.
 * @param  None
 * @retval None
 */
void OTG_FS_WKUP_IRQHandler(void)
{
//  if (USB_OTG_Core.cfg.low_power)
//  {
//    /* Reset SLEEPDEEP and SLEEPONEXIT bits */
//
//    SCB->SCR
//            &= (u32) ~((u32) (SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
//
//    SystemInit();/* After wake-up from sleep mode, reconfigure the system clock */
//
//    USB_OTG_UngateClock(&USB_OTG_Core);
////    STM_EVAL_LEDInit(LED3);
////    STM_EVAL_LEDOn(LED3);
//  }
//  else
//  {
////    STM_EVAL_LEDInit(LED4);
////    STM_EVAL_LEDOn(LED4);
//  }
  EXTI_ClearITPendingBit(EXTI_Line18);
}

/**
 * @brief  This function handles OTG FS Handler.
 * @param  None
 * @retval None
 */
void OTG_FS_IRQHandler(void)
{
#ifdef USE_DEVICE_MODE
  USBD_OTG_ISR_Handler(&USB_OTG_Core);
#endif

#ifdef USE_HOST_MODE
  USBH_OTG_ISR_Handler(&USB_OTG_Core);
#endif
}
#endif /* USE_USB_OTG_FS */

#ifdef USE_HOST_MODE
/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
  USB_OTG_BSP_TimerIRQ();
}
#endif

#ifdef USE_USB_OTG_HS
/**
 * @brief  This function handles OTG_HS_WKUP Handler.
 * @param  None
 * @retval None
 */
void OTG_HS_WKUP_IRQHandler(void)
{
  if(USB_OTG_Core.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_Core);
  }
  EXTI_ClearITPendingBit(EXTI_Line20);
}

/**
 * @brief  This function handles OTG HS Handler.
 * @param  None
 * @retval None
 */
void OTG_HS_IRQHandler(void)
{
  USBD_OTG_ISR_Handler(&USB_OTG_Core);
}
#endif /* USE_USB_OTG_HS */

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
/**
 * @brief  This function handles EP1_IN Handler.
 * @param  None
 * @retval None
 */
void OTG_HS_EP1_IN_IRQHandler(void)
{
  USBD_OTG_EP1IN_ISR_Handler (&USB_OTG_Core);
}

/**
 * @brief  This function handles EP1_OUT Handler.
 * @param  None
 * @retval None
 */
void OTG_HS_EP1_OUT_IRQHandler(void)
{
  USBD_OTG_EP1OUT_ISR_Handler (&USB_OTG_Core);
}
#endif /* USB_OTG_HS_DEDICATED_EP1_ENABLED */

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
 {
 }*/

/**
 * @}
 */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
