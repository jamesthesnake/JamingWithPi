/* Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_initilization_check.h
 *
 * Library initialization check helpers.
 * See: gnsdk_initilization.h
 *
 */

#ifndef GNSDK_INITIALIZATION_H
#define GNSDK_INITIALIZATION_H

#ifdef __cplusplus
extern "C"{
#endif

#ifndef GNSDK_SDKNAME
#error  GNSDK_SDKNAME not defined: GNSDK_SDKNAME must be set to the name of this SDK
#endif

/* create init check declaration for this library */
#define GNSDK_MACRO_CONCAT2(a, b)		a ## b
#define GNSDK_MACRO_CONCAT3(a, b, c)	a ## b ## c
#define GNSDK_MACRO_CREATENAME(a)		GNSDK_MACRO_CONCAT3(gnsdk_, a, _initchecks)
#define GNSDK_LIBRARY_INITCHECK			GNSDK_MACRO_CREATENAME(GNSDK_SDKNAME)

/* forward declaration */
gnsdk_uint32_t GNSDK_LIBRARY_INITCHECK(void);


/* initialization checking helpers */
#define	GNSDK_CHECK_INIT(error)		{ if (!GNSDK_LIBRARY_INITCHECK()) return (error); }
#define	GNSDK_CHECK_INIT_VOID()		{ if (!GNSDK_LIBRARY_INITCHECK()) return; }
#define	GNSDK_CHECK_INIT_BOOL()		(0 < GNSDK_LIBRARY_INITCHECK())
#define GNSDK_CHECK_INIT_ASSERT()	{ GNSDK_ASSERT(GNSDK_TRUE == GNSDK_CHECK_INIT_BOOL()); }

#ifdef __cplusplus
}
#endif

#endif	/* ifndef GNSDK_INITIALIZATION_H */
