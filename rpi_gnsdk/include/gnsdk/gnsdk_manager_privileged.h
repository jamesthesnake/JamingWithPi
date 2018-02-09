/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_MANAGER_PRIVILEGED_H_
#define _GNSDK_MANAGER_PRIVILEGED_H_

#include "gnsdk_manager.h"
#include "gnsdk_manager_gdo.h"
#include "gnsdk_manager_locales.h"

#ifdef __cplusplus
extern "C"{
#endif


/*****************************************************************************
** Privileged Client Options
*/
#define GNSDK_USER_OPTION_SERVICE_URL					"gnsdk_service_url"
#define GNSDK_USER_OPTION_CDS_HOST						"gnsdk_cds_host"
#define GNSDK_USER_OPTION_DO_NOT_COMPRESS_REQUESTS		"gnsdk_skip_compression"
#define GNSDK_USER_OPTION_DO_NOT_ENCRYPT_REQUESTS		"gnsdk_skip_encryption"

#define GNSDK_USER_OPTION_KEY_CRYPT_TYPE				"gnsdk_crypt_type"		/* encryption algorithm key - values below */
#define GNSDK_USER_OPTION_VALUE_CRYPT_3_V1				"gnsdk_crypt_3v1"
#define GNSDK_USER_OPTION_VALUE_CRYPT_4_V1				"gnsdk_crypt_4v1"
#define GNSDK_USER_OPTION_VALUE_CRYPT_4_V2				"gnsdk_crypt_4v2"
#define GNSDK_USER_OPTION_VALUE_CRYPT_4_V3				"gnsdk_crypt_4v3"
#define GNSDK_USER_OPTION_VALUE_CRYPT_4_V4				"gnsdk_crypt_4v4"


/*****************************************************************************
** Privileged Logging values
*/
#define	GNSDK_LOG_LEVEL_MASK_PRIVATE					0x0000FFFF			/* Log all private messages */

/* License File pre-defines */
#define GNSDK_LICENSE_OPTION_KEY_LICENSEE				"licensee"			/* licensee: Gracenote, Inc. */
#define GNSDK_LICENSE_OPTION_KEY_CLIENT_ID				"client_id"			/* client_id: 1234567 */
#define GNSDK_LICENSE_OPTION_KEY_NAME					"name"				/* name: Acme, Corp. */
#define GNSDK_LICENSE_OPTION_KEY_NOTES					"notes"				/* notes: FooBar Client App */
#define GNSDK_LICENSE_OPTION_KEY_START_DATE				"start_date"		/* start_date: 2008-11-04T18:00Z */
#define GNSDK_LICENSE_OPTION_KEY_END_DATE				"end_date"			/* end_date: 2008-11-04T18:01Z */
#define GNSDK_LICENSE_OPTION_KEY_TRIAL_END_DATE			"trial_end_date"	/* trial_end_date: 2008-11-04T18:00Z */
#define GNSDK_LICENSE_OPTION_KEY_MID_CD					"musicid_cd"		/* musicid_cd: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_MID_FILE				"musicid_file"		/* musicid_file: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_MID_TEXT				"musicid_text"		/* musicid_text: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_MID_STREAM				"musicid_stream"	/* musicid_stream: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_MID_FINGERPRINT		"musicid_fingerprint"/* musicid_fingerprint: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_VID					"videoid"			/* videoid: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_VIDEO_EXPLORE			"video_explore"		/* video_explore: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_STREAMID				"streamid"			/* streamid: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_SUBMIT					"submit"			/* submit: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_PLAYLIST				"playlist"			/* playlist generation */
#define GSNDK_LICENSE_OPTION_KEY_MID_MATCH				"musicid_match"		/* musicid_match enabled */
#define GNSDK_LICENSE_OPTION_KEY_CORRELATES				"correlates"		/* correlates retrieval */
#define GNSDK_LICENSE_OPTION_KEY_ACR					"acr"				/* acr */
#define GNSDK_LICENSE_OPTION_KEY_EPG					"epg"				/* epg */

/*
 * Deprecated keys, still needed to produce version 1.0 license file.  These 
 * keys should only be used in the license generator application, GNSDK should
 * use version 2.0 equivalents.
 */
#define GNSDK_LICENSE_OPTION_KEY_MID_DEPRECATED			"musicid"			/* musicid: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_MID_SEARCH_DEPRECATED	"musicid_search"	/* musicid_search: enabled, disabled, trial */
#define GNSDK_LICENSE_OPTION_KEY_VID_EXPLORE_DEPRECATED	"videoid_explore"	/* videoid_explore: enabled, disabled, trial */

#define GNSDK_LICENSE_OPTION_KEY_BLOCK_ONLINE			"block_online"		/* block_online */

/* some entitled data is licensed for local access */
#define GNSDK_LICENSE_OPTION_KEY_MEDIACLICK				"mediaclick"		/* entitlement: MediaClick XIDs */
#define GNSDK_LICENSE_OPTION_KEY_SORTABLE_YOMI			"sortable_yomi"		/* entitlement: AIM Yomi data */
#define GNSDK_LICENSE_OPTION_KEY_AIM_DATA				"aim_data"			/* entitlement: AIM Betsumei data */
#define GNSDK_LICENSE_OPTION_KEY_MOOD_DATA				"mood"				/* entitlement: mood */
#define GNSDK_LICENSE_OPTION_KEY_IMAGES					"images"			/* entitlement: images */

#define GNSDK_LICENSE_OPTION_DELIM						": "

#define GNSDK_LICENSE_OPTION_VALUE_GN					"Gracenote, Inc."
#define GNSDK_LICENSE_OPTION_VALUE_ENABLED				"enabled"
#define GNSDK_LICENSE_OPTION_VALUE_DISABLED				"disabled"
#define GNSDK_LICENSE_OPTION_VALUE_TRIAL				"trial"
#define GNSDK_LICENSE_OPTION_VALUE_DATE_FORMAT			"%04u-%02u-%02u"
#define GNSDK_LICENSE_OPTION_DATE_DELIM					"-"

#define GNSDK_LICENSE_PUBLIC_KEY						"lAADAAEAHgABAAApIbgOFcD6XH81m3Kb0GdalLX3NQ96vExZAVtuFv+PUVKJ1dI/j+N9jlDMVu7zQfhwhVoTocF4eqaZ8xyBBpGDV3wbWyfwVA3Oc3JRCLSq5sG79bAaJNVpZ4VYywr+k4aQSxyojnKJ6I0Sboj5VnDBpcnOYXVkxUabMJRsErbJNnZhro7rMjSfhG2g/aj5D4DJo+9x5LGo9O0HBk4wSTKBxdNKogK+kaonI3yGTdNV0FD150uFHPV2zVZPOj9B5aktdaS1PzKu0nDPLr6tfrou/PJNbVvaZJIGr15GpPxdnuq/L4nz2D34XBa0LmnzzrqXk1iWdkR5kv3fgxtLCxRoAQEAAAGqR+12BnVG3YfObxs9+eGBG7noPNgaj2z41xxjHsSKxkumNhSxeghOClO4kvDTpFvKreSAO2oCmGLuOZUxnXSwB3UPFj2XNsBMLdrlMld0JOgrvTcuQvViDI5gei4Z7A++1c+HGRw6b1V0s491uvUetD635PqAYMdglA4eept3fqR5FDz61q3CC+A6/J+J5WSDuBhwhp1v6iQVPVoWC1SYbQ2ONZPZA9WzfQe306eHYSUHmZDqa/OKXbFF1BHYM3EnzYe54ILBs9JZ7hSWUzmIqyoYPf4zjLH74xfsihHGOPXRP6kbS/Tn7TVqKsP1uPFQWpQc7CRedDzsTst59LetHwAAAAGtYvGtnbv7B2yMa9HdJm4CRt/tYod1FZn7LllwiC0BAQAAAQGk3fYbTag6pTBMHQ9tfce+x9BaAu+YWAZSj9UiACZV0FFaZZH5eYrSlzeawqqcDuR6iHfUEiF2Fc4Ma+JCd7+x9YO4AsIH3VSgM1IumFQqXLyOWarPgCU1Oe2Omb7LfyGtFuattb42EF3tsMheC9EMqAz/F6JY8d06iTikc0qbhg0qZ4DxZIfaP82hRvtJt8ctUqnoe7HMqnYAE49eViLmFnJ/fHlhqqq/2/jN2MAXrbOoI17mDqDbw8QN2j/4tXtyQqeMeFZFVBnVeqGxHIgPAhjC/4MfcE8E8TrITQIoI5vPlwuyHN2tn+kSJ2I4ZGo9I98x3Q9nVVkw1gvE+po="

/* License Version pre-defines */
#define GNSDK_LICENSE_OPTION_KEY_VERSION				"version"			/* version: 2_0 */
#define GNSDK_LICENSE_OPTION_VERSION_ONE_ZERO			"1_0"				/* 1.0 */
#define GNSDK_LICENSE_OPTION_VERSION_TWO_ZERO			"2_0"				/* 2.0 */


/*****************************************************************************
** Privileged Interface:
**					gnsdk_iostream_provider_interface_t
*/
#define GNSDK_IOSTREAM_PROVIDER_INTERFACE								"_gnsdk_iostream_provider_interface"

typedef struct _gnsdk_iostream_provider_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)		(struct _gnsdk_iostream_provider_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_iostream_read)			(gnsdk_void_t* p_iostream_data, gnsdk_void_t* data_buffer, gnsdk_size_t buffer_size, gnsdk_size_t* p_bytes_read);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_iostream_write)			(gnsdk_void_t* p_iostream_data, const gnsdk_void_t* data_buffer, gnsdk_size_t buffer_size, gnsdk_size_t* p_bytes_written);
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_iostream_release)		(gnsdk_void_t* p_iostream_data);

} gnsdk_iostream_provider_interface_t;



