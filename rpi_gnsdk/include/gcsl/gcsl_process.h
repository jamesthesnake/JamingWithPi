/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_process.h - Process interface for abstraction layer
 */

#ifndef	_GCSL_PROCESS_H_
#define _GCSL_PROCESS_H_

/*
 * Dependencies.
 */

#ifdef __cplusplus
extern "C"{
#endif


/*
** Library Initialization 
*/
gcsl_error_t	gcsl_process_initialize		(void);
gcsl_error_t	gcsl_process_shutdown		(void);

gcsl_cstr_t		gcsl_process_get_version	(void);
gcsl_cstr_t		gcsl_process_get_build_date	(void);


/*
** Shared Library Loading
*/

GCSL_DECLARE_HANDLE( gcsl_process_lib_handle_t );

#if (defined _WIN64)
typedef __int64 (__stdcall*			gcsl_process_sym_t)(); /* FARPROC */
#elif (defined _WIN32)
typedef int (__stdcall*				gcsl_process_sym_t)(); /* FARPROC */
#else
typedef gcsl_void_t*				gcsl_process_sym_t;
#endif

gcsl_error_t	gcsl_process_library_load	(gcsl_cstr_t library_filename, gcsl_process_lib_handle_t* p_lib_handle);
gcsl_error_t	gcsl_process_library_sym	(gcsl_process_lib_handle_t lib_handle, gcsl_cstr_t sym_name, gcsl_process_sym_t* pp_sym);
gcsl_error_t	gcsl_process_library_free	(gcsl_process_lib_handle_t lib_handle);


/* 
** Environment Vars
*/

gcsl_error_t	gcsl_process_read_env		(gcsl_cstr_t var_name, gcsl_str_t var_buffer, gcsl_size_t buffer_size);


/*
** Named Pipes
*/

GCSL_DECLARE_HANDLE( gcsl_process_pipe_handle_t );

gcsl_error_t	gcsl_process_pipe_create			(gcsl_cstr_t name, gcsl_uint32_t max_connections, gcsl_process_pipe_handle_t* ph_pipe);
gcsl_error_t	gcsl_process_pipe_wait_for_connect	(gcsl_process_pipe_handle_t h_pipe, gcsl_uint32_t timeout_ms);
gcsl_error_t	gcsl_process_pipe_open				(gcsl_cstr_t name, gcsl_process_pipe_handle_t* ph_pipe, gcsl_uint32_t timeout_ms);
gcsl_error_t	gcsl_process_pipe_read				(gcsl_process_pipe_handle_t h_pipe, gcsl_void_t* buffer, gcsl_size_t buffer_size, gcsl_size_t* p_bytes_read, gcsl_uint32_t timeout_ms);
gcsl_error_t	gcsl_process_pipe_write				(gcsl_process_pipe_handle_t h_pipe, const gcsl_void_t* buffer, gcsl_size_t buffer_size, gcsl_size_t* p_bytes_written, gcsl_uint32_t timeout_ms);
gcsl_error_t	gcsl_process_pipe_close				(gcsl_process_pipe_handle_t h_pipe);




#ifdef __cplusplus
}
#endif

#endif /* _GCSL_PROCESS_H_ */
