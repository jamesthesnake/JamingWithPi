/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_gcsp.h - Gracenote Client Server Protocol client functions
 */

#ifndef _GCSL_GCSP_H_
#define _GCSL_GCSP_H_

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * GCSP types
 */
typedef gcsl_uint32_t			gcsl_gcsp_lookup_flags_t;

/*
 * GCSP options HDO keys
 */
#define GCSP_OPTION_NETWORK_TIMEOUT					"gcsp_option_timeout"				/* ms before giving up */
#define GCSP_OPTION_NETWORK_LOADBALANCE				"gcsp_network_loadbalance"			/* enable true/false */
#define GCSP_OPTION_HTTP_PIPELINING					"gcsp_option_pipelining"			/* use http pipelining */
#define GCSP_OPTION_OVERRIDE_URL					"gcsp_option_override_url"			/* GCSP override url */

/* compression and checksum options */
#define GCSP_OPTION_DO_NOT_COMPRESS_REQUESTS		"gcsp_option_no_compression"	/* any string value that works in gcsl_string_atobool() */
#define GCSP_OPTION_DO_NOT_ENCRYPT_REQUESTS			"gcsp_option_no_encryption"		/* any string value that works in gcsl_string_atobool() */
#define GCSP_OPTION_REQUEST_COMPRESS_CKSUM_TYPE		"gcsp_option_compress_cksum_type"
#define GCSP_OPTION_REQUEST_ENCRYP_CKSUM_TYPE		"gcsp_option_encryp_cksum_type"
#define GCSP_OPTION_KEY_CRYPT_TYPE					"gcsp_option_crypt_type"			

#define GCSP_OPTION_VALUE_CRYPT_3_V1				"gcsp_option_crypt_3v1"
#define GCSP_OPTION_VALUE_CRYPT_4_V1				"gcsp_option_crypt_4v1"
#define GCSP_OPTION_VALUE_CRYPT_4_V2				"gcsp_option_crypt_4v2"
#define GCSP_OPTION_VALUE_CRYPT_4_V3				"gcsp_option_crypt_4v3"
#define GCSP_OPTION_VALUE_CRYPT_4_V4				"gcsp_option_crypt_4v4"

/* proxy support */
#define GCSP_OPTION_PROXY_HOST_INFO					"gcsp_option_proxy_host"		/* host:port */
#define GCSP_OPTION_PROXY_USER						"gcsp_option_proxy_user"
#define GCSP_OPTION_PROXY_PASS						"gcsp_option_proxy_pass"


/* gcsl_gcsp opaque handle
*/
GCSL_DECLARE_HANDLE( gcsl_gcsp_handle_t );

/*
 * Callback
 */

typedef enum
{
	gcsl_gcsp_status_unknown				= 0,

	gcsl_gcsp_status_connecting,
	gcsl_gcsp_status_sending,
	gcsl_gcsp_status_receiving,
	gcsl_gcsp_status_disconnected

} gcsl_gcsp_status_t;


typedef gcsl_void_t	(GCSL_CALLBACK_API *gcsl_gcsp_status_callback_fn)(
	const gcsl_void_t*	callback_data,
	gcsl_gcsp_status_t	status,
	gcsl_size_t			bytes_now,
	gcsl_size_t			bytes_done,
	gcsl_size_t			bytes_total,
	gcsl_bool_t*		pb_abort
	);

typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_gcsp_response_callback_fn)(
	const gcsl_void_t*		callback_data,
	gcsl_cstr_t				submit_url,
	gcsl_iostream_handle_t	response_stream,
	gcsl_bool_t*			pb_abort
	);

/*
 * Initialization
 */

gcsl_error_t	gcsl_gcsp_initialize		(void);
gcsl_error_t	gcsl_gcsp_shutdown			(void);

gcsl_cstr_t		gcsl_gcsp_get_version		(void);
gcsl_cstr_t		gcsl_gcsp_get_build_date	(void);


/******************************************************************************
 * GCSP Transaction APIs
 *	Buildup transaction handle with 1 or more requests, call execute, done
 */
gcsl_error_t	gcsl_gcsp_transaction_create(
	gcsl_gcsp_handle_t*				ptransaction_handle,
	gcsl_cstr_t						client_id,			/* required */
	gcsl_gcsp_status_callback_fn	callback,			/* optional */
	const gcsl_void_t*				callback_data		/* optional */
	);

/* helper to allow for easy transaction creation from existing transaction. will copy 
client, callback and options into a new empty transaction */
gcsl_error_t	gcsl_gcsp_transaction_create_from(
	gcsl_gcsp_handle_t				transaction_handle,
	gcsl_gcsp_handle_t*				p_transaction_copy_handle
	);

gcsl_error_t	gcsl_gcsp_transaction_option_set(
	gcsl_gcsp_handle_t				transaction_handle,
	gcsl_cstr_t						option_name,
	gcsl_cstr_t						option_value
	);

gcsl_error_t	gcsl_gcsp_transaction_add_request(
	gcsl_gcsp_handle_t				transaction_handle,
	gcsl_hdo_handle_t				request_hdo,		/* required. HDO representation of GCSP REQUEST xml */
	gcsl_cstr_t						request_id,
	gcsl_cstr_t						sdk_host_id,
	gcsl_bool_t						b_override_host_id
	);