/*****************************************************************************
** Privileged Interface:
**					gnsdk_gdo_provider_interface_t
*/
#define GNSDK_GDO_PROVIDER_INTERFACE										"_gnsdk_gdo_provider_interface"

typedef struct _gnsdk_gdo_provider_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_gdo_provider_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_type)				(gnsdk_void_t* p_gdo_data, gnsdk_cstr_t* p_context);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_child_count)			(gnsdk_void_t* p_gdo_data, gnsdk_cstr_t context_key, gnsdk_uint32_t* p_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_child)				(gnsdk_void_t* p_gdo_data, gnsdk_cstr_t context_key, gnsdk_uint32_t ordinal, gnsdk_bool_t b_can_remove, gnsdk_void_t** pp_child_gdo_data, struct _gnsdk_gdo_provider_interface_s** pp_gdo_provider);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_value_count)			(gnsdk_void_t* p_gdo_data, gnsdk_cstr_t value_key, gnsdk_uint32_t* p_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_value)				(gnsdk_void_t* p_gdo_data, gnsdk_cstr_t value_key, gnsdk_uint32_t ordinal, gnsdk_cstr_t* p_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_value_stream)		(gnsdk_void_t* p_gdo_data, gnsdk_cstr_t value_key, gnsdk_uint32_t ordinal, gnsdk_iostream_provider_interface_t* p_value_stream);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_render_value)		(gnsdk_void_t* p_gdo_data, gnsdk_uint32_t index, gnsdk_cstr_t* p_value_name, gnsdk_cstr_t* p_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_set_locale)				(gnsdk_void_t* p_gdo_data, gnsdk_locale_handle_t locale_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_locale)				(gnsdk_void_t* p_gdo_data, gnsdk_locale_handle_t* p_locale_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_release)					(gnsdk_void_t* p_gdo_data);

} gnsdk_gdo_provider_interface_t;


/*****************************************************************************
** Privileged Type:
**					gnsdk_query_provider_status_t
**
**   The p_status_data parameter to the callback function will always point
**   to at least a gnsdk_query_provider_status_data_t struct. The error definitions
**   below will list what struct the p_status_data parameter represents.
*/
typedef enum
{
	gnsdk_query_provider_status_unknown				= 0,	/* p_status_data = gnsdk_query_provider_status_data_t* */

	gnsdk_query_provider_status_query_begin,				/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_request_add,				/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_request_process,			/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_cache_search,				/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_cache_hit,					/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_cache_miss,					/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_cache_isfull,				/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_network_connecting,			/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_network_sending,			/* p_status_data = gnsdk_query_provider_status_progress_t* */
	gnsdk_query_provider_status_network_receiving,			/* p_status_data = gnsdk_query_provider_status_progress_t* */
	gnsdk_query_provider_status_network_disconnected,		/* p_status_data = gnsdk_query_provider_status_data_t* */
	gnsdk_query_provider_status_query_complete,				/* p_status_data = gnsdk_query_provider_status_data_t* */

	gnsdk_query_provider_status_error_extended_info			/* p_status_data = gnsdk_query_provider_status_error_t* */

} gnsdk_query_provider_status_t;


typedef struct
{
	gnsdk_uint32_t					struct_size;
	gnsdk_query_provider_status_t	status;

} gnsdk_query_provider_status_data_t;

#define GNSDK_QUERY_PROVIDER_STATUS_DATA_INIT		{ sizeof(gnsdk_query_provider_status_data_t), gnsdk_query_provider_status_unknown }

typedef struct
{
	gnsdk_uint32_t					struct_size;
	gnsdk_query_provider_status_t	status;
	gnsdk_size_t					bytes_done;
	gnsdk_size_t					bytes_total;

} gnsdk_query_provider_status_progress_t;

#define GNSDK_QUERY_PROVIDER_STATUS_PROGRESS_INIT	{ sizeof(gnsdk_query_provider_status_progress_t), gnsdk_query_provider_status_unknown, 0, 0 }

typedef struct
{
	gnsdk_uint32_t					struct_size;
	gnsdk_query_provider_status_t	status;
	gnsdk_error_t					error;
	gnsdk_cstr_t					error_message;

} gnsdk_query_provider_status_error_t;

#define GNSDK_QUERY_PROVIDER_STATUS_ERROR_INIT		{ sizeof(gnsdk_query_provider_status_error_t), gnsdk_query_provider_status_error_extended_info, GNSDK_SUCCESS, GNSDK_NULL }


typedef gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_query_provider_callback_fn)(
	const gnsdk_void_t*	callback_data,
	const gnsdk_void_t*	p_status_data,
	gnsdk_bool_t*		p_abort
	);


/*****************************************************************************
** Privileged Interface:
**					gnsdk_lookup_provider_interface_t
*/
#define GNSDK_LOOKUP_PROVIDER_INTERFACE									"_gnsdk_lookup_provider_interface"

