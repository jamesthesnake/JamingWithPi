/*
 * Copyright (c) 2012 Gracenote
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_lists.h - Gracenote Lists & Correlates Functionality
 *
 *	Provides Lists processing and access functionality. The invoker is
 *	responsible for providing raw lists data but this module parses the
 *	raw data storing the list internally where appropriate and provides
 *	a convenient api for accessing the list.
 *
 *	The invoker can:
 *	- load a list by type, region, language and descriptor
 *	- load a list from a raw list data the invoker possesses
 *	    - the raw list data must be in a suitable format being GCSP XML
 *	      schema or any format rendered by gcsl_lists
 *	- update a list (invoker responsible for providing updated list revision
 *	  if exists)
 *	- render a list to various re-loadable formats
 *	    - xml
 *	    - storage format suitable for lazy loading
 *	- render a list to various readable xml formats (not re-loadable)
 *	- access a loaded list
 *	- assemble a list from other list data formats
 *
 *	Loading a List:
 *	Use gcsl_lists_load or gcsl_lists_load_direct. The invoker must provide
 *	callback functions that provide the list raw data. The callback functions
 *	a defined by gcsl_lists_load_intf_t.
 *	gcsl_lists_load loads a list based upon the supplied type, region, language
 *	and descriptor.
 *	gcsl_lists_load_direct loads a list from raw data in possession of the invoker,
 *	for example a buffer containing data previously created by
 *	gcsl_lists_render_to_xml. It is also useful for loading and updating lists
 *	rendered to storage. The invoker can load lists based on the existence in local
 *	storage without needing the list name. Once loaded the list can then be updated.
 *
 *	Updating a List:
 *	TBD
 */

#ifndef	_GCSL_LISTS_H_
#define _GCSL_LISTS_H_