/* NB first pass at this only supports chained TUI_ID inputs */
gcsl_error_t	gcsl_gcsp_transaction_add_request_chained(
	gcsl_gcsp_handle_t				transaction_handle,
	gcsl_hdo_handle_t				request_hdo,		/* required. HDO representation of GCSP REQUEST xml */
	gcsl_hdo_handle_t				input_request_hdo,	/* the output of this request will be the input of request_hdo.
												NB: this request must have been already added to the transaction. */
	gcsl_cstr_t						sdk_host_identifier,
	gcsl_bool_t						b_override_host_identifier
	);

gcsl_error_t	gcsl_gcsp_transaction_find_request(
	gcsl_gcsp_handle_t				transaction_handle, 
	gcsl_cstr_t						request_id,
	gcsl_hdo_handle_t*				p_request_hdo
	);

gcsl_error_t	gcsl_gcsp_transaction_remove_request(
	gcsl_gcsp_handle_t				transaction_handle, 
	gcsl_cstr_t						request_id,
	gcsl_hdo_handle_t*				p_request_hdo
	);

/* all transactions default to a lang_id of 1 (English) if this API isn't called */
gcsl_error_t	gcsl_gcsp_transaction_set_format(
	gcsl_gcsp_handle_t				transaction_handle, 
	gcsl_cstr_t						p_lang_id,
	gcsl_cstr_t						p_encoding
	);

gcsl_error_t	gcsl_gcsp_transaction_get_format(
	gcsl_gcsp_handle_t				transaction_handle, 
	gcsl_cstr_t*					lang_id,
	gcsl_cstr_t*					encoding
	);

gcsl_error_t	gcsl_gcsp_transaction_execute(
	gcsl_gcsp_handle_t				transaction_handle
	);

gcsl_error_t	gcsl_gcsp_transaction_get_response(
	gcsl_gcsp_handle_t				transaction_handle,
	gcsl_cstr_t						request_id,
	gcsl_iostream_handle_t*			p_response_stream,
	gcsl_uint32_t*					p_response_code
	);

gcsl_error_t	gcsl_gcsp_transaction_delete(
	gcsl_gcsp_handle_t				transaction_handle
	);


/******************************************************************************
 * GCSP Connection APIs
 *	Create GCSP connection to service, post/put requests immediately
 *	Responses are sent to callback asynchronously
 */

gcsl_error_t	gcsl_gcsp_connection_create(
	gcsl_gcsp_handle_t*				p_connection_handle,
	gcsl_cstr_t						client_id,
	gcsl_cstr_t						sdk_host_identifier,
	gcsl_gcsp_status_callback_fn	status_callback,
	const gcsl_void_t*				callback_data
	);

gcsl_error_t	gcsl_gcsp_connection_option_set(
	gcsl_gcsp_handle_t				connection_handle,
	gcsl_cstr_t						option_name,
	gcsl_cstr_t						option_value
	);

gcsl_error_t	gcsl_gcsp_connection_send_request_hdo(
	gcsl_gcsp_handle_t				connection_handle,
	gcsl_hdo_handle_t				requests_hdo,
	gcsl_uint32_t					request_flags,
	gcsl_cstr_t						target_path,	/* GCSL_NULL for default */
	gcsl_gcsp_response_callback_fn	response_callback,
	const gcsl_void_t*				callback_data
	);

gcsl_error_t	gcsl_gcsp_connection_send_request_xml(
	gcsl_gcsp_handle_t				connection_handle,
	gcsl_cstr_t						request_xml,
	gcsl_uint32_t					request_flags,
	gcsl_cstr_t						target_path,	/* GCSL_NULL for default */
	gcsl_gcsp_response_callback_fn	response_callback,
	const gcsl_void_t*				callback_data
	);

#define		GCSP_REQUEST_SEND_POST						0x1
#define		GCSP_REQUEST_WAIT_FOR_RESPONSE				0x2
#define		GCSP_REQUEST_MULTIPART_START				0x10
#define		GCSP_REQUEST_MULTIPART_PUT					0x20
#define		GCSP_REQUEST_DEFAULT						(GCSP_REQUEST_SEND_POST|GCSP_REQUEST_WAIT_FOR_RESPONSE)


gcsl_error_t	gcsl_gcsp_connection_delete(
	gcsl_gcsp_handle_t				connection_handle
	);


/******************************************************************************
 * GCSP Request Builder APIs
 */

/* Request Building Helpers - jmctodo - see if we can abstract the fact that requests are HDO's so SKD manager can stop using hdo APis*/
gcsl_error_t	gcsl_gcsp_request_create(
	gcsl_gcsp_lookup_flags_t	lookup_type,
	gcsl_hdo_handle_t*			p_request_hdo
	);

gcsl_error_t	gcsl_gcsp_request_add_data(
	gcsl_hdo_handle_t			request_hdo, 
	gcsl_cstr_t					data_key, 
	gcsl_cstr_t					data_value, 
	gcsl_uint32_t				index
	);

gcsl_error_t	gcsl_gcsp_request_add_hdo(
	gcsl_hdo_handle_t			request_hdo, 
	gcsl_cstr_t					data_key, 
	gcsl_hdo_handle_t			data_hdo, 
	gcsl_uint32_t				index
	);

gcsl_error_t	gcsl_gcsp_request_add_option(
	gcsl_hdo_handle_t			request_hdo, 
	gcsl_cstr_t					option_key, 
	gcsl_cstr_t					option_value
	);

/* jmctodo replace this with request_get_cache_key() or get_guid() that returns md5 or whatever Paul uses for caching */
/* Helper functions to try and keep GCSP request knowledge in GCSL */
gcsl_error_t	gcsl_gcsp_request_helper_chained_to_tui_request(
	gcsl_hdo_handle_t		request_hdo, 
	gcsl_hdo_handle_t		response_hdo 
	);


