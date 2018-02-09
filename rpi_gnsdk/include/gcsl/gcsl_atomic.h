/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_atomic.h - Atomic counter functions
 */

#ifndef	_GCSL_ATOMIC_H_
#define _GCSL_ATOMIC_H_

#ifdef __cplusplus
extern "C"{
#endif 


/****** atomic library functions */
gcsl_error_t	gcsl_atomic_initialize		(void);
gcsl_error_t	gcsl_atomic_shutdown		(void);

gcsl_cstr_t		gcsl_atomic_get_version		(void);
gcsl_cstr_t		gcsl_atomic_get_build_date	(void);

/* if not specified in gcsl_platform.h, define the atomic types */

/****** spinlocks */
#ifndef GCSL_SPINLOCK_T
#define GCSL_SPINLOCK_T
typedef gcsl_long_t				gcsl_spinlock_t;
#endif

#ifndef GCSL_SPINLOCK_INIT
#define GCSL_SPINLOCK_INIT		(0)
#endif

gcsl_error_t	gcsl_spinlock_init(
								gcsl_spinlock_t* lock
								);

gcsl_error_t	gcsl_spinlock_lock(
								gcsl_spinlock_t* lock
								);

gcsl_error_t	gcsl_spinlock_unlock(
								gcsl_spinlock_t* lock
								);

gcsl_error_t	gcsl_spinlock_delete(
								gcsl_spinlock_t* lock
								);


/****** atomic counter functions */
#ifndef GCSL_TYPE_ATOMIC_T
#define GCSL_TYPE_ATOMIC_T
typedef struct { gcsl_int32_t atom; }	gcsl_atomic_t;
#endif

#ifndef GCSL_ATOMIC_INIT
#define GCSL_ATOMIC_INIT(i)				{ i }
#endif


gcsl_error_t	gcsl_atomic_set(
								gcsl_atomic_t* atomic, 
								gcsl_int32_t in_val
								);

gcsl_error_t	gcsl_atomic_add(
								gcsl_atomic_t* atomic, 
								gcsl_int32_t in_val
								);

gcsl_error_t	gcsl_atomic_read(
								gcsl_atomic_t* atomic, 
								gcsl_int32_t* out_val
								);

gcsl_error_t	gcsl_atomic_inc(
								gcsl_atomic_t* atomic, 
								gcsl_int32_t* out_val
								);
								
gcsl_error_t	gcsl_atomic_dec(
								gcsl_atomic_t* atomic, 
								gcsl_int32_t* out_val
								);



#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_ATOMIC_H_ */