#ifdef __cplusplus
extern "C"{
#endif 

/* List Types */
#define	GCSL_LIST_TYPE_GENRES					"gcsl_list_genres"
#define	GCSL_LIST_TYPE_GENRES_VIDEO				"gcsl_list_genres_video"
#define	GCSL_LIST_TYPE_ORIGINS					"gcsl_list_origins"
#define	GCSL_LIST_TYPE_ERAS						"gcsl_list_eras"
#define	GCSL_LIST_TYPE_ARTISTTYPES				"gcsl_list_artist_types"
#define	GCSL_LIST_TYPE_ROLES					"gcsl_list_roles"
#define	GCSL_LIST_TYPE_LANGUAGES				"gcsl_list_languages"
#define	GCSL_LIST_TYPE_POPULARITY				"gcsl_list_popularity"
#define	GCSL_LIST_TYPE_REGIONS					"gcsl_list_regions"
#define	GCSL_LIST_TYPE_MEDIATYPES				"gcsl_list_mediatypes"
#define	GCSL_LIST_TYPE_CLIENTMESSAGES			"gcsl_list_client_messages"
#define	GCSL_LIST_TYPE_OBJECTS					"gcsl_list_objects"
#define	GCSL_LIST_TYPE_AUDIENCES				"gcsl_list_audiences"
#define	GCSL_LIST_TYPE_ASPECTRATIOS				"gcsl_list_aspectratios"
#define	GCSL_LIST_TYPE_DVDASPECTRATIOS			"gcsl_list_dvdaspectratios"
#define	GCSL_LIST_TYPE_CONTRIBUTORS				"gcsl_list_contributors"
#define	GCSL_LIST_TYPE_DESCRIPTORS				"gcsl_list_descriptors"
#define	GCSL_LIST_TYPE_DESCRIPTORTYPES			"gcsl_list_descriptortypes"
#define	GCSL_LIST_TYPE_VIDEOREGIONS				"gcsl_list_videoregions"
#define	GCSL_LIST_TYPE_MEDIA					"gcsl_list_media" 
#define	GCSL_LIST_TYPE_RATINGS					"gcsl_list_ratings"
#define	GCSL_LIST_TYPE_RATINGTYPES				"gcsl_list_ratingtypes"
#define	GCSL_LIST_TYPE_FEATURETYPES				"gcsl_list_featuretypes"
#define	GCSL_LIST_TYPE_VIDEOTYPES				"gcsl_list_videotypes"
#define	GCSL_LIST_TYPE_PHONEME_CONVERSION		"gcsl_list_phonemeconversion"
#define	GCSL_LIST_TYPE_VIDEOSERIALTYPES			"gcsl_list_videoserialtypes"
#define	GCSL_LIST_TYPE_VIDEOCOLORTYPES			"gcsl_list_videocolortypes"
#define	GCSL_LIST_TYPE_VIDEOKINDTYPES			"gcsl_list_videokindtypes"
#define	GCSL_LIST_TYPE_VIDEOSOUNDTYPES			"gcsl_list_videosoundtypes"
#define	GCSL_LIST_TYPE_WORKTYPES				"gcsl_list_worktypes"
#define	GCSL_LIST_TYPE_CONTRIBUTORENTITYTYPES	"gcsl_list_contributorentitytypes"
#define	GCSL_LIST_TYPE_VIDEOAUDIENCE			"gcsl_list_videoaudience"
#define	GCSL_LIST_TYPE_VIDEOMOOD				"gcsl_list_videomood"
#define	GCSL_LIST_TYPE_VIDEOSTORYTYPE			"gcsl_list_videostorytype"
#define	GCSL_LIST_TYPE_VIDEOREPUTATION			"gcsl_list_videoreputation"
#define	GCSL_LIST_TYPE_VIDEOSCENARIO			"gcsl_list_videoscenario"
#define	GCSL_LIST_TYPE_VIDEOSETTINGENV			"gcsl_list_videosettingenv"
#define	GCSL_LIST_TYPE_VIDEOSETTINGPERIOD		"gcsl_list_videosettingperiod"
#define	GCSL_LIST_TYPE_VIDEOSOURCE				"gcsl_list_videosource"
#define	GCSL_LIST_TYPE_VIDEOSTYLE				"gcsl_list_videostyle"
#define	GCSL_LIST_TYPE_VIDEOTOPIC				"gcsl_list_videotopic"
#define	GCSL_LIST_TYPE_MEDIASPACES				"gcsl_list_mediaspaces"
#define	GCSL_LIST_TYPE_MOODS					"gcsl_list_moods"
#define	GCSL_LIST_TYPE_TEMPOS					"gcsl_list_tempos"
#define	GCSL_LIST_TYPE_COMPOSITION_FORM			"gcsl_list_compform"
#define	GCSL_LIST_TYPE_COMPOSITION_STYLE		"gcsl_list_compstyle"
#define	GCSL_LIST_TYPE_INSTRUMENTATION			"gcsl_list_instrumentation"
#define GCSL_LIST_TYPE_EPGVIEWINGTYPES			"gcsl_list_epgviewingtypes"
#define GCSL_LIST_TYPE_EPGAUDIOTYPES			"gcsl_list_epgaudiotypes"
#define GCSL_LIST_TYPE_EPGVIDEOTYPES			"gcsl_list_epgvideotypes"
#define GCSL_LIST_TYPE_EPGCAPTIONTYPES			"gcsl_list_epgcaptiontypes"
#define GCSL_LIST_TYPE_IPGCATEGORIES_L1			"gcsl_list_ipgcategories-l1"
#define GCSL_LIST_TYPE_IPGCATEGORIES_L2			"gcsl_list_ipgcategories-l2"
#define GCSL_LIST_TYPE_EPGPRODUCTIONTYPES		"gcsl_list_epgproductiontypes"
#define GCSL_LIST_TYPE_EPGDEVICETYPES			"gcsl_list_epgdevicetypes"
#define GCSL_LIST_TYPE_MOOD_GRID                "gcsl_list_mood_grid"

/* Correlate Lists */
#define	GCSL_CORRELATES_TYPE_GENRES				"gcsl_correlates_genre"
#define	GCSL_CORRELATES_TYPE_ORIGINS			"gcsl_correlates_origin"
#define	GCSL_CORRELATES_TYPE_ERAS				"gcsl_correlates_era"
#define	GCSL_CORRELATES_TYPE_ARTISTTYPES		"gcsl_correlates_arttype"
#define	GCSL_CORRELATES_TYPE_MOODS				"gcsl_correlates_mood"

/* List Descriptors */
#define	GCSL_LIST_DESC_SIMPLIFIED				"gcsl_list_desc_simplified"
#define	GCSL_LIST_DESC_DETAILED					"gcsl_list_desc_detailed"
#define	GCSL_LIST_DESC_MAPS						"gcsl_list_desc_maps"
#define	GCSL_LIST_DESC_V1_V2					"gcsl_list_desc_v1_v2"
#define	GCSL_LIST_DESC_V2_V1					"gcsl_list_desc_v2_v1"
#define	GCSL_LIST_DESC_DEMO						"gcsl_list_desc_demo"
#define	GCSL_LIST_DESC_MICRO					"gcsl_list_desc_micro"
#define	GCSL_LIST_DESC_MACRO					"gcsl_list_desc_macro"
#define	GCSL_LIST_DESC_DEVICE					"gcsl_list_desc_device"
#define	GCSL_LIST_DESC_CDDB1					"gcsl_list_desc_cddb1"
#define	GCSL_LIST_DESC_SONY						"gcsl_list_desc_sony"
#define GCSL_LIST_DESC_CDS_ID_MAP               "gcsl_list_desc_cdsid_map"

/* List Regions */
#define	GCSL_LIST_REGION_GLOBAL					"gcsl_list_region_global"
#define	GCSL_LIST_REGION_JAPAN					"gcsl_list_region_japan"
#define	GCSL_LIST_REGION_US						"gcsl_list_region_us"
#define	GCSL_LIST_REGION_CHINA					"gcsl_list_region_china"
#define	GCSL_LIST_REGION_TAIWAN					"gcsl_list_region_taiwan"
#define	GCSL_LIST_REGION_KOREA					"gcsl_list_region_korea"
#define	GCSL_LIST_REGION_EUROPE					"gcsl_list_region_europe"

/* List Languages - ISO 639-2 language identifiers. 

Note, this is not a complete list - just some languages defined here as helpers 
	http://www.loc.gov/standards/iso639-2/php/code_list.php
*/
#define	GCSL_LIST_LANG_ENGLISH					"eng"	/* 1  */
#define	GCSL_LIST_LANG_CHINESE_SIMP				"qtb"	/* 13 */
#define	GCSL_LIST_LANG_CHINESE_TRAD				"qtd"	/* 55 */
#define	GCSL_LIST_LANG_DUTCH					"dut"	/* 19 */
#define	GCSL_LIST_LANG_FRENCH					"fre"	/* 26 */
#define	GCSL_LIST_LANG_GERMAN					"ger"	/* 30 */
#define	GCSL_LIST_LANG_ITALIAN					"ita"	/* 43 */
#define	GCSL_LIST_LANG_JAPANESE					"jpn"	/* 44 */
#define	GCSL_LIST_LANG_KOREAN					"kor"	/* 48 */
#define	GCSL_LIST_LANG_PORTUGUESE_BRAZIL		"por"	/* 61 */
#define	GCSL_LIST_LANG_RUSSIAN					"rus"	/* 64 */
#define	GCSL_LIST_LANG_SPANISH					"spa"	/* 71 */
#define	GCSL_LIST_LANG_SWEDISH					"swe"	/* 73 */
#define	GCSL_LIST_LANG_THAI						"tha"	/* 76 */
#define	GCSL_LIST_LANG_POLSIH					"pol"	/* 60 */
#define	GCSL_LIST_LANG_TURKISH					"tur"	/* 77 */
#define	GCSL_LIST_LANG_FARSI					"per"
#define	GCSL_LIST_LANG_VIETNAMESE				"vie"
#define	GCSL_LIST_LANG_HUNGARIAN				"hun"
#define	GCSL_LIST_LANG_CZECH					"cze"
#define	GCSL_LIST_LANG_SLOVAK					"slo"
#define	GCSL_LIST_LANG_ROMANIAN					"rum"
#define	GCSL_LIST_LANG_GREEK					"gre"
#define	GCSL_LIST_LANG_ARABIC					"ara"
#define	GCSL_LIST_LANG_BAHASA_INDONESIA			"ind"
#define	GCSL_LIST_LANG_FINNISH					"fin"
#define	GCSL_LIST_LANG_NORWEGIAN				"nor"
#define	GCSL_LIST_LANG_CROATIAN					"scr"
#define	GCSL_LIST_LANG_BULGARIAN				"bul"
#define	GCSL_LIST_LANG_SERBIAN					"scc"
#define	GCSL_LIST_LANG_DANISH					"dan"


/* list flags */
#define	GCSL_LISTS_DEFAULT						0x00
#define	GCSL_LISTS_FUZZY_MATCH					0x01
#define	GCSL_LISTS_PARTIAL_ELEMENT_LOAD			0x02


/* xml format tag labels */
#define GCSL_LISTS_FORMAT_XML_BASE_TAG			"LIST"


/*
 * lists opaque handles
 */
GCSL_DECLARE_HANDLE( gcsl_lists_handle_t );
GCSL_DECLARE_HANDLE( gcsl_lists_element_handle_t );

GCSL_DECLARE_HANDLE( gcsl_lists_correlates_handle_t );
GCSL_DECLARE_HANDLE( gcsl_lists_correlates_set_handle_t );

GCSL_DECLARE_HANDLE( gcsl_lists_assemble_correlate_handle_t );
GCSL_DECLARE_HANDLE( gcsl_lists_assemble_correlate_set_handle_t );

/* list data format types */
typedef enum
{
	GCSL_LISTS_DATA_FORMAT_XML,
	GCSL_LISTS_DATA_FORMAT_STORAGE

}gcsl_lists_data_format_t;

/* list loading interface (callbacks) */
typedef gcsl_void_t 	(GCSL_CALLBACK_API *gcsl_lists_load_release_list_data)		(const gcsl_void_t* p_release_callback_data, const gcsl_void_t* list_data, gcsl_iostream_handle_t element_data_iostream);
typedef struct
{
	gcsl_error_t	(GCSL_CALLBACK_API *init)			(const gcsl_void_t* p_user_callback_data, gcsl_cstr_t gcsp_list_name, gcsl_cstr_t gcsp_lang_id, gcsl_uint32_t gcsp_rev_num, const gcsl_void_t** pp_list_data, gcsl_size_t* p_list_data_size, gcsl_iostream_handle_t* p_list_data_iostream, gcsl_lists_load_release_list_data* p_release_list_data_fn, gcsl_lists_data_format_t* p_data_format);
	gcsl_error_t	(GCSL_CALLBACK_API *init_cached)	(const gcsl_void_t* p_user_callback_data, gcsl_cstr_t gcsp_list_name, gcsl_cstr_t gcsp_lang_id, gcsl_uint32_t flags);
	gcsl_error_t 	(GCSL_CALLBACK_API *get_elements)	(const gcsl_void_t* p_user_callback_data, gcsl_uint32_t list_level, gcsl_uint32_t element_ref, const gcsl_void_t** pp_element_data, gcsl_size_t* p_element_data_size, gcsl_iostream_handle_t* p_element_data_iostream, const gcsl_void_t** pp_release_callback_data, gcsl_lists_load_release_list_data* p_release_data_fn, gcsl_lists_data_format_t* p_data_format);

}gcsl_lists_load_intf_t;


/* list rendering to storage interface (callbacks) */
typedef struct
{
	gcsl_error_t 	(GCSL_CALLBACK_API *init)				(const gcsl_void_t* p_user_callback_data, gcsl_cstr_t gcsp_list_name, gcsl_uint32_t gcsp_list_id, gcsl_cstr_t gcsp_lang_id, gcsl_uint32_t gcsp_rev_num);
	gcsl_error_t 	(GCSL_CALLBACK_API *complete)			(const gcsl_void_t* p_user_callback_data);
	gcsl_error_t 	(GCSL_CALLBACK_API *store_init_data)	(const gcsl_void_t* p_user_callback_data, gcsl_uint32_t list_id, gcsl_uint32_t list_lang_id, const gcsl_void_t* p_init_data, gcsl_size_t init_data_size);
	gcsl_error_t 	(GCSL_CALLBACK_API *store_element_data)	(const gcsl_void_t* p_user_callback_data, gcsl_uint32_t list_id, gcsl_uint32_t list_level, gcsl_uint32_t key, gcsl_uint32_t num_elements, const gcsl_void_t* p_element_data, gcsl_size_t element_data_size);

}gcsl_lists_store_intf_t;


/* correlate rendering to storage interface (callbacks) */
typedef struct
{
	gcsl_error_t	(GCSL_CALLBACK_API *init)				(const gcsl_void_t* p_user_callback_data, gcsl_cstr_t gcsp_list_correlate_name, gcsl_uint32_t gcsp_list_id, gcsl_uint32_t gcsp_rev_num);
	gcsl_error_t	(GCSL_CALLBACK_API *complete)			(const gcsl_void_t* p_user_callback_data);
	gcsl_error_t	(GCSL_CALLBACK_API *store_init_data)	(const gcsl_void_t* p_user_callback_data, gcsl_uint32_t gcsp_list_id, const gcsl_void_t* p_correlate_init_data, gcsl_size_t correlate_init_data_size);
	gcsl_error_t	(GCSL_CALLBACK_API *store_set_data)		(const gcsl_void_t* p_user_callback_data, gcsl_uint32_t mc, const gcsl_void_t* p_correlate_set_data, gcsl_size_t correlate_set_data_size);

}gcsl_lists_correlate_store_intf_t;

#ifdef _DEBUG
typedef enum
{
	GCSL_LISTS_LOG_CHANNEL_INFO,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LISTS_LOADED,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_FAILED,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_BY_ID,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_BY_MC,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_BY_IDX,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_BY_RANGE,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_BY_STR,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_BY_STR_FUZZY,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_FROM_CACHE,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_LIST_ELEMENT_GETS_CACHE_HIT_RATE,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_CORRELATE_TYPES_LOADED,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_CORRELATE_SET_CREATES,
	GCSL_LISTS_LOG_CHANNEL_STATS_NUM_CORRELATE_WEIGHT_GETS

}gcsl_lists_log_channel_t;

typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_lists_log_callback)(
	gcsl_lists_log_channel_t					channel,
	gcsl_cstr_t									log_message,
	gcsl_uint32_t								value
	);