#define GNSDK_LOOKUP_CAPABILITY_ONLINE									0x01
#define GNSDK_LOOKUP_CAPABILITY_LOCAL									0x02
#define GNSDK_LOOKUP_CAPABILITY_STREAMING								0x04
#define GNSDK_LOOKUP_CAPABILITY_MUSIC									0x10
#define GNSDK_LOOKUP_CAPABILITY_VIDEO									0x20
#define GNSDK_LOOKUP_CAPABILITY_TUI										0x100
#define GNSDK_LOOKUP_CAPABILITY_MUI										0x200
#define GNSDK_LOOKUP_CAPABILITY_CDTOC									0x400
#define GNSDK_LOOKUP_CAPABILITY_DVDTOC									0x800
#define GNSDK_LOOKUP_CAPABILITY_TEXT									0x1000
#define GNSDK_LOOKUP_CAPABILITY_FP_CMX									0x2000
#define GNSDK_LOOKUP_CAPABILITY_FP_FAPI									0x4000
#define GNSDK_LOOKUP_CAPABILITY_FP_ACR									0x8000


typedef struct _gnsdk_lookup_provider_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_lookup_provider_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_capabilities)			(gnsdk_uint32_t* p_capabilities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_create)				(gnsdk_query_provider_callback_fn callback, const gnsdk_void_t* callback_data, gnsdk_void_t** pp_lookup_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request)			(gnsdk_void_t* p_lookup_data, gnsdk_cstr_t request_type, gnsdk_cstr_t request_id, gnsdk_cstr_t sdk_host_identifier, gnsdk_bool_t b_override_host_identifier);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_data)		(gnsdk_void_t* p_lookup_data, gnsdk_cstr_t request_id, gnsdk_cstr_t data_key, gnsdk_cstr_t data_value, gnsdk_uint32_t data_ord);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_binary)	(gnsdk_void_t* p_lookup_data, gnsdk_cstr_t request_id, gnsdk_cstr_t data_key, gnsdk_void_t* data_value, gnsdk_size_t data_size, gnsdk_uint32_t data_ord);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_gdo)		(gnsdk_void_t* p_lookup_data, gnsdk_cstr_t request_id, gnsdk_cstr_t data_key, gnsdk_gdo_handle_t data_gdo, gnsdk_uint32_t data_ord);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_option)	(gnsdk_void_t* p_lookup_data, gnsdk_cstr_t request_id, gnsdk_cstr_t option_key, gnsdk_cstr_t option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_execute)				(gnsdk_void_t* p_lookup_data, gnsdk_user_handle_t user_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_get_response_gdo)		(gnsdk_void_t* p_lookup_data, gnsdk_cstr_t request_id, gnsdk_void_t** pp_gdo_data, gnsdk_gdo_provider_interface_t** pp_gdo_provider);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_get_response_stream)	(gnsdk_void_t* p_lookup_data, gnsdk_cstr_t request_id, gnsdk_void_t** pp_iostream_data, gnsdk_iostream_provider_interface_t** pp_iostream_provider);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_release)				(gnsdk_void_t* p_lookup_data);

} gnsdk_lookup_provider_interface_t;

/* primary objects */
#define GNSDK_LOOKUP_TYPE_ALBUM							"gnsdk_lookup_type_album"
#define GNSDK_LOOKUP_TYPE_AUDIO_WORK					"gnsdk_lookup_type_audio_work"
#define GNSDK_LOOKUP_TYPE_LYRIC							"gnsdk_lookup_type_lyric"
#define GNSDK_LOOKUP_TYPE_TRACK							"gnsdk_lookup_type_track"
#define GNSDK_LOOKUP_TYPE_SUBMIT						"gnsdk_lookup_type_submit"
#define GNSDK_LOOKUP_TYPE_WORKORDER						"gnsdk_lookup_type_workorder"
#define GNSDK_LOOKUP_TYPE_LIST							"gnsdk_lookup_type_list"
#define GNSDK_LOOKUP_TYPE_VIDEO_PRODUCT					"gnsdk_lookup_type_video_product"
#define GNSDK_LOOKUP_TYPE_VIDEO_WORK					"gnsdk_lookup_type_video_work"
#define GNSDK_LOOKUP_TYPE_VIDEO_SERIES					"gnsdk_lookup_type_video_series"
#define GNSDK_LOOKUP_TYPE_VIDEO_SEASON					"gnsdk_lookup_type_video_season"
#define GNSDK_LOOKUP_TYPE_VIDEO_CONTRIBUTOR				"gnsdk_lookup_type_video_contrib"
#define GNSDK_LOOKUP_TYPE_VIDEO_OBJECT					"gnsdk_lookup_type_video_obj"
#define GNSDK_LOOKUP_TYPE_TVPROGRAM						"gnsdk_lookup_type_tvprogram"
#define GNSDK_LOOKUP_TYPE_TVPROVIDER					"gnsdk_lookup_type_tvprovider"
#define GNSDK_LOOKUP_TYPE_TVCHANNEL						"gnsdk_lookup_type_tvchannel"
#define GNSDK_LOOKUP_TYPE_TVGRID						"gnsdk_lookup_type_tvgrid"
#define GNSDK_LOOKUP_TYPE_MATCH							"gnsdk_lookup_type_text_match" /* returns object that matches best */

/* used(?) by streamID */
#define GNSDK_LOOKUP_TYPE_VIDEO_MEDIA					"gnsdk_lookup_type_video_media"


/* ACR  'TUIDS' (for ACR pilot)*/
#define GNSDK_LOOKUP_TYPE_TUIDS_ALBUM					"gnsdk_lookup_type_tuids_album"
/* ACR 'proper' lookup for GA */
#define GNSDK_LOOKUP_TYPE_ACR							"gnsdk_lookup_type_acr"


/* LINK objects (used by gnsdk_link exclusively) */
#define GNSDK_LOOKUP_TYPE_GENRE_LINK					"gnsdk_lookup_type_genre_link"
#define GNSDK_LOOKUP_TYPE_ALBUM_LINK					"gnsdk_lookup_type_album_link"
#define GNSDK_LOOKUP_TYPE_TRACK_LINK					"gnsdk_lookup_type_track_link"
#define GNSDK_LOOKUP_TYPE_LYRIC_LINK					"gnsdk_lookup_type_lyric_link"
#define GNSDK_LOOKUP_TYPE_VIDEO_PRODUCT_LINK			"gnsdk_lookup_type_video_product_link"
#define GNSDK_LOOKUP_TYPE_VIDEO_WORK_LINK				"gnsdk_lookup_type_video_work_link"
#define GNSDK_LOOKUP_TYPE_VIDEO_SERIES_LINK				"gnsdk_lookup_type_video_series_link"
#define GNSDK_LOOKUP_TYPE_VIDEO_SEASON_LINK				"gnsdk_lookup_type_video_season_link"
#define GNSDK_LOOKUP_TYPE_VIDEO_CONTRIBUTOR_LINK		"gnsdk_lookup_type_video_contrib_link"

/* Scan n match */
#define GNSDK_LOOKUP_TYPE_MATCH_ID						"gnsdk_lookup_type_match_id"		/* Lookup up music xid based on fingerprints*/
#define GNSDK_LOOKUP_TYPE_COMPARE_MATCH_ID				"gnsdk_lookup_type_compare_match_id"	/*  Compare xid's for a single match based on an extended fingerprint*/

/* SUGGESTION objects */
#define GNSDK_LOOKUP_TYPE_VIDEO_PRODUCT_SUGGEST			"gnsdk_lookup_type_video_product_suggest"
#define GNSDK_LOOKUP_TYPE_VIDEO_WORK_SUGGEST			"gnsdk_lookup_type_video_work_suggest"
#define GNSDK_LOOKUP_TYPE_VIDEO_SERIES_SUGGEST			"gnsdk_lookup_type_video_series_suggest"
#define GNSDK_LOOKUP_TYPE_VIDEO_CONTRIBUTOR_SUGGEST		"gnsdk_lookup_type_video_contrib_suggest"

