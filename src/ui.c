/*
 * ui.c
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

/* Includes ------------------------------------------------------------------*/
#include <FreeRTOS.h>
#include <timers.h>

#include "system.h"
#include "ui.h"
#include "disp_1100.h"
#include "keypad.h"
#include "powermanager.h"
#include "player.h"
#include "audio_if.h"

extern uint32_t NeglectedDMA_Count;
extern PlayerState_Typedef PlayerState;

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  int hour;
  int minute;
  int second;
} TimePoint_Typedef;

typedef enum
{
  UIS_NOT_INITIALIZED, UIS_INITIALIZING, UIS_INITIALIZED
} UI_State_Typedef;

/* Private define ------------------------------------------------------------*/
#define DISP_LAST_ROW         (DISP_ROW_COUNT - 2)

/* Private macro -------------------------------------------------------------*/
#define DISP_ALIGN_CENTER(row, str) \
  Disp_String(MAX((int)(DISP_X_COUNT / 2) - ((int) strlen(str) - 1) * 6 / 2, (int)0), row, str, false)

#define DISP_ALIGN_RIGHT(row, str) \
  Disp_String(DISP_X_COUNT - strlen(str) * 6, row, str, false)

#define DISP_ALIGN_LEFT(row, str) \
  Disp_String(0, row, str, false)

/* Private variables ---------------------------------------------------------*/
;
static volatile u32 dispBKL_Timeout;
static volatile u32 KeyProcessed;
static UserInterfaceMode_Typedef ScreenMode;
static s32 ScreenSubMode;
static UI_State_Typedef UiState = UIS_NOT_INITIALIZED;

static xTimerHandle xBacklightTimer;
static xTimerHandle xKeyHoldTimer;

/* Private function prototypes -----------------------------------------------*/
//
//static void Screen_Clear(void);
//static void ScreenPainter_Main(void);
//static void ScreenPainter_PlayerMain(void);
//static void ScreenPainter_MSC(void);
//
static void Screen_DisableBacklightCallback(xTimerHandle xTimer);

static void Keypad_LockTimeoutCallback(void);
static void Keypad_HoldTimeoutCallback(xTimerHandle xTimer);

static void TimePoint(u32 raw_mstime, TimePoint_Typedef *time);

/* Private functions ---------------------------------------------------------*/
void UI_Init(void)
{
  if (UiState != UIS_NOT_INITIALIZED)
    return;

  trace("[init] UI\n");

  UiState = UIS_INITIALIZING;

  Disp_Init();

  Keypad_Init();

  Vibrator_Init();

  xBacklightTimer
      = xTimerCreate("Backlight Timer", 10000, pdFALSE,
	  (void *) Screen_DisableBacklightCallback,
	  Screen_DisableBacklightCallback);

  xKeyHoldTimer
      = xTimerCreate("Key Hold Timer", 100, pdTRUE,
	  (void *) Keypad_HoldTimeoutCallback,
	  Keypad_HoldTimeoutCallback);

  xTimerStart(xBacklightTimer, configTIMER_API_TIMEOUT_TICKS);

  Disp_SetBKL(ENABLE);
}

void UI_DeInit(void)
{
  /* Must be called with disabled scheduler */

  xTimerDelete(xBacklightTimer, configTIMER_API_TIMEOUT_TICKS);

  xTimerDelete(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);

  //Keyboard_DeInit();
  //Disp_DeInit();
}

//

void UI_PrintBytes(char *buf, u32 bytes)
{
  if (bytes < 1024)
  {
    sprintf(buf, "%uB/s", (unsigned int) bytes);
  }
  else if (bytes < 1024 * 1024)
  {
    sprintf(buf, "%uKB/s", (unsigned int) bytes / (1024));
  }
  else
  {
    sprintf(buf, "%uMB/s", (unsigned int) bytes / (1024 * 1024));
  }
}