#endif


/*
 * Initialization
 */
gcsl_error_t
gcsl_lists_initialize(void);

gcsl_error_t
gcsl_lists_shutdown(void);

gcsl_cstr_t
gcsl_lists_get_version(void);

gcsl_cstr_t
gcsl_lists_get_build_date(void);

#if _DEBUG
gcsl_void_t
gcsl_lists_set_log_callback(
	gcsl_lists_log_callback						log_callback_function
	);
#endif


/*
 * List loading
 */
gcsl_error_t
gcsl_lists_load(
	gcsl_cstr_t                	        		list_type,
	gcsl_cstr_t                	        		list_lang,
	gcsl_cstr_t                	        		list_region,
	gcsl_cstr_t                	        		list_desc,
	const gcsl_void_t*							p_callback_data,
	const gcsl_lists_load_intf_t* 	    		p_list_load_callback_functions,
	gcsl_uint32_t								flags,
	gcsl_lists_handle_t*       	        		p_list_handle
	);

gcsl_error_t
gcsl_lists_load_direct(
	const gcsl_void_t*                   		p_callback_data,
	const gcsl_lists_load_intf_t*       		p_list_load_callback_functions,
	gcsl_uint32_t								flags,
	gcsl_vector_handle_t                		list_vector_handle
	);

