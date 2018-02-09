/*
 * Copyright (c) 2009 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_random.h
 */

#ifndef	_GCSL_RANDOM_H_
#define _GCSL_RANDOM_H_

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Initialization
 */

gcsl_error_t	gcsl_random_initialize		(void);
gcsl_error_t	gcsl_random_shutdown		(void);

gcsl_cstr_t		gcsl_random_get_version		(void);
gcsl_cstr_t		gcsl_random_get_build_date	(void);


/* (s)crappy little random integer generator
**
** Use only for non-serious random generation. 
** Does not use libc rand() - uses internal implementation for platform 
** consistency.
**
** If you need a proper random number generator (worthy of cryptography) use 
** the gcsl_random_get_*() APIs farther below.
*/
gcsl_uint16_t	gcsl_random_rand(gcsl_uint32_t* p_seed);


/*  get buffer of random bytes */
gcsl_error_t	gcsl_random_get_bytes(gcsl_byte_t* buffer, gcsl_size_t buffer_size);
/*  get random 32-bit integer */
gcsl_error_t	gcsl_random_get_uint32(gcsl_uint32_t* p_random_uint32);



#ifdef __cplusplus
}
#endif


#endif /* _GCSL_RANDOM_H_ */


