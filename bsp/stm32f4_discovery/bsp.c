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
#include "bsp.h"
#include "audio_if.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static u32 LastADC_Value_mV;

/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum
{
  HS_NOT_PRESENT,
  HS_QUALIFYING,
  HS_PRESENT
} HeadsetStatus_Typedef;

/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef HAS_BATTERY
static uint16_t adc_buff[128];
extern uint16_t mV[ADCS_MAX];

static ADC_Source_Typedef ADC_Source = ADCS_MAX;
#endif

#ifdef HAS_HEADSET
static HeadsetStatus_Typedef HeadsetStatus;
#endif

static bool HeadsetButtonPressed;

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef HAS_HEADSET
static void UpdateHeadsetStatus(void);
#endif

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Power monitoring --------------------------------------------------------- */
#ifdef HAS_BATTERY
static void RunADC(void)
{
  uint8_t ADC_Channel;

  switch (ADC_Source)
  {
    case ADCS_BATTERY_VOLTAGE:
      ADC_Channel = ADC_BAT_CHANNEL;
      break;

    case ADCS_CHARGE_CURRENT:
      ADC_Channel = ADC_CHRG_CHANNEL;
      break;

    case ADCS_HEADSET_STATE:
      ADC_Channel = ADC_BTN_CHANNEL;
      break;

    default:
      PowerManager_ValuesReady();
      UpdateHeadsetStatus();
      return;
  }

  ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_28Cycles);

  /* Enable ADC */
  ADC_Cmd(ADC1, ENABLE);

  /* Clear DMA Stream Transfer Complete interrupt pending bit */
  DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);

  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);

  ADC_SoftwareStartConv(ADC1);
}

void DMA2_Stream0_IRQHandler(void)
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
  {
    ADC_Cmd(ADC1, DISABLE);
    DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, DISABLE);

    assert_param(ADC_Source < ADCS_MAX);

    unsigned i;
    uint32_t acc = 0;

    for (i = 0; i < SIZE_OF(adc_buff); i++)
    {
      acc += adc_buff[i];
    }

    acc /= SIZE_OF(adc_buff);

    mV[ADC_Source] = (acc * 2500) / (0xFFF);

    ADC_Source++;

    RunADC();
  }
}

static void ADC_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(ADC_BAT_RCC_AHB1Periph_GPIO |
      ADC_CHRG_RCC_AHB1Periph_GPIO | ADC_BTN_RCC_AHB1Periph_GPIO, ENABLE);

  /* Configure ADC Channel pins as analog inputs */

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStructure.GPIO_Pin = ADC_CHRG_PIN;
  GPIO_Init(ADC_CHRG_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = ADC_BAT_PIN;
  GPIO_Init(ADC_BAT_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = ADC_BTN_PIN;
  GPIO_Init(ADC_BTN_GPIO, &GPIO_InitStructure);
}

static void ADC_DMA_Config(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  NVIC_InitTypeDef      NVIC_InitStructure;

  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* DMA2 Stream0 channel0 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&adc_buff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = SIZE_OF(adc_buff);
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC1 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
}

static void BSP_StartADC(void)
{
  if (ADC_Source < ADCS_MAX)
  {
    trace("Warning! ADC conversion still in progress\n");
    return;
  }

  ADC_Source = 0;

  RunADC();
}
#endif

void BSP_InitPowerManager(void)
{
#ifdef HAS_BATTERY
  ADC_GPIO_Config();

  ADC_DMA_Config();

//  Scheduler_PutTask(10, BSP_StartADC, REPEAT);
#endif

#ifdef HAS_HEADSET


#endif
}

void BSP_InitPowerSourcesSense(void)
{
#ifdef HAS_BATTERY
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // VBUS
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
}

bool BSP_IsPowerSourceConnected(void)
{
#ifdef HAS_BATTERY
  return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
#endif

  return true;
}

void BSP_PowerEnable(void)
{
#ifdef USE_HOST_MODE
  /* Init Host Library */
  //USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID, &USB_Host, &USBH_MSC_cb, &USR_Callbacks);
#endif

#ifdef HAS_BATTERY
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(PWR_EN_AHB1_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = PWR_EN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PWR_EN_GPIO, &GPIO_InitStructure);

  GPIO_SetBits(PWR_EN_GPIO, PWR_EN_PIN);
#endif
}

void BSP_PowerDisable(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(
          RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC
                  | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Disable GPIOs clock */
  RCC_AHB1PeriphClockCmd(
          RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC
                  | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, DISABLE);

  NVIC_SystemReset();
}

/* disp_1100 -----------------------------------------------------------------*/
#include "disp_1100.h"

void Disp_GPIO_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable SPI and GPIO clocks */
  RCC_AHB1PeriphClockCmd(DISP_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(DISP_RCC_APB2Periph_SPI, ENABLE);

  GPIO_InitStructure.GPIO_Pin = DISP_Pin_RST | DISP_Pin_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(DISP_GPIO, &GPIO_InitStructure);

  /* Configure SPI pins: SCK (PA5), MOSI (PA7) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_Init(DISP_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = DISP_Pin_BKL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
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

bool Disp_GetCS(void)
{
  return (GPIO_ReadInputDataBit(DISP_GPIO, DISP_Pin_CS) == Bit_RESET);
}

void Disp_SetRST(FunctionalState enabled)
{
  (enabled == ENABLE) ? GPIO_ResetBits(DISP_GPIO, DISP_Pin_RST) : GPIO_SetBits(
          DISP_GPIO, DISP_Pin_RST);
}

/* sdio ----------------------------------------------------------------------*/
#ifdef HAS_SDIO
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
          RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | SD_DETECT_GPIO_CLK,
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
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
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
  GPIO_InitStructure.GPIO_Pin = SD_DETECT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SD_DETECT_GPIO_PORT, &GPIO_InitStructure);
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

  /*!< Check GPIO to detect SD */
//  if (GPIO_ReadInputDataBit(SD_DETECT_GPIO_PORT, SD_DETECT_PIN) != Bit_SET)
//  {
//    status = SD_NOT_PRESENT;
//  }
  return status;
}
#endif

/* keyboard ------------------------------------------------------------------*/
static KeyPin_Typedef KeyPins[] =
{
        KEY_PIN_TYPEDEFS
};

void BSP_Keypad_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  KEY_Typedef key;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

  for (key = 0; key < KEY_MAX_GPIO; key++)
  {
    if (!KeyPins[key].GPIOx)
      continue;

#ifdef F4DISCOVERY
    if (key == KEY_3)
    {
      continue;
    }
#endif

    RCC_AHB1PeriphClockCmd(KeyPins[key].RCC_AHB1Periph_GPIOx, ENABLE);
    GPIO_InitStructure.GPIO_Pin = (1 << KeyPins[key].GPIO_PinSourcex);
    GPIO_Init(KeyPins[key].GPIOx, &GPIO_InitStructure);
  }
}