gcsl_error_t
gcsl_lists_release(
	gcsl_lists_handle_t                 		list_handle
	);

gcsl_error_t
gcsl_lists_update(
	gcsl_lists_handle_t        	        		list_handle,
	const gcsl_void_t*                   		p_callback_data,
	const gcsl_lists_load_intf_t*	    		p_list_load_callback_functions,
	gcsl_uint32_t								flags,
	gcsl_lists_handle_t*       	        		p_new_list_handle
	);


/*
 * List specifics
 */
gcsl_error_t
gcsl_lists_list_get_type(
	gcsl_lists_handle_t 						list_handle,
	gcsl_cstr_t*        						p_type
	);

gcsl_error_t
gcsl_lists_list_get_language(
	gcsl_lists_handle_t 						list_handle,
	gcsl_cstr_t*        						p_lang
	);

gcsl_error_t
gcsl_lists_list_get_region(
	gcsl_lists_handle_t 						list_handle,
	gcsl_cstr_t*        						p_region
	);

gcsl_error_t
gcsl_lists_list_get_descriptor(
	gcsl_lists_handle_t 						list_handle,
	gcsl_cstr_t*        						p_descriptor
	);

gcsl_error_t
gcsl_lists_list_get_revision(
	gcsl_lists_handle_t 						list_handle,
	gcsl_uint32_t*        						p_revision
	);

