/* ***** BEGIN LICENSE BLOCK ***** 
 * Version: RCSL 1.0/RPSL 1.0 
 *  
 * Portions Copyright (c) 1995-2002 RealNetworks, Inc. All Rights Reserved. 
 *      
 * The contents of this file, and the files included with this file, are 
 * subject to the current version of the RealNetworks Public Source License 
 * Version 1.0 (the "RPSL") available at 
 * http://www.helixcommunity.org/content/rpsl unless you have licensed 
 * the file under the RealNetworks Community Source License Version 1.0 
 * (the "RCSL") available at http://www.helixcommunity.org/content/rcsl, 
 * in which case the RCSL will apply. You may also obtain the license terms 
 * directly from RealNetworks.  You may not use this file except in 
 * compliance with the RPSL or, if you have a valid RCSL with RealNetworks 
 * applicable to this file, the RCSL.  Please see the applicable RPSL or 
 * RCSL for the rights, obligations and limitations governing use of the 
 * contents of the file.  
 *  
 * This file is part of the Helix DNA Technology. RealNetworks is the 
 * developer of the Original Code and owns the copyrights in the portions 
 * it created. 
 *  
 * This file, and the files included with this file, is distributed and made 
 * available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL SUCH WARRANTIES, 
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. 
 * 
 * Technology Compatibility Kit Test Suite(s) Location: 
 *    http://www.helixcommunity.org/content/tck 
 * 
 * Contributor(s): 
 *  
 * ***** END LICENSE BLOCK ***** */

/**************************************************************************************
 * Fixed-point MP3 decoder
 * Jon Recker (jrecker@real.com), Ken Cooke (kenc@real.com)
 * June 2003
 *
 * assembly.h - assembly language functions and prototypes for supported platforms
 *
 * - inline rountines with access to 64-bit multiply results 
 * - x86 (_WIN32) and ARM (ARM_ADS, _WIN32_WCE) versions included
 * - some inline functions are mix of asm and C for speed
 * - some functions are in native asm files, so only the prototype is given here
 *
 * MULSHIFT32(x, y)    signed multiply of two 32-bit integers (x and y), returns top 32 bits of 64-bit result
 * FASTABS(x)          branchless absolute value of signed integer x
 * CLZ(x)              count leading zeros in x
 * MADD64(sum, x, y)   (Windows only) sum [64-bit] += x [32-bit] * y [32-bit]
 * SHL64(sum, x, y)    (Windows only) 64-bit left shift using __int64
 * SAR64(sum, x, y)    (Windows only) 64-bit right shift using __int64
 */

#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H

#if defined(__GNUC__) && defined (SIMULATOR)

typedef long long Word64;

static __inline int MULSHIFT32(int x, int y)
{
  return x * y;
}

static __inline int FASTABS(int x)
{
	int sign;

	sign = x >> (sizeof(int) * 8 - 1);
	x ^= sign;
	x -= sign;

	return x;
}

static __inline int CLZ(int x)
{
	int numZeros;

	if (!x)
	return (sizeof(int) * 8);

	numZeros = 0;
	while (!(x & 0x80000000)) {
		numZeros++;
		x <<= 1;
	}

	return numZeros;
}

/* MADD64, SHL64, SAR64:
 * write in assembly to avoid dependency on run-time lib for 64-bit shifts, muls
 *  (sometimes compiler thunks to function calls instead of code generating)
 * required for Symbian emulator
 */
//#ifdef __CW32__
//typedef long long Word64;
//#else
//typedef __int64 Word64;
//#endif
//
static __inline Word64 MADD64(Word64 sum, int x, int y)
{
  return (sum + ((Word64)x * y));
}
//
//static __inline Word64 SHL64(Word64 x, int n)
//{
//	unsigned int xLo = ((unsigned int *)&x)[0];
//	int xHi = ((int *)&x)[1];
//	unsigned char nb = (unsigned char)n;
//
//	if (n < 32) {
//		__asm {
//			mov edx, xHi
//			mov eax, xLo
//			mov cl, nb
//			shld edx, eax, cl
//			shl eax, cl
//		}
//	} else if (n < 64) {
//		/* shl masks cl to 0x1f */
//		__asm {
//			mov edx, xLo
//			mov cl, nb
//			xor eax, eax
//			shl edx, cl
//		}
//	} else {
//		__asm {
//			xor edx, edx
//			xor eax, eax
//		}
//	}
//}
//
static __inline Word64 SAR64(Word64 x, int n)
{
  return x >> n;
}

