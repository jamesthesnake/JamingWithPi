/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_crypt.h - abstract data encryption interface (based on service code).
 */

#ifndef	_GCSL_CRYPT_H_
#define _GCSL_CRYPT_H_

#ifdef __cplusplus
extern "C"{
#endif 


/*
 * Constants
 */

/* Asymmetric public key algorithms */

#define	GCSL_CRYPT_CRYPT_1			"gn-crypt-1"
#define	GCSL_CRYPT_CRYPT_1_V1		1

#define	GCSL_CRYPT_CRYPT_2			"gn-crypt-2"
#define	GCSL_CRYPT_CRYPT_2_V1		1
#define	GCSL_CRYPT_CRYPT_2_V2		2
#define	GCSL_CRYPT_CRYPT_2_V3		3

#define	GCSL_CRYPT_CRYPT_3			"gn-crypt-3"
#define	GCSL_CRYPT_CRYPT_3_V1		1

#define	GCSL_CRYPT_CRYPT_4			"gn-crypt-4"
#define	GCSL_CRYPT_CRYPT_4_V1		1	/* 18 "chars" of public key (all arithmatic can be within 64bits) */
#define	GCSL_CRYPT_CRYPT_4_V2		2	/* 24 "chars" of public key */
#define	GCSL_CRYPT_CRYPT_4_V3		3	/* 74 "chars" of publib key */
#define	GCSL_CRYPT_CRYPT_4_V4		4	/* 108 "chars" if public key and is equivalent to gn-crypt-3 */

#define	GCSL_CRYPT_CRYPT_TEA		"gn-crypt-tea"
#define	GCSL_CRYPT_CRYPT_TEA_V1		1

/*
 * Prototypes.
 */

gcsl_error_t	gcsl_crypt_initialize		(void);
gcsl_error_t	gcsl_crypt_shutdown			(void);

gcsl_cstr_t		gcsl_crypt_get_version		(void);
gcsl_cstr_t		gcsl_crypt_get_build_date	(void);

gcsl_error_t	gcsl_crypt_generate_keys(
	gcsl_cstr_t			enc_type,
	gcsl_uint32_t		enc_version,
	gcsl_str_t*			p_public_key,
	gcsl_str_t*			p_private_key
	);

/*  gcsl_crypt_encrypt
 * Description: This function allocates memory for the encrypted output.
 *
 * Args:	encryption_key				- symmetric encryption key
 *			payload						- input data to be encrypted
 *			payload_size				- size of input data
 *			encrypted_storage_data		- pointer to buffer to hold encrypted ouput
 *			encrypted_storage_data_size	- size of encrypted output buffer
 *
 * Returns:	CRYPTERR_NoError upon success or an error.
 *			Failure conditions include:
 *				NULL encryption_key
 *				Output buffer too small
 *
 */

gcsl_error_t	gcsl_crypt_encrypt(
	gcsl_cstr_t			enc_type,
	gcsl_uint32_t		enc_version,
	const gcsl_char_t*	public_key,
	gcsl_size_t			public_key_len,
	const gcsl_byte_t*	in_buffer,
	const gcsl_size_t	in_buffer_size,
	gcsl_byte_t**		out_buffer,
	gcsl_size_t*		out_buffer_size
	);

/*  gcsl_crypt_decrypt
 * Description: This function allocates memory for the decrypted output.
 *
 * Args:	encryption_key				- symmetric encryption key
 *			encrypted_storage_data		- encrypted input
 *			encrypted_storage_data_size	- size of encrypted input buffer
 *			decrypted_payload			- pointer to buffer to hold decrypted output
 *			decrypted_payload_size		- size of decrypted output buffer
 *
 * Returns:	CRYPTERR_NoError upon success or an error.
 *			Failure conditions include:
 *				NULL encryption_key
 *				Output buffer too small
 *				Invalid header format
 */
gcsl_error_t	gcsl_crypt_decrypt(
	gcsl_cstr_t			enc_type,
	gcsl_uint32_t		enc_version,
	const gcsl_char_t*	private_key,
	gcsl_size_t			private_key_len,
	const gcsl_byte_t*	in_buffer,
	const gcsl_size_t	in_buffer_size,
	gcsl_byte_t**		out_buffer,
	gcsl_size_t*		out_buffer_size
	);

/* DSA symmetric shared key stuff */

gcsl_error_t	gcsl_crypt_dsa_generate_keys(
	gcsl_str_t*			p_public_key,
	gcsl_str_t*			p_private_key
	);

gcsl_error_t	gcsl_crypt_dsa_sign_hash(
	const gcsl_char_t*	private_key,
	gcsl_size_t			private_key_len,
	const gcsl_byte_t*	in_buffer,
	const gcsl_size_t	in_buffer_size,
	gcsl_char_t**		p_signature,
	gcsl_size_t*		p_signature_size
	);

gcsl_error_t	gcsl_crypt_dsa_verify_hash(
	const gcsl_char_t*	public_key,
	gcsl_size_t			public_key_len,
	const gcsl_byte_t*	in_buffer,
	const gcsl_size_t	in_buffer_size,
	const gcsl_char_t*	signature,
	const gcsl_size_t	signature_size
	);

#ifdef __cplusplus
}
#endif 


#endif /* _GCSL_CRYPT_H_ */


