/* Copyright (c) 2007 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gcsl_initilization_check.h
 *
 * Library initialization check helpers.
 * See: gcsl_initilization.h
 *
 */

#ifndef GCSL_INITIALIZATION_H
#define GCSL_INITIALIZATION_H

#ifdef __cplusplus
extern "C"{
#endif 

#ifndef GCSL_LIBNAME
#error  GCSL_LIBNAME not defined: GCSL_LIBNAME must be set to the name of this library
#endif

/* create init check declaration for this library */
#define GCSL_MACRO_CONCAT2(a, b)		a ## b
#define GCSL_MACRO_CONCAT3(a, b, c)		a ## b ## c
#define GCSL_MACRO_CREATENAME(a)		GCSL_MACRO_CONCAT3(gcsl_, a, _initchecks)
#define GCSL_LIBRARY_INITCHECK			GCSL_MACRO_CREATENAME(GCSL_LIBNAME)

/* forward declaration */
gcsl_uint32_t GCSL_LIBRARY_INITCHECK(void);


/* initialization checking helpers */
#define	GCSL_CHECK_INIT(error)		{ if (!GCSL_LIBRARY_INITCHECK()) return (error); }
#define	GCSL_CHECK_INIT_VOID()		{ if (!GCSL_LIBRARY_INITCHECK()) return; }
#define	GCSL_CHECK_INIT_BOOL()		(0 < GCSL_LIBRARY_INITCHECK())
#define GCSL_CHECK_INIT_ASSERT()	{ GCSL_ASSERT(GCSL_TRUE == GCSL_CHECK_INIT_BOOL()); }

#ifdef __cplusplus
}
#endif

#endif	/* ifndef GCSL_INITIALIZATION_H */
