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
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "common.h"

char *__env[1] = { 0 };
char **environ = __env;

void _exit(int rc)
{
  UNUSED(rc);
  assert_param(0);

  while(1)
    ;
}

int _open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
  errno = -ENOSYS;
  return -1; /* Always fails */
}

int _lseek(int file, int offset, int whence)
{
  if ((STDOUT_FILENO == file) || (STDERR_FILENO == file))
  {
    return 0;
  }

  errno = -EBADF;
  return -1;
}

int _close(int file)
{
  errno = EBADF;
  return -1;
}

int _fstat(int file, struct stat *st)
{
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
  UNUSED(file);
  UNUSED(ptr);
  UNUSED(len);

    errno = EBADF;
    return -1;
}

int newlib_heap_size;

void *_sbrk(int nbytes)
{
  extern unsigned int _sheap_newlib;
  extern unsigned int _ssram1;

  /* stm32f42/43 uCs have 2048K Flash and 192K non-CCM SRAM */
  int has_256K_sram = (*(volatile uint16_t *) 0x1FFF7A22 == 2048);
  char *_eheap_newlib = (char *) &_ssram1 + (has_256K_sram ? 64 : 0) * 1024;

  /* The statically held previous end of the heap, with its initialization. */
  static char *heap_ptr = (char *) &_sheap_newlib; /* Previous end */

  if ((unsigned int) heap_ptr + nbytes <= (unsigned int) _eheap_newlib)
  {
    void *base = heap_ptr;
    heap_ptr += nbytes;
    newlib_heap_size += nbytes;
    return base;
  }
  else
  {
    assert_param(!"No mem");

    errno = ENOMEM;
    return (void *) -1;
  }
}
