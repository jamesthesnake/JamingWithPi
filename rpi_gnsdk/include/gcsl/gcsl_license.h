/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_license.h
 */

#ifndef _GCSL_LICENSE_H_
#define _GCSL_LICENSE_H_

#ifdef	__cplusplus
extern "C" {
#endif

gcsl_error_t	gcsl_license_initialize		(void);
gcsl_error_t	gcsl_license_shutdown		(void);

gcsl_cstr_t		gcsl_license_get_version	(void);
gcsl_cstr_t		gcsl_license_get_build_date	(void);


gcsl_error_t	gcsl_license_create(
	gcsl_cstr_t		license_content,
	gcsl_str_t*		p_signed_license,
	gcsl_cstr_t		private_key
	);

gcsl_error_t	gcsl_license_verify(
	gcsl_cstr_t		signed_license,
	gcsl_str_t*		p_license_content,
	gcsl_cstr_t		public_key
	);

gcsl_error_t	gcsl_license_make_key(
	gcsl_str_t*		p_public_key,
	gcsl_str_t*		p_private_key
	);


#ifdef	__cplusplus
}
#endif

#endif /* _GCSL_LICENSE_H_ */