void UI_VariableChangedHandler(VAR_Index var)
{
  static char str_buf[256];
  int rem;

  int row = 0;

  u8 slider_pos;
  TimePoint_Typedef time;
  char *str;

  if (SystemState == SS_PLAYER)
  {
    switch (var)
    {
      case VAR_ScreenMode:
        switch (ScreenMode)
        {
          case UIM_Player_HalfLocked:
          case UIM_Player_HalfUnlocked:
            str = "Press *  ";
            break;

          case UIM_Player_Locked:
            str = "Locked   ";
            break;

          default:
            str = "         ";
            break;
        }
        DISP_ALIGN_CENTER(DISP_LAST_ROW-1, str); //regions
        break;

      case VAR_PlayerState:
        Disp_String(0, 1, "                       ", false);
        Disp_String(0, 2, "                       ", false);
        Disp_String(0, 3, "                       ", false);
        Disp_String(0, 4, "                       ", false);
        Disp_String(0, 5, "                       ", false);
        Disp_String(0, DISP_LAST_ROW, "                       ", false);

        if (ScreenMode == UIM_Player && Player_GetStatus() == PS_STOPPED)
        {
          Disp_String(0, 1, " STOPPED", true);
          break;
        }

        if (ScreenMode == UIM_Player && Player_GetStatus() == PS_ERROR_FILE)
        {
          Disp_String(0, 1, Player_GetErrorString(), true);
          break;
        }

        row = 1;
        //      sprintf(str_buf, "%i / %i", plist_curr + 1, plist_cnt);
        //      DISP_ALIGN_CENTER(row++, str_buf);

        str_buf[0] = 0;

        rem = sizeof(str_buf) - strlen(str_buf) - 1;

//        if (*PlayerState.metadata.artist)
//        {
//          strncat(str_buf, PlayerState.metadata.artist, rem);
//
//          rem = sizeof(str_buf) - strlen(str_buf) - 1;
//
//          strncat(str_buf, " - ", rem);
//        }
//
//        if (*PlayerState.metadata.title)
//        {
//          strncat(str_buf, PlayerState.metadata.title, rem);
//        }
//        else
//        {
          strncat(str_buf, PlayerState.metadata.file_name, rem);
//        }

        rem = sizeof(str_buf) - strlen(str_buf) - 1;

        if (*PlayerState.metadata.notes)
        {
          strncat(str_buf, " ", rem);

          rem = sizeof(str_buf) - strlen(str_buf) - 1;

          strncat(str_buf, PlayerState.metadata.notes, rem);

          rem = sizeof(str_buf) - strlen(str_buf) - 1;
        }

        if (strlen(str_buf) > 16 /*symbols per row*/* 4 /*rows*/)
        {
          str_buf[16 * 4 - 1] = '~';
          str_buf[16 * 4] = 0;
        }

        Disp_String(0, row++, str_buf, true);

        TimePoint(PlayerState.metadata.mstime_max, &time);
        if (time.hour)
          sprintf(str_buf, "%01i:%02i:%02i", time.hour, time.minute,
                  time.second);
        else
          sprintf(str_buf, "%i:%02i", time.minute, time.second);
        DISP_ALIGN_RIGHT(DISP_LAST_ROW, str_buf);
        /*break;*/

      case VAR_AudioPosition:
        slider_pos = 0;
        if (PlayerState.metadata.mstime_max)
        {
          slider_pos = PlayerState.metadata.mstime_curr * DISP_X_COUNT
                  / PlayerState.metadata.mstime_max;
        }

        for (u8 i = 0; i < DISP_X_COUNT; i++)
        {
          Disp_SetData(i, DISP_LAST_ROW + 1, (i < slider_pos) ? 0xFF : 0x00);
        }

        TimePoint(PlayerState.metadata.mstime_curr, &time);
        if (time.hour)
          sprintf(str_buf, "%01i:%02i:%02i", time.hour, time.minute,
                  time.second);
        else
          sprintf(str_buf, "%i:%02i", time.minute, time.second);

        Disp_String(0, DISP_LAST_ROW, "         ", false);
        Disp_String(0, DISP_LAST_ROW, str_buf, false);
        break;

        //    case VAR_Audio_NeglectedDMA_Count:
        //      sprintf(str_buf, "xDMA: %u", NeglectedDMA_Count);
        //      Disp_String(0, 5, str_buf, false);
        //      break;

      case VAR_AudioStatus:
        //sprintf(str_buf, "%iHz", file->meta.sample_rate);

        if (ScreenMode == UIM_Player_Seeking)
        {
          DISP_ALIGN_CENTER(0, (ScreenSubMode > 0) ? ">>" : "<<"); //regions
          break;
        }

        str = "  ";

        DISP_ALIGN_CENTER(0, str);

        switch (Audio_GetState())
        {
          case AS_PLAYING:
            str = "O";
            break;

          case AS_STOPPED:
            break;

          case AS_PAUSED:
            str = "-";
            break;

          case AS_ERROR:
          default:
            str = "~";
            break;
        }
        DISP_ALIGN_CENTER(0, str);
        break;

          default:
            break;
    }
  }

  switch (var)
  {
  case VAR_SystemState:
    Disp_Clear();
    switch (SystemState)
    {
    case SS_START:
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_Init);
      break;

    case SS_PLAYER:
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player);
      SyncVariable(VAR_AudioVolume);
      break;

    case SS_USB_MSC:
      DISP_ALIGN_CENTER(2, "USB Disk");
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_MSC);
      break;

    default:
      break;
    }
    UiState = UIS_INITIALIZED;
    break;

  case VAR_MSC_Speed:
    sprintf(str_buf, "Rx: ");
    UI_PrintBytes(str_buf + sizeof("Rx"), MSC_TxSpeed);
    Disp_String(0, 3, "                       ", false);
    DISP_ALIGN_LEFT(3, str_buf);

    sprintf(str_buf, "Wx: ");
    UI_PrintBytes(str_buf + sizeof("Wx"), MSC_RxSpeed);
    Disp_String(0, 4, "                       ", false);
    DISP_ALIGN_LEFT(4, str_buf);
    break;


  case VAR_AudioVolume:
    sprintf(str_buf, "<%i>", Audio_GetVolume());
    DISP_ALIGN_RIGHT(0, str_buf);
    break;

  case VAR_BatteryState:
