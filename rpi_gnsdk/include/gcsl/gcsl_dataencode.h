/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_dataencode.h
 */

#ifndef	_GCSL_DATAENCODE_H_
#define _GCSL_DATAENCODE_H_

#ifdef __cplusplus
extern "C"{
#endif 

/*
 * Constants.
 */

/* GCSL_DATA_ENCODE_FLAGS */
#define GCSL_DATA_ENCODE_ENCRYPT_CRYPT4				0x01 /* GCSL_ENCRYPT_CRYPT_4: "gn-crypt-4" */
#define GCSL_DATA_ENCODE_COMPRESS_ZIP				0x02 /* GCSL_COMPR_ZIP: "gn-zip" */

/*
 * Typedefs
 */
typedef gcsl_byte_t gcsl_data_encode_flags_t;

/*
 * Prototypes.
 */

gcsl_error_t	gcsl_dataencode_initialize		(void);
gcsl_error_t	gcsl_dataencode_shutdown		(void);

gcsl_cstr_t		gcsl_dataencode_get_version		(void);
gcsl_cstr_t		gcsl_dataencode_get_build_date	(void);


gcsl_error_t
gcsl_dataencode_isencoded(
	const gcsl_byte_t*	payload_data,
	gcsl_size_t			payload_data_size,
	gcsl_bool_t*		pb_isencoded
	);


/*  gcsl_dataencode_encode
 * Description: Encode data using the specified GCSL_DATA_ENCODE_FLAGS
 *			This function allocates memory for the encoded output.
 *
 * Args:	payload_data		- payload input
 *			payload_data_size	- size of payload input buffer
 *			encoded_data		- pointer to a buffer to hold encoded output (allocated by this function)
 *			encoded_data_size	- size of encoded output buffer
 *			data_encode_flags	- specifies how to pack the data (encryption and/or compression)
 *			encryption_key		- encryption key (optional, only needed if the GCSL_DATA_ENCODE_ENCRYPT flag is specified)
 *
 * Returns:	GCSLDATAENCODEERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Memory allocation error
 */
gcsl_error_t
gcsl_dataencode_encode(
	const gcsl_byte_t*			payload_data,
	gcsl_size_t					payload_data_size,
	gcsl_byte_t**				encoded_data,
	gcsl_size_t*				encoded_data_size,
	gcsl_data_encode_flags_t	data_encode_flags,
	const gcsl_byte_t*			encryption_key,
	gcsl_size_t					encryption_key_size
	);

gcsl_error_t
gcsl_dataencode_encode_stream(
	gcsl_iostream_handle_t		in_stream,
	gcsl_byte_t**				encoded_data,
	gcsl_size_t*				encoded_data_size,
	gcsl_data_encode_flags_t	data_encode_flags,
	const gcsl_byte_t*			encryption_key,
	gcsl_size_t					encryption_key_size
	);

/*  gcsl_dataencode_decode
 * Description: Decode data previously packed using gcsl_dataenc_encode()
 *			This function allocates memory for the payload output.
 *
 * Args:	encoded_data		- encoded input
 *			encoded_data_size	- size of encoded input buffer
 *			payload_data		- pointer to a buffer to hold payload output (allocated by this function)
 *			payload_data_size	- size of payload output buffer
 *			decryption_key		- decryption key (optional, only needed if payload_data is encrypted
 *
 *
 * Returns:	GCSLDATAENCODEERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Memory allocation error
 *				Invalid header format
 *				Invalid data format
 */
gcsl_error_t
gcsl_dataencode_decode(
	const gcsl_byte_t*	encoded_data,
	gcsl_size_t			encoded_data_size,
	gcsl_byte_t**		payload_data,
	gcsl_size_t*		payload_data_size,
	const gcsl_byte_t*	decryption_key,
	gcsl_size_t			decryption_key_size
	);

/*  gcsl_dataencode_freedata
 * Description: Free data returned from gcsl_dataencode_decode and
 *			gcsl_dataencode_encode.
 */
gcsl_error_t
gcsl_dataencode_freedata(
	gcsl_byte_t* data
	);


/*
** IOStream DataEncode APIs
*/
gcsl_error_t
gcsl_dataencode_decode_stream(
						const gcsl_byte_t*			encryption_key,
						gcsl_size_t					encryption_key_size,
						gcsl_iostream_handle_t		in_stream,
						gcsl_iostream_handle_t*		p_out_stream
						);



#ifdef __cplusplus
}
#endif 


#endif /* _GCSL_DATAENCODE_H_ */


