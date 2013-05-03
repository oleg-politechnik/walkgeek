/*
 * bsp_config.h
 *
 * Copyright (c) 2012, Oleg Tsaregorodtsev
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

/* Define to prevent recursive inclusion ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef BSP_CONFIG_H_
#define BSP_CONFIG_H_

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "stm32f4_discovery_audio_codec.h"

/* Exported defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define PWR_EN_GPIO                 GPIOB
#define PWR_EN_AHB1_CLK             RCC_AHB1Periph_GPIOB
#define PWR_EN_PIN                  GPIO_Pin_2

/* disp_1100 -----------------------------------------------------------------*/
#define DISP_GPIO                   GPIOA
#define DISP_GPIO_CLK               RCC_AHB1Periph_GPIOA

#define DISP_PinSrc_RST             GPIO_PinSource2
#define DISP_PinSrc_BKL             GPIO_PinSource3
#define DISP_Pin_RST                GPIO_Pin_2
#define DISP_Pin_BKL                GPIO_Pin_3
#define DISP_Pin_CS                 GPIO_Pin_4

#define DISP_Pin_SCK                GPIO_Pin_5
#define DISP_Pin_MOSI               GPIO_Pin_7
#define DISP_PinSrc_SCK             GPIO_PinSource5
#define DISP_PinSrc_MOSI            GPIO_PinSource7

#define DISP_SPI                    SPI1
#define DISP_SPI_IRQ                SPI1_IRQn
#define DISP_GPIO_AF_SPI            GPIO_AF_SPI1
#define DISP_RCC_APB2Periph_SPI     RCC_APB2Periph_SPI1

#define Disp_IRQHandler             SPI1_IRQHandler

/* keyboard ------------------------------------------------------------------*/
#define KEY_DEBOUNCE_MS             20

typedef struct {
  GPIO_TypeDef* GPIOx;
  uint8_t GPIO_PinSourcex;
  uint16_t RCC_AHB1Periph_GPIOx;
} KeyPin_Typedef;

#include "keypad.h"

/* Keep this in sync with KEY_Typedef */

#define KEY_PIN_TYPEDEFS \
  { /* KEY_PPP      */ GPIOA, GPIO_PinSource0,  RCC_AHB1Periph_GPIOA}, \
  { /* KEY_C        */ GPIOC, GPIO_PinSource15, RCC_AHB1Periph_GPIOC}, \
  { /* KEY_SEL      */ GPIOD, GPIO_PinSource13, RCC_AHB1Periph_GPIOD}, \
  { /* KEY_UP       */ GPIOE, GPIO_PinSource8,  RCC_AHB1Periph_GPIOE}, \
  { /* KEY_DOWN     */ GPIOE, GPIO_PinSource14, RCC_AHB1Periph_GPIOE}, \
  { /* KEY_1        */ GPIOD, GPIO_PinSource11, RCC_AHB1Periph_GPIOD}, \
  { /* KEY_2        */ GPIOD, GPIO_PinSource10, RCC_AHB1Periph_GPIOD}, \
  { /* KEY_3        */ GPIOE, GPIO_PinSource10, RCC_AHB1Periph_GPIOE}, \
  { /* KEY_4        */ GPIOA, GPIO_PinSource15, RCC_AHB1Periph_GPIOA}, \
  { /* KEY_5        */ GPIOE, GPIO_PinSource15, RCC_AHB1Periph_GPIOE}, \
  { /* KEY_6        */ GPIOE, GPIO_PinSource11, RCC_AHB1Periph_GPIOE}, \
  { /* KEY_7        */ GPIOE, GPIO_PinSource12, RCC_AHB1Periph_GPIOE}, \
  { /* KEY_8        */ GPIOD, GPIO_PinSource15, RCC_AHB1Periph_GPIOD}, \
  { /* KEY_9        */ GPIOE, GPIO_PinSource9,  RCC_AHB1Periph_GPIOE}, \
  { /* KEY_ASTERICK */ GPIOE, GPIO_PinSource13, RCC_AHB1Periph_GPIOE}, \
  { /* KEY_0        */ GPIOA, GPIO_PinSource8,  RCC_AHB1Periph_GPIOA}, \
  { /* KEY_POUND    */ GPIOE, GPIO_PinSource7,  RCC_AHB1Periph_GPIOE}