#ifdef HAS_BATTERY
    if (PowerManager_GetState() == PM_ONLINE)
    {
      sprintf(str_buf, F1_2"C ",
	  FLOAT_TO_1_2(PowerManager_GetChargingCurrent()));
    }
    else
    {
      sprintf(str_buf, F1_2"v ", FLOAT_TO_1_2(PowerManager_GetBatteryVoltage()));
    }
    DISP_ALIGN_LEFT(0, str_buf);//region
    break;
#endif

  default:
    break;
  }
}

void UI_MainCycle(void)
{
  if (UiState == UIS_NOT_INITIALIZED)
    return;

  u8 i = 0;

  Disp_MainThread();

  if (UiState == UIS_INITIALIZING)
  {
    if (displayVariableFlags[VAR_SystemState])
      i = VAR_SystemState;
    else
      return;
  }

  for (; i < MAX_DISPLAY_VARIABLES; ++i)
  {
    if (displayVariableFlags[i])
    {
      UI_VariableChangedHandler(i);

      //CPU_CompareExchange((u32*) displayVariableFlags[i], true, false);

      displayVariableFlags[i] = false;

    }
  }
}

static void TimePoint(u32 raw_mstime, TimePoint_Typedef *time)
{
  time->second = raw_mstime / 1000;
  time->minute = time->second / 60;
  time->hour = time->minute / 60;
  time->second %= 60;
  time->minute %= 60;
}

void Keypad_KeyPressedCallback(KEY_Typedef key)
{
  if (UiState != UIS_INITIALIZED)
    return;

  KeyProcessed = RESET;
  if (ScreenMode != UIM_Player_Locked && ScreenMode != UIM_Player_HalfUnlocked)
  {
    xTimerStop(xBacklightTimer, configTIMER_API_TIMEOUT_TICKS);
    Disp_SetBKL(ENABLE);
  }

  if ((key == KEY_PPP && ScreenMode != UIM_Player_Locked) || key == KEY_BTN)
  {
    xTimerChangePeriod(xKeyHoldTimer, 3000, configTIMER_API_TIMEOUT_TICKS);
    xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);
  }

  if (key == KEY_APP_PLAYER && SystemState != SS_PLAYER)
  {
    System_SetState(SS_PLAYER);
    return;
  }

  if (key == KEY_APP_MSC && SystemState != SS_USB_MSC)
  {
    System_SetState(SS_USB_MSC);
    return;
  }

  switch (ScreenMode)
  {
  case UIM_Player:
    switch (key)
    {
    case KEY_PREV:
      ScreenSubMode = -10;
      xTimerChangePeriod(xKeyHoldTimer, 1000, configTIMER_API_TIMEOUT_TICKS);
      xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);
      break;

    case KEY_NEXT:
      ScreenSubMode = 10;
      xTimerChangePeriod(xKeyHoldTimer, 1000, configTIMER_API_TIMEOUT_TICKS);
      xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);
      break;

    case KEY_DIR_START:
      Player_AsyncCommand(PC_DIR_START, 0);
      break;

    case KEY_DIR_END:
      Player_AsyncCommand(PC_DIR_END, 0);
      break;

    case KEY_UP:
      ScreenSubMode = 1;
      Audio_ChangeVolume(ScreenSubMode);
      xTimerChangePeriod(xKeyHoldTimer, 1000, configTIMER_API_TIMEOUT_TICKS);
      xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);
      break;

    case KEY_DOWN:
      ScreenSubMode = -1;
      Audio_ChangeVolume(ScreenSubMode);
      xTimerChangePeriod(xKeyHoldTimer, 1000, configTIMER_API_TIMEOUT_TICKS);
      xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);
      break;

    case KEY_SEL:
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player_HalfLocked);
      xTimerChangePeriod(xKeyHoldTimer, 1000, configTIMER_API_TIMEOUT_TICKS);
      xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);
      break;

    default:
      break;
    }
    break;

  case UIM_Player_HalfLocked:
    switch (key)
    {
    case KEY_ASTERICK:
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player_Locked);
      KeyProcessed = SET;
      /* fall through */

    default:
      Keypad_LockTimeoutCallback();
      break;
    }
    break;

  case UIM_Player_Locked:
    switch (key)
    {
    case KEY_SEL:
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player_HalfUnlocked);
      xTimerChangePeriod(xKeyHoldTimer, 1000, configTIMER_API_TIMEOUT_TICKS);
      xTimerStart(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);
      break;

    default:
      break;
    }
    break;

  case UIM_Player_HalfUnlocked:
    switch (key)
    {
    case KEY_ASTERICK:
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player);
      KeyProcessed = SET;
      xTimerStart(xBacklightTimer, configTIMER_API_TIMEOUT_TICKS);

      Disp_SetBKL(ENABLE);

    case KEY_PPP:
    case KEY_UP:
    case KEY_DOWN:
    case KEY_SEL:
    case KEY_C:
      Keypad_LockTimeoutCallback();
      break;

    default:
      break;
    }
    break;

  case UIM_MSC:
    //      switch (key)
    //      {
    //        case KEY_SEL:
    //          switch (App_Mode())
    //          {
    //            case APP_MODE_MSC:
    //              App_SetMode(APP_MODE_USB_AUDIO);
    //              KeyProcessed = SET;
    //              break;
    //
    //            case APP_MODE_USB_AUDIO:
    //              App_SetMode(APP_MODE_MSC);
    //              KeyProcessed = SET;
    //              break;
    //
    //            default:
    //              break;
    //          }
    //          break;
    //
    //        default:
    //          break;
    //      }
    break;

  case UIM_Player_Seeking:
    //      Player_AsyncCommand(PC_PAUSE, 0);
    break;

  case UIM_Init:
    break;
  }
}