gcsl_error_t
gcsl_lists_list_get_gcsp_name(
	gcsl_lists_handle_t 						list_handle,
	gcsl_cstr_t*        						p_name
	);

gcsl_error_t
gcsl_lists_list_get_id(
	gcsl_lists_handle_t 						list_handle,
	gcsl_uint32_t*      						p_id
	);

gcsl_error_t
gcsl_lists_list_get_callback_data(
	gcsl_lists_handle_t 						list_handle,
	const gcsl_void_t**      					pp_callback_data
	);

gcsl_error_t
gcsl_lists_list_get_flags(
	gcsl_lists_handle_t 						list_handle,
	gcsl_uint32_t*      						p_flags
	);

gcsl_error_t
gcsl_lists_list_get_updated(
	gcsl_lists_handle_t 						list_handle,
	gcsl_bool_t*      							p_updated
	);

gcsl_error_t
gcsl_lists_helper_map_gcsp_lang_id(
	gcsl_cstr_t     							lang_str,
	gcsl_cstr_t*    							p_lang_id
	);

gcsl_error_t
gcsl_lists_helper_map_gcsp_lang_str(
	gcsl_cstr_t     							lang_id,
	gcsl_cstr_t*    							p_lang_str
	);

/* 
 * List Item direct access 
 */

