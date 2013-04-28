/*
 * powermanager.c
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
#include "powermanager.h"
#include "scheduler.h"
#include "system.h"
#include "disp_1100.h"
#include "nestedfilter.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static PowerManagerState_Typedef PowerManagerState;
static ADC_Source_Typedef ADC_Source;
static NestedFilterSet_Typedef *BatteryVoltageFilter = NULL;
static NestedFilterSet_Typedef *ChargeCurrentFilter = NULL;

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void RAM_FUNC PowerManager_PeriodicCallback(void);

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void PowerManager_Init(void)
{
  PowerManagerState = PM_OFFLINE;

  /* results in 2^9=512 effective window size averaging filter */
  BatteryVoltageFilter = NestedFilter_Init(3, 3);
  ChargeCurrentFilter = NestedFilter_Init(3, 3);

  Scheduler_PutTask(100, PowerManager_PeriodicCallback, REPEAT);

  BSP_InitPowerManager();
}

void PowerManager_MainThread(void)
{
  if ((PowerManagerState == PM_OFFLINE) && BSP_IsPowerSourceConnected())
  {
    /* Display charging indication when the power is attached */
    /* Other power-consuming modules can be enabled here */
    System_PowerEnable();
    //System_SetState(SS_PLAYER); /* TODO */
    PowerManagerState = PM_ONLINE;

    USBD_Init();
  }
  else if ((PowerManagerState == PM_ONLINE) && !BSP_IsPowerSourceConnected())
  {
    PowerManagerState = PM_OFFLINE;

    USBD_DeInit();
  }
}

void RAM_FUNC PowerManager_PeriodicCallback(void)
{
  switch (ADC_Source)
  {
    case ADCS_BATTERY_VOLTAGE:
      NestedFilter_AddMeasure(BatteryVoltageFilter,
              BSP_GetLast_ADC_Result_mV(), VAR_BatteryVoltage);
      ADC_Source = ADCS_CHARGE_CURRENT;
      break;

    case ADCS_CHARGE_CURRENT:
      NestedFilter_AddMeasure(ChargeCurrentFilter, BSP_GetLast_ADC_Result_mV(),
              VAR_BatteryVoltage);
      ADC_Source = ADCS_BATTERY_VOLTAGE;
      break;

    default:
      ADC_Source = ADCS_BATTERY_VOLTAGE;
      break;
  }

  if (PowerManagerState == PM_OFFLINE)
  {
    ADC_Source = ADCS_BATTERY_VOLTAGE;
  }

  BSP_StartPowerManagerADC(ADC_Source);
}

float PowerManager_GetBatteryVoltage(void)
{
  return (float) NestedFilter_GetValue(BatteryVoltageFilter) / 1000;
}

float PowerManager_GetChargingCurrent(void)
{
  /* XXX this is incorrect value -> needs a const coefficient */
#define RPROG_OHM (1600+270)

  return (float) (NestedFilter_GetValue(ChargeCurrentFilter) / 1000) * RPROG_OHM / 1000;
}

PowerManagerState_Typedef PowerManager_GetState(void)
{
  return PowerManagerState;
}
