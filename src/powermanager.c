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

#ifdef HAS_BATTERY

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "powermanager.h"
#include "system.h"
#include "nestedfilter.h"
#include "audio_if.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static PowerManagerState_Typedef PowerManagerState;
static NestedFilterSet_Typedef *BatteryVoltageFilter = NULL;
static NestedFilterSet_Typedef *ChargeCurrentFilter = NULL;

uint16_t mV[ADCS_MAX];

/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void PowerManager_Init(void)
{
  BSP_InitPowerSourcesSense();

  PowerManagerState = PM_OFFLINE;

  /* results in 2^9=512 effective window size averaging filter */
  BatteryVoltageFilter = NestedFilter_Init(3, 3);
  /* results in 2^12=4096 effective window size averaging filter */
  ChargeCurrentFilter = NestedFilter_Init(3, 4);

  BSP_InitPowerManager();
}

void PowerManager_MainThread(void)
{
  if ((PowerManagerState == PM_OFFLINE) && BSP_IsPowerSourceConnected())
  {
    /* Display charging indication when the power is attached */
    /* Other power-consuming modules can be enabled here */
    PowerManagerState = PM_ONLINE;

    System_VbusApplied();
  }
  else if ((PowerManagerState == PM_ONLINE) && !BSP_IsPowerSourceConnected())
  {
    PowerManagerState = PM_OFFLINE;

    System_VbusDetached();
  }
}

void PowerManager_ValuesReady(void)
{
  uint16_t Vref_Compensation = 0;

  if (Audio_GetState() != AS_PLAYING)
  {
    Vref_Compensation = 100;
  }

  NestedFilter_AddMeasure(BatteryVoltageFilter,
          mV[ADCS_BATTERY_VOLTAGE] + Vref_Compensation, VAR_BatteryState);
  NestedFilter_AddMeasure(ChargeCurrentFilter,
          mV[ADCS_CHARGE_CURRENT], VAR_BatteryState);
}

float PowerManager_GetBatteryVoltage(void)
{
  return 2.f * NestedFilter_GetValue(BatteryVoltageFilter) / 1000;
}

float PowerManager_GetChargingCurrent(void)
{
  return (NestedFilter_GetValue(ChargeCurrentFilter) / 1000.f) * RPROG_OHM / 1000;
}

PowerManagerState_Typedef PowerManager_GetState(void)
{
  return PowerManagerState;
}

#endif
