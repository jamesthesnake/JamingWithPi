/* Copyright (c) 2012 Gracenote.

   This software may not be used in any way or distributed
   without permission. All rights reserved.

   Some code herein may be covered by US and international
   patents.
*/

#ifndef _SDKMGR_INTERFACES_H_
#define _SDKMGR_INTERFACES_H_

#include "gnsdk_manager_lists.h"
#include "gnsdk_manager_privileged.h"

#ifdef __cplusplus
extern "C"{
#endif


/*
 * sdkmgr_interfaces.h:	Service interfaces provided by the SDK Manager. 'Consumer' interfaces, for our internal use.
 */

GNSDK_DECLARE_HANDLE( gnsdk_marshalled_interface_handle_t );

gnsdk_error_t	_sdkmgr_interfaces_initialize	(void);
gnsdk_error_t	_sdkmgr_interfaces_shutdown		(void);


typedef struct _sdkmanager_instance_t
{
	gnsdk_uint32_t	magic;
	gnsdk_cstr_t	version;

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_query_interface)			(gnsdk_cstr_t intf_name, gnsdk_uint32_t capabilities, gnsdk_uint32_t index, gnsdk_void_t** phInterface);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_register_interface)		(gnsdk_cstr_t intf_name, gnsdk_cstr_t custom_name, gnsdk_void_t* phInterface, gnsdk_size_t intf_size, gnsdk_void_t* p_instance_data, gnsdk_marshalled_interface_handle_t* p_intf_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_deregister_interface)	(gnsdk_marshalled_interface_handle_t handle, gnsdk_void_t** pp_instance_data);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_register_client)			(gnsdk_byte_t client_pkg_id, gnsdk_cstr_t sz_client_pkg_str);

} sdkmanager_instance_t;

#define GNSDK_MANAGER_MAGIC			0x1eeeeee1


/******************************************************************************
 * Interfaces supported by SDK Manager
 ******************************************************************************/

/*
 * Interfaces that SDK Manager provides
 */

/******************************************************************************
 * Handle Manager
 */
#define GNSDK_HANDLEMANAGER_INTERFACE		"_gnsdk_handlemanager_interface"

typedef struct _gnsdk_handlemanager_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)					(struct _gnsdk_handlemanager_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_add)					(gnsdk_handle_t handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_remove)				(gnsdk_handle_t handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_verify)				(gnsdk_handle_t handle, gnsdk_uint32_t magic);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_verify_sdkmgr)			(gnsdk_handle_t handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_verify_user)			(gnsdk_handle_t handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_verify_gdo)			(gnsdk_handle_t handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_verify_list)			(gnsdk_handle_t handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_handlemanager_verify_list_element)	(gnsdk_handle_t handle);

} gnsdk_handlemanager_interface_t;


/******************************************************************************
 * I/O Stream
 */
#define GNSDK_IOSTREAM_INTERFACE			"_gnsdk_iostream_interface"

GNSDK_DECLARE_HANDLE( gnsdk_iostream_handle_t );

typedef struct _gnsdk_iostream_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_iostream_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_iostream_read)				(gnsdk_iostream_handle_t iostream_handle, gnsdk_void_t* data_buffer, gnsdk_size_t buffer_size, gnsdk_size_t* p_bytes_read);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_iostream_write)				(gnsdk_iostream_handle_t iostream_handle, const gnsdk_void_t* data_buffer, gnsdk_size_t buffer_size, gnsdk_size_t* p_bytes_written);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_iostream_release)			(gnsdk_iostream_handle_t iostream_handle);

} gnsdk_iostream_interface_t;


/******************************************************************************
 * GDO
 */
#define GNSDK_GDO_INTERFACE			"_gnsdk_gdo_interface"

typedef enum
{
	GNSDK_GDODOM_ELEM_UNKNOWN = 0,
	GNSDK_GDODOM_ELEM_VALUE,
	GNSDK_GDODOM_ELEM_CHILD,
	GNSDK_GDODOM_ELEM_CHILD_MAP,
	GNSDK_GDODOM_ELEM_ATTR,
	GNSDK_GDODOM_ELEM_CONTAINER,			/* simply another layer for the current GDO */
	GNSDK_GDODOM_ELEM_VALUE_CONTAINER,		/* another layer to hold the current value */
	GNSDK_GDODOM_ELEM_CHILD_CONTAINER,		/* another layer to hold the child GDO */
	GNSDK_GDODOM_ELEM_ATTR_PREDEF,
	GNSDK_GDODOM_ELEM_ATTR_PRIMARY,			/* if ORD == 1, PRIMARY = Y */
	GNSDK_GDODOM_ELEM_ATTR_BOOL,			/* value, as Y or N */
	GNSDK_GDODOM_ELEM_ATTR_BOOL_REVERSED,	/* opposite of value, as Y or N */
	GNSDK_GDODOM_ELEM_VALUE_BOOL

} gnsdk_gdo_render_elem_type_t;

typedef enum
{
	GNSDK_GDODOM_COUNT_UNKNOWN = 0,
	GNSDK_GDODOM_COUNT_SINGLE,
	GNSDK_GDODOM_COUNT_DOUBLE,
	GNSDK_GDODOM_COUNT_ORDERED,
	GNSDK_GDODOM_COUNT_NOORDER

} gnsdk_gdo_render_elem_count_t;

typedef	struct _gnsdk_gdo_render_elem_s
{
	gnsdk_cstr_t						gdo_key;
	gnsdk_cstr_t						render_name;

	gnsdk_gdo_render_elem_type_t		elem_type;
	gnsdk_uint32_t						render_flag;
	gnsdk_gdo_render_elem_count_t		count_flag;

	struct _gnsdk_gdo_render_elem_s*	p_render_child;
	gnsdk_uint32_t						num_child_items;

} gnsdk_gdo_render_elem_t;