gcsl_error_t
gcsl_lists_list_get_element_by_id(
	gcsl_lists_handle_t             			list_handle,
	gcsl_uint32_t                   			id,
	gcsl_uint32_t                   			level,
	gcsl_lists_element_handle_t*    			p_element_handle
	);

gcsl_error_t
gcsl_lists_list_get_element_by_range(
	gcsl_lists_handle_t           				list_handle,
	gcsl_uint32_t                 				value,
	gcsl_uint32_t                 				level,
	gcsl_lists_element_handle_t*  				p_element_handle
	);

gcsl_error_t
gcsl_lists_list_get_element_by_display_string(
	gcsl_lists_handle_t           				list_handle,
	gcsl_cstr_t                 				display_string,
	gcsl_uint32_t                 				level,
	gcsl_lists_element_handle_t*  				p_element_handle
	);


/* 
 * List Navigation 
 */
gcsl_error_t
gcsl_lists_list_get_level_count(
	gcsl_lists_handle_t             			list_handle,
	gcsl_uint32_t*                  			p_count
	);

gcsl_error_t
gcsl_lists_list_get_element_count(
	gcsl_lists_handle_t             			list_handle,
	gcsl_uint32_t                   			level,
	gcsl_uint32_t*                  			p_count
	);

gcsl_error_t
gcsl_lists_list_get_element(
	gcsl_lists_handle_t             			list_handle,
	gcsl_uint32_t                   			level,
	gcsl_uint32_t                   			index,
	gcsl_lists_element_handle_t*    			p_element_handle
	);


/*
 * List Elements
 */
gcsl_error_t
gcsl_lists_element_get_display_string(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_cstr_t*                    			p_string
	);

gcsl_error_t
gcsl_lists_element_get_range(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_uint32_t*                  			p_low,
	gcsl_uint32_t*                  			p_high
	);

gcsl_error_t
gcsl_lists_element_get_id(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_uint32_t*                  			p_id
	);

gcsl_error_t
gcsl_lists_element_get_master_code(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_uint32_t*                  			p_mc
	);

