/* Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gcsl_socket.h
 *
 * Interface to platform-specific routines for the communications layer
 *
 */

#ifndef GCSL_SOCKET_H
#define GCSL_SOCKET_H

#ifdef __cplusplus
extern "C"{
#endif 


#if (defined GCSL_CREATE_IMPORTS)
	#define CENTRALIZED_SOCKET_API		GCSL_IMPORTED_API
#elif (defined GCSL_CREATE_EXPORTS)
	#define CENTRALIZED_SOCKET_API		GCSL_EXPORTED_API
#else
	#define CENTRALIZED_SOCKET_API
#endif

#ifndef GCSL_SOCKET_TEST
#ifdef _DEBUG
	#define GCSL_SOCKET_TEST    1
#endif
#endif

/*
 * Constants.
 */


#define	GCSL_SOCKET_DEFAULT_TRANSFER_TIMEOUT			30000		/* 30,000 milliseconds == 30 seconds */
#define	GCSL_SOCKET_DEFAULT_TRANSFER_TIMEOUT_QUANTUM	250			/* 250,000 microseconds == 250 milliseconds */

#define	GCSL_SOCKET_DEFAULT_RECEIVE_BUFFER_SIZE			4096		/* 4096 bytes == 4 KB */
#define	GCSL_SOCKET_DEFAULT_TRANSFER_SIZE_QUANTUM		1024		/* 1024 bytes == 1 KB */


/*
 * Typedefs
 */

GCSL_DECLARE_HANDLE( gcsl_socket_handle_t );


/*
 * Prototypes
 */

gcsl_error_t	gcsl_socket_initialize		(void);
gcsl_error_t	gcsl_socket_shutdown		(void);

gcsl_cstr_t		gcsl_socket_get_version		(void);
gcsl_cstr_t		gcsl_socket_get_build_date	(void);


/* connect to a remote machine / create socket handle */
gcsl_error_t	gcsl_socket_connect(
								gcsl_socket_handle_t*	p_socket_handle,
								gcsl_cstr_t				address,
								gcsl_uint16_t			port,
								gcsl_uint32_t			timeout_ms
								);

/* disconnect from a remote machine / delete socket handle */
gcsl_error_t	gcsl_socket_close(
								gcsl_socket_handle_t	socket_handle
								);

/* establish new endpoint to receive socket connections from */
gcsl_error_t	gcsl_socket_create_endpoint(
								gcsl_socket_handle_t*	p_endpoint_handle,
								gcsl_cstr_t				address_name, /* IP address or GCSL_NULL */
								gcsl_uint16_t			port,
								gcsl_uint32_t			max_connections
								);

/* wait on socket created by 'create_endpoint' for connection */
gcsl_error_t	gcsl_socket_wait_for_connect(
								gcsl_socket_handle_t	endpoint_handle,
								gcsl_socket_handle_t*	p_socket_handle,
								gcsl_uint32_t			timeout_ms
								);

/* send data to a remote machine */
gcsl_error_t	gcsl_socket_send(
								gcsl_socket_handle_t	socket_handle,
								const gcsl_void_t*		buffer,
								gcsl_size_t				send_size,
								gcsl_size_t*			size_sent,
								gcsl_uint32_t			timeout_ms
								);

/* receive data from  a remote machine */
gcsl_error_t	gcsl_socket_receive(
								gcsl_socket_handle_t	socket_handle,
								gcsl_void_t*			buffer,
								gcsl_size_t				receive_size,
								gcsl_size_t*			size_received,
								gcsl_uint32_t			timeout_ms
								);

/* resolve a hostname to its set of IPs */
gcsl_error_t	gcsl_socket_resolve(
								gcsl_cstr_t				hostname,
								gcsl_str_t*				p_address_set
								);


typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_socket_marker_status_callback_fn)(
	const gcsl_void_t*	app_data,
	gcsl_cstr_t			hostname,
	gcsl_size_t			connect_count,
	gcsl_size_t			disconnect_count,
	gcsl_size_t			send_count,
	gcsl_size_t			sent_bytes,
	gcsl_size_t			sent_bytes_max,
	gcsl_size_t			receive_count,
	gcsl_size_t			received_bytes,
	gcsl_size_t			received_bytes_max,
	gcsl_size_t			b_socket_open,
	gcsl_size_t			b_socket_close
	);

CENTRALIZED_SOCKET_API gcsl_void_t			gcsl_socket_marker_initialize	(gcsl_socket_marker_status_callback_fn callback_fn);
CENTRALIZED_SOCKET_API gcsl_void_t			gcsl_socket_marker_start		(const gcsl_void_t* app_data, gcsl_void_t** p_marker_data);
CENTRALIZED_SOCKET_API gcsl_void_t			gcsl_socket_marker_end			(gcsl_void_t* marker_data);

#define GCSL_SOCKET_MARKSTART(app_data)		{ gcsl_void_t* __p_socket_marker; gcsl_socket_marker_start(app_data, &__p_socket_marker);
#define GCSL_SOCKET_MARKEND					gcsl_socket_marker_end(__p_socket_marker); }




#ifdef __cplusplus
}
#endif

#endif	/* ifndef GCSL_SOCKET_H */
