/*
 * config.h
 *
 *  Created on: Apr 29, 2013
 *      Author: otsaregorodtsev
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdarg.h>
#include <nuttx/compiler.h>

#define CONFIG_MM_REGIONS 1
#define CONFIG_MM_MULTIHEAP 1
#define __KERNEL__ 1
#define CONFIG_NUTTX_KERNEL 1

#define CONFIG_LIBC_FLOATINGPOINT 1

#undef  OK
#define OK 0

typedef signed int         intptr_t;
typedef unsigned int       uintptr_t;

//#define DEBUGASSERT assert_param
#define DEBUGASSERT(...)

/* Memory Management */

#define mlldbg(...)
#define mvdbg(...)

struct mallinfo
{
  int arena;    /* This is the total size of memory allocated
                 * for use by malloc in bytes. */
  int ordblks;  /* This is the number of free (not in use) chunks */
  int mxordblk; /* Size of the largest free (not in use) chunk */
  int uordblks; /* This is the total size of memory occupied by
                 * chunks handed out by malloc. */
  int fordblks; /* This is the total size of memory occupied
                 * by free (not in use) chunks.*/
};

#endif /* CONFIG_H_ */
