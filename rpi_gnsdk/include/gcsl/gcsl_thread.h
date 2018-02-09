/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_thread.h - Threading related functions
 */

#ifndef	_GCSL_THREAD_H_
#define _GCSL_THREAD_H_

#ifdef __cplusplus
extern "C"{
#endif 


/* if not specified in gcsl_platform.h, define the thread types */
GCSL_DECLARE_HANDLE( gcsl_thread_handle_t );
GCSL_DECLARE_HANDLE( gcsl_critsec_handle_t );
GCSL_DECLARE_HANDLE( gcsl_rwlock_handle_t );
GCSL_DECLARE_HANDLE( gcsl_event_handle_t );

/* thread creation start address function type */
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_thread_startaddr_fn)(gcsl_void_t* arg);


/*
** Library Initialization
*/
gcsl_error_t	gcsl_thread_initialize		(void);
gcsl_error_t	gcsl_thread_shutdown		(void);

gcsl_cstr_t		gcsl_thread_get_version		(void);
gcsl_cstr_t		gcsl_thread_get_build_date	(void);


/*
** Critical Sections
*/
gcsl_error_t	gcsl_thread_critsec_create(
								gcsl_critsec_handle_t* p_critical_section
								);
gcsl_error_t	gcsl_thread_critsec_delete(
								gcsl_critsec_handle_t critical_section
								);
gcsl_error_t	gcsl_thread_critsec_enter(
								gcsl_critsec_handle_t critical_section
								);
gcsl_error_t	gcsl_thread_critsec_leave(
								gcsl_critsec_handle_t critical_section
								);

/*
** Read/Write Locks
*/
gcsl_error_t	gcsl_thread_rwlock_create(
								gcsl_rwlock_handle_t* p_rwlock
								);
gcsl_error_t	gcsl_thread_rwlock_readlock(
								gcsl_rwlock_handle_t rwlock
								);
gcsl_error_t	gcsl_thread_rwlock_writelock(
								gcsl_rwlock_handle_t rwlock
								);
gcsl_error_t	gcsl_thread_rwlock_unlock(
								gcsl_rwlock_handle_t rwlock
								);
gcsl_error_t	gcsl_thread_rwlock_delete(
								gcsl_rwlock_handle_t rwlock
								);

/*
** Event Synchronization
*/
gcsl_error_t	gcsl_thread_event_create(
								gcsl_event_handle_t*	p_event_handle,
								gcsl_bool_t				b_create_signaled,
								gcsl_bool_t				b_manual_reset
								);

gcsl_error_t	gcsl_thread_event_delete(
								gcsl_event_handle_t event_handle
								);

gcsl_error_t	gcsl_thread_event_wait(
								gcsl_event_handle_t event_handle,
								gcsl_uint32_t		timeout
								);

gcsl_error_t	gcsl_thread_event_signal(
								gcsl_event_handle_t event_handle
								);

gcsl_error_t	gcsl_thread_event_reset(
								gcsl_event_handle_t event_handle
								);


/*
** Threads
*/

/* thread_handle is an optional param to hold the created thread’s handle.
 * If you get back the optional gcsl_thread_handle_t, it is required that you call 
 * gcsl_thread_wait_and_cleanup to ensure the thread resources are correctly freed. 
 */
gcsl_error_t	gcsl_thread_create(
								gcsl_thread_startaddr_fn startaddr, 
								gcsl_uint32_t stack_size, 
								gcsl_void_t* arg, 
								gcsl_thread_handle_t* thread_handle
								);

/* Set thread priority.  Scale of -5 to 5.
 * 0 is normal.
 * -5 is lowest.
 * 5 is highest.
 */
gcsl_error_t	gcsl_thread_set_priority(
								gcsl_thread_handle_t thread_handle,
								gcsl_int32_t thread_priority
								);

/* It is required that if the calling thread gets back the thread handle that it call
 * gcsl_thread_wait_and_cleanup which blocks until the referenced thread finishes and 
 * then cleans up any associated resources and frees the handle.
 */
gcsl_error_t	gcsl_thread_wait_and_cleanup(
								gcsl_thread_handle_t	thread_handle,
								gcsl_uint32_t			timeout_ms
								);

#define	GCSL_THREAD_TIMEOUT_INFINITE		0xffffffff


/****** thread utility functions */

/* put the calling thread to sleep - relenquish the processor*/
gcsl_error_t	gcsl_thread_sleep(
								gcsl_uint32_t milliseconds
								);
								
/* If thread_handle is GCSL_NULL, these act on the current thread 
 */

/* get ID of thread */
gcsl_error_t	gcsl_thread_get_id(
								gcsl_thread_handle_t	thread_handle, 
								gcsl_uint32_t*			thread_id
								);

/* set name for thread */
gcsl_error_t	gcsl_thread_set_name(
								gcsl_thread_handle_t	thread_handle,
								gcsl_cstr_t				name
								);

/* get name set for thread */
gcsl_error_t	gcsl_thread_get_name(
								gcsl_thread_handle_t	thread_handle,
								gcsl_str_t				name_buf,
								gcsl_size_t				name_buf_size
								);

/*
* Thread Local Storage
*/
#if (defined GCSL_CREATE_IMPORTS)
	#define CENTRALIZED_THREAD_API		GCSL_IMPORTED_API
#elif (defined GCSL_CREATE_EXPORTS)
	#define CENTRALIZED_THREAD_API		GCSL_EXPORTED_API
#else
	#define CENTRALIZED_THREAD_API
#endif

extern CENTRALIZED_THREAD_API GCSL_THREAD_STORE_KEY		g_gcsl_thread_store_key;


typedef gcsl_void_t	(GCSL_CALLBACK_API *gcsl_thread_tls_free_fn)(gcsl_void_t* ptr);

gcsl_error_t	gcsl_thread_store_set(
								gcsl_thread_handle_t	thread_handle,
								gcsl_void_t*			ptr,
								gcsl_thread_tls_free_fn	tls_free_fn
								);

gcsl_error_t	gcsl_thread_store_get(
								gcsl_thread_handle_t	thread_handle,
								gcsl_void_t**			p_ptr
								);

gcsl_error_t	gcsl_thread_store_clear(
								gcsl_thread_handle_t	thread_handle
								);


#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_THREAD_H_ */
