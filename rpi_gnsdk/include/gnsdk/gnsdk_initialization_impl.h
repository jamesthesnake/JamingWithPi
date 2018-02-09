/* Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_initilization.h
 *
 * Thread-safe Initialize/Shutdown helper code.
 *
 */

#ifndef GNSDK_INITIALIZATION_IMPL_H
#define GNSDK_INITIALIZATION_IMPL_H

#include "gnsdk_initialization.h"

#ifdef __cplusplus
extern "C"{
#endif

/* start address function type */
typedef gnsdk_error_t (GNSDK_CALLBACK_API *gnsdk_library_init_function_t)(gnsdk_void_t* arg);

/* count of successful runs through init function */
static	gcsl_spinlock_t		_g_init_lock = GCSL_SPINLOCK_INIT;
static	gcsl_uint32_t		_g_initialized = 0;


/* intialization test helper */
gnsdk_uint32_t GNSDK_LIBRARY_INITCHECK  (void)
{
	GNSDK_ASSERT(_g_initialized > 0);
	return _g_initialized;
}

static gnsdk_error_t
_gnsdk_library_initialize(gnsdk_library_init_function_t init_func, gnsdk_void_t* init_arg)
{
	gnsdk_error_t	error = GNSDKERR_NoError;

	GCSL_DOSTACKTRACE();

	gcsl_spinlock_lock(&_g_init_lock);
	{
		/* first initialize does the work */
		if (0 == _g_initialized)
		{
			/* call initialization callback */
			if (init_func)
			{
				error = init_func(init_arg);
			}
		}

		/* success! up the init'd count */
		if (!error)
			_g_initialized += 1;
	}
	gcsl_spinlock_unlock(&_g_init_lock);

	if (error)
	{
		/* negative initialized = not so fine and dandy */
		GNSDK_ASSERT(!error);
		return error;
	}

	/* positive initialized = fine and dandy */
	return GNSDKERR_NoError;
}

static gnsdk_error_t
_gnsdk_library_shutdown(gnsdk_library_init_function_t shutdown_func, gnsdk_void_t* shutdown_arg)
{
	gcsl_spinlock_t	spinlock_init = GCSL_SPINLOCK_INIT;
	gcsl_error_t	error         = GCSL_SUCCESS;

	GCSL_DOSTACKTRACE();

	if (0 == _g_initialized)
	{
		GNSDK_ASSERT(_g_initialized > 0);
		return GNSDKERR_NotInited;
	}

	gcsl_spinlock_lock(&_g_init_lock);
	{
		/* last de-init does the work */
		if (1 == _g_initialized)
		{
			if (shutdown_func)
				error = shutdown_func(shutdown_arg);
		}

		_g_initialized -= 1;
	}
	gcsl_spinlock_unlock(&_g_init_lock);

	if (0 == _g_initialized)
	{
		gcsl_spinlock_delete(&_g_init_lock);
		_g_init_lock = spinlock_init;
	}

	return error;
}


#ifdef __cplusplus
}
#endif

#endif	/* ifndef GNSDK_INITIALIZATION_IMPL_H */