gcsl_error_t
gcsl_lists_element_get_parent(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_lists_element_handle_t*    			p_element_handle
	);

gcsl_error_t
gcsl_lists_element_get_level(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_uint32_t*                  			p_level
	);

gcsl_error_t
gcsl_lists_element_get_child_count(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_uint32_t*                  			p_count
	);

gcsl_error_t
gcsl_lists_element_get_child(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_uint32_t                   			index,
	gcsl_lists_element_handle_t*    			p_element_handle
	);

gcsl_error_t
gcsl_lists_element_get_value(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_cstr_t                     			value_key,
	gcsl_cstr_t*                    			p_value
	);

gcsl_error_t
gcsl_lists_element_get_type(
	gcsl_lists_element_handle_t     			element_handle,
	gcsl_cstr_t*                    			p_type
	);

gcsl_error_t
gcsl_lists_element_release(
	gcsl_lists_element_handle_t					element_handle
	);

/* for use with gcsl_lists_element_get_value */
#define	GCSL_LISTS_VALUE_KEY_DESC					"DESC"
#define	GCSL_LISTS_VALUE_KEY_RATINGTYPE_ID			"RATING_TYPE_ID"
#define	GCSL_LISTS_VALUE_KEY_CDS_ID					"CDS_ID"


/*
 * List Rendering
 */

#define GCSL_LISTS_RENDER_MINIMAL               	0x0000
#define GCSL_LISTS_RENDER_SUBMIT_IDS            	0x0002  /* basically, same as master codes, just labeled for GNSDK public consumption */
#define GCSL_LISTS_RENDER_SINGLE_LEVEL          	0x0010  /* render just the single level as given by the 'levels' param */

#define GCSL_LISTS_RENDER_LOADABLE              	0x0100  /* for when we want XML that can be used in load_direct() API */

gcsl_error_t
gcsl_lists_list_render(
	gcsl_lists_handle_t 						list_handle,
	gcsl_lists_data_format_t					data_format,
	gcsl_uint32_t 								levels,
	gcsl_uint32_t 								flags,
	const gcsl_void_t*                   		p_callback_data,
	const gcsl_lists_store_intf_t* 				p_list_store_intf,
	const gcsl_lists_load_intf_t*  	    		p_list_load_callback_functions,
	gcsl_lists_handle_t*						p_list_handle
	);


/*
 * Correlate Loading
 */
gcsl_error_t
gcsl_lists_correlates_load(
	gcsl_cstr_t                      			correlates_type,
	const gcsl_void_t*                   		p_callback_data,
	const gcsl_lists_load_intf_t*   			p_list_load_callback_functions,
	gcsl_lists_correlates_handle_t*  			p_correlates_handle
	);

gcsl_error_t
gcsl_lists_correlates_load_direct(
	const gcsl_void_t*                   		p_user_callback_data,
	const gcsl_lists_load_intf_t*       		p_list_load_callback_functions,
	gcsl_uint32_t								flags,
	gcsl_lists_correlates_handle_t*				p_correlates_handle
	);

gcsl_error_t
gcsl_lists_correlates_release(
	gcsl_lists_correlates_handle_t 	    		correlates_handle
	);

gcsl_error_t
gcsl_lists_correlates_update(
	gcsl_lists_correlates_handle_t      		correlates_handle,
	const gcsl_void_t*                   		p_callback_data,
	const gcsl_lists_load_intf_t*       		p_list_load_callback_functions,
	gcsl_lists_correlates_handle_t*     		p_new_correlates_handle
	);

gcsl_error_t
gcsl_lists_correlates_get_revision(
	gcsl_lists_correlates_handle_t 	    		correlates_handle,
	gcsl_uint32_t*                      		p_revision
	);

gcsl_error_t
gcsl_lists_correlates_get_id(
	gcsl_lists_correlates_handle_t      		correlates_handle,
	gcsl_uint32_t*                      		p_id
	);

gcsl_error_t
gcsl_lists_correlates_get_type(
	gcsl_lists_correlates_handle_t      		correlates_handle,
	gcsl_cstr_t*                         		p_type
	);