typedef struct _gnsdk_gdo_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_gdo_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_create)					(gnsdk_void_t* p_gdo_data, gnsdk_gdo_provider_interface_t* p_gdo_provider, gnsdk_user_handle_t user_handle, gnsdk_cstr_t locale_group, gnsdk_uint32_t render_flags, gnsdk_gdo_handle_t* p_gdo_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_create_from_xml)			(gnsdk_cstr_t sz_xml, gnsdk_user_handle_t user_handle, gnsdk_cstr_t locale_group, gnsdk_gdo_handle_t* p_gdo_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_addref)					(gnsdk_gdo_handle_t gdo_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_release)					(gnsdk_gdo_handle_t gdo_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_type)				(gnsdk_gdo_handle_t gdo_handle, gnsdk_cstr_t* p_context);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_value_count)			(gnsdk_gdo_handle_t gdo_handle, gnsdk_cstr_t data_key, gnsdk_uint32_t* p_data_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_value)				(gnsdk_gdo_handle_t gdo_handle, gnsdk_cstr_t data_key, gnsdk_uint32_t ordinal, gnsdk_cstr_t* p_data_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_value_stream)		(gnsdk_gdo_handle_t gdo_handle, gnsdk_cstr_t data_key, gnsdk_uint32_t ordinal, gnsdk_iostream_interface_t* p_value_stream);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_child_count)			(gnsdk_gdo_handle_t gdo_handle, gnsdk_cstr_t data_key, gnsdk_uint32_t* p_data_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_child)				(gnsdk_gdo_handle_t gdo_handle, gnsdk_cstr_t data_key, gnsdk_uint32_t ordinal, gnsdk_bool_t b_can_remove, gnsdk_gdo_handle_t* p_child_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_internal)			(gnsdk_gdo_handle_t gdo_handle, gnsdk_void_t** pp_gdo_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_render_flags)		(gnsdk_gdo_handle_t gdo_handle, gnsdk_uint32_t* p_render_flags);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_set_locale)				(gnsdk_gdo_handle_t gdo_handle, gnsdk_locale_handle_t locale_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_get_locale)				(gnsdk_gdo_handle_t gdo_handle, gnsdk_locale_handle_t* p_locale_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_render_to_xml)			(gnsdk_gdo_handle_t gdo_handle, gnsdk_uint32_t render_flags, gnsdk_gdo_render_elem_t* p_custom_render, gnsdk_str_t* p_xml);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_gdo_free_xml)				(gnsdk_str_t xml);

} gnsdk_gdo_interface_t;


/******************************************************************************
 * Lookup
 */
#define GNSDK_LOOKUP_INTERFACE			"_gnsdk_lookup_interface"	/* 2.0 GCSP refactor school */

GNSDK_DECLARE_HANDLE( gnsdk_lookup_handle_t );

typedef struct _gnsdk_lookup_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_lookup_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_capabilities)			(struct _gnsdk_lookup_interface_s* me, gnsdk_uint32_t* p_capabilities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_create)				(struct _gnsdk_lookup_interface_s* me, gnsdk_query_provider_callback_fn callback, const gnsdk_void_t* callback_data, gnsdk_lookup_handle_t* p_lookup_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request)			(gnsdk_lookup_handle_t lookup_handle, gnsdk_cstr_t request_type, gnsdk_cstr_t request_id, gnsdk_cstr_t sdk_host_identifier, gnsdk_bool_t b_override_host_identifier);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_data)		(gnsdk_lookup_handle_t lookup_handle, gnsdk_cstr_t request_id, gnsdk_cstr_t data_key, gnsdk_cstr_t data_value, gnsdk_uint32_t data_ord);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_binary)	(gnsdk_lookup_handle_t lookup_handle, gnsdk_cstr_t request_id, gnsdk_cstr_t data_key, gnsdk_void_t* data_value, gnsdk_size_t data_size, gnsdk_uint32_t data_ord);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_gdo)		(gnsdk_lookup_handle_t lookup_handle, gnsdk_cstr_t request_id, gnsdk_cstr_t data_key, gnsdk_gdo_handle_t data_gdo, gnsdk_uint32_t data_ord);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_add_request_option)	(gnsdk_lookup_handle_t lookup_handle, gnsdk_cstr_t request_id, gnsdk_cstr_t option_key, gnsdk_cstr_t option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_execute)				(gnsdk_lookup_handle_t lookup_handle, gnsdk_user_handle_t user_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_get_response_gdo)		(gnsdk_lookup_handle_t lookup_handle, gnsdk_cstr_t request_id, gnsdk_gdo_handle_t* p_gdo_response);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_get_response_stream)	(gnsdk_lookup_handle_t lookup_handle, gnsdk_cstr_t request_id, gnsdk_iostream_handle_t* p_response_stream);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_lookup_release)				(gnsdk_lookup_handle_t lookup_handle);

} gnsdk_lookup_interface_t;

/* Options for gnsdk_lookup_add_request_option */
#define GNSDK_LOOKUP_OPTION_LANGUAGE					"gnsdk_lookup_option_language"
#define GNSDK_LOOKUP_OPTION_AGGRESSIVE					"gnsdk_lookup_option_aggressive"
#define GNSDK_LOOKUP_OPTION_PERFECT 					"gnsdk_lookup_option_perfect"
#define GNSDK_LOOKUP_OPTION_STREAM						"gnsdk_lookup_option_stream"
#define GNSDK_LOOKUP_OPTION_IGNORE_LOW_POP				"gnsdk_lookup_option_nolowpop"
#define GNSDK_LOOKUP_OPTION_ABORT_TOO_MANY				"gnsdk_lookup_option_aborttoomany"
#define GNSDK_LOOKUP_OPTION_QUERY_RESULT_LIMIT			"gnsdk_lookup_option_queryresultlimit"
#define GNSDK_LOOKUP_OPTION_SORT_ALGORITHM				"gnsdk_lookup_option_sortalgorithm"
#define GNSDK_LOOKUP_OPTION_TEST_MODE					"gnsdk_lookup_option_test_mode"
#define GNSDK_LOOKUP_OPTION_CACHE_USAGE					"gnsdk_lookup_option_cache_usage"
#define GNSDK_LOOKUP_OPTION_PRESET						"gnsdk_lookup_option_preset"
#define GNSDK_LOOKUP_OPTION_OUTPUT						"gnsdk_lookup_option_output"
#define GNSDK_LOOKUP_OPTION_ADDITIONAL_CREDITS			"gnsdk_lookup_option_additionalcredits"
#define GNSDK_LOOKUP_OPTION_RESULT_SINGLE				"gnsdk_lookup_option_result_single"
#define GNSDK_LOOKUP_OPTION_RESULT_PREFERXID			"gnsdk_lookup_option_result_preferxid"
#define GNSDK_LOOKUP_OPTION_RESULT_PREFERCOVER			"gnsdk_lookup_option_result_prefercover"

#define GNSDK_LOOKUP_OPTION_VALUE_CACHE_DEFAULT			"gnsdk_lookup_option_value_cache_default"
#define GNSDK_LOOKUP_OPTION_VALUE_CACHE_SKIP			"gnsdk_lookup_option_value_nocache"
#define GNSDK_LOOKUP_OPTION_VALUE_CACHE_SKIP_READ		"gnsdk_lookup_option_value_cache_skip_read"
#define GNSDK_LOOKUP_OPTION_VALUE_CACHE_SKIP_WRITE		"gnsdk_lookup_option_value_cache_skip_write"
#define GNSDK_LOOKUP_OPTION_VALUE_CACHE_ONLY			"gnsdk_lookup_option_value_cache_only"

