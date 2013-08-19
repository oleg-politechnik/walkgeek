/*
 * ui.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UI_H_
#define UI_H_

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "disp_1100.h"

/* Exported constants --------------------------------------------------------*/
#define KEY_PREV        KEY_1
#define KEY_NEXT        KEY_3

#define KEY_DIR_START   KEY_4
#define KEY_DIR_END     KEY_6

#define KEY_APP_PLAYER  KEY_7
#define KEY_APP_MSC     KEY_8

#define KEY_RESET_PLAYER 	KEY_C
#define KEY_SAVE_PLAYER_STATE	KEY_5

#define DISP_LAST_ROW         (DISP_ROW_COUNT - 2)

#define configUI_BACKLIGHT_TIMEOUT_MS   (10000 / portTICK_RATE_MS)

#define configUI_PRESS_TICK_MS          (100 / portTICK_RATE_MS)
#define configUI_MAIN_INTERVAL_MS       (300 / portTICK_RATE_MS)
#define configUI_PRESS_TIMEOUT_MS       (800 / portTICK_RATE_MS)
#define configUI_LONG_PRESS_TIMEOUT_MS       (2000 / portTICK_RATE_MS)

#define configUI_LOCK_UNLOCK_TIMEOUT_MS (1000 / portTICK_RATE_MS)

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  UIM_Uninitialized,
  UIM_Player,
//  UIM_FileBrowser,
  UIM_USB,
  UIM_MAX
} UserInterfaceMode_Typedef;

typedef enum
{
  VAR_SystemState,
  VAR_ScreenMode,
  VAR_BatteryState,

  VAR_PlayerTrack,
  VAR_PlayerPosition,
  VAR_PlayerScreenMode,

  VAR_AudioStatus,
  VAR_AudioVolume,

  VAR_MSC_Speed,

  VAR_MAX
} VAR_Index;

/*
 * Screen is like a layer plus a set of event handling functions.
 */
typedef struct
{
    void (*Init)(void);
    void (*DeInit)(void);
    void (*UpdateVar)(VAR_Index);
    u16 (*KeyPressedHandler)(KEY_Typedef key);
    u16 (*KeyHoldHandler)(KEY_Typedef key);
    void (*KeyReleasedHandler)(KEY_Typedef key);
} Screen_Typedef;

typedef enum
{
  UIE_KeyReleased,
  UIE_KeyPressed,
  UIE_VariableChanged,
  UIE_KeyHoldTimeout
} eUserInterfaceEvent;

/* Exported macro ------------------------------------------------------------*/
#define DISP_ALIGN_CENTER(row, str) \
  Disp_String(MAX((int)(DISP_X_COUNT / 2) - ((int) strlen(str) - 1) * 6 / 2, (int)0), row, str, false)

#define DISP_ALIGN_RIGHT(row, str) \
  Disp_String(DISP_X_COUNT - strlen(str) * 6, row, str, false)

#define DISP_ALIGN_LEFT(row, str) \
  Disp_String(0, row, str, false)

#define UI_SetVariable(var_ix, var, val) do { if (var != val) { \
        var = val; UI_SyncVariable(var_ix); } } while(0)

/* Exported functions ------------------------------------------------------- */
void UI_EnableBacklight(void);
void UI_DisableBacklight(void);
void UI_StartHoldTimer(u16 timeout);

void Vibrator_SendSignal(u16 ms);

void UI_PreInit(void);

void UI_SendEvent(eUserInterfaceEvent event, int arg);
void UI_SendEventFromISR(eUserInterfaceEvent event, int arg);

void UI_SyncVariable(VAR_Index var);

/* */
//extern char str_buf[DISP_COL_COUNT];

#endif /* UI_H_ */