#define GNSDK_LOOKUP_OPTION_ENABLE_LINK					"gnsdk_lookup_option_link"
#define GNSDK_LOOKUP_OPTION_ENABLE_DSP					"gnsdk_lookup_option_dsp"
#define GNSDK_LOOKUP_OPTION_ENABLE_SONIC				"gnsdk_lookup_option_sonic"
#define GNSDK_LOOKUP_OPTION_ENABLE_AIM					"gnsdk_lookup_option_aim"
#define GNSDK_LOOKUP_OPTION_ENABLE_CLASSICAL			"gnsdk_lookup_option_class"
#define GNSDK_LOOKUP_OPTION_ENABLE_GLOBALIDS			"gnsdk_lookup_option_globalids"
#define GNSDK_LOOKUP_OPTION_ENABLE_EXPLORE				"gnsdk_lookup_option_exp"
#define GNSDK_LOOKUP_OPTION_ENABLE_PLAYLIST				"gnsdk_lookup_option_playlist"

#define GNSDK_LOOKUP_OPTION_ANCHORED_SEARCH				"gnsdk_lookup_option_anch"

/* Lookup Data - each request has one or more pieces of data - jmctodo - trim anything that SDKs won't use directly*/
#define GNSDK_LOOKUP_DATA_ALBUM_TOC						"gnsdk_lookup_data_toc"
#define GNSDK_LOOKUP_DATA_TUI							"gnsdk_lookup_data_tui"
#define GNSDK_LOOKUP_DATA_TUI_TAG						"gnsdk_lookup_data_tui_tag"
#define GNSDK_LOOKUP_DATA_GNUID							"gnsdk_lookup_data_gnuid"
#define GNSDK_LOOKUP_DATA_REV							"gnsdk_lookup_data_rev"
#define GNSDK_LOOKUP_DATA_ALBUM_ARTIST					"gnsdk_lookup_data_album_artist"
#define GNSDK_LOOKUP_DATA_ALBUM_TITLE					"gnsdk_lookup_data_album_title"
#define GNSDK_LOOKUP_DATA_TRACK_ARTIST					"gnsdk_lookup_data_track_artist"
#define GNSDK_LOOKUP_DATA_ARTIST						"gnsdk_lookup_data_artist" /* covers both album and track artists */
#define GNSDK_LOOKUP_DATA_TRACK_TITLE					"gnsdk_lookup_data_track_title"
#define GNSDK_LOOKUP_DATA_GENRE							"gnsdk_lookup_data_genre"
#define GNSDK_LOOKUP_DATA_COMPOSER						"gnsdk_lookup_data_composer"
#define GNSDK_LOOKUP_DATA_FILE_NAME						"gnsdk_lookup_data_file_name"
#define GNSDK_LOOKUP_DATA_FOLDER_NAME					"gnsdk_lookup_data_folder_name"
#define GNSDK_LOOKUP_DATA_GPARENT_FOLDER_NAME			"gnsdk_lookup_data_gparent_folder_name"
#define GNSDK_LOOKUP_DATA_LYRIC_ARTIST					"gnsdk_lookup_data_lyric_artist"
#define GNSDK_LOOKUP_DATA_LYRIC_TITLE					"gnsdk_lookup_data_lyric_title"
#define GNSDK_LOOKUP_DATA_LYRIC_FRAGMENT				"gnsdk_lookup_data_lyric_fragment"
#define GNSDK_LOOKUP_DATA_MUI							"gnsdk_lookup_data_mui"
#define GNSDK_LOOKUP_DATA_LFS							"gnsdk_lookup_data_lfs"
#define GNSDK_LOOKUP_DATA_MEDIA_ID						"gnsdk_lookup_data_media_id"
#define GNSDK_LOOKUP_DATA_TRACK_MATCHED					"gnsdk_lookup_data_track_matched"

#define GNSDK_LOOKUP_DATA_LIST_NAME						"gnsdk_lookup_data_list_name"
#define GNSDK_LOOKUP_DATA_LIST_REV						"gnsdk_lookup_data_list_rev"

#define GNSDK_LOOKUP_DATA_VID_TOC_SOURCE				"gnsdk_lookup_data_vid_toc_src"
#define GNSDK_LOOKUP_DATA_VID_TOC_ALGORITHM				"gnsdk_lookup_data_vid_toc_alg"
#define GNSDK_LOOKUP_DATA_VID_TOC_ORIGINALCOUNT			"gnsdk_lookup_data_vid_toc_orig_cnt"
#define GNSDK_LOOKUP_DATA_VID_TOC_TYPE					"gnsdk_lookup_data_vid_toc_type"
#define GNSDK_LOOKUP_DATA_VID_TOC_OFFSETS_VALUE			"gnsdk_lookup_data_vid_toc_offsets"
#define GNSDK_LOOKUP_DATA_VID_TOC_OFFSETS_FPS			"gnsdk_lookup_data_vid_toc_offsets_fps"
#define GNSDK_LOOKUP_DATA_VID_TOC_OFFSETS_SAMPLE_RATE	"gnsdk_lookup_data_vid_toc_offsets_sample_rate"
#define GNSDK_LOOKUP_DATA_VID_TOC_OFFSETS_ORIGINALCOUNT	"gnsdk_lookup_data_vid_toc_offsets_orig_cnt"
#define GNSDK_LOOKUP_DATA_VID_TOC_OFFSETS_TITLENUM		"gnsdk_lookup_data_vid_toc_offsets_title_num"

#define GNSDK_LOOKUP_DATA_VALUE_TOC_TYPE_DVD			"gnsdk_lookup_data_value_vid_toc_dvd"
#define GNSDK_LOOKUP_DATA_VALUE_TOC_TYPE_DVD_ANGLES		"gnsdk_lookup_data_value_vid_toc_dvd_angles"
#define GNSDK_LOOKUP_DATA_VALUE_TOC_TYPE_BD				"gnsdk_lookup_data_value_vid_toc_bd"

#define GNSDK_LOOKUP_DATA_VID_TITLE						"gnsdk_lookup_data_vid_title"
#define GNSDK_LOOKUP_DATA_VID_GN_REGION					"gnsdk_lookup_data_vid_gn_region"
#define GNSDK_LOOKUP_DATA_VID_TV_SYSTEM					"gnsdk_lookup_data_vid_tv_system"
#define GNSDK_LOOKUP_DATA_VID_MEDIA_TYPE				"gnsdk_lookup_data_vid_media_type"
#define GNSDK_LOOKUP_DATA_VID_MATCH_LOCATOR				"gnsdk_lookup_data_vid_match_locator"
#define GNSDK_LOOKUP_DATA_VID_ASPECT_RATIO				"gnsdk_lookup_data_vid_aspect_ratio"
#define GNSDK_LOOKUP_DATA_VID_VOL_LABEL					"gnsdk_lookup_data_vid_vol_label"

#define GNSDK_LOOKUP_DATA_VID_FILTER_SEASON_NUM			"gnsdk_lookup_data_vid_filter_season_num"
#define GNSDK_LOOKUP_DATA_VID_FILTER_SEASON_EPISODE_NUM	"gnsdk_lookup_data_vid_filter_season_episode_num"
#define GNSDK_LOOKUP_DATA_VID_FILTER_SERIES_EPISODE_NUM	"gnsdk_lookup_data_vid_filter_series_episode_num"