#define	GNSDK_LOOKUP_OPTION_EXACT_ONLY		        	"gnsdk_lookup_option_exact_only"
#define GNSDK_LOOKUP_OPTION_RESULT_SINGLE				"gnsdk_lookup_option_result_single"

/******************************************************************************
 * Content
 */
#define GNSDK_CONTENT_INTERFACE			"_gnsdk_content_interface"

GNSDK_DECLARE_HANDLE( gnsdk_content_handle_t );

typedef struct _gnsdk_content_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_content_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_capabilities)		(struct _gnsdk_content_interface_s* me, gnsdk_uint32_t* p_capabilities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_request_create)		(struct _gnsdk_content_interface_s* me, gnsdk_user_handle_t user_handle, gnsdk_cstr_t content_type, gnsdk_query_provider_callback_fn callback, const gnsdk_void_t* callback_data, gnsdk_content_handle_t* p_content_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_set_request_data)	(gnsdk_content_handle_t content_handle, gnsdk_cstr_t content_data, gnsdk_cstr_t data_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_set_option)			(gnsdk_content_handle_t content_handle, gnsdk_cstr_t option_name, gnsdk_cstr_t option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_data_fetch)			(gnsdk_content_handle_t content_handle, gnsdk_bool_t b_decoded, gnsdk_byte_t** pp_buffer, gnsdk_size_t* p_buffer_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_data_delete)			(gnsdk_content_handle_t content_handle, gnsdk_byte_t* p_buffer);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_content_request_release)		(gnsdk_content_handle_t content_handle);

} gnsdk_content_interface_t;

#define GNSDK_CONTENT_TYPE_IMAGE_COVER				"gnsdk_content_image_cover"
#define GNSDK_CONTENT_TYPE_IMAGE_VIDEO				"gnsdk_content_image_video"
#define GNSDK_CONTENT_TYPE_IMAGE_ARTIST				"gnsdk_content_image_artist"
#define GNSDK_CONTENT_TYPE_TEXT_REVIEW				"gnsdk_content_text_review"
#define GNSDK_CONTENT_TYPE_TEXT_BIOGRAPHY			"gnsdk_content_text_bio"
#define GNSDK_CONTENT_TYPE_TEXT_ARTIST_NEWS			"gnsdk_content_text_artnews"
#define GNSDK_CONTENT_TYPE_LYRICS					"gnsdk_content_text_lyrics"
#define GNSDK_CONTENT_TYPE_TEXT_COMMENTS_LISTENER	"gnsdk_content_text_liscomm"
#define GNSDK_CONTENT_TYPE_TEXT_COMMENTS_RELEASE	"gnsdk_content_text_relcomm"
#define GNSDK_CONTENT_TYPE_TEXT_NEWS				"gnsdk_content_text_news"
#define GNSDK_CONTENT_TYPE_DSP_12TONE				"gnsdk_content_dsp_12t"

#define GNSDK_CONTENT_DATA_ID						"gnsdk_content_data_id"
#define GNSDK_CONTENT_DATA_ID_TAG					"gnsdk_content_data_idtag"
#define GNSDK_CONTENT_DATA_ORIGIN					"gnsdk_content_data_origin"
#define GNSDK_CONTENT_DATA_SIZE						"gnsdk_content_data_size"
#define GNSDK_CONTENT_DATA_TYPE						"gnsdk_content_data_type" /* like jpeg, xml, etc */
#define GNSDK_CONTENT_DATA_TUI						"gnsdk_content_data_tui"
#define GNSDK_CONTENT_DATA_TUI_TAG					"gnsdk_content_data_tuitag"

#define GNSDK_CONTENT_OPTION_CACHE_ONLY				"gnsdk_content_option_cache_only"
#define GNSDK_CONTENT_OPTION_CACHE_SKIP				"gnsdk_content_option_cache_skip"
#define GNSDK_CONTENT_OPTION_COVER_AS_GENRE			"gnsdk_content_option_cover_genre"	/* album cover otherwise */

#define GNSDK_CONTENT_DATA_SIZE_VALUE_75			"gsndk_content_sz_75"
#define GNSDK_CONTENT_DATA_SIZE_VALUE_170			"gsndk_content_sz_170"
#define GNSDK_CONTENT_DATA_SIZE_VALUE_300			"gsndk_content_sz_300"
#define GNSDK_CONTENT_DATA_SIZE_VALUE_450			"gsndk_content_sz_450"
#define GNSDK_CONTENT_DATA_SIZE_VALUE_720			"gsndk_content_sz_720"
#define GNSDK_CONTENT_DATA_SIZE_VALUE_1080			"gsndk_content_sz_1080"

#define GNSDK_CONTENT_DATA_SIZE_VALUE_110			"gsndk_content_sz_110"
#define GNSDK_CONTENT_DATA_SIZE_VALUE_220			"gsndk_content_sz_220"

#define GNSDK_CONTENT_DATA_TYPE_VALUE_JPEG			"gsndk_content_jpeg"
#define GNSDK_CONTENT_DATA_TYPE_VALUE_PNG			"gsndk_content_png"
#define GNSDK_CONTENT_DATA_TYPE_VALUE_TEXT			"gsndk_content_text"
#define GNSDK_CONTENT_DATA_TYPE_VALUE_XML			"gsndk_content_xml"

#define GNSDK_CONTENT_DATA_ORIGIN_VALUE_FRONT		"gsndk_content_front"

/******************************************************************************
 * Storage
 */
#define GNSDK_STORAGE_INTERFACE						"_gnsdk_storage_interface"

GNSDK_DECLARE_HANDLE( gnsdk_storage_handle_t );
GNSDK_DECLARE_HANDLE( gnsdk_storage_record_handle_t );
GNSDK_DECLARE_HANDLE( gnsdk_storage_iterator_handle_t );

#define GNSDK_STORAGE_OPTION_SCHEME_FILEIO			"gnsdk_storage_option_fileioscheme"
#define GNSDK_STORAGE_FILEIO_SPEED						"gnsdk_storage_speedfileio"		/* value for GNSDK_STORAGE_OPTION_SCHEME_FILEIO */
#define GNSDK_STORAGE_FILEIO_INTEGRITY					"gnsdk_storage_integfileio"		/* value for GNSDK_STORAGE_OPTION_SCHEME_FILEIO */