/* Vibrator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define VIBRATOR_RCC_AHB1Periph_GPIO  RCC_AHB1Periph_GPIOB
#define VIBRATOR_PIN                  GPIO_Pin_4
#define VIBRATOR_GPIO                 GPIOB

/* ADC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define ADC_BAT_GPIO                  GPIOB
#define ADC_BAT_RCC_AHB1Periph_GPIO   RCC_AHB1Periph_GPIOB
#define ADC_BAT_PIN                   GPIO_Pin_0
#define ADC_BAT_CHANNEL               ADC_Channel_8

#define ADC_CHRG_GPIO                 GPIOB
#define ADC_CHRG_RCC_AHB1Periph_GPIO  RCC_AHB1Periph_GPIOB
#define ADC_CHRG_PIN                  GPIO_Pin_1
#define ADC_CHRG_CHANNEL              ADC_Channel_9

#define ADC_BAT_CHRG_ADC                 ADC1
#define ADC_BAT_CHRG_RCC_APB2Periph_ADC  RCC_APB2Periph_ADC1





/* SD ------------------------------------------------------------------------*/
#define SDIO_IRQ_PRIORITY       1
#define SDIO_IRQ_SUBPRIORITY    0

/*------------------------------------
             CONFIGURATION: Audio Codec Driver Configuration parameters
                                      ----------------------------------------*/
/* Audio Transfer mode (I2S Interrupt) */
//#define I2S_INTERRUPT                 /* Uncomment this line to enable audio transfert with I2S interrupt*/

/* Audio Transfer mode (DMA, Interrupt or Polling) */
#define AUDIO_MAL_MODE_NORMAL         /* Uncomment this line to enable the audio
                                         Transfer using DMA */
#define AUDIO_MAL_MODE_CIRCULAR  /* Uncomment this line to enable the audio
                                         Transfer using DMA */

/* For the DMA modes select the interrupt that will be used */
#define AUDIO_MAL_DMA_IT_TC_EN        /* Uncomment this line to enable DMA Transfer Complete interrupt */
/*#define AUDIO_MAL_DMA_IT_HT_EN*/   /* Uncomment this line to enable DMA Half Transfer Complete interrupt */
/* #define AUDIO_MAL_DMA_IT_TE_EN */  /* Uncomment this line to enable DMA Transfer Error interrupt */

/* Select the interrupt preemption priority and subpriority for the DMA interrupt */
#define EVAL_AUDIO_IRQ_PREPRIO           0   /* Select the preemption priority level(0 is the highest) */
#define EVAL_AUDIO_IRQ_SUBRIO            0   /* Select the sub-priority level (0 is the highest) */

/* Uncomment the following line to use the default Codec_TIMEOUT_UserCallback()
   function implemented in stm32f4_discovery_audio_codec.c file.
   Codec_TIMEOUT_UserCallback() function is called whenever a timeout condition
   occurs during communication (waiting on an event that doesn't occur, bus
   errors, busy devices ...). */
/* #define USE_DEFAULT_TIMEOUT_CALLBACK */

/* Enable this define to use the I2S DMA for writing into DAC register */
//#define DAC_USE_I2S_DMA
/*----------------------------------------------------------------------------*/

/*------------------------------------
                    OPTIONAL Configuration defines parameters
                                      ----------------------------------------*/
/* I2C clock speed configuration (in Hz)
  WARNING:
   Make sure that this define is not already declared in other files (ie.
  stm322xg_eval.h file). It can be used in parallel by other modules. */
#ifndef I2C_SPEED
 #define I2C_SPEED                        100000
#endif /* I2C_SPEED */

/* Uncomment defines below to select standard for audio communication between
  Codec and I2S peripheral */
#define I2S_STANDARD_PHILLIPS
/* #define I2S_STANDARD_MSB */
/* #define I2S_STANDARD_LSB */

/* Uncomment the defines below to select if the Master clock mode should be
  enabled or not */
#define CODEC_MCLK_ENABLED
/* #deine CODEC_MCLK_DISABLED */