#define GNSDK_LOOKUP_DATA_VID_FILTER_GENRE_INCLUDE				"gnsdk_lookup_data_vid_filter_genre_include"
#define GNSDK_LOOKUP_DATA_VID_FILTER_GENRE_EXCLUDE				"gnsdk_lookup_data_vid_filter_genre_exclude"
#define GNSDK_LOOKUP_DATA_VID_FILTER_PRODUCTION_TYPE_INCLUDE	"gnsdk_lookup_data_vid_filter_production_type_include"
#define GNSDK_LOOKUP_DATA_VID_FILTER_PRODUCTION_TYPE_EXCLUDE	"gnsdk_lookup_data_vid_filter_production_type_exclude"
#define GNSDK_LOOKUP_DATA_VID_FILTER_RATING_INCLUDE				"gnsdk_lookup_data_vid_filter_rating_include"
#define GNSDK_LOOKUP_DATA_VID_FILTER_RATING_EXCLUDE				"gnsdk_lookup_data_vid_filter_rating_exclude"
#define GNSDK_LOOKUP_DATA_VID_FILTER_ORIGIN_INCLUDE				"gnsdk_lookup_data_vid_filter_origin_include"
#define GNSDK_LOOKUP_DATA_VID_FILTER_ORIGIN_EXCLUDE				"gnsdk_lookup_data_vid_filter_origin_exclude"
#define GNSDK_LOOKUP_DATA_VID_FILTER_PRIMARY_LANGUAGE_INCLUDE	"gnsdk_lookup_data_vid_filter_primary_language_include"
#define GNSDK_LOOKUP_DATA_VID_FILTER_PRIMARY_LANGUAGE_EXCLUDE	"gnsdk_lookup_data_vid_filter_primary_language_exclude"
#define GNSDK_LOOKUP_DATA_VID_FILTER_FORMAT_INCLUDE				"gnsdk_lookup_data_vid_filter_format_include"
#define GNSDK_LOOKUP_DATA_VID_FILTER_FORMAT_EXCLUDE				"gnsdk_lookup_data_vid_filter_format_exclude"
#define GNSDK_LOOKUP_DATA_VID_FILTER_SERIAL_TYPE_INCLUDE		"gnsdk_lookup_data_vid_filter_serial_type_include"
#define GNSDK_LOOKUP_DATA_VID_FILTER_SERIAL_TYPE_EXCLUDE		"gnsdk_lookup_data_vid_filter_serial_type_exclude"

/* XID support */
#define GNSDK_LOOKUP_DATA_VID_XID_ID					"gnsdk_lookup_data_vid_xid_id"
#define GNSDK_LOOKUP_DATA_VID_XID_DATASOURCE			"gnsdk_lookup_data_vid_xid_source"
#define GNSDK_LOOKUP_DATA_VID_XID_DATATYPE				"gnsdk_lookup_data_vid_xid_type"

/* Abstracted ID support (XID or otherwise) :
Note: This must replace the above or be replaced by the above for a common approach
*/
#define GNSDK_LOOKUP_DATA_ID							"gnsdk_lookup_data_id"
#define GNSDK_LOOKUP_DATA_ID_SOURCE						"gnsdk_lookup_data_id_source"
#define GNSDK_LOOKUP_DATA_ID_TYPE						"gnsdk_lookup_data_id_type"

/* CONTRIBUTORS AND WORKS */
#define GNSDK_LOOKUP_DATA_VID_CONTRIBUTOR_NAME			"gnsdk_lookup_data_vid_contributor_name"
#define GNSDK_LOOKUP_DATA_VID_CHARACTER_NAME			"gnsdk_lookup_data_vid_character_name"
#define GNSDK_LOOKUP_DATA_VID_WORK_FRANCHISE			"gnsdk_lookup_data_vid_work_franchise"
#define GNSDK_LOOKUP_DATA_VID_WORK_SERIES				"gnsdk_lookup_data_vid_work_series"
#define GNSDK_LOOKUP_DATA_VID_WORK_SEASON 				"gnsdk_lookup_data_vid_work_season"
#define GNSDK_LOOKUP_DATA_VID_ALL						"gnsdk_lookup_data_vid_all"
#define GNSDK_LOOKUP_DATA_VID_SERIES_TITLE				"gnsdk_lookup_data_vid_series_title"

/* EPG Data */

#define GNSDK_LOOKUP_DATA_EPG_COUNTRY					"gnsdk_lookup_data_epg_country"
#define GNSDK_LOOKUP_DATA_EPG_POSTAL_CODE				"gnsdk_lookup_data_epg_postal_code"
#define GNSDK_LOOKUP_DATA_EPG_ONID						"gnsdk_lookup_data_epg_onid"
#define GNSDK_LOOKUP_DATA_EPG_TSID						"gnsdk_lookup_data_epg_tsid"
#define GNSDK_LOOKUP_DATA_EPG_SID						"gnsdk_lookup_data_epg_sid"
#define GNSDK_LOOKUP_DATA_EPG_IDENT						"gnsdk_lookup_data_epg_ident"
#define GNSDK_LOOKUP_DATA_TVPROVIDER_TUI				"gnsdk_lookup_data_tvprovider_tui"
#define GNSDK_LOOKUP_DATA_TVPROVIDER_TUI_TAG			"gnsdk_lookup_data_tvprovider_tui_tag"
#define GNSDK_LOOKUP_DATA_TVCHANNEL_TUI					"gnsdk_lookup_data_tvchannel_tui"
#define GNSDK_LOOKUP_DATA_TVCHANNEL_TUI_TAG				"gnsdk_lookup_data_tvchannel_tui_tag"
#define GNSDK_LOOKUP_DATA_START_DATE					"gnsdk_lookup_data_start_date"
#define GNSDK_LOOKUP_DATA_END_DATE						"gnsdk_lookup_data_end_date"
#define GNSDK_LOOKUP_DATA_EPG_PROGRAM_TITLE				"gnsdk_lookup_data_epg_program_title"

/* Work Orders */
#define GNSDK_LOOKUP_DATA_ALBUM							"gnsdk_lookup_data_album"
#define GNSDK_LOOKUP_DATA_OBJECT_TYPE					"gnsdk_lookup_data_object_type"
#define GNSDK_LOOKUP_DATA_VALUE_OBJECT_TYPE_ALBUM		"gnsdk_lookup_data_value_obj_album"

/* Genre cover art */
#define GNSDK_LOOKUP_DATA_GENRE_ID						"gnsdk_lookup_data_genre_id"

/* Ranges */
#define GNSDK_LOOKUP_DATA_RESULT_RANGE_START			"gnsdk_lookup_data_result_range_start"
#define GNSDK_LOOKUP_DATA_RESULT_RANGE_END				"gnsdk_lookup_data_result_range_end"

#define GNSDK_LOOKUP_DATA_FPX_ALG_NAME					"gnsdk_lookup_data_fpx_algname"
#define GNSDK_LOOKUP_DATA_FPX_ALG_VERSION				"gnsdk_lookup_data_fpx_algver"
#define GNSDK_LOOKUP_DATA_FPX_MATCH_STATE				"gnsdk_lookup_data_fpx_matchstate"
#define GNSDK_LOOKUP_DATA_FPX_QUERY_DATA				"gnsdk_lookup_data_fpx_querydata"
#define GNSDK_LOOKUP_DATA_CMX_QUERY_DATA				"gnsdk_lookup_data_cmx_querydata"