/******************************************************************************
 * GCSP Response Helper APIs
 */

/* position response stream to start of response matching 'response_id' */
gcsl_error_t	gcsl_gcsp_response_stream_seek_to_id(
	gcsl_iostream_handle_t		responses_stream,
	gcsl_cstr_t					response_id,
	gcsl_uint32_t*				p_response_code
	);

/* Response level error handling helper. returns the full error code and if the response contained GEMP XML, a copy of that */
gcsl_error_t	gcsl_gcsp_response_code_to_error(
	gcsl_uint32_t				response_code,
	gcsl_error_t*				p_response_error
	);


#define GCSP_RESPONSE_CODE_PREFIX(code)					(code / 10000)
#define GCSP_RESPONSE_MATCH_CODE_PREFIX					1
#define GCSP_RESPONSE_SERVER_ERROR_PREFIX				4
#define GCSP_RESPONSE_CLIENT_ERROR_PREFIX				5

#define GCSP_RESPONSE_MATCH_CODE_OK						10000
#define GCSP_RESPONSE_MATCH_CODE_EXACT					10001
#define GCSP_RESPONSE_MATCH_CODE_MULTI_EXACT			10002
#define GCSP_RESPONSE_MATCH_CODE_FUZZY					10003
#define GCSP_RESPONSE_MATCH_CODE_NONE					10004
#define GCSP_RESPONSE_MATCH_CODE_NO_NEW_REV				10005
#define GCSP_RESPONSE_MATCH_CODE_PARTIAL				10006
#define GCSP_RESPONSE_MATCH_CODE_AGGRESSIVE				10007

#define GCSP_RESPONSE_SERVER_ERROR_CLIENT_ID			40013 /* I've seen this when client ID isn't enabled for FAPI */

#define GCSP_RESPONSE_MATCH_CODE_CHAINED_INVALID_ARG	50002 /* Invalid inputs or Chained input not set. */
#define GCSP_RESPONSE_MATCH_CODE_MISSING_FIELD			50011 /* A required field is missing. */
#define GCSP_RESPONSE_MATCH_CODE_INVALID_CONTENTS		50014 /* A field contains invalid contents */

/*
GCSP Response Codes

10000	OK
10001	Exact Match
10002	Multiple Exact Match
10003	Fuzzy Matches
10004	No Match
10005	No New Revision
10006	Partial TOC match (a match on a title unit)
10007	Aggressive match logic applied (results could be misleading)

30001	Quota Exceeded

40013	Cannot send query to service 3 XP server for gcsp_default.

50002	Invalid Argument
50003	Invalid Key
50005	Invalid Client
50006	Invalid User
50007	Invalid Registration Keys
50011	A required field is missing.
50014	A field contains invalid contents
*/

/* Lookup Data - each request has one or more pieces of data */
#define GCSL_GCSP_DATA_NONE							"gcsp_lookup_data_none"
#define GCSL_GCSP_DATA_ALBUM_TOC					"gcsp_lookup_data_toc"
#define GCSL_GCSP_DATA_TUI							"gcsp_lookup_data_tui"
#define GCSL_GCSP_DATA_TUI_TAG						"gcsp_lookup_data_tui_tag"
#define GCSL_GCSP_DATA_GNUID						"gcsp_lookup_data_gnuid"
#define GCSL_GCSP_DATA_REV							"gcsp_lookup_data_rev"
#define GCSL_GCSP_DATA_REV_TAG						"gcsp_lookup_data_rev_tag"
#define GCSL_GCSP_DATA_COMPOSER						"gcsp_lookup_data_composer"
#define GCSL_GCSP_DATA_ALBUM_ARTIST					"gcsp_lookup_data_album_artist"
#define GCSL_GCSP_DATA_ALBUM_TITLE					"gcsp_lookup_data_album_title"
#define GCSL_GCSP_DATA_TRACK_ARTIST					"gcsp_lookup_data_track_artist"
#define GCSL_GCSP_DATA_ARTIST						"gcsp_lookup_data_artist" /* covers both album and track artists */
#define GCSL_GCSP_DATA_TRACK_TITLE					"gcsp_lookup_data_track_title"
#define GCSL_GCSP_DATA_FILE_NAME					"gcsp_lookup_data_file_name"
#define GCSL_GCSP_DATA_FOLDER_NAME					"gcsp_lookup_data_folder_name"
#define GCSL_GCSP_DATA_LYRIC_ARTIST					"gcsp_lookup_data_lyric_artist"
#define GCSL_GCSP_DATA_LYRIC_TITLE					"gcsp_lookup_data_lyric_title"
#define GCSL_GCSP_DATA_LYRIC_FRAGMENT				"gcsp_lookup_data_lyric_fragment"
#define GCSL_GCSP_DATA_FP							"gcsp_lookup_data_fp" /* used by MID-F, so i guess it implies CMX? jmctodo snuff this one in favor of CMX-specific*/
#define GCSL_GCSP_DATA_MUI							"gcsp_lookup_data_mui"
#define GCSL_GCSP_DATA_LFS							"gcsp_lookup_data_lfs"
#define GCSL_GCSP_DATA_MEDIA_ID						"gcsp_lookup_data_media_id"
#define GCSL_GCSP_DATA_TRACK_MATCHED				"gcsp_lookup_data_track_matched"
#define GCSL_GCSP_DATA_TRACK_NUM					"gcsp_lookup_data_track_num"
#define GCSL_GCSP_DATA_CHAINED_INPUT_IDENT			"gcsp_lookup_data_chained_input_ident"

