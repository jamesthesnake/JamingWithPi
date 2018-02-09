/* Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gcsl_initilization.h
 *
 * Thread-safe Initialize/Shutdown helper code.
 *
 */

#ifndef GCSL_INITIALIZATION_IMPL_H
#define GCSL_INITIALIZATION_IMPL_H

#include "gcsl_initialization.h"

#ifdef __cplusplus
extern "C"{
#endif

/* start address function type */
typedef gcsl_error_t (GCSL_CALLBACK_API *gcsl_library_init_function_t)(gcsl_void_t* arg);

/* count of successful runs through init function */
static	gcsl_spinlock_t		_g_init_lock = GCSL_SPINLOCK_INIT;
static	gcsl_uint32_t		_g_initialized = 0;


/* intialization test helper */
gcsl_uint32_t GCSL_LIBRARY_INITCHECK  (void)
{
	GCSL_ASSERT(_g_initialized > 0);
	return _g_initialized;
}

static gcsl_error_t
_gcsl_library_initialize(gcsl_library_init_function_t init_func, gcsl_void_t* init_arg)
{
	gcsl_error_t	error = GCSL_SUCCESS;

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
				GCSL_ASSERT(!error);
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
		GCSL_ASSERT(!error);
		return GCSLERR_InitFailed;
	}

	/* positive initialized = fine and dandy */
	return GCSLERR_NoError;
}

static gcsl_error_t
_gcsl_library_shutdown(gcsl_library_init_function_t shutdown_func, gcsl_void_t* shutdown_arg)
{
	gcsl_spinlock_t	spinlock_init = GCSL_SPINLOCK_INIT;
	gcsl_error_t	error         = GCSL_SUCCESS;

	GCSL_DOSTACKTRACE();

	if (0 == _g_initialized)
	{
		GCSL_ASSERT(_g_initialized > 0);
		return GCSLERR_NotInited;
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

#endif	/* ifndef GCSL_INITIALIZATION_IMPL_H */