bool BSP_Keypad_GetKeyStatus(KEY_Typedef key)
{
  if (key == KEY_BTN)
  {
    return HeadsetButtonPressed;
  }

  assert_param(key < KEY_MAX_GPIO);

  if (!KeyPins[key].GPIOx)
    return false;

#ifdef F4DISCOVERY
  if (key == KEY_3)
  {
    return GPIO_ReadInputDataBit(KeyPins[key].GPIOx, (1 << KeyPins[key].GPIO_PinSourcex));
  }
#endif

  return !GPIO_ReadInputDataBit(KeyPins[key].GPIOx, (1 << KeyPins[key].GPIO_PinSourcex));
}

#ifdef HAS_HEADSET
void CheckHeadsetInserted(void)
{
  u16 head_mV = mV[ADCS_HEADSET_STATE];

  if (HeadsetStatus == HS_QUALIFYING)
  {
    HeadsetStatus = (head_mV < HANDSET_LOW_THRESHOLD_MV
            && head_mV > BTN_PRESSED_HIGH_THRESHOLD_MV) ? HS_PRESENT : HS_NOT_PRESENT;
    HeadsetButtonPressed = false;

    trace("Headset was inserted\n");
  }
}

void UpdateHeadsetStatus(void)
{
  if (HeadsetStatus == HS_QUALIFYING)
    return;

  u16 head_mV = mV[ADCS_HEADSET_STATE];

  /* Apply hysteresis */
  if (HeadsetStatus == HS_NOT_PRESENT && head_mV < HANDSET_LOW_THRESHOLD_MV
          && head_mV > BTN_PRESSED_HIGH_THRESHOLD_MV)
  {
    /* ... and wait while pulling off / inserting */
    HeadsetStatus = HS_QUALIFYING;
//    Scheduler_PutTask(500, CheckHeadsetInserted, NO_REPEAT);
  }
  else if (HeadsetStatus == HS_PRESENT && head_mV > HANDSET_HIGH_THRESHOLD_MV)
  {
    HeadsetStatus = HS_NOT_PRESENT;
    HeadsetButtonPressed = false;
    trace("Headset was removed\n");
  }

  if (HeadsetStatus == HS_PRESENT)
  {
    if (!HeadsetButtonPressed && head_mV < BTN_PRESSED_LOW_THRESHOLD_MV)
    {
      HeadsetButtonPressed = true;
    }
    else if (HeadsetButtonPressed && head_mV > BTN_PRESSED_HIGH_THRESHOLD_MV)
    {
      HeadsetButtonPressed = false;
    }
  }
}
#endif

/**
 * @brief  Get next data sample callback
 * @param  None
 * @retval Next data sample to be sent
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  return 0;
}

/* vibrator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Vibrator_Init(void)
{
#ifdef HAS_VIBRATOR
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(VIBRATOR_RCC_AHB1Periph_GPIO, ENABLE);

  GPIO_InitStructure.GPIO_Pin = VIBRATOR_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(VIBRATOR_GPIO, &GPIO_InitStructure);

  Vibrator_Disable();
#endif
}

void Vibrator_Disable(void)
{
#ifdef HAS_VIBRATOR
  GPIO_SetBits(VIBRATOR_GPIO, VIBRATOR_PIN);
#endif
}


void Vibrator_Enable(void)
{
#ifdef HAS_VIBRATOR
  GPIO_ResetBits(VIBRATOR_GPIO, VIBRATOR_PIN);
#endif
}


#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line, uint8_t* expr)
{
  /* User can add his own implementation to report the file name and line number,
   ex: printf("Wrong parameters value: file %s on line %d\n", file, line) */

  char buf[1024];
  int row = 0;

  //TODO: add application state

  Audio_CommandSync(AC_STOP);

  Disp_Clear();

  Disp_String(0, row++, "ASSERT FAILED", true);
  Disp_String(0, row, expr, true);
  row += 2;

  sprintf(buf, "line %i in %s", (int) line, strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
  /*todo: test on windows*/
  Disp_String(0, row, buf, true);

  /* Infinite loop */
  while (1)
  {
    Disp_IRQHandler();
    Disp_MainThread();
  }
}
#endif
