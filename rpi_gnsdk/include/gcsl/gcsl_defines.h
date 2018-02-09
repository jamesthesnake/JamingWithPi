/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_defines.h - The type definitions used by the gracenote appl
 * and the definition of macros.
 */

#ifndef	_GCSL_DEFINES_H_
#define _GCSL_DEFINES_H_

#ifdef __cplusplus
	/* C++ likes these better */
	#define GCSL_NULL			(0)
	#define GCSL_EXTERN_C		extern "C"
	extern "C" {
#else
	#define GCSL_EXTERN_C
#endif

/* include platform dependent definitions first */
#include "gcsl_platform.h"


#ifdef GCSL_NOASSERT
	#undef GCSL_ASSERT
	#define GCSL_ASSERT(exp)
#endif

/*
 * Constants.
 */
#ifndef GCSL_FALSE
#define GCSL_FALSE				((gcsl_bool_t)(0))
#endif

#ifndef GCSL_TRUE
#define GCSL_TRUE				((gcsl_bool_t)(1))
#endif

#ifndef GCSL_NULL
#define GCSL_NULL				((gcsl_void_t*)(0))
#endif

/* filename maximium size */
#ifndef GCSL_MAX_PATH
#define	GCSL_MAX_PATH			260
#endif

#ifndef GCSL_MAX_FNAME
#define	GCSL_MAX_FNAME			256
#endif

#define GCSL_UINT8_MAX			((gcsl_uint8_t)0xFF)
#define GCSL_INT8_MAX			((gcsl_uint8_t)127)
#define GCSL_INT8_MIN			((gcsl_uint8_t)(GCSL_INT8_MAX - 1))

#define GCSL_UINT16_MAX			((gcsl_uint16_t)0xFFFF)
#define GCSL_INT16_MAX			((gcsl_uint16_t)32767)
#define GCSL_INT16_MIN			((gcsl_uint16_t)(GCSL_INT16_MAX - 1))

#define GCSL_UINT32_MAX			((gcsl_uint32_t)0xFFFFFFFF)
#define GCSL_INT32_MAX			((gcsl_uint32_t)2147483647)
#define GCSL_INT32_MIN			((gcsl_uint32_t)(GCSL_INT32_MAX - 1))

#define GCSL_UINT64_MAX			((gcsl_uint64_t)0xFFFFFFFFFFFFFFFF)
#define GCSL_INT64_MAX			((gcsl_uint64_t)9223372036854775807)
#define GCSL_INT64_MIN			((gcsl_uint64_t)(GCSL_INT64_MIN - 1))

/* Common loop impl macros */
#define JUMP_LOOP_START			for (;;) {
#define JUMP_LOOP_END			break; }

/* byte swapping helpers */
#define GCSL_BSWAP_32(x)		((((x) & 0xFF000000) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | (((x) & 0x000000FF) << 24) )
#define GCSL_BSWAP_16(x)		((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))

/*
 * Typedef
 */

#ifndef GCSL_VOID_T
#define GCSL_VOID_T
typedef void					gcsl_void_t;
#endif /* GCSL_VOID_T */

/* chars are set as 'unsigned' by compiler flags, but must remain 'char' here
 * to avoid compiler type complaints galor. */
#ifndef GCSL_CHAR_T
#define GCSL_CHAR_T
typedef char					gcsl_char_t;
#endif /* GCSL_CHAR_T */

#ifndef GCSL_BYTE_T
#define GCSL_BYTE_T
typedef unsigned char			gcsl_byte_t;
#endif /* GCSL_BYTE_T */

#ifndef GCSL_INT8_T
#define GCSL_INT8_T
typedef signed char				gcsl_int8_t;
#endif /* GCSL_INT8_T */

#ifndef GCSL_INT16_T
#define GCSL_INT16_T
typedef short					gcsl_int16_t;
#endif /* GCSL_INT16_T */

#ifndef GCSL_INT32_T
#define GCSL_INT32_T
typedef int						gcsl_int32_t;
#endif /* GCSL_INT32_T */

#ifndef GCSL_INT64_T
#define GCSL_INT64_T
typedef long long				gcsl_int64_t;
#endif /* GCSL_INT64_T */

#ifndef GCSL_UINT8_T
#define GCSL_UINT8_T
typedef unsigned char			gcsl_uint8_t;
#endif /* GCSL_UINT8_T */

#ifndef GCSL_UINT16_T
#define GCSL_UINT16_T
typedef unsigned short			gcsl_uint16_t;
#endif /* GCSL_UINT16_T */

#ifndef GCSL_UINT32_T
#define GCSL_UINT32_T
typedef unsigned int			gcsl_uint32_t;
#endif /* GCSL_UINT32_T */

#ifndef GCSL_UINT64_T
#define GCSL_UINT64_T
typedef unsigned long long		gcsl_uint64_t;
#endif /* GCSL_UINT64_T */

#ifndef GCSL_SIZE_T
#define GCSL_SIZE_T
typedef size_t					gcsl_size_t;
#endif /* GCSL_SIZE_T */

#ifndef GCSL_UINTPTR_T
#define GCSL_UINTPTR_T
typedef uintptr_t				gcsl_uintptr_t;
#endif /* GCSL_UINTPTR_T */

#ifndef GCSL_INTPTR_T
#define GCSL_INTPTR_T
typedef intptr_t				gcsl_intptr_t;
#endif /* GCSL_INTPTR_T */

#ifndef GCSL_STR_T
#define GCSL_STR_T
typedef gcsl_char_t*			gcsl_str_t;
#endif /* GCSL_STR_T */

#ifndef GCSL_CSTR_T
#define GCSL_CSTR_T
typedef const gcsl_char_t*		gcsl_cstr_t;
#endif /* GCSL_CSTR_T */

#ifndef GCSL_FLT32_T
#define GCSL_FLT32_T
typedef float					gcsl_flt32_t;
#endif /* GCSL_FLT32_T */

#ifndef GCSL_FLT64_T
#define GCSL_FLT64_T
typedef double					gcsl_flt64_t;
#endif /* GCSL_FLT64_T */

#ifndef GCSL_FLT128_T
#define GCSL_FLT128_T
typedef long double				gcsl_flt128_t;
#endif /* GCSL_FLT128_T */

#ifndef GCSL_BOOL_T
#define GCSL_BOOL_T
typedef char					gcsl_bool_t;
#endif /* GCSL_BOOL_T */

#ifndef GCSL_ERROR_T
#define GCSL_ERROR_T
typedef gcsl_uint32_t			gcsl_error_t;
#endif /* GCSL_ERROR_T */

#ifndef GCSL_UNICHAR_T
#define GCSL_UNICHAR_T
typedef unsigned short			gcsl_unichar_t;
#endif /* GCSL_UNICHAR_T */

#ifndef GCSL_CUNICHAR_T
#define GCSL_CUNICHAR_T
typedef const gcsl_unichar_t	gcsl_cunichar_t;
#endif /* GCSL_CUNICHAR_T */

#ifndef GCSL_UNISTR_T
#define GCSL_UNISTR_T
typedef gcsl_unichar_t*			gcsl_unistr_t;
#endif /* GCSL_UNISTR_T */

#ifndef GCSL_CUNISTR_T
#define GCSL_CUNISTR_T
typedef const gcsl_unichar_t*	gcsl_cunistr_t;
#endif /* GCSL_CUNISTR_T */

#ifndef GCSL_HANDLE_T
#define GCSL_HANDLE_T
	typedef gcsl_void_t*		gcsl_handle_t;
	#ifdef GCSL_STRICT_HANDLES
		#define GCSL_DECLARE_HANDLE(handle) 	struct handle##_s { gcsl_uint32_t magic; }; typedef struct handle##_s* handle
	#else
		#define GCSL_DECLARE_HANDLE(handle) 	typedef gcsl_handle_t handle
	#endif
#endif /* GCSL_HANDLE_T */



#ifdef __cplusplus
}
#endif

#endif /* _GCSL_DEFINES_H_ */
