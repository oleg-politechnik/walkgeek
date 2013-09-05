/*
 * player_ui.c
 *
 * Copyright (c) 2013, Oleg Tsaregorodtsev
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
#include <FreeRTOS.h>
#include <timers.h>

#include "ui.h"
#include "disp_1100.h"
#include "player.h"
#include "audio_if.h"

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
extern uint32_t NeglectedDMA_Count;
extern sPlayerState PlayerState;
extern volatile u32 KeyProcessed;

/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum
{
  PSM_Uninitialized,
  PSM_Normal,
  PSM_Seeking,
  PSM_HalfLocked,
  PSM_Locked,
  PSM_HalfUnlocked
} PlayerScreenMode_Typedef;

typedef struct
{
  int hour;
  int minute;
  int second;
} TimePoint_Typedef;

/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void PlayerScreen_Init(void);
static void PlayerScreen_DeInit(void);
static void PlayerScreen_VariableChangedHandler(VAR_Index var);
static u16 PlayerScreen_KeyPressedHandler(KEY_Typedef key);
static u16 PlayerScreen_KeyHoldHandler(KEY_Typedef key);
static void PlayerScreen_KeyReleasedHandler(KEY_Typedef key);

static void LockTimeoutCallback(xTimerHandle xTimer);

static void TimePoint(u32 raw_mstime, TimePoint_Typedef *time);

/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Screen_Typedef PlayerScreen = {
        .Init = PlayerScreen_Init,
        .DeInit = PlayerScreen_DeInit,
        .UpdateVar = PlayerScreen_VariableChangedHandler,
        .KeyPressedHandler = PlayerScreen_KeyPressedHandler,
        .KeyHoldHandler = PlayerScreen_KeyHoldHandler,
        .KeyReleasedHandler = PlayerScreen_KeyReleasedHandler
};

static xTimerHandle xKeypadLockTimer;

static int ScreenSubMode;

static PlayerScreenMode_Typedef PlayerScreenMode;

/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void PlayerScreen_Init(void)
{
  PlayerScreenMode = PSM_Normal;

  xKeypadLockTimer = xTimerCreate((signed portCHAR *) "Keypad Lock Timer",
          configUI_LOCK_UNLOCK_TIMEOUT_MS, pdFALSE, (void *) LockTimeoutCallback,
          LockTimeoutCallback);

  assert_param(xKeypadLockTimer);

  UI_SyncVariable(VAR_AudioVolume);
  UI_SyncVariable(VAR_AudioStatus);
}

static void PlayerScreen_DeInit(void)
{
  PlayerScreenMode = PSM_Uninitialized;

  int result;

  result = xTimerDelete(xKeypadLockTimer, configTIMER_API_TIMEOUT_MS);
  configASSERT(result);
}

static void PlayerScreen_VariableChangedHandler(VAR_Index var)
{
  TimePoint_Typedef time;

  u8 slider_pos;
  u8 row;
  int rem;
  char state;
  bool double_channel;

  char str_buf[DISP_COL_COUNT * DISP_ROW_COUNT];

  char *str;

  sMetadata *metadata = &Player_GetState()->metadata;

  switch (var)
  {
    case VAR_HeadsetStatus:
#if HAS_HEADSET
      if (Player_GetState()->status == PS_PLAYING)
      {
        if (Audio_GetState() == AS_PLAYING && !BSP_IsHeadsetConnected())
        {
          Audio_CommandSync(AC_PAUSE);
        }
        else if (Audio_GetState() == AS_PAUSED && BSP_IsHeadsetConnected())
        {
          Audio_CommandSync(AC_PLAY);
        }
      }
#endif
      break;

    case VAR_AudioStatus:
      str = "  ";

      DISP_ALIGN_CENTER(0, str);

      if (PlayerScreenMode == PSM_Seeking)
      {
        if (ScreenSubMode < 0)
        {
          str = "<<";
        }
        else
        {
          str = ">>";
        }
      }
      else
      {
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
      }
      DISP_ALIGN_CENTER(0, str);
      break;

    case VAR_AudioVolume:
      sprintf(str_buf, "<%2i>", Audio_GetVolume());
      DISP_ALIGN_RIGHT(0, str_buf);
      break;

    case VAR_PlayerScreenMode:
      switch (PlayerScreenMode)
      {
        case PSM_HalfUnlocked:
          UI_EnableBacklight();
          /* no break here */
        case PSM_HalfLocked:
          Disp_ClearRow(DISP_LAST_ROW - 1);
          DISP_ALIGN_CENTER(DISP_LAST_ROW-1, "Press *");
          break;

        case PSM_Locked:
          Disp_ClearRow(DISP_LAST_ROW - 1);
          DISP_ALIGN_CENTER(DISP_LAST_ROW-1, "Locked");
          UI_DisableBacklight();
          break;

        default:
          UI_SyncVariable(VAR_PlayerTrack);
          break;
      }
      break;

    case VAR_PlayerScreenModeFromPlayerTrack:
       switch (PlayerScreenMode)
       {
         case PSM_HalfUnlocked:
         case PSM_HalfLocked:
           Disp_ClearRow(DISP_LAST_ROW - 1);
           DISP_ALIGN_CENTER(DISP_LAST_ROW-1, "Press *");
           break;

         case PSM_Locked:
           Disp_ClearRow(DISP_LAST_ROW - 1);
           DISP_ALIGN_CENTER(DISP_LAST_ROW-1, "Locked");
           break;

         default:
           break;
       }
       break;

    case VAR_PlayerTrack:
      UI_SyncVariable(VAR_PlayerScreenModeFromPlayerTrack);
      for (int i = 1; i <= DISP_LAST_ROW; i++)
      {
        Disp_ClearRow(i);
      }

      if (Player_GetState()->status == PS_STOPPED)
      {
        Disp_String(0, 1, " STOPPED", true);
        break;
      }

      if (Player_GetState()->status == PS_ERROR_FILE)
      {
        Disp_String(0, 1, Player_GetState()->metadata.error_string, true);
        break;
      }

      row = 1;

      str_buf[0] = 0;

      rem = sizeof(str_buf) - strlen(str_buf) - 1;

      //        if (*metadata->artist)
      //        {
      //          strncat(str_buf, metadata->artist, rem);
      //
      //          rem = sizeof(str_buf) - strlen(str_buf) - 1;
      //
      //          strncat(str_buf, " - ", rem);
      //        }
      //
      //        if (*metadata->title)
      //        {
      //          strncat(str_buf, metadata->title, rem);
      //        }
      //        else
      //        {
      if (metadata->file_path)
        strncat(str_buf, metadata->file_path, rem);
      //        }

      rem = sizeof(str_buf) - strlen(str_buf) - 1;

      if (*metadata->notes)
      {
        strncat(str_buf, " ", rem);

        rem = sizeof(str_buf) - strlen(str_buf) - 1;

        strncat(str_buf, metadata->notes, rem);

        rem = sizeof(str_buf) - strlen(str_buf) - 1;
      }

      if (strlen(str_buf) > 16 /*symbols per row*/* (DISP_LAST_ROW - 1) /*rows*/)
      {
        str_buf[16 * 4 - 1] = '~';
        str_buf[16 * 4] = 0;
      }

      Disp_String(0, row++, str_buf, true);

      TimePoint(metadata->mstime_max, &time);
      if (time.hour)
        sprintf(str_buf, "%01i:%02i:%02i", time.hour, time.minute, time.second);
      else
        sprintf(str_buf, "%i:%02i", time.minute, time.second);
      DISP_ALIGN_RIGHT(DISP_LAST_ROW, str_buf);
      UI_SyncVariable(VAR_PlayerPosition);
      break;

    case VAR_PlayerPosition:
      slider_pos = 0;
      if (metadata->mstime_max)
      {
        slider_pos = metadata->mstime_curr * DISP_X_COUNT
                / metadata->mstime_max;
      }

      for (u8 i = 0; i < DISP_X_COUNT; i++)
      {
        Disp_SetData(i, DISP_LAST_ROW + 1, (i < slider_pos) ? 0xFF : 0x00);
      }

      TimePoint(metadata->mstime_curr, &time);
      if (time.hour)
        sprintf(str_buf, "%01i:%02i:%02i", time.hour, time.minute, time.second);
      else
        sprintf(str_buf, "%i:%02i", time.minute, time.second);

      Disp_String(0, DISP_LAST_ROW, "         ", false);
      Disp_String(0, DISP_LAST_ROW, str_buf, false);
      break;

    default:
      break;
  }
}