#define GCSL_GCSP_DATA_LIST_NAME					"gcsp_lookup_data_list_name"
#define GCSL_GCSP_DATA_LIST_REV						"gcsp_lookup_data_list_rev"

#define GCSL_GCSP_DATA_VID_TOC_SOURCE				"gcsp_lookup_data_vid_toc_src"
#define GCSL_GCSP_DATA_VID_TOC_ALGORITHM			"gcsp_lookup_data_vid_toc_alg"
#define GCSL_GCSP_DATA_VID_TOC_ORIGINALCOUNT		"gcsp_lookup_data_vid_toc_orig_cnt"
#define GCSL_GCSP_DATA_VID_TOC_TYPE					"gcsl_gcsp_lookup_data_vid_toc_type" /* ANGLES */

#define GCSL_GCSP_DATA_VALUE_TOC_TYPE_DVD_ANGLES	"gcsl_gcsp_lookup_data_value_toc_type_dvd_angles"

#define GCSL_GCSP_DATA_VID_TOC_OFFSETS_VALUE			"gcsp_lookup_data_vid_toc_offsets"
#define GCSL_GCSP_DATA_VID_TOC_OFFSETS_FPS				"gcsp_lookup_data_vid_toc_offsets_fps"
#define GCSL_GCSP_DATA_VID_TOC_OFFSETS_SAMPLE_RATE		"gcsp_lookup_data_vid_toc_offsets_sample_rate"
#define GCSL_GCSP_DATA_VID_TOC_OFFSETS_ORIGINALCOUNT	"gcsp_lookup_data_vid_toc_offsets_orig_cnt"
#define GCSL_GCSP_DATA_VID_TOC_OFFSETS_TITLENUM			"gcsp_lookup_data_vid_toc_offsets_title_num"

#define GCSL_GCSP_DATA_VID_TITLE						"gcsp_lookup_data_vid_title"
#define GCSL_GCSP_DATA_VID_GN_REGION					"gcsp_lookup_data_vid_gn_region"
#define GCSL_GCSP_DATA_VID_TV_SYSTEM					"gcsp_lookup_data_vid_tv_system"
#define GCSL_GCSP_DATA_VID_MEDIA_TYPE					"gcsp_lookup_data_vid_media_type"
#define GCSL_GCSP_DATA_VID_MATCH_LOCATOR				"gcsp_lookup_data_vid_match_locator"
#define GCSL_GCSP_DATA_VID_ASPECT_RATIO					"gcsp_lookup_data_vid_aspect_ratio"
#define GCSL_GCSP_DATA_VID_VOL_LABEL					"gcsp_lookup_data_vid_vol_label"

#define GCSL_GCSP_DATA_VID_FILTER_SEASON_NUM			"gcsp_lookup_data_vid_filter_season_num"
#define GCSL_GCSP_DATA_VID_FILTER_SEASON_EPISODE_NUM	"gcsp_lookup_data_vid_filter_season_episode_num"
#define GCSL_GCSP_DATA_VID_FILTER_SERIES_EPISODE_NUM	"gcsp_lookup_data_vid_filter_series_episode_num"

#define GCSL_GCSP_DATA_VID_FILTER_GENRE_INCLUDE				"gcsp_lookup_data_vid_filter_genre_include"
#define GCSL_GCSP_DATA_VID_FILTER_GENRE_EXCLUDE				"gcsp_lookup_data_vid_filter_genre_exclude"
#define GCSL_GCSP_DATA_VID_FILTER_PRODUCTION_TYPE_INCLUDE	"gcsp_lookup_data_vid_filter_production_type_include"
#define GCSL_GCSP_DATA_VID_FILTER_PRODUCTION_TYPE_EXCLUDE	"gcsp_lookup_data_vid_filter_production_type_exclude"
#define GCSL_GCSP_DATA_VID_FILTER_RATING_INCLUDE			"gcsp_lookup_data_vid_filter_rating_include"
#define GCSL_GCSP_DATA_VID_FILTER_RATING_EXCLUDE			"gcsp_lookup_data_vid_filter_rating_exclude"
#define GCSL_GCSP_DATA_VID_FILTER_ORIGIN_INCLUDE			"gcsp_lookup_data_vid_filter_origin_include"
#define GCSL_GCSP_DATA_VID_FILTER_ORIGIN_EXCLUDE			"gcsp_lookup_data_vid_filter_origin_exclude"
#define GCSL_GCSP_DATA_VID_FILTER_PRIMARY_LANGUAGE_INCLUDE	"gcsp_lookup_data_vid_filter_primary_language_include"
#define GCSL_GCSP_DATA_VID_FILTER_PRIMARY_LANGUAGE_EXCLUDE	"gcsp_lookup_data_vid_filter_primary_language_exclude"
#define GCSL_GCSP_DATA_VID_FILTER_FORMAT_INCLUDE			"gcsp_lookup_data_vid_filter_format_include"
#define GCSL_GCSP_DATA_VID_FILTER_FORMAT_EXCLUDE			"gcsp_lookup_data_vid_filter_format_exclude"
#define GCSL_GCSP_DATA_VID_FILTER_SERIAL_TYPE_INCLUDE		"gcsp_lookup_data_vid_filter_serial_type_include"
#define GCSL_GCSP_DATA_VID_FILTER_SERIAL_TYPE_EXCLUDE		"gcsp_lookup_data_vid_filter_serial_type_exclude"