void Keypad_KeyReleasedCallback(KEY_Typedef key)
{
  //trace("key %u released\n", key);

  if (UiState != UIS_INITIALIZED)
    return;

  if (KeyProcessed == SET)
  {
    KeyProcessed = RESET;
    return;
  }

  xTimerStart(xBacklightTimer, configTIMER_API_TIMEOUT_TICKS);

  xTimerStop(xKeyHoldTimer, configTIMER_API_TIMEOUT_TICKS);

  switch (ScreenMode)
  {
  case UIM_Player:
    switch (key)
    {
    case KEY_PPP:
    case KEY_BTN:
      Audio_CommandSync(AC_PLAY_PAUSE);
      break;

    case KEY_NEXT:
      Player_AsyncCommand(PC_NEXT, 0);
      break;

    case KEY_PREV:
      Player_AsyncCommand(PC_PREV, 0);
      break;

    default:
      break;
    }
    break;

  case UIM_Player_Seeking:
    SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player);
    Player_AsyncCommand(PC_SEEK, 0); /* restore */
    break;

  case UIM_Player_HalfLocked:
  case UIM_Player_Locked:
  case UIM_Player_HalfUnlocked:
  case UIM_Init:
  case UIM_MSC:
    break;
  }
}

void Keypad_HoldTimeoutCallback(xTimerHandle xTimer)
{
  KEY_Typedef key = Keypad_CurrentKey();

  if (KeyProcessed == SET)
  {
    KeyProcessed = RESET;
    return;
  }

  if ((key == KEY_PPP && ScreenMode != UIM_Player_Locked) || key == KEY_BTN)
  {
    System_SetState(SS_SHUTDOWN);
    return;
  }

  switch (ScreenMode)
  {
  case UIM_Player:
  case UIM_Player_Seeking:
    switch (key)
    {
    case KEY_NEXT:
    case KEY_PREV:
      SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player_Seeking);
      Player_AsyncCommand(PC_SEEK, ScreenSubMode * 1000);
      break;

    case KEY_UP:
    case KEY_DOWN:
      Audio_ChangeVolume(ScreenSubMode);
      break;

    default:
      break;
    }
    break;

  default:
    break;
  }
}

void Screen_DisableBacklightCallback(xTimerHandle xTimer)
{
  Disp_SetBKL(DISABLE);
}

void Keypad_LockTimeoutCallback(void)
{
  switch (ScreenMode)
  {
  case UIM_Player_HalfLocked: //lock failed
    SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player);
    break;

  case UIM_Player_HalfUnlocked: //unlock failed
    SetVariable(VAR_ScreenMode, ScreenMode, UIM_Player_Locked);
    break;

  default:
    break;
  }
}

void Vibrator_SendSignal(u16 ms)
{
//  Vibrator_Enable();
//  Scheduler_PutTask(ms, Vibrator_Disable, NO_REPEAT);
}