/* OPAQUE SUBMIT support */
#define GNSDK_LOOKUP_DATA_OPAQUE_DATA					"gnsdk_lookup_data_opaque_data"
#define GNSDK_LOOKUP_DATA_TYPE							"gnsdk_lookup_data_type"
#define GNSDK_LOOKUP_DATA_SUBTYPE						"gnsdk_lookup_data_subtype"
#define GNSDK_LOOKUP_DATA_IDENT							"gnsdk_lookup_data_ident"
#define GNSDK_LOOKUP_DATA_ENCODING						"gnsdk_lookup_data_encoding"

#define GNSDK_LOOKUP_DATA_VALUE_MEDIA_TYPE_CD			"1"
#define GNSDK_LOOKUP_DATA_VALUE_MEDIA_TYPE_DVD			"2"
#define GNSDK_LOOKUP_DATA_VALUE_MEDIA_TYPE_BD			"3"
#define GNSDK_LOOKUP_DATA_VALUE_MEDIA_TYPE_HD_DVD		"4"
#define GNSDK_LOOKUP_DATA_VALUE_ASPECT_4_3				"4:3"
#define GNSDK_LOOKUP_DATA_VALUE_ASPECT_WIDESCREEN		"widescreen"
#define GNSDK_LOOKUP_DATA_VALUE_SAMPLE_RATE_4500		"45000"
#define GNSDK_LOOKUP_DATA_VALUE_SAMPLE_RATE_25			"25"
#define GNSDK_LOOKUP_DATA_VALUE_SAMPLE_RATE_30			"30"
#define GNSDK_LOOKUP_DATA_VALUE_AACS_CCID				"aacs-ccid"

#define GNSDK_LOOKUP_DATA_VALUE_XID_DATASOURCE_GRACENOTE	"gracenote"
#define GNSDK_LOOKUP_DATA_VALUE_XID_DATATYPE_UPC			"UPC"
#define GNSDK_LOOKUP_DATA_VALUE_XID_DATATYPE_ISAN			"ISAN"

#define GNSDK_LOOKUP_RESULT_VALUE_NO_MATCHES			"gnsdk_result_no_matches"			/* 0 matches */
#define GNSDK_LOOKUP_RESULT_VALUE_SINGLE_MATCH			"gnsdk_result_single_match"			/* 1 exact match */
#define GNSDK_LOOKUP_RESULT_VALUE_FUZZY_MATCHES			"gnsdk_result_fuzzy_matches"		/* 1-n fuzzy matches */
#define GNSDK_LOOKUP_RESULT_VALUE_MULTI_EXACT_MATCHES	"gnsdk_result_multiexact_matches"	/* 2-n exact matches */
#define GNSDK_LOOKUP_RESULT_VALUE_NO_NEW_REV			"gnsdk_result_no_new_rev"			/* no new revision */
#define GNSDK_LOOKUP_RESULT_VALUE_PARTIAL_MATCHES		"gnsdk_result_partial_matches"		/* 1-n partial toc matches */
#define GNSDK_LOOKUP_RESULT_VALUE_AGGRESSIVE_MATCHES	"gnsdk_result_agro_matches"			/* 1-n partial toc matches */
#define GNSDK_LOOKUP_RESULT_VALUE_ERROR					"gnsdk_result_error"				/* an error has occured */
#define GNSDK_LOOKUP_RESULT_VALUE_SERVER_ERROR			"gnsdk_result_server_error"			/* a server error has occured */
#define GNSDK_LOOKUP_RESULT_VALUE_CLIENT_ERROR			"gnsdk_result_client_error"			/* a client error has occured */
#define GNSDK_LOOKUP_RESULT_VALUE_MISSING_FIELD			"gnsdk_result_missing_filed"		/* a required field was missing */
#define GNSDK_LOOKUP_RESULT_VALUE_INVALID_CONTENTS		"gnsdk_result_invalid_contents"		/* a field contains invalid contents */
#define GNSDK_LOOKUP_RESULT_VALUE_SUCCESS				"gnsdk_result_success"				/* success */

/*****************************************************************************
** Privileged Interface:
**					gnsdk_content_provider_interface_t
*/
#define GNSDK_CONTENT_PROVIDER_INTERFACE								"_gnsdk_content_provider_interface"

#define GNSDK_CONTENT_CAPABILITY_ONLINE									0x01
#define GNSDK_CONTENT_CAPABILITY_LOCAL									0x02
#define GNSDK_CONTENT_CAPABILITY_CACHED									0x04
#define GNSDK_CONTENT_CAPABILITY_COVERART								0x10 /* jmctodo add more of these if we really want to support this as a capability */

typedef struct _gnsdk_content_provider_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_content_provider_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_capabilities)		(gnsdk_uint32_t* p_capabilities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_request_create)		(gnsdk_user_handle_t user_handle, gnsdk_cstr_t content_type, gnsdk_query_provider_callback_fn callback, const gnsdk_void_t* callback_data, gnsdk_void_t** pp_content_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_set_request_data)	(gnsdk_void_t* p_content_data, gnsdk_cstr_t content_data, gnsdk_cstr_t data_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_set_option)			(gnsdk_void_t* p_content_data, gnsdk_cstr_t option_name, gnsdk_cstr_t option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_data_fetch)			(gnsdk_void_t* p_content_data, gnsdk_bool_t b_decoded, gnsdk_byte_t** pp_buffer, gnsdk_size_t* p_buffer_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_data_delete)			(gnsdk_void_t* p_content_data, gnsdk_byte_t* p_buffer);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_request_release)		(gnsdk_void_t* p_content_data);

} gnsdk_content_provider_interface_t;



/*****************************************************************************
** Privileged Interface:
**					gnsdk_storage_provider_interface_t
*/
#define GNSDK_STORAGE_PROVIDER_INTERFACE							"_gnsdk_storage_provider_interface"

#define GNSDK_STORAGE_CAPABILITY_ONDISK								0x01
#define GNSDK_STORAGE_CAPABILITY_INMEMORY							0x02
#define GNSDK_STORAGE_CAPABILITY_REMOTE								0x04

typedef enum
{
	gnsdk_storage_field_type_unknown	= 0,

	gnsdk_storage_field_type_string,
	gnsdk_storage_field_type_integer,
	gnsdk_storage_field_type_binary

} gnsdk_storage_field_type_t;


#define GNSDK_STORAGE_FIELD_FLAG_DEFAULT	0x0
#define GNSDK_STORAGE_FIELD_FLAG_INDEXED	0x1
#define GNSDK_STORAGE_FIELD_FLAG_UNIQUE		0x2