/* Metadata Submit */
#define GCSL_GCSP_DATA_ALBUM								"gcsp_data_album"	
#define GCSL_GCSP_DATA_OBJECT_TYPE							"gcsp_lookup_data_object_type"	
#define GCSL_GCSP_DATA_VALUE_OBJECT_TYPE_ALBUM				"gcsp_data_value_object_type_album"

/* XID support */
#define GCSL_GCSP_DATA_VID_XID_ID					"gcsp_lookup_data_vid_xid_id"
#define GCSL_GCSP_DATA_VID_XID_DATASOURCE			"gcsp_lookup_data_vid_xid_source"
#define GCSL_GCSP_DATA_VID_XID_DATATYPE				"gcsp_lookup_data_vid_xid_type"

/* CONTRIBUTORS AND WORKS */
#define GCSL_GCSP_DATA_VID_CONTRIBUTOR_NAME			"gcsp_lookup_data_vid_contributor_name"
#define GCSL_GCSP_DATA_VID_CHARACTER_NAME			"gcsp_lookup_data_vid_character_name"
#define GCSL_GCSP_DATA_VID_WORK_FRANCHISE			"gcsp_lookup_data_vid_work_franchise"
#define GCSL_GCSP_DATA_VID_WORK_SERIES				"gcsp_lookup_data_vid_work_series"
#define GCSL_GCSP_DATA_VID_WORK_SEASON 				"gcsp_lookup_data_vid_work_season"
#define GCSL_GCSP_DATA_VID_ALL						"gcsp_lookup_data_vid_all"
#define GCSL_GCSP_DATA_VID_SERIES_TITLE				"gcsp_lookup_data_vid_series_title"

/* EPG */
#define GCSL_GCSP_DATA_EPG_COUNTRY                  "gcsl_lookup_data_epg_country"
#define GCSL_GCSP_DATA_EPG_POSTAL_CODE              "gcsl_lookup_data_epg_postal_code"
#define GCSL_GCSP_DATA_EPG_ONID                     "gcsl_lookup_data_epg_onid"
#define GCSL_GCSP_DATA_EPG_TSID                     "gcsl_lookup_data_epg_tsid"
#define GCSL_GCSP_DATA_EPG_SID                      "gcsl_lookup_data_epg_sid"
#define GCSL_GCSP_DATA_EPG_PROGRAM_TITLE			"gcsp_lookup_data_epg_program_title"
/* Note: TVPROVIDER_TUI and TVPROVIDER_TUI_TAG are here because it differentiates a TVCHANNEL-by-TVCHANNEL TUI lookup from a TVCHANNEL-by-PROVIDER TUI lookup*/
#define GCSL_GCSP_DATA_TVPROVIDER_TUI				"gcsp_lookup_data_tvprovider_tui"
#define GCSL_GCSP_DATA_TVPROVIDER_TUI_TAG			"gcsp_lookup_data_tvprovider_tui_tag"
/* Note: TVCHANNEL_TUI and TVCHANNEL_TUI_TAG are here because it differentiates the TVCHANNEL TUIs from the OBJECT TUIS (WORK/PRODUCT, ETC) in a TVGRID LOOKUP */
#define GCSL_GCSP_DATA_TVCHANNEL_TUI				"gcsp_lookup_data_tvchannel_tui"
#define GCSL_GCSP_DATA_TVCHANNEL_TUI_TAG			"gcsp_lookup_data_tvchannel_tui_tag"
#define GCSL_GCSP_DATA_START_DATE					"gcsp_lookup_data_start_date"
#define GCSL_GCSP_DATA_END_DATE						"gcsp_lookup_data_end_date"



/* Genre cover art */
#define GCSL_GCSP_DATA_GENRE_ID						"gcsp_lookup_data_genre_id"

/* Ranges */
#define GCSL_GCSP_DATA_RESULT_RANGE_START			"gcsp_lookup_data_result_range_start"
#define GCSL_GCSP_DATA_RESULT_RANGE_END				"gcsp_lookup_data_result_range_end"

#define GCSL_GCSP_DATA_FPX_ALG_NAME					"gcsp_lookup_data_fpx_algname"
#define GCSL_GCSP_DATA_FPX_ALG_VERSION				"gcsp_lookup_data_fpx_algver"
#define GCSL_GCSP_DATA_FPX_MATCH_STATE				"gcsp_lookup_data_fpx_matchstate"
#define GCSL_GCSP_DATA_FPX_QUERY_DATA				"gcsp_lookup_data_fpx_querydata"
#define GCSL_GCSP_DATA_CMX_QUERY_DATA				"gcsp_lookup_data_cmx_querydata"

/* OPAQUE SUBMIT support */
#define GCSL_GCSP_DATA_OPAQUE_DATA					"gcsp_lookup_data_opaque_data"
#define GCSL_GCSP_DATA_TYPE							"gcsp_lookup_data_type"
#define GCSL_GCSP_DATA_SUBTYPE						"gcsp_lookup_data_subtype"
#define GCSL_GCSP_DATA_IDENT						"gcsp_lookup_data_ident"
#define GCSL_GCSP_DATA_ENCODING						"gcsp_lookup_data_encoding"
#define GCSL_GCSP_DATA_MULTIPART_ID					"gcsp_lookup_data_chunk_id"
#define GCSL_GCSP_DATA_MULTIPART_ORD				"gcsp_lookup_data_chunk_ord"
#define GCSL_GCSP_DATA_MULTIPART_COUNT				"gcsp_lookup_data_chunk_count"