#define GNSDK_STORAGE_OPTION_SCHEME_MEMORY			"gnsdk_storage_option_memscheme"
#define GNSDK_STORAGE_MEMORY_EMBEDDED					"gnsdk_storage_embeddedmem"		/* value for GNSDK_STORAGE_OPTION_SCHEME_MEMORY */
#define GNSDK_STORAGE_MEMORY_SERVER						"gnsdk_storage_servermem"		/* value for GNSDK_STORAGE_OPTION_SCHEME_MEMORY */


typedef struct _gnsdk_storage_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_storage_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_capabilities)		(struct _gnsdk_storage_interface_s* me, gnsdk_uint32_t* p_capabilities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_open)				(struct _gnsdk_storage_interface_s* me, gnsdk_cstr_t group_name, gnsdk_cstr_t storage_name, gnsdk_cstr_t location, gnsdk_storage_handle_t* p_storage_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_create)				(struct _gnsdk_storage_interface_s* me, gnsdk_cstr_t group_name, gnsdk_cstr_t storage_name, gnsdk_cstr_t location, gnsdk_storage_handle_t* p_storage_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_read)				(gnsdk_storage_handle_t storage_handle, gnsdk_storage_record_handle_t query_record_handle, gnsdk_storage_iterator_handle_t* p_iterator_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_update)				(gnsdk_storage_handle_t storage_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_get_size)			(gnsdk_storage_handle_t storage_handle, gnsdk_size_t* p_storage_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_empty)				(gnsdk_storage_handle_t storage_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_version_get)			(gnsdk_storage_handle_t storage_handle, gnsdk_cstr_t* p_version);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_version_set)			(gnsdk_storage_handle_t storage_handle, gnsdk_cstr_t version);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_delete)				(gnsdk_storage_handle_t storage_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_field_count)			(gnsdk_storage_handle_t storage_handle, gnsdk_uint32_t* p_field_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_field_get)			(gnsdk_storage_handle_t storage_handle, gnsdk_uint32_t field_index, gnsdk_cstr_t* p_field_name, gnsdk_storage_field_type_t* p_field_type, gnsdk_uint32_t* p_field_flags);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_field_set)			(gnsdk_storage_handle_t storage_handle, gnsdk_cstr_t field_name, gnsdk_storage_field_type_t field_type, gnsdk_uint32_t field_flags);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_option_get)			(gnsdk_storage_handle_t storage_handle, gnsdk_cstr_t option_name, gnsdk_cstr_t* p_option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_option_set)			(gnsdk_storage_handle_t storage_handle, gnsdk_cstr_t option_name, gnsdk_cstr_t option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_release)				(gnsdk_storage_handle_t storage_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_validate)			(struct _gnsdk_storage_interface_s*	me, gnsdk_cstr_t group_name, gnsdk_cstr_t location, gnsdk_bool_t* p_is_valid);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_compact)				(struct _gnsdk_storage_interface_s*	me, gnsdk_cstr_t group_name, gnsdk_cstr_t location);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_create)		(gnsdk_storage_handle_t storage_handle, gnsdk_storage_record_handle_t* p_record_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_insert)		(gnsdk_storage_record_handle_t record_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_update)		(gnsdk_storage_record_handle_t record_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_delete)		(gnsdk_storage_record_handle_t record_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_set_binary)	(gnsdk_storage_record_handle_t record_handle, gnsdk_cstr_t field_name, const gnsdk_void_t* data, gnsdk_size_t data_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_set_string)	(gnsdk_storage_record_handle_t record_handle, gnsdk_cstr_t field_name, gnsdk_cstr_t string);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_set_uint)		(gnsdk_storage_record_handle_t record_handle, gnsdk_cstr_t field_name, gnsdk_uint32_t value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_get_binary)	(gnsdk_storage_record_handle_t record_handle, gnsdk_cstr_t field_name, gnsdk_void_t** p_field_data, gnsdk_size_t* p_data_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_get_string)	(gnsdk_storage_record_handle_t record_handle, gnsdk_cstr_t field_name, gnsdk_cstr_t* p_string);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_get_uint)		(gnsdk_storage_record_handle_t record_handle, gnsdk_cstr_t field_name, gnsdk_uint32_t* p_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_record_release)		(gnsdk_storage_record_handle_t record_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_iterator_next)		(gnsdk_storage_iterator_handle_t iterator_handle, gnsdk_storage_record_handle_t* p_record_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_storage_iterator_release)	(gnsdk_storage_iterator_handle_t iterator_handle);

} gnsdk_storage_interface_t;


#define SDKMGR_DAY_SECONDS					(60*60*24)
#define SDKMGR_HOUR_SECONDS					(60*60)


/******************************************************************************
 * License
 */
#define GNSDK_LICENSE_INTERFACE			"_gnsdk_license_interface"

typedef struct _gnsdk_license_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_license_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_license_check_permission)	(gnsdk_user_handle_t user_handle, gnsdk_cstr_t feature, gnsdk_error_t* p_permission_test);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_license_bypass)				(gnsdk_cstr_t clientid, gnsdk_bool_t b_allow_bypass);

} gnsdk_license_interface_t;



/******************************************************************************
 * Error Info
 */
#define GNSDK_ERRORINFO_INTERFACE		"_gnsdk_errorinfo_interface"

typedef struct _gnsdk_errorinfo_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_errorinfo_interface_s* me);

	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_errorinfo_set)				(gnsdk_error_t error_code, gnsdk_error_t source_error_code, gnsdk_cstr_t error_api, gnsdk_cstr_t err_msg);
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_errorinfo_setf)				(gnsdk_error_t error_code, gnsdk_error_t source_error_code, gnsdk_cstr_t error_api, gnsdk_cstr_t err_msg_fmt, ...);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_errorinfo_get)				(gnsdk_error_t* p_error_code, gnsdk_error_t* p_source_error_code, gnsdk_cstr_t* p_error_desc);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_errorinfo_error_get_desc)	(gnsdk_error_t error_code, gnsdk_cstr_t* p_error_desc);

} gnsdk_errorinfo_interface_t;



/******************************************************************************
 * List Manager
 */
#define GNSDK_LISTMANAGER_INTERFACE         "_gnsdk_listmanager_interface"

