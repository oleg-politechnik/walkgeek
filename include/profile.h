/*
 * profile.h
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

/* Define to prevent recursive inclusion ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef PROFILE_H_
#define PROFILE_H_

/* Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "software_conf.h"
#include "cpu_config.h"

/* Exported defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define Profiler_EnterFunc(func) Profiler_DoEnterFunc(#func, func)

/* Exported types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum
{
  PF_TOTAL,
  PF_PRELOAD,
  PF_CODEC_TOTAL,
  PF_CODEC_DECODE,

//  PF_CELT_EBANDS,
//  PF_CELT_1,
//  PF_CELT_2,
//  PF_CELT_3,
//  PF_CELT_4,
//  PF_CELT_5,
//  PF_CELT_6,
  PF_CELT_7,
//  PF_CELT_8,
//  PF_CELT_9,
//  PF_CELT_10,
//  PF_CELT_11,
//  PF_CELT_12,
//  PF_CELT_13,
//  PF_CELT_14,
  PF_CELT_15,
//  PF_CELT_16,
//  PF_CELT_17,
//  PF_CELT_18,
//  PF_CELT_19,
//  PF_CELT_20,

  PF_MAX
} ProfileFunction_Typedef;

/* Exported functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef PROFILING
void Profiler_Init(void);
void Profiler_SetTotal(u32 total);
void Profiler_Print(void);

static inline void Profiler_DoEnterFunc(char *func_name, ProfileFunction_Typedef func)
{
  extern u32 profile_entry_points[PF_MAX];
  extern char* profile_func_names[PF_MAX];

  assert_param(func < PF_MAX);

  profile_func_names[func] = func_name;

  profile_entry_points[func] = uS_Profiler_GetValue();
}

static inline void Profiler_ExitFunc(ProfileFunction_Typedef func)
{
  extern u32 profile_entry_points[PF_MAX];
  extern u32 profile_results[PF_MAX];

  assert_param(func < PF_MAX);

  profile_results[func] += uS_Profiler_GetDiff(profile_entry_points[func]);
}

unsigned int Profiler_GetResult(ProfileFunction_Typedef func);
#else
#define Profiler_Init()
#define Profiler_DoEnterFunc(...)
#define Profiler_ExitFunc(...)
#define Profiler_Print()
#define Profiler_GetResult(...) 0
#endif

/* Exported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Exported static inline functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#endif /* PROFILE_H_ */