#define GCSL_GCSP_DATA_VALUE_MEDIA_TYPE_CD			"1"
#define GCSL_GCSP_DATA_VALUE_MEDIA_TYPE_DVD			"2"
#define GCSL_GCSP_DATA_VALUE_MEDIA_TYPE_BD			"3"
#define GCSL_GCSP_DATA_VALUE_MEDIA_TYPE_HD_DVD		"4"
#define GCSL_GCSP_DATA_VALUE_TRUE					"true"
#define GCSL_GCSP_DATA_VALUE_FALSE					"false"
#define GCSL_GCSP_DATA_VALUE_ASPECT_4_3				"4:3"
#define GCSL_GCSP_DATA_VALUE_ASPECT_WIDESCREEN		"widescreen"
#define GCSL_GCSP_DATA_VALUE_SAMPLE_RATE_4500		"45000"
#define GCSL_GCSP_DATA_VALUE_SAMPLE_RATE_25			"25"
#define GCSL_GCSP_DATA_VALUE_SAMPLE_RATE_30			"30"
#define GCSL_GCSP_DATA_VALUE_AACS_CCID				"aacs-ccid"

#define GCSL_GCSP_DATA_VALUE_XID_DATASOURCE_GRACENOTE	"gracenote"
#define GCSL_GCSP_DATA_VALUE_XID_DATATYPE_UPC			"UPC"
#define GCSL_GCSP_DATA_VALUE_XID_DATATYPE_ISAN			"ISAN"

#define GCSL_GCSP_REQUEST_OPTION_SINGLE					"SINGLE_BEST"		/* MATCH_SELECT = SINGLE_BEST */
#define GCSL_GCSP_REQUEST_OPTION_PREFER_COVER			"SINGLE_BEST_COVER" /* MATCH_SELECT = SINGLE_BEST_COVER */
#define GCSL_GCSP_REQUEST_OPTION_PREFER_XID				"PREFER_XID"
#define GCSL_GCSP_REQUEST_OPTION_AGGRO_MATCHING			"AGGRESSIVE_MATCHING"
#define GCSL_GCSP_REQUEST_OPTION_PERFECT_MATCHING		"PERFECT_MATCHING"
#define GCSL_GCSP_REQUEST_OPTION_STREAM					"STREAM"
#define GCSL_GCSP_REQUEST_OPTION_NO_LOW_POP				"IGNORE_LOW_POPULARITY"
#define GCSL_GCSP_REQUEST_OPTION_ABORT_TOO_MANY			"ABORT_TOO_MANY"
#define GCSL_GCSP_REQUEST_OPTION_RESULT_LIMIT			"LIMIT"
#define GCSL_GCSP_REQUEST_OPTION_SORT_ALG				"SORT_ALGORITHM"
#define GCSL_GCSP_REQUEST_OPTION_SUBMIT_MODE			"SUBMIT_MODE"
#define GCSL_GCSP_REQUEST_OPTION_ALLOW_MULTIPLE			"ALLOW_MULTIPLE"
#define GCSL_GCSP_REQUEST_OPTION_PRESET					"gcsp_option_preset"
#define GCSL_GCSP_REQUEST_OPTION_OUTPUT					"gcsp_option_output"

#define GCSL_GCSP_REQUEST_DATA_CLIENT_ID				"gcsp_request_data_clientid"
#define GCSL_GCSP_REQUEST_DATA_CLIENT_ID_TAG			"gcsp_request_data_clientidtag"
#define GCSL_GCSP_REQUEST_DATA_CLIENT_APP_VERSION		"gcsp_request_data_clientappver"
#define GCSL_GCSP_REQUEST_DATA_USER_ID					"gcsp_request_data_userid"
#define GCSL_GCSP_REQUEST_DATA_USER_ID_TAG				"gcsp_request_data_useridtag"
#define GCSL_GCSP_REQUEST_DATA_USER_LOCATION			"gcsp_request_data_userlocation"
#define GCSL_GCSP_REQUEST_DATA_USER_PLATFORM			"gcsp_request_data_userplatform"


/*
 * Lookup types
 */

#define	GCSL_GCSP_LOOKUP_TYPE_PRIMARY_MASK						(0x000000FF)
#define	GCSL_GCSP_LOOKUP_TYPE_INPUT_MASK						(0x00000F00)
#define	GCSL_GCSP_LOOKUP_TYPE_OPTION_MASK						(0xFFFFF000)

/* helpers for switching on things */
#define GCSL_GCSP_LOOKUP_IS_OPTION_SET(option, flags)			(gcsl_bool_t)(0 != (flags & option))
#define GCSL_GCSP_LOOKUP_GET_INPUT(flags)						(gcsl_gcsp_lookup_flags_t)(flags & GCSL_GCSP_LOOKUP_TYPE_INPUT_MASK)
#define GCSL_GCSP_LOOKUP_GET_PRIMARY(flags)						(gcsl_gcsp_lookup_flags_t)(flags & GCSL_GCSP_LOOKUP_TYPE_PRIMARY_MASK)
#define GCSL_GCSP_LOOKUP_GET_TUI_FROM_CHAINED(flags)			(gcsl_gcsp_lookup_flags_t)((flags & ~GCSL_GCSP_LOOKUP_TYPE_INPUT_MASK)|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)

/* Lookup type flags */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_NONE							(0x00000000)

