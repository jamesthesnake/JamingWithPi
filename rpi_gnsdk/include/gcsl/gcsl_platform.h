/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_platform.h - Contains platform-specific definitions.
 * USE THIS FILE TO OVERRIDE THE DEFINITIONS IN gcsl_defines.h
 */

 #ifndef _GCSL_DEFINES_H_
 #error gcsl_platforms.h should not be included directly. Use #include "gcsl_defines.h"
 #endif

/*
 * Linux ARM 32-bit Flavor
 */

#ifndef _GCSL_PLATFORM_H_
#define _GCSL_PLATFORM_H_

/* platform identifiers */
#define GCSL_LINUX
#define GCSL_LINUX_ARM
#define GCSL_LINUX_ARM_32

/* platform specificities */
#define GCSL_PLATFORM_LITTLE_ENDIAN			1
#define GCSL_PLATFORM_BIG_ENDIAN			0
#define GCSL_PLATFORM_FS_CASE_SENSITIVE		1
#define GCSL_PLATFORM_HARDWARE_FLOAT		1
#define GCSL_PLATFORM_HARDWARE_64BIT_ARITH	0
#define GCSL_PLATFORM_SOFTWARE_64BIT_ARITH	1

#define GCSL_PLATFORM_DIR_DELIM_CHAR		'/'
#define GCSL_PLATFORM_DIR_DELIM_STR			"/"

#define GCSL_EXPORTED_API
#define GCSL_IMPORTED_API
#define	GCSL_CALLBACK_API

#define _XOPEN_SOURCE 500 /* for pread, pwrite */

#include <assert.h>
#define GCSL_ASSERT(exp)					assert(exp)

#include <stddef.h> /* for size_t */
#include <stdarg.h> /* for va_list */


#define GCSL_INTPTR_T
typedef long int							gcsl_intptr_t;

#define GCSL_UINTPTR_T
typedef unsigned long int					gcsl_uintptr_t;

#define GCSL_SIZE_T
typedef unsigned long						gcsl_size_t;


/* pthread_spinlock_t requires -D_XOPEN_SOURCE=600, ok but,
** I can't seem to find a PTHREAD_SPINLOCK_INITIALIZER anywhere
** so we're just going to use a mutex */
#include <pthread.h>

#define GCSL_SPINLOCK_T
typedef pthread_mutex_t						gcsl_spinlock_t;

#define GCSL_SPINLOCK_INIT					PTHREAD_MUTEX_INITIALIZER

#define GCSL_THREAD_STORE_KEY				pthread_key_t

/* byte swapping from native to LE/BE */
#define GCSL_BSWAP32_TO_LE(x)		(x)
#define GCSL_BSWAP32_TO_BE(x)		GCSL_BSWAP_32(x)

#define GCSL_BSWAP32_FROM_LE(x)		(x)
#define GCSL_BSWAP32_FROM_BE(x)		GCSL_BSWAP_32(x)


#endif /* _GCSL_PLATFORM_H_ */