typedef struct _gnsdk_lists_interface_s
{
	gnsdk_void_t    (GNSDK_CALLBACK_API *gnsdk_interface_release)               (struct _gnsdk_lists_interface_s* me);

	/* lists */
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_retrieve)                   (gnsdk_cstr_t list_type, gnsdk_cstr_t list_language, gnsdk_cstr_t list_region, gnsdk_cstr_t list_descriptor, gnsdk_user_handle_t user_handle, gnsdk_manager_query_callback_fn callback, const gnsdk_void_t* callback_data, gnsdk_list_handle_t* p_list_handle);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_release)                    (gnsdk_list_handle_t list_handle);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_update)                     (gnsdk_list_handle_t list_handle, gnsdk_user_handle_t user_handle, gnsdk_manager_query_callback_fn callback, const gnsdk_void_t* callback_data, gnsdk_list_handle_t* p_updated_list_handle);

	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_type)                   (gnsdk_list_handle_t list_handle, gnsdk_cstr_t* p_type);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_language)               (gnsdk_list_handle_t list_handle, gnsdk_cstr_t* p_language);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_region)                 (gnsdk_list_handle_t list_handle, gnsdk_cstr_t* p_region);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_descriptor)             (gnsdk_list_handle_t list_handle, gnsdk_cstr_t* p_description);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_revision)               (gnsdk_list_handle_t list_handle, gnsdk_cstr_t* p_revision);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_level_count)            (gnsdk_list_handle_t list_handle, gnsdk_uint32_t* p_count);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_element_count)          (gnsdk_list_handle_t list_handle, gnsdk_uint32_t level, gnsdk_uint32_t* p_count);

	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_render_to_xml)              (gnsdk_list_handle_t list_handle, gnsdk_uint32_t levels, gnsdk_uint32_t flags, gnsdk_str_t* p_xml);

	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_element_by_id)          (gnsdk_list_handle_t list_handle, gnsdk_uint32_t item_id, gnsdk_uint32_t list_level, gnsdk_list_element_handle_t* p_element);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_element_by_range)       (gnsdk_list_handle_t list_handle, gnsdk_uint32_t value, gnsdk_uint32_t list_level, gnsdk_list_element_handle_t* p_element);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_element_by_string)      (gnsdk_list_handle_t list_handle, gnsdk_cstr_t value, gnsdk_uint32_t list_level, gnsdk_list_element_handle_t* p_element);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_get_element)                (gnsdk_list_handle_t list_handle, gnsdk_uint32_t index, gnsdk_uint32_t list_level, gnsdk_list_element_handle_t* p_element);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_element_release)            (gnsdk_list_element_handle_t element);

	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_list_type)           (gnsdk_list_element_handle_t list_element, gnsdk_cstr_t* p_type);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_id)                  (gnsdk_list_element_handle_t list_element, gnsdk_uint32_t* p_id);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_master_code)         (gnsdk_list_element_handle_t list_element, gnsdk_uint32_t* p_mc);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_display_string)      (gnsdk_list_element_handle_t list_element, gnsdk_cstr_t* p_display_string);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_level)               (gnsdk_list_element_handle_t list_element, gnsdk_uint32_t* p_level);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_range)               (gnsdk_list_element_handle_t list_element, gnsdk_uint32_t* p_low, gnsdk_uint32_t* p_high);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_value)               (gnsdk_list_element_handle_t list_element, gnsdk_cstr_t value_name, gnsdk_cstr_t* psz_value);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_child_count)         (gnsdk_list_element_handle_t list_element, gnsdk_uint32_t* p_count);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_child)               (gnsdk_list_element_handle_t list_element, gnsdk_uint32_t ordinal, gnsdk_list_element_handle_t* p_child);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_parent)              (gnsdk_list_element_handle_t list_element, gnsdk_list_element_handle_t* p_parent);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_element_get_type)      			(gnsdk_list_element_handle_t list_element, gnsdk_cstr_t* p_display_string);
	gnsdk_error_t 	(GNSDK_CALLBACK_API	*gnsdk_element_addref)					(gnsdk_list_element_handle_t list_element );

	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_map_lang_id_to_iso)         (gnsdk_cstr_t lang_id, gnsdk_cstr_t* p_lang_iso);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_list_map_lang_id_from_iso)       (gnsdk_cstr_t lang_iso, gnsdk_cstr_t* p_lang_id);

	/* correlates */
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_correlates_retrieve)             (gnsdk_cstr_t correlates_type, gnsdk_user_handle_t user_handle, gnsdk_manager_query_callback_fn callback, const gnsdk_void_t* callback_user_data, gnsdk_list_correlates_handle_t* p_correlates_handle);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_correlates_release)              (gnsdk_list_correlates_handle_t correlates_handle);

	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_correlates_data_revision)        (gnsdk_list_correlates_handle_t correlates_handle, gnsdk_uint32_t* p_revision);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_correlates_render_set)           (gnsdk_list_correlates_handle_t correlates_handle, gnsdk_uint32_t master_code, gnsdk_str_t* p_correlate_xml);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_correlates_get_correlate_set)    (gnsdk_list_correlates_handle_t correlates_handle, gnsdk_uint32_t master_code, gnsdk_list_correlate_set_handle_t* p_correlate_set_handle);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_correlate_set_get_weight)        (gnsdk_list_correlate_set_handle_t correlate_set_handle, gnsdk_uint32_t master_code, gnsdk_int32_t* p_weight);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_correlate_set_release)           (gnsdk_list_correlate_set_handle_t correlate_set_handle);

	/* locales */
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_locale_get_default)              (gnsdk_cstr_t locale_group, gnsdk_locale_handle_t* p_locale_handle);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_locale_get_info)                 (gnsdk_locale_handle_t locale_handle, gnsdk_cstr_t* p_group, gnsdk_cstr_t* p_language, gnsdk_cstr_t* p_region, gnsdk_cstr_t* p_descriptor, gnsdk_cstr_t* p_revision);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_locale_addref)                   (gnsdk_locale_handle_t locale_handle);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_locale_release)                  (gnsdk_locale_handle_t locale_handle);

} gnsdk_lists_interface_t;



/******************************************************************************
 * Serialization
 */
#define GNSDK_SERIALIZATION_INTERFACE			"_gnsdk_serialization_interface"

typedef struct _gnsdk_serialization_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)		(struct _gnsdk_serialization_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_serialize_data)			(const gnsdk_byte_t* p_data, gnsdk_size_t data_size, gnsdk_str_t* p_serialized);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_deserialize_data)		(gnsdk_cstr_t serialized, gnsdk_byte_t** pp_data, gnsdk_size_t* p_data_size);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_deserialize_data_free)	(gnsdk_byte_t* p_data);

} gnsdk_serialization_interface_t;


/******************************************************************************
 * DSP/Fingerprinting
 */
#define GNSDK_DSP_INTERFACE			"_gnsdk_dsp_interface"