#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_USER					(0x00000001)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_HELLO				(0x00000002)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM				(0x00000003)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK				(0x00000004) /* NB: at this point, GCSP doesn't support 'track' requests, but this may change, for now, this just translates to ALBUM */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_LYRIC				(0x00000005)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_WORKORDERS			(0x00000006)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUBMIT				(0x00000007)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_AUDIO_WORK			(0x00000008)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_LIST					(0x00000009)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT		(0x0000000a)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK			(0x0000000b)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES			(0x0000000c)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON			(0x0000000d)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB		(0x0000000e)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_MEDIA			(0x0000000f)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_OBJECT			(0x00000010)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVPROGRAM			(0x00000011)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TUIDS_ALBUM			(0x00000012)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ACR					(0x00000013)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_AUDIO_MEDIA			(0x00000020)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_GENRE				(0x00000030)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUGGESTIONS			(0x00000040)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_MATCH_INFO			(0x00000050)   /*Primary request type for Scan and Match */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL			(0x00000060)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVPROVIDER			(0x00000061)
/* Codes 0x62 to 0x64 are reserved for variations on TVCHANNELs and TVPROVIDERS */
/* These will go away when INPUT_TYPES are created for these */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL_BY_TVPROVIDER_TUI	(0x00000062)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL_BY_DVB				(0x00000063)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVPROVIDER_BY_POSTALCODE		(0x00000064)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVGRID						(0x00000065)


#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI					(0x00000100)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC					(0x00000200)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT					(0x00000300)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_ALBUM					(0x00000400) /* for metadata submit */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED				(0x00000500)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_MUI					(0x00000600)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX					(0x00000700) /* FP XML */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_CMX					(0x00000800) /* Cantametrix sig */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC_AND_FP_CMX			(0x00000900) /* CD TOC and Cantametrix sig */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_DATA					(0x00000a00) /* Opaque submits */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_ID						(0x00000b00)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_XID					(0x00000c00)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC_AND_XID			(0x00000d00) /* BD TOC and aacs-ccid XID */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX_AND_XID			(0x00000e00) /* Scan and Match request*/
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX_AND_TUI			(0x00000f00)/* Scan and Match support for TUIs and FP*/