typedef struct _gnsdk_storage_provider_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_storage_provider_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_capabilities)		(gnsdk_uint32_t* p_capabilities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_open)				(gnsdk_cstr_t group_name, gnsdk_cstr_t storage_name, gnsdk_cstr_t location, gnsdk_void_t** pp_storage_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_create)				(gnsdk_cstr_t group_name, gnsdk_cstr_t storage_name, gnsdk_cstr_t location, gnsdk_void_t** pp_storage_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_validate)			(gnsdk_cstr_t group_name, gnsdk_cstr_t location, gnsdk_bool_t* p_is_valid);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_compact)				(gnsdk_cstr_t group_name, gnsdk_cstr_t location);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_read)				(gnsdk_void_t* p_storage_data, gnsdk_void_t* p_query_record_data, gnsdk_void_t** pp_iterator_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_update)				(gnsdk_void_t* p_storage_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_get_size)			(gnsdk_void_t* p_storage_data, gnsdk_size_t* p_storage_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_empty)				(gnsdk_void_t* p_storage_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_version_get)			(gnsdk_void_t* p_storage_data, gnsdk_cstr_t* p_version);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_version_set)			(gnsdk_void_t* p_storage_data, gnsdk_cstr_t version);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_location_set)		(gnsdk_void_t* p_storage_data, gnsdk_cstr_t location);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_delete)				(gnsdk_void_t* p_storage_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_field_count)			(gnsdk_void_t* p_storage_data, gnsdk_uint32_t* p_field_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_field_get)			(gnsdk_void_t* p_storage_data, gnsdk_uint32_t field_index, gnsdk_cstr_t* p_field_name, gnsdk_storage_field_type_t* p_field_type, gnsdk_uint32_t* p_field_flags);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_field_set)			(gnsdk_void_t* p_storage_data, gnsdk_cstr_t field_name, gnsdk_storage_field_type_t field_type, gnsdk_uint32_t field_flags);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_option_get)			(gnsdk_void_t* p_storage_data, gnsdk_cstr_t option_name, gnsdk_cstr_t* p_option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_option_set)			(gnsdk_void_t* p_storage_data, gnsdk_cstr_t option_name, gnsdk_cstr_t option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_release)				(gnsdk_void_t* p_storage_data);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_iterator_next)				(gnsdk_void_t* p_iterator_data, gnsdk_void_t** pp_record_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_iterator_release)			(gnsdk_void_t* p_iterator_data);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_create)				(gnsdk_void_t* p_storage_data, gnsdk_void_t** pp_record_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_insert)				(gnsdk_void_t* p_record_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_update)				(gnsdk_void_t* p_record_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_delete)				(gnsdk_void_t* p_record_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_set_binary)			(gnsdk_void_t* p_record_data, gnsdk_cstr_t field_name, const gnsdk_void_t* field_data, gnsdk_size_t data_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_set_string)			(gnsdk_void_t* p_record_data, gnsdk_cstr_t field_name, gnsdk_cstr_t string);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_set_uint)				(gnsdk_void_t* p_record_data, gnsdk_cstr_t field_name, gnsdk_uint32_t value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_get_binary)			(gnsdk_void_t* p_record_data, gnsdk_cstr_t field_name, gnsdk_void_t** p_field_data, gnsdk_size_t* p_data_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_get_string)			(gnsdk_void_t* p_record_data, gnsdk_cstr_t field_name, gnsdk_cstr_t* p_string);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_get_uint)				(gnsdk_void_t* p_record_data, gnsdk_cstr_t field_name, gnsdk_uint32_t* p_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_record_release)				(gnsdk_void_t* p_record_data);

} gnsdk_storage_provider_interface_t;


/*****************************************************************************
** Privileged Interface:
**					gnsdk_http_provider_interface_t
*/
#define GNSDK_HTTP_PROVIDER_INTERFACE							"_gnsdk_http_provider_interface"

typedef struct _gnsdk_http_provider_interface_s
{
	gnsdk_error_t	(GNSDK_CALLBACK_API *open)				(gnsdk_void_t** pp_connection_data, gnsdk_cstr_t host_name, gnsdk_uint16_t port, gnsdk_bool_t b_host_is_proxy, gnsdk_uint32_t timeout);
	gnsdk_void_t	(GNSDK_CALLBACK_API *close)				(gnsdk_void_t* p_connection_data);

	gnsdk_error_t	(GNSDK_CALLBACK_API *send_request)		(gnsdk_void_t* p_connection_data, gnsdk_cstr_t http_method, gnsdk_cstr_t headers, gnsdk_cstr_t path, gnsdk_size_t content_length);
	gnsdk_error_t	(GNSDK_CALLBACK_API *send_content)		(gnsdk_void_t* p_connection_data, const gnsdk_void_t* content_buffer, gnsdk_size_t content_length);

	gnsdk_error_t	(GNSDK_CALLBACK_API *recv_response)		(gnsdk_void_t* p_connection_data, gnsdk_void_t* buffer, gnsdk_size_t buffer_size, gnsdk_size_t* p_bytes_rcvd);

	gnsdk_error_t	(GNSDK_CALLBACK_API *resolve)			(gnsdk_cstr_t host_name, gnsdk_char_t* address_buf, gnsdk_size_t buffer_size);

} gnsdk_http_provider_interface_t;


/*****************************************************************************
** Privileged Interface:
**					gnsdk_memory_provider_interface_t
*/
#define GNSDK_MEMORY_PROVIDER_INTERFACE							"_gnsdk_memory_provider_interface"

typedef struct _gnsdk_memory_provider_interface_s
{
	gnsdk_error_t	(GNSDK_CALLBACK_API *memory_initialize)	(void);
	gnsdk_void_t	(GNSDK_CALLBACK_API *memory_shutdown)	(void);

	gnsdk_void_t*	(GNSDK_CALLBACK_API *memory_alloc)		(gnsdk_size_t size);
	gnsdk_void_t*	(GNSDK_CALLBACK_API *memory_calloc)		(gnsdk_size_t count, gnsdk_size_t size);
	gnsdk_void_t*	(GNSDK_CALLBACK_API *memory_realloc)	(gnsdk_void_t* p_ptr, gnsdk_size_t size);
	gnsdk_void_t	(GNSDK_CALLBACK_API *memory_free)		(gnsdk_void_t* p_ptr);

	gnsdk_void_t	(GNSDK_CALLBACK_API *memory_memcpy)		(gnsdk_void_t *dest, const gnsdk_void_t *src, gnsdk_size_t size);
	gnsdk_void_t	(GNSDK_CALLBACK_API *memory_memmove)	(gnsdk_void_t *dest, const gnsdk_void_t *src, gnsdk_size_t size);
	gnsdk_void_t	(GNSDK_CALLBACK_API *memory_memset)		(gnsdk_void_t *dest, gnsdk_byte_t val, gnsdk_size_t count);
	gnsdk_int32_t	(GNSDK_CALLBACK_API *memory_memcmp)		(const gnsdk_void_t *buff1, const gnsdk_void_t *buff2, gnsdk_size_t count);

} gnsdk_memory_provider_interface_t;


/******************************************************************************
** Privileged GDO Values:
*/

/** GNSDK_GDO_VALUE_EXTERNALID_VENDOR
  * Summary:
  *   Retrieves an external ID vendor value from a GDO.
*/
#define GNSDK_GDO_VALUE_EXTERNALID_VENDOR				"gnsdk_val_xid_vendor"

/** GNSDK_QUERY_OPTION_ENABLE_AIM_DATA
  * Summary:
  *   Indicate whether a response should include any associated <label name="conditional">\<Yomi/Betsumi?\>
  *   </label>data.
*/
#define GNSDK_QUERY_OPTION_ENABLE_AIM_DATA				"gnsdk_query_option_enable_aim"

/******************************************************************************
** Internal Lists
*/
#define	GNSDK_DESCRIPTOR_CDS_ID_MAP						"gnsdk_desc_cds_map"
#define	GNSDK_LIST_KEY_CDS_ID							"gnsdk_list_key_cds_id"
#define	GNSDK_DESCRIPTOR_MAP							"gnsdk_desc_map"
#define	GNSDK_DESCRIPTOR_V1_V2							"gnsdk_desc_v1_v2"

/******************************************************************************
** Correlate Lists
*/
#define	GNSDK_CORRELATES_TYPE_GENRES					"gnsdk_correlates_genre"
#define	GNSDK_CORRELATES_TYPE_ORIGINS					"gnsdk_correlates_origin"
#define	GNSDK_CORRELATES_TYPE_ERAS						"gnsdk_correlates_era"
#define	GNSDK_CORRELATES_TYPE_ARTISTTYPES				"gnsdk_correlates_arttype"
#define	GNSDK_CORRELATES_TYPE_MOODS						"gnsdk_correlates_mood"