#elif defined(__GNUC__) && defined(ARM)

/**************************************************************************************
 * Fixed-point HE-AAC decoder
 * Jon Recker (jrecker@real.com)
 * February 2005
 *
 * assembly.h - inline assembly language functions and prototypes
 *
 * MULSHIFT32(x, y) 		signed multiply of two 32-bit integers (x and y),
 *                            returns top 32-bits of 64-bit result
 * CLIPTOSHORT(x)			convert 32-bit integer to 16-bit short,
 *                            clipping to [-32768, 32767]
 * FASTABS(x)               branchless absolute value of signed integer x
 * CLZ(x)                   count leading zeros on signed integer x
 * MADD64(sum64, x, y)		64-bit multiply accumulate: sum64 += (x*y)
 **************************************************************************************/

static __inline__ int MULSHIFT32(int x, int y) {
	/* important rules for smull RdLo, RdHi, Rm, Rs:
	 *     RdHi and Rm can't be the same register
	 *     RdLo and Rm can't be the same register
	 *     RdHi and RdLo can't be the same register
	 * Note: Rs determines early termination (leading sign bits) so if you want to specify
	 *   which operand is Rs, put it in the SECOND argument (y)
	 * For inline assembly, x and y are not assumed to be R0, R1 so it shouldn't matter
	 *   which one is returned. (If this were a function call, returning y (R1) would
	 *   require an extra "mov r0, r1")
	 */
	int zlow;
//    __asm__ volatile ("smull %0,%1,%2,%3" : "=&r" (zlow), "=r" (y) : "r" (x), "1" (y)) ;
	__asm__ volatile ("smull %0,%1,%2,%3" : "=&r" (zlow), "=r" (y) : "r" (x), "1" (y) : "cc");
	return y;
}

static __inline short CLIPTOSHORT(int x) {
	int sign;

	/* clip to [-32768, 32767] */
	sign = x >> 31;
	if (sign != (x >> 15))
		x = sign ^ ((1 << 15) - 1);

	return (short) x;
}

static __inline int FASTABS(int x) {
//	int sign;
//
//	sign = x >> (sizeof(int) * 8 - 1);
//	x ^= sign;
//	x -= sign;
//
//	return x;

	int t = 0; /*Really is not necessary to initialiaze only to avoid warning*/

	__asm__ volatile (
			"eor %0,%2,%2, asr #31;"
			"sub %0,%1,%2, asr #31;"
			: "=&r" (t)
			: "0" (t), "r" (x)
	);

	return t;
}

static __inline int CLZ(int x) {
	int numZeros;

	/*if (!x)
	 return (sizeof(int) * 8);

	 numZeros = 0;
	 while (!(x & 0x80000000)) {
	 numZeros++;
	 x <<= 1;
	 }*/

	__asm__ ("clz %0, %1" : "=r" (numZeros) : "r" (x) : "cc");

	return numZeros;
}

typedef long long Word64;

typedef union _U64 {
	Word64 w64;
	struct {
		/* ARM ADS = little endian */
		unsigned int lo32;
		signed int hi32;
	} r;
} U64;

static __inline Word64 MADD64(Word64 sum64, int x, int y) {
	U64 u;
	u.w64 = sum64;

	__asm__ volatile ("smlal %0,%1,%2,%3" : "+&r" (u.r.lo32), "+&r" (u.r.hi32) : "r" (x), "r" (y) : "cc");

	return u.w64;
}

static __inline Word64 SAR64(Word64 x, int n) {
	return x >> n;
}

#else

#error Unsupported platform in assembly.h

#endif	/* platforms */

#endif /* _ASSEMBLY_H */
