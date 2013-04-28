/***********************************************************************/
/*                                                                     */
/*  SYSCALLS.C:  System Calls                                          */
/*  most of this is from newlib-lpc and a Keil-demo                    */
/*                                                                     */
/*  These are "reentrant functions" as needed by                       */
/*  the WinARM-newlib-config, see newlib-manual.                       */
/*  Collected and modified by Martin Thomas                            */
/*                                                                     */
/***********************************************************************/

/* adapted for the SAM7 "serial.h" mthomas 10/2005 */

#include <stdlib.h>
#include <reent.h>
#include <sys/stat.h>
#include "ff.h"
#include "stm32f4xx_conf.h"
#include "disp_1100.h"
//#include "debug/debug.h"

//_ssize_t _read_r(
//    struct _reent *r,
//    int file,
//    void *ptr,
//    size_t len)
//{
//	char c;
//	int  i;
//	unsigned char *p;
//
//	p = (unsigned char*)ptr;
//
//	for (i = 0; i < len; i++) {
//		// c = uart0Getch();
//		// c = uart0GetchW();
//		while ( !uart0_kbhit() ) ;
//		c = (char) uart0_getc();
//		if (c == 0x0D) {
//			*p='\0';
//			break;
//		}
//		*p++ = c;
//		uart0_putc(c);
//	}
//	return len - i;
//}


//_ssize_t _write_r(struct _reent *r, int file, const void *ptr, size_t len)
//{
//    int i;
//    const unsigned char *p;
//
//    p = (const unsigned char*) ptr;
//
//    for (i = 0; i < len; i++) {
//        if (*p == '\n')
//            uart_putc('\r');
//        uart_putc(*p++);
//    }
//
//    return len;
//}

int _close_r(struct _reent *r, int file)
{
  return 0;
}

_off_t _lseek_r(struct _reent *r, int file, _off_t ptr, int dir)
{
  return (_off_t) 0; /*  Always indicate we are at file beginning.  */
}

int _fstat_r(struct _reent *r, int file, struct stat *st)
{
  /*  Always set as character device.				*/
  //    st->st_mode = S_IFCHR;
  /* assigned to strong type with implicit 	*/
  /* signed/unsigned conversion.  Required by 	*/
  /* newlib.					*/

  return 0;
}

int isatty(int file); /* avoid warning */

int isatty(int file)
{
  return 1;
}

#if 0
static void _exit (int n)
{
  label: goto label; /* endless loop */
}
#endif

/* "malloc clue function" from newlib-lpc/Keil-Demo/"generic" */

/**** Locally used variables. ****/
// mt: "cleaner": extern char* end;
extern char _end[]; /*  end is set in the linker command 	*/
/* file and is the end of statically 	*/
/* allocated data (thus start of heap).	*/

extern uint32_t _Min_Heap_Size;

static char *heap_ptr; /* Points to current end of the heap.	*/

/************************** _sbrk_r *************************************
 * Support function. Adjusts end of heap to provide more memory to
 * memory allocator. Simple and dumb with no sanity checks.

 *  struct _reent *r -- re-entrancy structure, used by newlib to
 *                      support multiple threads of operation.
 *  ptrdiff_t nbytes -- number of bytes to add.
 *                      Returns pointer to start of new heap area.
 *
 *  Note:  This implementation is not thread safe (despite taking a
 *         _reent structure as a parameter).
 *         Since _s_r is not used in the current implementation,
 *         the following messages must be suppressed.
 */
void * _sbrk_r(struct _reent *_s_r, ptrdiff_t nbytes)
{
  char *base; /*  errno should be set to  ENOMEM on error  */

  if (!heap_ptr)
  { /*  Initialize if first time through.  */
    heap_ptr = _end;
  }
  base = heap_ptr; /*  Point to end of heap.  */
  heap_ptr += nbytes; /*  Increase heap.  */

  assert_param(_Min_Heap_Size < (uint32_t) (_end - heap_ptr));

  return base; /*  Return pointer to start of new heap area.  */
}

void abort(void)
{
  while (1)
    ;
}
//
//#include <sys/stat.h>
//
//enum
//{
//    UART_FR_RXFE = 0x10, UART_FR_TXFF = 0x20, UART0_ADDR = 0x4000C000,
//};
//
//#define UART_DR(baseaddr) (*(unsigned int *)(baseaddr))
//#define UART_FR(baseaddr) (*(((unsigned int *)(baseaddr))+6))

int _close(int file)
{
  return 0;
}

int _fstat(int file, struct stat *st)
{
  //    st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int file)
{
  return 1;
}

int _lseek(int file, int ptr, int dir)
{
  return 0;
}

int _open(const char *name, int flags, int mode)
{
  return -1;
}

int _read(int file, char *ptr, int len)
{
  //    int todo;
  //    if (len == 0)
  //        return 0;
  //    while (UART_FR(UART0_ADDR) & UART_FR_RXFE)
  //        ;
  //    *ptr++ = UART_DR(UART0_ADDR);
  //    for (todo = 1; todo < len; todo++) {
  //        if (UART_FR(UART0_ADDR) & UART_FR_RXFE) {
  //            break;
  //        }
  //        *ptr++ = UART_DR(UART0_ADDR);
  //    } rteturn todo

  return -1;
}

//__errno

//static char *heap_end = 0;
//caddr_t _sbrk(int incr)
//{
//    extern char __cs3_heap_start; /* Defined by the linker */
//    extern char __cs3_heap_end; /* Defined by the linker */
//    char *prev_heap_end;
//    if (heap_end == 0) {
//        heap_end = &__cs3_heap_start;
//    }
//    prev_heap_end = heap_end;
//    if (heap_end + incr > &__cs3_heap_end) {
//        /* Heap and stack collision */
//        return (caddr_t) 0;
//    }
//    heap_end += incr;
//    return (caddr_t) prev_heap_end;
//}
//
int _write(int file, char *ptr, int len)
{
  //    int todo;
  //    for (todo = 0; todo < len; todo++) {
  //        UART_DR(UART0_ADDR) = *ptr++;
  //    }
  return len;
}