typedef enum
{
	gnsdk_dsp_algorithm_id_unknown = 0,

	gnsdk_dsp_algorithm_id_cmx,			/* audio: 15 seconds, medium quality (cantametrix) */
	gnsdk_dsp_algorithm_id_cmx_submit,	/* audio: reference file identification fingerprint */
	gnsdk_dsp_algorithm_id_fapi_3svlq,  /* audio: 3 seconds, very low quality (mobile audio) */
	gnsdk_dsp_algorithm_id_fapi_3smq,   /* audio: 3 seconds, medium quality (media monitoring) */
	gnsdk_dsp_algorithm_id_fapi_6smq,   /* audio: 6 seconds, medium quality (media monitoring) */
	gnsdk_dsp_algorithm_id_fapi_submit, /* audio: philips reference fingerprint */
	gnsdk_dsp_algorithm_id_fhg_5x3,     /* video: 5 fps, 3 seconds (media monitoring) */
	gnsdk_dsp_algorithm_id_s12t,		/* audio features: s12t algorithm */
	gnsdk_dsp_algorithm_id_fex,         /* audio features: fex algorithm */
	gnsdk_dsp_algorithm_id_afx3,        /* audio features: afx3 algorithm */
	gnsdk_dsp_algorithm_id_chroma,      /* audio features: chroma algorithm */
	gnsdk_dsp_algorithm_id_micro_fapi_query,  /* audio:  */
	gnsdk_dsp_algorithm_id_nano_fapi_query,   /* audio:  */
#ifdef GCSL_FINGRERPRINT_ENABLE_MICRO_NANO_REFERENCE
	gnsdk_dsp_algorithm_id_micro_fapi_submit, /* audio:  */
	gnsdk_dsp_algorithm_id_nano_fapi_submit,  /* audio:  */
#endif
	gnsdk_dsp_algorithm_id_fake = 99
}
gnsdk_dsp_algorithm_id_t;

typedef enum
{
	gnsdk_dsp_algorithm_type_unknown	= 0,

	gnsdk_dsp_algorithm_type_query		= 1,
	gnsdk_dsp_algorithm_type_submit		= 2
}
gnsdk_dsp_algorithm_type_t;

typedef enum
{
	gnsdk_dsp_audio_format_unknown = 0,

	gnsdk_dsp_audio_format_pcm8,
	gnsdk_dsp_audio_format_pcm16,
	gnsdk_dsp_audio_format_pcm32_float,
	gnsdk_dsp_audio_format_ALaw,
	gnsdk_dsp_audio_format_uLaw
}
gnsdk_dsp_audio_format_t;

typedef enum
{
	gnsdk_dsp_pixel_format_unknown = 0,

	gnsdk_dsp_pixel_format_rgb24,
	gnsdk_dsp_pixel_format_bgr24        /* Windows "RGB24" is really BGR */
}
gnsdk_dsp_pixel_format_t;

typedef enum
{
	gnsdk_dsp_frame_origin_unknown = 0,

	gnsdk_dsp_frame_origin_lower_left,  /* Windows bitmaps are this way */
	gnsdk_dsp_frame_origin_upper_left
}
gnsdk_dsp_frame_origin_t;

#define GNSDK_DSP_INTF_FEATURE_QUALITY_DEFAULT		0x0
#define GNSDK_DSP_INTF_FEATURE_QUALITY_SHORT		0x1
#define GNSDK_DSP_INTF_FEATURE_QUALITY_SILENT		0x2

typedef gnsdk_uint32_t	gnsdk_dsp_intf_feature_qualities_t;

GNSDK_DECLARE_HANDLE( gnsdk_dsp_analyzer_handle_t );
GNSDK_DECLARE_HANDLE( gnsdk_dsp_data_handle_t );

typedef gnsdk_void_t (GNSDK_CALLBACK_API *gnsdk_dsp_callback_fn)(
	const gnsdk_void_t*			userdata,
	gnsdk_dsp_analyzer_handle_t	analyzer_handle,
	gnsdk_dsp_data_handle_t		data_handle
	);

#define GNSDK_DSP_INFO_ALG_NAME					"gnsdk_dsp_info_alg_name"
#define GNSDK_DSP_INFO_ALG_VERSION				"gnsdk_dsp_info_alg_version"
#define GNSDK_DSP_INFO_ALG_BUILD				"gnsdk_dsp_info_alg_build"

#define GNSDK_DSP_INFO_MIN_BLOCKS_REQUIRED		"gnsdk_dsp_info_minblockreq"
#define GNSDK_DSP_INFO_MAX_BLOCKS_REQUIRED		"gnsdk_dsp_info_maxblockreq"


typedef struct _gnsdk_dsp_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_dsp_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_algorithms_count)			(gnsdk_uint32_t* p_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_algorithms_enum)				(gnsdk_uint32_t index, gnsdk_dsp_algorithm_id_t* p_alg_id, gnsdk_dsp_algorithm_type_t* p_alg_type, gnsdk_cstr_t* p_alg_name, gnsdk_cstr_t* p_alg_version, gnsdk_cstr_t* p_alg_alias);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_create_audio_analyzer)		(gnsdk_dsp_algorithm_id_t algorithm_id, gnsdk_uint32_t sample_rate, gnsdk_dsp_audio_format_t sample_format, gnsdk_uint32_t channels, gnsdk_cstr_t config_paramns, gnsdk_dsp_callback_fn callback, const gnsdk_void_t* callback_userdata, gnsdk_dsp_analyzer_handle_t* p_analyzer_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_create_video_analyzer)		(gnsdk_dsp_algorithm_id_t algorithm_id, gnsdk_dsp_pixel_format_t pixel_format, gnsdk_dsp_frame_origin_t frame_origin, gnsdk_cstr_t config_params, gnsdk_dsp_callback_fn callback, const gnsdk_void_t* callback_userdata, gnsdk_dsp_analyzer_handle_t* p_analyzer_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_analyzer_add_audio_buffer)	(gnsdk_dsp_analyzer_handle_t analyzer_handle, const gnsdk_byte_t* audio_data, gnsdk_size_t audio_data_bytes, gnsdk_time_us_t timestamp, gnsdk_bool_t* p_complete);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_analyzer_add_video_frame)	(gnsdk_dsp_analyzer_handle_t analyzer_handle, const gnsdk_byte_t* frame_data, gnsdk_uint32_t frame_width, gnsdk_uint32_t frame_height, gnsdk_time_us_t timestamp, gnsdk_bool_t* p_complete);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_analyzer_flush)				(gnsdk_dsp_analyzer_handle_t analyzer_handle, gnsdk_dsp_intf_feature_qualities_t* p_qualities);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_analyzer_get_info)			(gnsdk_dsp_analyzer_handle_t analyzer_handle, gnsdk_cstr_t info_key, gnsdk_cstr_t* info_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_analyzer_delete)				(gnsdk_dsp_analyzer_handle_t analyzer_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_data_get_data)				(gnsdk_dsp_data_handle_t data_handle, const gnsdk_void_t** data, gnsdk_size_t* length, gnsdk_time_us_t* duration, gnsdk_time_us_t* offset, gnsdk_bool_t* is_discontinuity, gnsdk_uint32_t* block_id);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_data_get_info)				(gnsdk_dsp_data_handle_t data_handle, gnsdk_cstr_t info_key, gnsdk_cstr_t* info_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_data_format)					(gnsdk_dsp_data_handle_t data_handle, gnsdk_cstr_t format, gnsdk_str_t* result);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_data_delete)					(gnsdk_dsp_data_handle_t data_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_create_query_data)			(gnsdk_dsp_analyzer_handle_t analyzer_handle, gnsdk_dsp_data_handle_t* data_handles, gnsdk_size_t data_handle_count, gnsdk_str_t* result);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_free_query_data)				(gnsdk_str_t result);

} gnsdk_dsp_interface_t;