gcsl_error_t
gcsl_lists_correlates_get_updated(
	gcsl_lists_correlates_handle_t      		correlates_handle,
	gcsl_bool_t*                         		p_updated
	);


/*
 * Correlate Sets
 */
gcsl_error_t
gcsl_lists_correlates_set_create(
	gcsl_lists_correlates_handle_t      		corrlates_handle,
	gcsl_uint32_t                       		mc,
	gcsl_lists_correlates_set_handle_t* 		ph_correlate_set
	);

gcsl_error_t
gcsl_lists_correlates_set_get_weight(
	gcsl_lists_correlates_set_handle_t  		h_correlate_set,
	gcsl_uint32_t                       		mc,
	gcsl_int32_t*                       		p_weight
	);

gcsl_error_t
gcsl_lists_correlates_set_delete(
	gcsl_lists_correlates_set_handle_t  		h_correlate_set
	);


/* 
 * Correlate Rendering
 */
gcsl_error_t
gcsl_lists_correlates_render(
	gcsl_lists_correlates_handle_t              correlates_handle,
	gcsl_lists_data_format_t					render_format,
	gcsl_uint32_t                               min_weight,
	const gcsl_void_t*                   		p_user_callback_data,
	const gcsl_lists_correlate_store_intf_t*    p_list_correlate_store_intf,
	const gcsl_lists_load_intf_t*       		p_list_load_callback_functions,
	gcsl_lists_correlates_handle_t*     		p_rendered_correlates_handle
	);

gcsl_error_t
gcsl_lists_correlates_set_render(
	gcsl_lists_correlates_handle_t  			corrlates_handle,
	gcsl_uint32_t                   			mc,
	gcsl_str_t*                     			p_xml
	);


/*
 * Correlate Assembly
 */
typedef enum
{
	GCSL_LISTS_CORRELATE_MICRO = 1,
	GCSL_LISTS_CORRELATE_MACRO = 2

}gcsl_lists_correlate_type_t;

gcsl_error_t
gcsl_lists_assemble_correlate_create(
	gcsl_lists_assemble_correlate_handle_t* 	p_assemble_correlate_handle
	);

gcsl_error_t
gcsl_lists_assemble_correlate_delete(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle
	);

gcsl_error_t
gcsl_lists_assemble_correlate_finalize(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle,
	gcsl_lists_correlates_handle_t*         	p_correlate_handle
	);

gcsl_error_t
gcsl_lists_assemble_correlate_set_id(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle,
	gcsl_lists_correlate_type_t             	type,
	gcsl_uint32_t                           	list_id
	);

gcsl_error_t
gcsl_lists_assemble_correlate_set_name(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle,
	gcsl_lists_correlate_type_t             	type,
	gcsl_cstr_t                             	list_name
	);

gcsl_error_t
gcsl_lists_assemble_correlate_set_revision(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle,
	gcsl_lists_correlate_type_t             	type,
	gcsl_cstr_t                             	list_revision
	);

gcsl_error_t
gcsl_lists_assemble_correlate_set_map_list(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle,
	gcsl_lists_handle_t                     	list_handle
	);

gcsl_error_t
gcsl_lists_assemble_correlate_macro_list_data(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle,
	gcsl_void_t*								p_list_data
	);

gcsl_error_t
gcsl_lists_assemble_correlate_micro_list_data(
	gcsl_lists_assemble_correlate_handle_t  	assemble_correlate_handle,
	gcsl_void_t*								p_list_data
	);


#ifdef GCSL_LISTS_VALIDATE_LIST_DATA
#ifdef _DEBUG
/*
 * List Data Validation - only for internal Gracenote use
 */
typedef gcsl_void_t
(*gcsl_lists_validate_issue_fn)(
	gcsl_lists_handle_t list_handle,
	gcsl_cstr_t         issue_message
	);

gcsl_error_t
gcsl_lists_set_validation_callback(
	gcsl_lists_validate_issue_fn issue_callback
	);

extern gcsl_lists_validate_issue_fn g_gcsl_lists_validation_issue_callback;

#endif /* _DEBUG */
#endif /* GCSL_LISTS_VALIDATE_LIST_DATA */


#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_LISTS_H_ */
