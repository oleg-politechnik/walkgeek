/*
 * common.h
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
#ifndef COMMON_H_
#define COMMON_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "types.h"
#include "trace.h"
#include "assert.h"

/* Exported defines ----------------------------------------------------------*/
#ifdef SIMULATOR
# define RAM_FUNC
#else
# define RAM_FUNC __attribute__ ((section(".fastcode")))
#endif

#define ICODE_ATTR      /*__attribute__ ((section(".fastcode")))*/

#define _BV(shift)  (1 << shift)

#define SIZE_OF(array)  (sizeof(array) / sizeof(array[0]))

#define CHECK_VOID(expr) if (!(expr)) return;
#define CHECK(expr, retval) if (!(expr)) return retval;

#define INC_WRAP(var, max_val) do { var++; if (var >= max_val) var = 0; } while(0);

#ifndef MIN
# define MIN(a,b)  ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
# define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

#define UNUSED(var) (void)var

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  FUNC_SUCCESS,
  FUNC_ERROR,
  FUNC_NOT_SUCCESS
} FuncResult;

typedef enum
{
  false = 0,
  true
} bool;

/* Exported macro ------------------------------------------------------------*/
#define F1_2            "%1u.%02u"
#define FLOAT_TO_1_2(f) (unsigned int) (f), (unsigned int) (((f) - (unsigned int) (f)) * 100)

/* Exported functions --------------------------------------------------------*/


#endif /* COMMON_H_ */
