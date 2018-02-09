/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gnsdk_platform.h - Contains platform-specific definitions.
 * USE THIS FILE TO OVERRIDE THE DEFINITIONS IN gnsdk_defines.h
 */

 #ifndef _GNSDK_DEFINES_H_
 #error gnsdk_platforms.h should not be included directly. Use #include "gnsdk_defines.h"
 #endif

/*
 * Windows Flavor
 */

#ifndef _GNSDK_PLATFORM_H_
#define _GNSDK_PLATFORM_H_


#define GNSDK_WINDOWS
#define GNSDK_WINDOWS_X86
#define GNSDK_WINDOWS_X86_32
#define GNSDK_PLATFORM_STR		"Windows (x86)"


#define GNSDK_EXPORTED_API	__declspec(dllexport)
#define GNSDK_IMPORTED_API	__declspec(dllimport)
#define	GNSDK_CALLBACK_API	__cdecl
#define GNSDK_API			__stdcall

#include <crtdbg.h>
#define GNSDK_ASSERT(exp)	_ASSERT(exp)

#define GNSDK_INT64_T
typedef __int64 gnsdk_int64_t;

#define GNSDK_UINT64_T
typedef unsigned __int64 gnsdk_uint64_t;

#include <stddef.h>


#endif /* _GNSDK_PLATFORM_H_ */