/* Uncomment this line to enable verifying data sent to codec after each write
  operation */
//#define VERIFY_WRITTENDATA

#define PLLI2S_N   258
#define PLLI2S_R   3
/*----------------------------------------------------------------------------*/

/*-----------------------------------
                    Hardware Configuration defines parameters
                                     -----------------------------------------*/
/* Audio Reset Pin definition */
#define AUDIO_RESET_GPIO_CLK           RCC_AHB1Periph_GPIOC
#define AUDIO_RESET_PIN                GPIO_Pin_7
#define AUDIO_RESET_GPIO               GPIOC

/* I2S peripheral configuration defines */
#define CODEC_I2S                      SPI2
#define CODEC_I2S_CLK                  RCC_APB1Periph_SPI2
#define CODEC_I2S_ADDRESS              (SPI2_BASE + 0x000C)
#define CODEC_I2S_GPIO_AF              GPIO_AF_SPI2
#define CODEC_I2S_IRQ                  SPI2_IRQn
#define CODEC_I2S_GPIO_CLOCK           (RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB)
#define CODEC_I2S_WS_PIN               GPIO_Pin_12
#define CODEC_I2S_SCK_PIN              GPIO_Pin_13
#define CODEC_I2S_SD_PIN               GPIO_Pin_15
#define CODEC_I2S_MCK_PIN              GPIO_Pin_6
#define CODEC_I2S_WS_PINSRC            GPIO_PinSource12
#define CODEC_I2S_SCK_PINSRC           GPIO_PinSource13
#define CODEC_I2S_SD_PINSRC            GPIO_PinSource15
#define CODEC_I2S_MCK_PINSRC           GPIO_PinSource6
#define CODEC_I2S_GPIO                 GPIOB
#define CODEC_I2S_WS_GPIO              GPIOB
#define CODEC_I2S_MCK_GPIO             GPIOC
#define Audio_I2S_IRQHandler           SPI2_IRQHandler


 #define AUDIO_MAL_DMA_PERIPH_DATA_SIZE DMA_PeripheralDataSize_HalfWord
 #define AUDIO_MAL_DMA_MEM_DATA_SIZE    DMA_MemoryDataSize_HalfWord
 #define DMA_MAX_SZE                    0xFFFF


 #define DAC_DHR12L1_ADDRESS            0x4000740C
 #define DAC_DHR12R1_ADDRESS            0x40007408
 #define DAC_DHR8R1_ADDRESS             0x40007410
 #define AUDIO_DAC_CHANNEL              DAC_Channel_1

 /* I2S DMA Stream definitions */
 #define AUDIO_I2S_DMA_CLOCK            RCC_AHB1Periph_DMA1
 #define AUDIO_I2S_DMA_STREAM           DMA1_Stream4
 #define AUDIO_I2S_DMA_DREG             CODEC_I2S_ADDRESS
 #define AUDIO_I2S_DMA_CHANNEL          DMA_Channel_0
 #define AUDIO_I2S_DMA_IRQ              DMA1_Stream4_IRQn
 #define AUDIO_I2S_DMA_FLAG_TC          DMA_FLAG_TCIF4
 #define AUDIO_I2S_DMA_FLAG_HT          DMA_FLAG_HTIF4
 #define AUDIO_I2S_DMA_FLAG_FE          DMA_FLAG_FEIF4
 #define AUDIO_I2S_DMA_FLAG_TE          DMA_FLAG_TEIF4
 #define AUDIO_I2S_DMA_FLAG_DME         DMA_FLAG_DMEIF4

 #define Audio_MAL_I2S_IRQHandler       DMA1_Stream4_IRQHandler

 /* DAC DMA Stream definitions */
 #define AUDIO_DAC_DMA_CLOCK            RCC_AHB1Periph_DMA1
 #define AUDIO_DAC_DMA_STREAM           DMA1_Stream0
 #define AUDIO_DAC_DMA_DREG             DAC_DHR12L1_ADDRESS
 #define AUDIO_DAC_DMA_CHANNEL          DMA_Channel_0
 #define AUDIO_DAC_DMA_IRQ              DMA1_Stream0_IRQn
 #define AUDIO_DAC_DMA_FLAG_TC          DMA_FLAG_TCIF0
 #define AUDIO_DAC_DMA_FLAG_HT          DMA_FLAG_HTIF0
 #define AUDIO_DAC_DMA_FLAG_FE          DMA_FLAG_FEIF0
 #define AUDIO_DAC_DMA_FLAG_TE          DMA_FLAG_TEIF0
 #define AUDIO_DAC_DMA_FLAG_DME         DMA_FLAG_DMEIF0

 #define Audio_MAL_DAC_IRQHandler       DMA1_Stream0_IRQHandler