void LockTimeoutCallback(xTimerHandle xTimer)
{
  switch (PlayerScreenMode)
  {
    case PSM_HalfLocked: //lock failed
      UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_Normal);
      break;

    case PSM_HalfUnlocked: //unlock failed
      UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_Locked);
      break;

    default:
      break;
  }
}

u16 PlayerScreen_KeyPressedHandler(KEY_Typedef key)
{
  int result;

  switch (PlayerScreenMode)
  {
    case PSM_Normal:
      switch (key)
      {
        case KEY_PREV:
          ScreenSubMode = -10;
          return configUI_PRESS_TIMEOUT_MS;

        case KEY_NEXT:
          ScreenSubMode = 10;
          return configUI_PRESS_TIMEOUT_MS;

        case KEY_DIR_START:
          Player_AsyncCommand(PC_DIR_START, 0);
          break;

        case KEY_DIR_END:
          Player_AsyncCommand(PC_DIR_END, 0);
          break;

        case KEY_RESET_PLAYER:
          Player_AsyncCommand(PC_DEINIT, 0);
          Player_AsyncCommand(PC_INIT, 0);
          break;

        case KEY_SAVE_PLAYER_STATE:
          Player_AsyncCommand(PC_SAVE_CURRENT_DIR, 0);
          break;

        case KEY_UP:
          ScreenSubMode = 1;
          Audio_ChangeVolume(ScreenSubMode);
          return configUI_PRESS_TIMEOUT_MS;

        case KEY_DOWN:
          ScreenSubMode = -1;
          Audio_ChangeVolume(ScreenSubMode);
          return configUI_PRESS_TIMEOUT_MS;

        case KEY_SEL:
          UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_HalfLocked);
          result = xTimerStart(xKeypadLockTimer, configTIMER_API_TIMEOUT_MS);
          configASSERT(result);
          break;

        default:
          break;
      }
      break;

    case PSM_HalfLocked:
      switch (key)
      {
        case KEY_ASTERICK:
          UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_Locked);
          KeyProcessed = SET;
          /* fall through */

        default:
          LockTimeoutCallback(0);
          break;
      }
      break;

    case PSM_Locked:
      switch (key)
      {
        case KEY_SEL:
          UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_HalfUnlocked);
          result = xTimerStart(xKeypadLockTimer, configTIMER_API_TIMEOUT_MS);
          configASSERT(result);
          break;

        default:
          break;
      }
      break;

    case PSM_HalfUnlocked:
      switch (key)
      {
        case KEY_ASTERICK:
          UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_Normal);
          KeyProcessed = SET;
          UI_EnableBacklight();

        case KEY_PPP:
        case KEY_UP:
        case KEY_DOWN:
        case KEY_SEL:
        case KEY_C:
          LockTimeoutCallback(0);
          break;

        default:
          break;
      }

    default:
      break;
  }

  return 0;
}

