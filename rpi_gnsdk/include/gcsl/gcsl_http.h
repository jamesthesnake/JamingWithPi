/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_http.h
 */

#ifndef _GCSL_HTTP_H_
#define _GCSL_HTTP_H_

#ifdef	__cplusplus
extern "C" {
#endif

/* HTTP options */
#define	GCSL_HTTP_OPTION_HOSTNAME_TTL				"gcsl_http_option_hostnamettl"
#define	GCSL_HTTP_VALUE_HOSTNAME_TTL_DEFAULT		"5" /* 5 minutes (valid from 1-n minutes) */

#define	GCSL_HTTP_OPTION_NETWORK_TIMEOUT			"gcsl_http_option_timeout"
#define	GCSL_HTTP_VALUE_NETWORK_TIMEOUT_DEFAULT		"30000" /* 30,000 milliseconds (30 seconds) */

/* HTTP headers */
#define	HTTP_HEADER_FIELD_USER_AGENT				"User-Agent"
#define	HTTP_HEADER_FIELD_CONTENT_LENGTH			"Content-Length"
#define	HTTP_HEADER_FIELD_REDIRECT					"Location"
#define	HTTP_HEADER_FIELD_CONTENT_TYPE				"Content-Type"

/* gcsl_http connection handle */
GCSL_DECLARE_HANDLE( gcsl_http_handle_t );

/* library initialization */
gcsl_error_t	gcsl_http_initialize		(void);
gcsl_error_t	gcsl_http_shutdown			(void);

gcsl_cstr_t		gcsl_http_get_version		(void);
gcsl_cstr_t		gcsl_http_get_build_date	(void);


/* http status enums */
typedef enum
{
	gcsl_http_status_unknown		= 0,

	gcsl_http_status_connecting,
	gcsl_http_status_sending,
	gcsl_http_status_receiving,
	gcsl_http_status_disconnected

} gcsl_http_status_t;

/* callback definitions */
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_http_response_status_fn)(
										const gcsl_void_t*	callback_data,
										gcsl_http_status_t	status,
										gcsl_size_t			bytes,
										gcsl_bool_t*		pb_abort
										);

typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_http_response_header_fn)(
										const gcsl_void_t*	callback_data,
										gcsl_cstr_t			header_key,
										gcsl_cstr_t			header_value,
										gcsl_bool_t*		pb_abort
										);

#define GCSL_HTTP_HEADER_KEY_HTTP_VERSION			"http_version"
#define GCSL_HTTP_HEADER_KEY_HTTP_STATUS_CODE		"http_status_code"
#define GCSL_HTTP_HEADER_KEY_HTTP_STATUS_REASON		"http_status_reason"

typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_http_response_content_fn)(
										const gcsl_void_t*	callback_data,
										gcsl_void_t*		content_buffer,
										gcsl_size_t			content_buffer_size,
										gcsl_size_t			content_size_done,
										gcsl_size_t			content_size_total,
										gcsl_bool_t*		pb_abort
										);


/* http connection creation */
gcsl_error_t	gcsl_http_connection_create(
										gcsl_http_handle_t*				p_connection,
										gcsl_cstr_t						proxy_host,
										gcsl_uint32_t					timeout_ms,
										gcsl_http_response_status_fn	response_status_fn,
										gcsl_http_response_header_fn	response_header_fn,
										gcsl_http_response_content_fn	response_content_fn,
										const gcsl_void_t*				callback_data,
										gcsl_bool_t						b_pipelining
										);

gcsl_error_t	gcsl_http_connection_delete(
										gcsl_http_handle_t		connection
										);

gcsl_error_t	gcsl_http_connection_option_set(
										gcsl_http_handle_t		connection,
										gcsl_cstr_t				option_key,
										gcsl_cstr_t				option_value
										);

gcsl_error_t	gcsl_http_connection_proxy_auth(
										gcsl_http_handle_t		connection,
										gcsl_cstr_t				username,
										gcsl_cstr_t				password
										);

/* http communications */ 
gcsl_error_t	gcsl_http_send_request(
										gcsl_http_handle_t		connection,
										gcsl_cstr_t				send_method,
										gcsl_cstr_t				target_url,
										gcsl_stringmap_handle_t	header_values,	/* don't put content_length in here */
										const gcsl_void_t*		content_buffer, 
										gcsl_size_t				content_length	
										);

#define GCSL_HTTP_METHOD_GET			"GET"
#define GCSL_HTTP_METHOD_PUT			"PUT"
#define GCSL_HTTP_METHOD_PUT_MULTIPART	"PUT-MP" /* will not auto-restablish connection */
#define GCSL_HTTP_METHOD_POST			"POST"


gcsl_error_t	gcsl_http_wait_for_response(
										gcsl_http_handle_t		connection
										);


gcsl_error_t	gcsl_http_can_retry(
										gcsl_http_handle_t		connection,
										gcsl_bool_t*			pb_retry
										);

/* helpers */
gcsl_error_t	gcsl_http_parse_url(
										gcsl_cstr_t		host_url,
										gcsl_str_t		host_name,
										gcsl_size_t		host_name_size,
										gcsl_uint16_t*	p_port,
										gcsl_cstr_t*	p_path
										);



/* HTTP provider interface */
typedef struct gcsl_http_provider_interface_s
{
	gcsl_error_t	(GCSL_CALLBACK_API *open)				(gcsl_void_t** pp_connection_data, gcsl_cstr_t host_name, gcsl_uint16_t port, gcsl_bool_t b_host_is_proxy, gcsl_uint32_t timeout_ms);
	gcsl_void_t		(GCSL_CALLBACK_API *close)				(gcsl_void_t* p_connection_data);

	gcsl_error_t	(GCSL_CALLBACK_API *send_request)		(gcsl_void_t* p_connection_data, gcsl_cstr_t http_method, gcsl_cstr_t headers, gcsl_cstr_t path, gcsl_size_t content_length);
	gcsl_error_t	(GCSL_CALLBACK_API *send_content)		(gcsl_void_t* p_connection_data, const gcsl_void_t* content_buffer, gcsl_size_t content_length);

	gcsl_error_t	(GCSL_CALLBACK_API *recv_response)		(gcsl_void_t* p_connection_data, gcsl_void_t* buffer, gcsl_size_t buffer_size, gcsl_size_t* p_bytes_rcvd);

	gcsl_error_t	(GCSL_CALLBACK_API *resolve)			(gcsl_cstr_t host_name, gcsl_char_t* address_buf, gcsl_size_t buffer_size);

} gcsl_http_provider_interface_t;

/* set HTTP provider override */
gcsl_error_t	gcsl_http_register_provider_interface(
										gcsl_http_provider_interface_t*	p_http_interface
										);

#ifdef	__cplusplus
}
#endif

#endif /* _GCSL_HTTP_H_ */
