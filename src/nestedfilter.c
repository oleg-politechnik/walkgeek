/*
 * nestedfilter.c
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
#include "nestedfilter.h"
#include <malloc.h>

/* Imported variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private define ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private macro ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private function prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Private functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
NestedFilterSet_Typedef *NestedFilter_Init(u8 filter_count,
        u8 filter_buffer_size)
{
  int i;
  NestedFilterSet_Typedef *nfs = malloc(sizeof(NestedFilterSet_Typedef));
  nfs->count = filter_count;
  nfs->filters = malloc(sizeof(NestedFilter_Typedef) * filter_count);

  for (i = 0; i < filter_count; i++)
  {
    nfs->filters[i].size = filter_buffer_size;
    nfs->filters[i].pos = 0;
    nfs->filters[i].buf = malloc(sizeof(nfpoint_t) * filter_buffer_size);
    memset(nfs->filters[i].buf, 0, sizeof(nfpoint_t) * filter_buffer_size);
  }

  return nfs;
}

void NestedFilter_AddMeasure(NestedFilterSet_Typedef *nfs, nfpoint_t p, VAR_Index var_ix)
{
  int filter_ix = 0;
  u8 i;
  nfpoint_aggregate_t temp_avg_value;
  NestedFilter_Typedef *nf;

  do
  {
    nf = &nfs->filters[filter_ix];

    nf->buf[nf->pos] = p;

    nf->pos++;
    if (nf->pos < nf->size)
    {
      return;
    }

    nf->pos = 0;
    temp_avg_value = 0;
    for (i = 0; i < nf->size; i++)
    {
      temp_avg_value += nf->buf[i];
    }

    temp_avg_value /= nf->size;

    p = temp_avg_value;

    filter_ix++;
  } while (filter_ix < nfs->count);

  SetVariable(var_ix, nfs->value, temp_avg_value);
}

nfpoint_t NestedFilter_GetValue(NestedFilterSet_Typedef *nfs)
{
  return nfs->value;
}
