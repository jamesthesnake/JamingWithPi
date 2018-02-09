/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_iostream.h - Data stream enabling object
 */

#ifndef _GCSL_IOSTREAM_H_
#define _GCSL_IOSTREAM_H_

#ifdef	__cplusplus
extern "C" {
#endif


/*
 * Initialization
 */

gcsl_error_t	gcsl_iostream_initialize		(void);
gcsl_error_t	gcsl_iostream_shutdown			(void);

gcsl_cstr_t		gcsl_iostream_get_version		(void);
gcsl_cstr_t		gcsl_iostream_get_build_date	(void);



GCSL_DECLARE_HANDLE( gcsl_iostream_handle_t );


typedef gcsl_error_t (GCSL_CALLBACK_API *gcsl_iostream_read_buffer_fn)	(const gcsl_void_t* callback_data, gcsl_void_t* buffer, gcsl_size_t buffer_size, gcsl_size_t* p_bytes_read);
typedef gcsl_error_t (GCSL_CALLBACK_API *gcsl_iostream_write_buffer_fn)	(const gcsl_void_t* callback_data, const gcsl_void_t* buffer, gcsl_size_t buffer_size, gcsl_size_t* p_bytes_written);
typedef gcsl_error_t (GCSL_CALLBACK_API *gcsl_iostream_flush_fn)		(const gcsl_void_t* callback_data);
typedef gcsl_error_t (GCSL_CALLBACK_API *gcsl_iostream_reset_fn)		(const gcsl_void_t* callback_data);
typedef gcsl_void_t  (GCSL_CALLBACK_API *gcsl_iostream_release_fn)		(const gcsl_void_t* callback_data);

typedef struct _gcsl_iostream_provider_interface_s
{
	gcsl_iostream_read_buffer_fn	read_buffer_fn;
	gcsl_iostream_write_buffer_fn	write_buffer_fn;
	gcsl_iostream_flush_fn			flush_fn;
	gcsl_iostream_reset_fn			reset_fn;
	gcsl_iostream_release_fn		release_fn;

} gcsl_iostream_provider_interface_t;



gcsl_error_t	gcsl_iostream_create			(gcsl_iostream_handle_t* ph_iostream, gcsl_size_t buffer_size, gcsl_iostream_provider_interface_t* p_iostream_intf, const gcsl_void_t* callback_data);
gcsl_error_t	gcsl_iostream_create_from_buffer(gcsl_iostream_handle_t* ph_iostream, gcsl_void_t* buffer, gcsl_size_t buffer_size, gcsl_iostream_release_fn release_buffer_fn, const gcsl_void_t* callback_data);

gcsl_error_t	gcsl_iostream_addref			(gcsl_iostream_handle_t h_iostream);
gcsl_error_t	gcsl_iostream_release			(gcsl_iostream_handle_t h_iostream);

gcsl_error_t	gcsl_iostream_can_read			(gcsl_iostream_handle_t h_iostream, gcsl_bool_t* pb_can_read);
gcsl_error_t	gcsl_iostream_can_write			(gcsl_iostream_handle_t h_iostream, gcsl_bool_t* pb_can_write);
gcsl_error_t	gcsl_iostream_can_reset			(gcsl_iostream_handle_t h_iostream, gcsl_bool_t* pb_can_reset);

gcsl_error_t	gcsl_iostream_read				(gcsl_iostream_handle_t h_iostream, gcsl_void_t* data_buffer, gcsl_size_t buffer_size, gcsl_size_t* p_bytes_read);
gcsl_error_t	gcsl_iostream_read_entire		(gcsl_iostream_handle_t h_iostream, gcsl_void_t** data_buffer, gcsl_size_t* p_buffer_size);
gcsl_error_t	gcsl_iostream_putback			(gcsl_iostream_handle_t h_iostream, const gcsl_void_t* data_buffer, gcsl_size_t buffer_size);
gcsl_error_t	gcsl_iostream_write				(gcsl_iostream_handle_t h_iostream, const gcsl_void_t* data_buffer, gcsl_size_t buffer_size, gcsl_size_t* p_bytes_written);
gcsl_error_t	gcsl_iostream_flush				(gcsl_iostream_handle_t h_iostream);
gcsl_error_t	gcsl_iostream_reset				(gcsl_iostream_handle_t h_iostream);

gcsl_error_t	gcsl_iostream_throughput		(gcsl_iostream_handle_t h_iostream, gcsl_size_t* p_read_total, gcsl_size_t* p_write_total);



#ifdef	__cplusplus
}
#endif

#endif /* _GCSL_IOSTREAM_H_ */
