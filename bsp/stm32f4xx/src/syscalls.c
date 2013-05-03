/*
 * http://www.embecosm.com/appnotes/ean9/ean9-howto-newlib-1.0.html
 *
 * Howto: Porting newlib
 * A Simple Guide
 *
 * Jeremy Bennett
 * Embecosm
 *
 * Application Note 9. Issue 1
 * July 2010
 *
 * Copyright (c) 2010 Embecosm Limited
 */

#include <stdlib.h>
#include <sys/stat.h>
/*#include "ff.h"*/
#include "stm32f4xx_conf.h"
#include "disp_1100.h"
#include <nuttx/mm.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

/* XXX
 * #include <errno.h>
 * #undef errno
 * extern int errno;
 *
 */










char *__env[1] = { 0 };
char **environ = __env;

void _exit(int rc)
{
  UNUSED(rc);
  assert_param(0);

  while(1)
    ;
}

int _close(int file)
{
  errno = EBADF;

  //  if (file < FILE_MIN_USER || file > FILE_MAX_USER)
  //    return -1;

  return 0; //?????
}

int _fstat(int file, struct stat *st)
{
  //fixme
  if ((STDOUT_FILENO == file) || (STDERR_FILENO == file))
  {
    st->st_mode = S_IFCHR;
    return 0;
  }
  else
  {
    errno = EBADF;
    return -1;
  }
}

int _getpid()
{
  return 1; /* Success */
}

int _isatty(int file)
{
  if ((file == STDOUT_FILENO) || (file == STDERR_FILENO))
  {
    return 1;
  }
  else
  {
    errno = EBADF;
    return -1;
  }
}

int _kill(int pid, int sig)
{
  UNUSED(pid);
  UNUSED(sig);

  errno = EINVAL;
  return -1; /* Always fails */
}



int _read(int file, char *ptr, int len)
{
  {
    errno = EBADF;
    return -1;
  }
}



void *_sbrk(int nbytes)
{
  extern unsigned int _estack;
  extern unsigned int _ssram1;

  /* The statically held previous end of the heap, with its initialization. */
  static void *heap_ptr = (void *) &_estack; /* Previous end */

  int has_256K_sram = (*(volatile uint16_t *) 0x1FFF7A22 == 2048);
  void *_eheap = &_ssram1 + (has_256K_sram ? 64 : 0) * 1024;

  if (heap_ptr + nbytes < _eheap)
  {
    void *base = heap_ptr;
    heap_ptr += nbytes;
    return base;
  }
  else
  {
    errno = ENOMEM;
    return (void *) -1;
  }
}
