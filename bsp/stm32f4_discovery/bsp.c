/*
 * bsp.c
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

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "system.h"
#include "powermanager.h"
#include "disp_1100.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static u32 LastADC_Value_mV;

/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Power monitoring --------------------------------------------------------- */
void ADC_IRQHandler(void)
{
  if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == SET)
  {
    LastADC_Value_mV = ADC_GetConversionValue(ADC1) * 2500 * 2 / 0xFFF;
  }
}

u32 BSP_GetLast_ADC_Result_mV(void)
{
  return LastADC_Value_mV;
}

void BSP_InitPowerManager(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); /*todo define*/

  /* Configure ADC Channels pin as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); /*todo define*/

  /* Configure ADC Channels pin as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void BSP_InitPowerSourcesSense(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // VBUS
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void BSP_StartPowerManagerADC(ADC_Source_Typedef ADC_Source)
{
  assert_param(ADC_Source < ADCS_MAX);

  uint8_t ADC_Channel;
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;

  switch (ADC_Source)
  {
    case ADCS_BATTERY_VOLTAGE:
      ADC_Channel = ADC_Channel_11;
      break;

    case ADCS_CHARGE_CURRENT:
      ADC_Channel = ADC_Channel_8;
      break;

    default:
      return;
  }

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);

  /* ADC Common Init */
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC peripherals Init */
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_3Cycles);

  /* Enable ADC */
  ADC_Cmd(ADC1, ENABLE);
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

  ADC_SoftwareStartConv(ADC1);
}

bool BSP_IsPowerSourceConnected(void)
{
  return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
}

void BSP_PowerEnable(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(PWR_EN_AHB1_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = PWR_EN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PWR_EN_GPIO, &GPIO_InitStructure);

  GPIO_SetBits(PWR_EN_GPIO, PWR_EN_PIN);
}

void BSP_PowerDisable(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(PWR_EN_AHB1_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = PWR_EN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PWR_EN_GPIO, &GPIO_InitStructure);
}

/* disp_1100 -----------------------------------------------------------------*/
#include "disp_1100.h"

void SPI1_IRQHandler(void)
{
  Disp_IRQHandler();
}

void Disp_GPIO_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable SPI and GPIO clocks */
  RCC_AHB1PeriphClockCmd(DISP_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(DISP_RCC_APB2Periph_SPI, ENABLE);

  GPIO_InitStructure.GPIO_Pin = DISP_Pin_BKL | DISP_Pin_RST | DISP_Pin_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(DISP_GPIO, &GPIO_InitStructure);

  /* Configure SPI pins: SCK (PA5), MOSI (PA7) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_Init(DISP_GPIO, &GPIO_InitStructure);

  GPIO_PinAFConfig(DISP_GPIO, GPIO_PinSource5, DISP_GPIO_AF_SPI);
  GPIO_PinAFConfig(DISP_GPIO, GPIO_PinSource7, DISP_GPIO_AF_SPI);
}

void Disp_SetBKL(FunctionalState enabled)
{
  (enabled == ENABLE) ? GPIO_ResetBits(DISP_GPIO, DISP_Pin_BKL) : GPIO_SetBits(
          DISP_GPIO, DISP_Pin_BKL);
}

void Disp_SetCS(FunctionalState enabled)
{
  (enabled == ENABLE) ? GPIO_ResetBits(DISP_GPIO, DISP_Pin_CS) : GPIO_SetBits(
          DISP_GPIO, DISP_Pin_CS);
}

void Disp_SetRST(FunctionalState enabled)
{
  (enabled == ENABLE) ? GPIO_ResetBits(DISP_GPIO, DISP_Pin_RST) : GPIO_SetBits(
          DISP_GPIO, DISP_Pin_RST);
}

/* sdio ----------------------------------------------------------------------*/
#include "stm324xg_eval_sdio_sd.h"

/**
 * @brief  DeInitializes the SDIO interface.
 * @param  None
 * @retval None
 */
void SD_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Disable SDIO Clock */
  SDIO_ClockCmd(DISABLE);

  /*!< Set Power State to OFF */
  SDIO_SetPowerState(SDIO_PowerState_OFF);

  /*!< DeInitializes the SDIO peripheral */
  SDIO_DeInit();

  /* Disable the SDIO APB2 Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDIO, DISABLE);

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_MCO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_MCO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_MCO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_MCO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_MCO);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_MCO);

  /* Configure PC.08, PC.09, PC.10, PC.11 pins: D0, D1, D2, D3 pins */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
          | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure PD.02 CMD line */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Configure PC.12 pin: CLK pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  Initializes the SD Card and put it into StandBy State (Ready for
 *         data transfer).
 * @param  None
 * @retval None
 */
void SD_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(
          RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD/* | SD_DETECT_GPIO_CLK*/,
          ENABLE);

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_SDIO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_SDIO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SDIO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SDIO);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SDIO);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_SDIO);

  /* Configure PC.08, PC.09, PC.10, PC.11 pins: D0, D1, D2, D3 pins */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
          | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure PD.02 CMD line */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Configure PC.12 pin: CLK pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*!< Configure SD_SPI_DETECT_PIN pin: SD Card detect pin */
  //    GPIO_InitStructure.GPIO_Pin = SD_DETECT_PIN;
  //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  //    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  //    GPIO_Init(SD_DETECT_GPIO_PORT, &GPIO_InitStructure);
  /* Enable the SDIO APB2 Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDIO, ENABLE);

  /* Enable the DMA2 Clock */
  RCC_AHB1PeriphClockCmd(SD_SDIO_DMA_CLK, ENABLE);
}

