/************************************************************************
 * mm/mm_user.c
 *
 *   Copyright (C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************/

/************************************************************************
 * Included Files
 ************************************************************************/

#include <nuttx/config.h>
#include <assert.h>
#include <nuttx/mm.h>
#include "cpu.h"

/************************************************************************
 * Pre-processor definition
 ************************************************************************/

/************************************************************************
 * Private Types
 ************************************************************************/

/************************************************************************
 * Public Data
 ************************************************************************/

/* This is the user heap */

struct mm_heap_s g_mmheap_user;

/************************************************************************
 * Private Functions
 ************************************************************************/

/************************************************************************
 * Public Functions
 ************************************************************************/

void CPU_InitUserHeap(void)
{
  mm_initialize(&g_mmheap_user, CPU_GetUserHeapStart(), CPU_GetUserHeapSize());
}

void print_user_heap_mallinfo()
{
  struct mallinfo info;

  mm_mallinfo(&g_mmheap_user, &info);

  printf("user heap status: %db free / %db alloc\n", info.fordblks, info.uordblks);
}

void *user_malloc(size_t size)
{
  void *buf = mm_malloc(&g_mmheap_user, size);
  assert_param(buf);
  return buf;
}

void *user_zalloc(size_t size)
{
  void *buf = mm_zalloc(&g_mmheap_user, size);
  assert_param(buf);
  return buf;
}

void user_free(void *mem)
{
//  printf("user_free: %p\n", mem);

  mm_free(&g_mmheap_user, mem);
}

void *user_calloc(size_t n, size_t elem_size)
{
  void *buf = mm_calloc(&g_mmheap_user, n, elem_size);
  assert_param(buf);
  return buf;
}

void *user_realloc(void *oldmem, size_t size)
{
  void *buf = mm_realloc(&g_mmheap_user, oldmem, size);

  assert_param(buf);

//  printf("user_realloc: %p->%p, %u\n", oldmem, buf, size);

  return buf;
}
