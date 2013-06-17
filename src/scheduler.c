/*
 * scheduler.c
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
#include "scheduler.h"
#include <stdlib.h>
#include "system.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  s32 timeout_ms;
  u32 timeout_ms_reload;
  void *callback;
} Task_Typedef;

/* Private define ------------------------------------------------------------*/
#define SCHEDULER_MAX_TASK  20

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static Task_Typedef tasks[SCHEDULER_MAX_TASK];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static inline Task_Typedef* Task_Find(void *callback)
{
  u32 i;

  for (i = 0; i < SCHEDULER_MAX_TASK; ++i)
  {
    if (tasks[i].callback == callback)
    {
      return &tasks[i];
    }
  }

  return NULL;
}

void Scheduler_Reset(void)
{
  CPU_DisableInterrupts();
  {
    bzero(tasks, sizeof(tasks));
  }
  CPU_RestoreInterrupts();
}

FuncResult Scheduler_PutTask(u32 timeout_ms, void(*callback)(void),
        RepeatPolicy repeat)
{
  Task_Typedef* task;
  FuncResult ret = FUNC_ERROR;

  timeout_ms /= SCHEDULER_MS_GRANULARITY;

  assert_param(callback);
  assert_param(timeout_ms);

  CPU_DisableInterrupts();

  task = Task_Find(callback);
  if (task == NULL)
  {
    task = Task_Find(NULL); /* find free space */

    assert_param (task != NULL);

    task->callback = callback;
  }

  task->timeout_ms = timeout_ms;
  ret = FUNC_SUCCESS;

  if (repeat == REPEAT)
  {
    task->timeout_ms_reload = task->timeout_ms;
  }
  else
  {
    task->timeout_ms_reload = 0;
  }

  CPU_RestoreInterrupts();

  return ret;
}

void Scheduler_RemoveTask(void(*callback)(void))
{
  Task_Typedef* task;

  assert_param(callback);

  CPU_DisableInterrupts();
  {
    task = Task_Find(callback);
    if (task == NULL)
    {
      task = Task_Find(NULL);

      if (task != NULL)
      {
        task->callback = NULL;
      }
    }
  }
  CPU_RestoreInterrupts();
}

void Scheduler_1msCycle(void)
{
  u32 i;
  void (*callback)(void);

  static u32 counter;
  counter++;
  counter %= SCHEDULER_MS_GRANULARITY;
  if (counter > 0)
    return;

  CPU_DisableInterrupts();

  for (i = 0; i < SCHEDULER_MAX_TASK; ++i)
  {
    callback = 0;

    if (tasks[i].callback != NULL)
    {
      if (tasks[i].timeout_ms > 0)
      {
        tasks[i].timeout_ms -= 1;
      }

      if (tasks[i].timeout_ms == 0)
      {
        callback = tasks[i].callback;
        if (tasks[i].timeout_ms_reload > 0)
        {
          tasks[i].timeout_ms = tasks[i].timeout_ms_reload;
        }
        else
        {
          tasks[i].callback = NULL;
        }
      }
    }

    if (callback)
    {
      (*callback)();
    }
  }

  CPU_RestoreInterrupts();
}