/******************************************************************************
 * User handles
 */
#define GNSDK_USERINFO_INTERFACE					"_gnsdk_userinfo_interface"

typedef struct _gnsdk_userinfo_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_userinfo_interface_s* me);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_user_clientinfo)				(gnsdk_user_handle_t	user_handle, gnsdk_cstr_t* p_client_id, gnsdk_cstr_t* p_client_tag, gnsdk_cstr_t* p_client_ver);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_user_addref)					(gnsdk_user_handle_t	user_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_user_release)				(gnsdk_user_handle_t	user_handle);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_user_option_get)				(gnsdk_user_handle_t	user_handle, gnsdk_cstr_t option_name, gnsdk_cstr_t* p_option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_user_option_enum)			(gnsdk_user_handle_t	user_handle, gnsdk_uint32_t index, gnsdk_cstr_t* p_option_name, gnsdk_cstr_t* p_option_value);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_user_data_set)				(gnsdk_user_handle_t	user_handle, gnsdk_cstr_t data_name, gnsdk_cstr_t data_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_user_data_get)				(gnsdk_user_handle_t	user_handle, gnsdk_cstr_t data_name, gnsdk_cstr_t* p_data_value);

} gnsdk_userinfo_interface_t;


/******************************************************************************
** External Database Consumer/Installer
*/

#define		GNSDK_EDB_CONFIG_KEY_INDEX_TOCS					    "index_tocs"				    /* boolean */
#define		GNSDK_EDB_CONFIG_KEY_INDEX_TEXT					    "index_text"				    /* boolean */

#define		GNSDK_EDB_CONFIG_KEY_TEXT_MAX_ALBUMS_RANK			"text_max_albums_rank"			/* maximum rank value for albums to be indexed as text. */
#define		GNSDK_EDB_CONFIG_KEY_TEXT_MAX_CONTRIBS_RANK			"text_max_contribs_rank"		/* maximum rank value for contribs to be indexed as text. */
#define		GNSDK_EDB_CONFIG_KEY_TEXT_EXCL_TRACKS				"text_exclude_tracks"			/* boolean */

#define		GNSDK_EDB_CONFIG_KEY_MAX_ALBUMS_RANK				"max_albums_rank"			    /* rank value for the last album to be installed. */
#define		GNSDK_EDB_CONFIG_KEY_MAX_EXTRA_CONTRIBS_RANK		"max_extra_contribs_rank"		/* rank value for the last 'extra' contrib to be installed */

#define		GNSDK_EDB_CONFIG_KEY_MAX_ALBUM_BYTES			    "max_albums_bytes"			    /* in bytes */
#define		GNSDK_EDB_CONFIG_KEY_MAX_EXTRA_CONTRIB_BYTES	    "max_extra_contribs_bytes"	    /* in bytes */
#define		GNSDK_EDB_CONFIG_KEY_MAX_IMAGE_BYTES			    "max_images_bytes"			    /* in bytes */

#define		GNSDK_EDB_CONFIG_KEY_MIN_CMI_ALBUMS				    "min_cmi_albums"			    /* count */
#define		GNSDK_EDB_CONFIG_KEY_MIN_COMPOSERS				    "min_composers"			        /* count */


#define		GNSDK_EDB_CONFIG_KEY_INCL_IMAGE_SIZE			    "images_size"				    /* GN image size descriptor string (like "170x170") */
#define		GNSDK_EDB_CONFIG_KEY_INCL_COVER_ART				    "images_cover_art"			    /* boolean */
#define		GNSDK_EDB_CONFIG_KEY_INCL_CONTRIB_IMAGES		    "images_contrib"			    /* boolean */
#define		GNSDK_EDB_CONFIG_KEY_INCL_GENRE_IMAGES			    "images_genre"				    /* boolean */

#define		GNSDK_EDB_CONFIG_KEY_INCL_TEMPO_PRIMARY				"data_tempo_primary"			/* boolean */
#define		GNSDK_EDB_CONFIG_KEY_INCL_TEMPO_VECTOR				"data_tempo_vector"				/* boolean */

#define		GNSDK_EDB_CONFIG_KEY_INCL_MOOD						"data_mood"						/* boolean */
#define		GNSDK_EDB_CONFIG_KEY_MOOD_CUTOFF_LENGTH				"data_mood_cutoff_length"		/* integer */
#define		GNSDK_EDB_CONFIG_KEY_MOOD_CUTOFF_WEIGHT				"data_mood_cutoff_weight"		/* integer */

#define		GNSDK_EDB_CONFIG_KEY_INCL_DATA_AIM_YOMI			    "data_aim_yomi"				    /* boolean */
#define		GNSDK_EDB_CONFIG_KEY_INCL_DATA_AIM_BETSUMEI		    "data_aim_betsumei"			    /* boolean - 'composite' betsumei string. used for phonetics */
#define		GNSDK_EDB_CONFIG_KEY_INCL_CLASSICAL_DATA		    "data_classical"			    /* boolean */
#define		GNSDK_EDB_CONFIG_KEY_EXCL_TRACK_DATA			    "data_exclude_tracks"			/* boolean */
#define		GNSDK_EDB_CONFIG_KEY_INCL_TRACK_TUI				    "data_include_track_tuis"		/* boolean */
#define		GNSDK_EDB_CONFIG_KEY_INCL_ALTERNATES			    "data_alternate_names_titles"	/* boolean - i.e. anything that isn't 'official' */