u16 PlayerScreen_KeyHoldHandler(KEY_Typedef key)
{
  switch (PlayerScreenMode)
  {
    case PSM_Normal:
    case PSM_Seeking:
      switch (key)
      {
        case KEY_NEXT:
        case KEY_PREV:
          if (Player_IsSeekable())
          {
            UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_Seeking);
            Player_AsyncCommand(PC_SEEK, ScreenSubMode * 1000);
            return configUI_PRESS_TICK_MS;
          }
          break;

        case KEY_UP:
        case KEY_DOWN:
          Audio_ChangeVolume(ScreenSubMode);
          return configUI_PRESS_TICK_MS;
          break;

        default:
          break;
      }
      break;

        default:
          break;
  }

  return 0;
}

void PlayerScreen_KeyReleasedHandler(KEY_Typedef key)
{
  if (key == KEY_BTN)
  {
    Audio_CommandSync(AC_PLAY_PAUSE);
    return;
  }

  switch (PlayerScreenMode)
  {
    case PSM_Normal:
      switch (key)
      {
        case KEY_PPP:
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

    case PSM_Seeking:
      UI_SetVariable(VAR_PlayerScreenMode, PlayerScreenMode, PSM_Normal);
      Player_AsyncCommand(PC_SEEK, 0); /* restore */
      break;

    default:
      break;
  }
}

void TimePoint(u32 raw_mstime, TimePoint_Typedef *time)
{
  time->second = raw_mstime / 1000;
  time->minute = time->second / 60;
  time->hour = time->minute / 60;
  time->second %= 60;
  time->minute %= 60;
}

bool PlayerScreen_IsLocked(void)
{
  return (PlayerScreenMode == PSM_Locked);
}