/* I2C peripheral configuration defines (control interface of the audio codec) */
#define CODEC_I2C                      I2C2
#define CODEC_I2C_CLK                  RCC_APB1Periph_I2C2
#define CODEC_I2C_GPIO_CLOCK           RCC_AHB1Periph_GPIOB
#define CODEC_I2C_GPIO_AF              GPIO_AF_I2C2
#define CODEC_I2C_GPIO                 GPIOB
#define CODEC_I2C_SCL_PIN              GPIO_Pin_10
#define CODEC_I2C_SDA_PIN              GPIO_Pin_11
#define CODEC_I2S_SCL_PINSRC           GPIO_PinSource10
#define CODEC_I2S_SDA_PINSRC           GPIO_PinSource11

/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define CODEC_FLAG_TIMEOUT             ((uint32_t)0x1000)
#define CODEC_LONG_TIMEOUT             ((uint32_t)(300 * CODEC_FLAG_TIMEOUT))
/*----------------------------------------------------------------------------*/

/*-----------------------------------
                        Audio Codec User defines
                                     -----------------------------------------*/
/* Audio interface : I2S or DAC */
#define AUDIO_INTERFACE_I2S           1
#define AUDIO_INTERFACE_DAC           2

/* Codec output DEVICE */
#define OUTPUT_DEVICE_SPEAKER         1
#define OUTPUT_DEVICE_HEADPHONE       2
#define OUTPUT_DEVICE_BOTH            3
#define OUTPUT_DEVICE_AUTO            4

/* Volume Levels values */
#define DEFAULT_VOLMIN                0x00
#define DEFAULT_VOLMAX                0xFF
#define DEFAULT_VOLSTEP               0x04

#define AUDIO_PAUSE                   0
#define AUDIO_RESUME                  1

/* Codec POWER DOWN modes */
#define CODEC_PDWN_HW                 1
#define CODEC_PDWN_SW                 2

/* MUTE commands */
#define AUDIO_MUTE_ON                 1
#define AUDIO_MUTE_OFF                0
/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define SD_DETECT_PIN                    GPIO_Pin_1
#define SD_DETECT_GPIO_PORT              GPIOD
#define SD_DETECT_GPIO_CLK               RCC_AHB1Periph_GPIOD

#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40012C80)
/**
 * @brief  SDIO Intialization Frequency (400KHz max)
 */
#define SDIO_INIT_CLK_DIV                ((uint8_t)0x76)
/**
 * @brief  SDIO Data Transfer Frequency (25MHz max)
 */
#define SDIO_TRANSFER_CLK_DIV            ((uint8_t)0x0)

#define SD_SDIO_DMA                   DMA2
#define SD_SDIO_DMA_CLK               RCC_AHB1Periph_DMA2

#define SD_SDIO_DMA_STREAM3           3
//#define SD_SDIO_DMA_STREAM6           6

#ifdef SD_SDIO_DMA_STREAM3
#define SD_SDIO_DMA_STREAM            DMA2_Stream3
#define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
#define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF3
#define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF3
#define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF3
#define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF3
#define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF3
#define SD_SDIO_DMA_IRQn              DMA2_Stream3_IRQn
#define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream3_IRQHandler
#elif defined SD_SDIO_DMA_STREAM6
#define SD_SDIO_DMA_STREAM            DMA2_Stream6
#define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
#define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF6
#define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF6
#define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF6
#define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF6
#define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF6
#define SD_SDIO_DMA_IRQn              DMA2_Stream6_IRQn
#define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream6_IRQHandler
#endif /* SD_SDIO_DMA_STREAM3 */

#endif /* BSP_CONFIG_H_ */