#define     GNSDK_EDB_CONFIG_KEY_INCL_LISTS_PLAYLIST            "lists_playlist"                /* boolean */
#define     GNSDK_EDB_CONFIG_KEY_INCL_LISTS_GENRES_DESC         "lists_genre"                   /* simplified or detailed */
#define     GNSDK_EDB_CONFIG_KEY_INCL_LISTS_GENRES_MAX_LEVEL    "lists_genre_max_level"         /* count - i.e. maximum genre list level included in lists store */
#define     GNSDK_EDB_CONFIG_KEY_INCL_LISTS_FUZZY_MATCH    		"lists_fuzzy_match"         	/* boolean */

#define     GNSDK_EDB_CONFIG_KEY_SOURCE_DB_ID					"source_db_id"					/* string */
#define     GNSDK_EDB_CONFIG_KEY_SOURCE_APP_VERSION				"source_app_version"			/* string */

#define		GNSDK_EDB_CONFIG_VALUE_SEPARATOR					"|"								/* for keys that support multiple values (like image size) */

typedef enum
{
	gnsdk_edb_image_format_unknown = 0,
	gnsdk_edb_image_format_jpeg

} gnsdk_edb_image_format_t;

typedef enum
{
	gnsdk_edb_image_type_unknown = 0,
	gnsdk_edb_image_type_cover,
	gnsdk_edb_image_type_contributor,
	gnsdk_edb_image_type_genre

} gnsdk_edb_image_type_t;

#define GNSDK_EDB_CONSUMER_INTERFACE			"_gnsdk_edb_consumer_interface"

typedef struct _gnsdk_edb_consumer_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_edb_consumer_interface_s* me);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_install_begin)				(gnsdk_gdo_handle_t conf_gdo);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_install_end)                 (void);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_edb_begin)                   (void); /* jmctodo PATDF todo: come up with a better function for this, currently used for correlates */
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_edb_end)                     (void);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_consume_gdo)					(gnsdk_gdo_handle_t gdo_handle, gnsdk_bool_t* p_done);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_consume_image)				(gnsdk_cstr_t cds_id, gnsdk_byte_t* buffer, gnsdk_size_t size, gnsdk_edb_image_type_t type, gnsdk_cstr_t gn_dimension_identifier, gnsdk_edb_image_format_t format, gnsdk_bool_t* p_done);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_get_store_size)				(gnsdk_size_t* size); /* this should return the number of bytes for the consumer's LDS */

} gnsdk_edb_consumer_interface_t;


#define GNSDK_EDB_INSTALLER_INTERFACE			"_gnsdk_edb_installer_interface"

typedef struct _gnsdk_edb_installer_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)			(struct _gnsdk_edb_installer_interface_s* me);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_install_begin)				(gnsdk_gdo_handle_t conf_gdo);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_install_end)					(void);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_edb_begin)                   (void);
	gnsdk_error_t   (GNSDK_CALLBACK_API *gnsdk_edb_end)                     (void);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_provide_gdo)					(gnsdk_gdo_handle_t gdo_handle); /* jmctodo consider p_done, so we can bail if everyone else does */
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_provide_image)				(gnsdk_cstr_t cds_id, gnsdk_byte_t* buffer, gnsdk_size_t size, gnsdk_edb_image_type_t type, gnsdk_cstr_t gn_dimension_identifier, gnsdk_edb_image_format_t format); /* jmctodo consider p_done, so we can bail if everyone else does */
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_get_store_size)				(gnsdk_size_t* size); /* this should return the total numbr of bytes for the LDS set */

} gnsdk_edb_installer_interface_t;


/******************************************************************************
* Moodgrid DataSource Interface
*/


#define GNSDK_MOODGRID_DATASOURCE_INTERFACE	"_gnsdk_moodgrid_datasource_interface"


GNSDK_DECLARE_HANDLE(gnsdk_moodgrid_data_transaction_handle_t);

typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_callback_fn)(
	const gnsdk_void_t* callback_user_data,
	const gnsdk_void_t* p_status_data,
	gnsdk_bool_t* p_abort
	) ;


typedef struct _gnsdk_moodgrid_datasource_interface_s
{
	gnsdk_void_t	(GNSDK_CALLBACK_API *gnsdk_interface_release)								(struct _gnsdk_moodgrid_datasource_interface_s* me);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_capabilities)				(struct _gnsdk_moodgrid_datasource_interface_s* me, gnsdk_uint32_t* p_capabilities);

	/* Provider  options and Gdo's*/
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_is_valid) 					(struct _gnsdk_moodgrid_datasource_interface_s* me, gnsdk_bool_t* p_is_valid);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_gdo_get)						(struct _gnsdk_moodgrid_datasource_interface_s* me, gnsdk_cstr_t ident, gnsdk_gdo_handle_t* p_gdo);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_data_get)					(struct _gnsdk_moodgrid_datasource_interface_s* me, gnsdk_cstr_t key, gnsdk_cstr_t* p_value);

	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_option_get)					(struct _gnsdk_moodgrid_datasource_interface_s* me, gnsdk_cstr_t option_name, gnsdk_cstr_t* p_option_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_option_set)					(struct _gnsdk_moodgrid_datasource_interface_s* me, gnsdk_cstr_t option_name, gnsdk_cstr_t option_value);

	/* Transaction management  */
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_create)			(struct _gnsdk_moodgrid_datasource_interface_s* me , gnsdk_moodgrid_data_transaction_handle_t* p_transaction_handle, gnsdk_user_handle_t user_handle, gnsdk_moodgrid_datasource_callback_fn callback, gnsdk_void_t* callback_userdata);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_filter_create)	(gnsdk_moodgrid_data_transaction_handle_t transaction_handle, gnsdk_cstr_t list_type,gnsdk_cstr_t list_value, gnsdk_cstr_t condition_type,gnsdk_uint32_t*  p_index );
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_find)			(gnsdk_moodgrid_data_transaction_handle_t transaction_handle);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_find_estimate)	(gnsdk_moodgrid_data_transaction_handle_t transaction_handle, gnsdk_uint32_t* p_estimate);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_result_count)	(gnsdk_moodgrid_data_transaction_handle_t transaction_handle, gnsdk_uint32_t*  p_count);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_result_enum)		(gnsdk_moodgrid_data_transaction_handle_t transaction_handle, gnsdk_uint32_t index, gnsdk_cstr_t* p_ident, gnsdk_cstr_t* p_group);
	gnsdk_error_t	(GNSDK_CALLBACK_API *gnsdk_moodgrid_datasource_transaction_release)			(gnsdk_moodgrid_data_transaction_handle_t transaction_handle);

} gnsdk_moodgrid_datasource_interface_t;


#ifdef __cplusplus
}
#endif

#endif /* _SDKMGR_INTERFACES_H_ */

