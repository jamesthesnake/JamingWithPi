/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_cds.h - Content Delivery System functions
 */

#ifndef	_GCSL_CDS_H_
#define _GCSL_CDS_H_

#ifdef __cplusplus
extern "C"{
#endif 

/*
 * CDS Content Request HDO keys
 */

/* these are the param values that were documented at code time. if there is a
param you want that isn't here, fret not you can add it.  the value name will
be the param and the value data will be the param data */
#define	CDS_REQUEST_CONTENT_CLASS					"class"
#define	CDS_REQUEST_CONTENT_ID						"id"
#define	CDS_REQUEST_CONTENT_TAG						"tag"
#define	CDS_REQUEST_CONTENT_ORIGIN					"origin"
#define	CDS_REQUEST_CONTENT_SIZE					"size"
#define	CDS_REQUEST_CONTENT_TYPE					"type"
#define	CDS_REQUEST_CONTENT_PAGE					"page"

/*
 * CDS options keys
 */
#define CDS_CONTENT_CLASS_IMAGE_COVER				"cover"
#define CDS_CONTENT_CLASS_IMAGE_VIDEO				"image"
#define CDS_CONTENT_CLASS_IMAGE_ARTIST				"image-artist"
#define CDS_CONTENT_CLASS_TEXT_REVIEW				"review"
#define CDS_CONTENT_CLASS_TEXT_BIOGRAPHY			"biography"
#define CDS_CONTENT_CLASS_TEXT_ARTIST_NEWS			"artist-news"
#define CDS_CONTENT_CLASS_LYRICS					"lyrics"
#define CDS_CONTENT_CLASS_TEXT_COMMENTS_LISTENER	"listener-comments"
#define CDS_CONTENT_CLASS_TEXT_COMMENTS_RELEASE		"new-release-comments"
#define CDS_CONTENT_CLASS_TEXT_NEWS					"news"
#define CDS_CONTENT_CLASS_DSP_12TONE				"12tonesmfmf"

/*
 * CDS options keys
 */
#define	CDS_OPTION_NETWORK_TIMEOUT		"gcsl_cds_transfer_timeout"		/* ms before giving up */
#define CDS_OPTION_NETWORK_LOADBALANCE	"gcsl_cds_network_loadbalance"	/* enable true/false */
#define	CDS_OPTION_HTTP_CHUNK_SIZE		"gcsl_cds_chunk_size"			/* bytes per send/receive - for best callback experience */
#define	CDS_OPTION_OVERRIDE_HOST		"gcsl_cds_override_host"		/* override cds hostname */
#define	CDS_OPTION_PROXY_HOST_INFO		"gcsl_cds_proxy_host_info"		/* host:port */
#define	CDS_OPTION_PROXY_USER			"gcsl_cds_proxy_user"
#define	CDS_OPTION_PROXY_PASS			"gcsl_cds_proxy_pass"
#define	CDS_OPTION_HTTP_MAX_REDIRECTS	"gcsl_cds_max_redirects"

/* CDS request opaque handle
*/
GCSL_DECLARE_HANDLE( gcsl_cds_handle_t );


typedef enum
{
	gcsl_cds_status_unknown				= 0,

	gcsl_cds_status_connecting,
	gcsl_cds_status_sending,
	gcsl_cds_status_receiving,
	gcsl_cds_status_disconnected 

} gcsl_cds_status_t;


typedef gcsl_void_t	(GCSL_CALLBACK_API	*gcsl_cds_callback_fn)(
											const gcsl_void_t*	user_data,
											gcsl_cds_status_t	status,
											gcsl_size_t			bytes_done,
											gcsl_size_t			bytes_total,
											gcsl_bool_t*		p_abort
											);

/*
 * Initialization
 */

gcsl_error_t	gcsl_cds_initialize		(void);
gcsl_error_t	gcsl_cds_shutdown		(void);

/*
 * Version and Build
 */
gcsl_cstr_t		gcsl_cds_get_version	(void);
gcsl_cstr_t		gcsl_cds_get_build_date	(void);

/*
 * Content Retrieval
 */
gcsl_error_t	gcsl_cds_create_request(
											gcsl_cds_handle_t*		p_request_handle,
											gcsl_hdo_handle_t		cds_request_hdo,	/* required. keys defined above */
											gcsl_cstr_t				client_id,			/* required */
											gcsl_cds_callback_fn	callback,			/* optional */
											const gcsl_void_t*		callback_data,		/* optional */
											gcsl_stringmap_handle_t	cds_options			/* optional. keys defined above */
										);

gcsl_error_t	gcsl_cds_fetch_content(
											gcsl_cds_handle_t		request_handle,
											gcsl_byte_t**			p_out_buffer,		/* this will be allocated by CDS, caller must call gcsl_cds_free_content */
											gcsl_size_t*			p_out_buffer_size
											);

gcsl_error_t	gcsl_cds_decode_content(
											const gcsl_byte_t*		in_buffer,
											gcsl_size_t				in_buffer_size,
											gcsl_byte_t**			p_out_buffer,		/* this will be allocated by CDS, caller must call gcsl_cds_free_content */
											gcsl_size_t*			p_out_buffer_size
											);

gcsl_error_t	gcsl_cds_free_content(
											gcsl_byte_t*			out_buffer
											);

gcsl_error_t	gcsl_cds_delete_request(
											gcsl_cds_handle_t		request_handle
										);



#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_CDS_H_ */

