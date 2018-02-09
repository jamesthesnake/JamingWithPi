/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_compression.h - abstract data compression/decompression interface.
 */

#ifndef	_GCSL_COMPRESSION_H_
#define _GCSL_COMPRESSION_H_

#ifdef __cplusplus
extern "C" {
#endif 


/*
 * Typedefs
 */
typedef const gcsl_char_t*	gcsl_compression_type_t;

#define	GCSL_COMPRESSION_TYPE_UNKNOWN	"gn-comp-unk"
#define	GCSL_COMPRESSION_TYPE_GNZIP		"gn-zip"		/* NB: this needs to match the GCSP compression type string */


/*
 * Prototypes.
 */

gcsl_error_t	gcsl_compression_initialize		(void);
gcsl_error_t	gcsl_compression_shutdown		(void);

gcsl_cstr_t		gcsl_compression_get_version	(void);
gcsl_cstr_t		gcsl_compression_get_build_date	(void);


/*
** IOStream Compression APIs
*/
gcsl_error_t
gcsl_compression_compress_stream(
							gcsl_compression_type_t					type,
							gcsl_iostream_handle_t					in_stream,
							gcsl_byte_t**							out_buffer,
							gcsl_size_t*							out_buffer_size
							);

gcsl_error_t
gcsl_compression_decompress_stream(
							gcsl_compression_type_t					type,
							gcsl_iostream_handle_t					in_stream,
							gcsl_iostream_handle_t*					p_out_stream
							);


/*
** Buffer Compression APIs
*/
gcsl_error_t
gcsl_compression_compress(	gcsl_compression_type_t					type,
							const gcsl_byte_t*						in_buffer,
							gcsl_size_t								in_buffer_size,
							gcsl_byte_t**							out_buffer,
							gcsl_size_t*							out_buffer_size
							);

gcsl_error_t
gcsl_compression_decompress(gcsl_compression_type_t					type,
							const gcsl_byte_t*						in_buffer,
							gcsl_size_t								in_buffer_size,
							gcsl_byte_t**							out_buffer,
							gcsl_size_t*							out_buffer_size
							);

gcsl_error_t
gcsl_compression_freebuffer(gcsl_byte_t*							out_buffer
							);



#ifdef __cplusplus
}
#endif 


#endif /* _GCSL_COMPRESSION_H_ */