/**
 * @brief  Detect if SD card is correctly plugged in the memory slot.
 * @param  None
 * @retval Return if SD is detected or not
 */
uint8_t SD_Detect(void)
{
  __IO uint8_t status = SD_PRESENT;

  //  /*!< Check GPIO to detect SD */
  //  if (GPIO_ReadInputDataBit(SD_DETECT_GPIO_PORT, SD_DETECT_PIN) != Bit_RESET)
  //  {
  //    status = SD_NOT_PRESENT;
  //  }
  return status;
}

/* keyboard ------------------------------------------------------------------*/
#include "keyboard.h"

static void BSP_KeyboardSetRow(u8 row_index)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure row pins as input */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_ROW_PINS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEYBOARD_ROW_GPIO, &GPIO_InitStructure);

  GPIO_ResetBits(KEYBOARD_ROW_GPIO, KEYBOARD_ROW_PINS);

  /* Configure row pins as output */
  switch (row_index)
  {
    case 1:
      GPIO_SetBits(KEYBOARD_ROW_GPIO, KEYBOARD_ROW1_PIN);
      GPIO_InitStructure.GPIO_Pin = KEYBOARD_ROW1_PIN;
      break;

    case 2:
      GPIO_SetBits(KEYBOARD_ROW_GPIO, KEYBOARD_ROW2_PIN);
      GPIO_InitStructure.GPIO_Pin = KEYBOARD_ROW2_PIN;
      break;

    default:
      return;
      break;
  }

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEYBOARD_ROW_GPIO, &GPIO_InitStructure);
}

void BSP_Keyboard_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(KEYBOARD_COL_CLOCK, ENABLE);

  /* Configure col pins as input */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_COL0_PIN | KEYBOARD_COL1_PIN
          | KEYBOARD_COL2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEYBOARD_COL_GPIO, &GPIO_InitStructure);

  RCC_AHB1PeriphClockCmd(KEYBOARD_ROW_CLOCK, ENABLE);
  BSP_KeyboardSetRow(-1);

  //

  RCC_AHB1PeriphClockCmd(BUTTON_ESC_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = BUTTON_ESC_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(BUTTON_ESC_GPIO, &GPIO_InitStructure);
}

u8 BSP_KeyboardGetRowValues(u8 row_index)
{
  u32 value = 0, temp;

  BSP_KeyboardSetRow(row_index);

  temp = GPIO_ReadInputData(KEYBOARD_COL_GPIO);
  value |= (temp & KEYBOARD_COL0_PIN) >> (KEYBOARD_COL0_PINSRC - 0);
  value |= (temp & KEYBOARD_COL1_PIN) >> (KEYBOARD_COL1_PINSRC - 1);
  value |= (temp & KEYBOARD_COL2_PIN) >> (KEYBOARD_COL2_PINSRC - 2);

  BSP_KeyboardSetRow(-1);

  return value;
}

void BSP_InitPPPButton()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(BUTTON_PPP_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = BUTTON_PPP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(BUTTON_PPP_GPIO, &GPIO_InitStructure);
}

bool BSP_GetPPPButton()
{
  return !GPIO_ReadInputDataBit(BUTTON_PPP_GPIO, BUTTON_PPP_PIN);
}

bool BSP_GetESCButton()
{
  return false /* !GPIO_ReadInputDataBit(BUTTON_ESC_GPIO, BUTTON_ESC_PIN) */ ;
}

/**
 * @brief  Codec_TIMEOUT_UserCallback
 * @param  None
 * @retval None
 */
uint32_t Codec_TIMEOUT_UserCallback(void)
{
  I2C_InitTypeDef I2C_InitStructure;

  /* I2C Timeout error (CS43L22) */

  I2C_GenerateSTOP(I2C1, ENABLE);
  I2C_SoftwareResetCmd(I2C1, ENABLE);
  I2C_SoftwareResetCmd(I2C1, DISABLE);

  I2C_DeInit(I2C1);

  /* CODEC_I2C peripheral configuration */
  I2C_DeInit(I2C1);
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x33;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
  /* Enable the I2C peripheral */
  I2C_Cmd(I2C1, ENABLE);
  I2C_Init(I2C1, &I2C_InitStructure);

  /* I2C error recovered */

  return 0;
}

/**
 * @brief  Get next data sample callback
 * @param  None
 * @retval Next data sample to be sent
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  return 0;
}