GNSDK_DECLARE_HANDLE( gnsdk_list_correlates_handle_t );

/*****************************************************************************
** Privileged API: gnsdk_manager_register_* (register provider interface)
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_register_storage_provider	(gnsdk_cstr_t intf_name, gnsdk_storage_provider_interface_t* p_intf);

gnsdk_error_t GNSDK_API
gnsdk_manager_register_http_provider	(gnsdk_cstr_t intf_name, gnsdk_http_provider_interface_t* p_intf);

gnsdk_error_t GNSDK_API
gnsdk_manager_register_memory_provider	(gnsdk_cstr_t intf_name, gnsdk_memory_provider_interface_t* p_intf);


/*****************************************************************************
** Privileged API: gnsdk_manager_query_interface
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_query_interface			(gnsdk_cstr_t intf_name, gnsdk_void_t** p_intf);

#define GNSDK_INTERFACE_RELEASE(p_intf)	if (p_intf) { p_intf->gnsdk_interface_release(p_intf); p_intf = GNSDK_NULL; }


/*****************************************************************************
** Privileged API: gnsdk_manager_status
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_status(gnsdk_uint32_t op, gnsdk_size_t* p_current, gnsdk_size_t* p_highwater, gnsdk_bool_t b_reset_highwater);

#define GNSDK_MANAGER_STATUS_MEMORY_USED		1
#define GNSDK_MANAGER_STATUS_MALLOC_COUNT		2


/*****************************************************************************
** Privileged API: gnsdk_manager_memory_warn
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_memory_warn(void (*mem_warn_fn)(gnsdk_void_t* p_arg, gnsdk_size_t cur_mem_size, gnsdk_size_t memory_warn_size), gnsdk_void_t* p_arg, gnsdk_size_t memory_warn_size);



/****************************************************************************
** GNSDK Metric defines
*/
#ifndef GNSDK_METRICS_ALL
	#define GNSDK_METRICS_ALL 0
#endif

#if GNSDK_METRICS_ALL
	#ifndef GNSDK_METRICS_MEMORY
		#define GNSDK_METRICS_MEMORY	1
	#endif
	#ifndef GNSDK_METRICS_FILE
		#define GNSDK_METRICS_FILE		1
	#endif
	#ifndef GNSDK_METRICS_SOCKET
		#define GNSDK_METRICS_SOCKET	1
	#endif
	#ifndef GNSDK_METRICS_TIME
		#define GNSDK_METRICS_TIME		1
	#endif
#else
	#ifndef GNSDK_METRICS_MEMORY
		#define GNSDK_METRICS_MEMORY	0
	#endif
	#ifndef GNSDK_METRICS_FILE
		#define GNSDK_METRICS_FILE		0
	#endif
	#ifndef GNSDK_METRICS_SOCKET
		#define GNSDK_METRICS_SOCKET	0
	#endif
	#ifndef GNSDK_METRICS_TIME
		#define GNSDK_METRICS_TIME		0
	#endif
#endif

#if GNSDK_METRICS_MEMORY
	#define GNSDK_METRIC_MEMORY_START(name)	GCSL_MEMORY_MARKSTART(name)
	#define GNSDK_METRIC_MEMORY_END			GCSL_MEMORY_MARKEND
#else
	#define GNSDK_METRIC_MEMORY_START(name)
	#define GNSDK_METRIC_MEMORY_END
#endif

#if GNSDK_METRICS_FILE
	#define GNSDK_METRIC_FILE_START(name) 	GCSL_FS_MARKSTART(name)
	#define GNSDK_METRIC_FILE_END 			GCSL_FS_MARKEND
#else
	#define GNSDK_METRIC_FILE_START(name)
	#define GNSDK_METRIC_FILE_END
#endif

#if GNSDK_METRICS_SOCKET
	#define GNSDK_METRIC_SOCKET_START(name) GCSL_SOCKET_MARKSTART(name)
	#define GNSDK_METRIC_SOCKET_END			GCSL_SOCKET_MARKEND
#else
	#define GNSDK_METRIC_SOCKET_START(name)
	#define GNSDK_METRIC_SOCKET_END
#endif

#if GNSDK_METRICS_TIME
	#define GNSDK_METRIC_TIME_START(name) 	GCSL_TIME_MARKSTART(name)
	#define GNSDK_METRIC_TIME_END			GCSL_TIME_MARKEND
#else
	#define GNSDK_METRIC_TIME_START(name)
	#define GNSDK_METRIC_TIME_END
#endif

#define GNSDK_METRIC_MARKSTART(name)	GNSDK_METRIC_SOCKET_START(name) GNSDK_METRIC_FILE_START(name) GNSDK_METRIC_TIME_START(name) GNSDK_METRIC_MEMORY_START(name)
#define GNSDK_METRIC_MARKEND			GNSDK_METRIC_MEMORY_END GNSDK_METRIC_TIME_END GNSDK_METRIC_FILE_END GNSDK_METRIC_SOCKET_END


/****************************************************************************
** GNSDK MoodGrid Datasource Provider  Interface.
*/
#define GNSDK_MOODGRID_DATASOURCE_PROVIDER_INTERFACE	"_gnsdk_moodgrid_datasource_provider_interface"

typedef struct _gnsdk_moodgrid_datasource_provider_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)								(struct _gnsdk_moodgrid_datasource_provider_interface_s* me, gnsdk_void_t* intf_object);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_capabilities)				(gnsdk_uint32_t* p_capabilities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_gdo_get)						(struct _gnsdk_moodgrid_datasource_provider_interface_s* me, gnsdk_void_t* intf_object, gnsdk_cstr_t ident, gnsdk_void_t** p_gdo);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_data_get)					(struct _gnsdk_moodgrid_datasource_provider_interface_s* me, gnsdk_void_t* intf_object, gnsdk_cstr_t key, gnsdk_cstr_t* p_value);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_option_get)					(struct _gnsdk_moodgrid_datasource_provider_interface_s* me, gnsdk_void_t* intf_object, gnsdk_cstr_t option_name, gnsdk_cstr_t* p_option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_option_set)					(struct _gnsdk_moodgrid_datasource_provider_interface_s* me, gnsdk_void_t* intf_object, gnsdk_cstr_t option_name, gnsdk_cstr_t option_value);

	/* Transaction management  */
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_create)			(struct _gnsdk_moodgrid_datasource_provider_interface_s* me , gnsdk_void_t* intf_object, gnsdk_void_t** pp_transaction_handle,gnsdk_void_t*	user_handle, gnsdk_query_provider_callback_fn callback, gnsdk_void_t* callback_userdata);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_filter_create)	(gnsdk_void_t* p_transaction_handle, gnsdk_cstr_t list_type,gnsdk_cstr_t list_value, gnsdk_cstr_t condition_type,gnsdk_uint32_t*  p_index );
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_find)			( gnsdk_void_t* p_transaction_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_find_estimate)	( gnsdk_void_t* p_transaction_handle, gnsdk_uint32_t* p_out_estimate);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_result_count)	( gnsdk_void_t* p_transaction_handle, gnsdk_uint32_t*  p_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_result_enum)		( gnsdk_void_t* p_transaction_handle, gnsdk_uint32_t index, gnsdk_cstr_t* p_ident, gnsdk_cstr_t* p_group);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_release)			( gnsdk_void_t* p_transaction_handle);

} gnsdk_moodgrid_datasource_provider_interface_t;


#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_MANAGER_PRIVILEGED_H_ */