#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_CONTRIB			(0x00010000) /* for use in SUGGESTION searches */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_WORK			(0x00020000) /* for use in SUGGESTION searches */ 
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_SERIES			(0x00040000) /* for use in SUGGESTION searches */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_PRODUCT			(0x00080000) /* for use in SUGGESTION searches */
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK					(0x00100000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA					(0x00200000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_FILE_SET				(0x00400000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_PRESET				(0x00800000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_BD					(0x01000000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ANCHOR				(0x02000000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_DATA_CMI				(0x04000000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS	(0x08000000)


/*
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_XXXX					(0x10000000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_XXXX					(0x20000000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_XXXX					(0x40000000)
#define GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_XXXX					(0x80000000)
*/

/* precooked lookup types */
#define GCSL_GCSP_LOOKUP_TYPE_NONE								(GCSL_GCSP_LOOKUP_TYPE_FLAG_NONE)
#define GCSL_GCSP_LOOKUP_TYPE_USER								(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_USER)
#define GCSL_GCSP_LOOKUP_TYPE_HELLO								(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_HELLO)

#define GCSL_GCSP_LOOKUP_TYPE_LIST								(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_LIST)
#define GCSL_GCSP_LOOKUP_TYPE_LFS								(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_LIST|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_FILE_SET)

/* jmctodo work towards not using these pre-cooked lookup types anywhere.  instead branch on the flags themselves */
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TOC							(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TUI							(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_MUI							(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_MUI)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TOC_AND_FP_CMX				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC_AND_FP_CMX)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_FP_CMX						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_CMX)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_FP_FPX						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TEXT						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TEXT_PRESET					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_PRESET)

/* sch: adding support for requesting credits */
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TOC_ADD_CREDITS				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TUI_ADD_CREDITS				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_MUI_ADD_CREDITS				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_MUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TOC_AND_FP_CMX_ADD_CREDITS	(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC_AND_FP_CMX|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_FP_CMX_ADD_CREDITS			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_CMX|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_FP_FPX_ADD_CREDITS			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TEXT_ADD_CREDITS			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_TEXT_PRESET_ADD_CREDITS		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_PRESET|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)

#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_LINK_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_LINK_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_EXTRA_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_ALBUM_EXTRA_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_WORKORDERS_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_WORKORDERS|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)

#define GCSL_GCSP_LOOKUP_TYPE_SUBMIT_ALBUM						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUBMIT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_ALBUM)
#define GCSL_GCSP_LOOKUP_TYPE_SUBMIT_OPAQUE						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUBMIT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_DATA)

#define GCSL_GCSP_LOOKUP_TYPE_GENRE_LINK						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_GENRE|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_ID|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)

#define GCSL_GCSP_LOOKUP_TYPE_TRACK_TUI							(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_FP_CMX						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_CMX)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_FP_FPX						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_TEXT						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_TEXT_PRESET					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_PRESET)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_LINK_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_LINK_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_EXTRA_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_EXTRA_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)

/* sch: adding support for requesting credits */
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_TUI_ADD_CREDITS				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_FP_CMX_ADD_CREDITS			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_CMX|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_FP_FPX_ADD_CREDITS			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_TEXT_ADD_CREDITS			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)
#define GCSL_GCSP_LOOKUP_TYPE_TRACK_TEXT_PRESET_ADD_CREDITS		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TRACK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_PRESET|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ADDITIONAL_CREDITS)

#define GCSL_GCSP_LOOKUP_TYPE_LYRIC_TEXT						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_LYRIC|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)
#define GCSL_GCSP_LOOKUP_TYPE_LYRIC_TEXT_PRESET					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_LYRIC|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_PRESET)
#define GCSL_GCSP_LOOKUP_TYPE_LYRIC_LINK_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_LYRIC|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)

#define GCSL_GCSP_LOOKUP_TYPE_AUDIO_WORK_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_AUDIO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_AUDIO_WORK_EXTRA_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_AUDIO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_AUDIO_WORK_EXTRA_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_AUDIO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)

#define GCSL_GCSP_LOOKUP_TYPE_AUDIO_MEDIA_FP_FPX				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_AUDIO_MEDIA|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_MEDIA_FP_FPX				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_MEDIA|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX)

#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_OBJECT_XID					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_OBJECT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_XID)
/* NB: these two aren't supported, but to avoid setting them, it is handy to have them defined */
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_OBJECT_LINK_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_OBJECT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_OBJECT_EXTRA_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_OBJECT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)

#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_TOC_DVD				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_TOC_BD				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_BD)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_TOC_BD_AND_XID		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TOC_AND_XID|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_BD)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_TEXT				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_TEXT_ANCHOR			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_ANCHOR)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_XID					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_XID)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_LINK_TUI			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_LINK_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_EXTRA_TUI			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_PRODUCT_EXTRA_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_PRODUCT|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)

#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_LINK_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_LINK_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_EXTRA_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_EXTRA_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_TEXT					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_WORK_XID					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_WORK|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_XID)

#define GCSL_GCSP_LOOKUP_TYPE_TVPROGRAM_TUI						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVPROGRAM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_TVPROGRAM_LINK_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVPROGRAM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_TVPROGRAM_LINK_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVPROGRAM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)

#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_TUI						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_LINK_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_LINK_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)

#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SEASON_XID					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_XID)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SEASON_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SEASON_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SEASON_LINK_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SEASON_LINK_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SEASON_EXTRA_TUI			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SEASON_EXTRA_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SEASON|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)

#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_XID					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_XID)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_TEXT					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_LINK_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_LINK_CHAINED			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_EXTRA_TUI			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_SERIES_EXTRA_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_SERIES|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)

#define GCSL_GCSP_LOOKUP_TYPE_TUIDS_ALBUM_FP_FPX				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TUIDS_ALBUM|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX)
#define GCSL_GCSP_LOOKUP_TYPE_ACR_FP_FPX						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_ACR|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX)

#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_TUI					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_CHAINED				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_TEXT				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_XID					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_XID)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_EXTRA_TUI			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_EXTRA_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_EXTRA)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_LINK_TUI			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_VIDEO_CONTRIB_LINK_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_VIDEO_CONTRIB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)

#define GCSL_GCSP_LOOKUP_TYPE_SUGGESTIONS_VIDEO_PRODUCT			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUGGESTIONS|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_PRODUCT)
#define GCSL_GCSP_LOOKUP_TYPE_SUGGESTIONS_VIDEO_WORK			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUGGESTIONS|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_WORK)
#define GCSL_GCSP_LOOKUP_TYPE_SUGGESTIONS_VIDEO_SERIES			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUGGESTIONS|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_SERIES)
#define GCSL_GCSP_LOOKUP_TYPE_SUGGESTIONS_VIDEO_CONTRIB			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_SUGGESTIONS|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_VIDEO_CONTRIB)

#define GCSL_GCSP_LOOKUP_TYPE_MATCH_INFO_FP_CMX					(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_MATCH_INFO|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_CMX)
#define GCSL_GCSP_LOOKUP_TYPE_MATCH_INFO_COMPARE_XID			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_MATCH_INFO|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX_AND_XID)
#define GCSL_GCSP_LOOKUP_TYPE_MATCH_INFO_COMPARE_TUI			(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_MATCH_INFO|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_FP_FPX_AND_TUI)

/*TODO: When INPUT_TYPES are created for PROVIDER, DVB and POSTALCODE, replace the following 
 #define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_PROVIDER_TUI			GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL_BY_TVPROVIDER_TUI
  will become
 #define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_TVPROVIDER_TUI			GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL | GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TVPROVIDER_TUI
 */
#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_TVPROVIDER_TUI		GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL_BY_TVPROVIDER_TUI
#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_TVPROVIDER_LINK_TUI		(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL_BY_TVPROVIDER_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_TVPRODIVER_LINK_CHAINED	(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL_BY_TVPROVIDER_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)

#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_DVB					GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVCHANNEL_BY_DVB
#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_DVB_LINK_TUI			(GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_DVB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)
#define GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_DVB_LINK_CHAINED		(GCSL_GCSP_LOOKUP_TYPE_TVCHANNEL_BY_DVB|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_CHAINED|GCSL_GCSP_LOOKUP_TYPE_FLAG_OPTION_LINK)

#define GCSL_GCSP_LOOKUP_TYPE_TVPROVIDER_BY_POSTALCODE			GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVPROVIDER_BY_POSTALCODE
#define GCSL_GCSP_LOOKUP_TYPE_TVGRID							GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVGRID
#define GCSL_GCSP_LOOKUP_TYPE_TVGRID_BY_OBJECT_TUI				(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVGRID|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TUI)
#define GCSL_GCSP_LOOKUP_TYPE_TVGRID_TEXT						(GCSL_GCSP_LOOKUP_TYPE_FLAG_PRIMARY_TVGRID|GCSL_GCSP_LOOKUP_TYPE_FLAG_INPUT_TEXT)

#ifdef	__cplusplus
}
#endif

#endif /* _GCSL_GCSP_H_ */
