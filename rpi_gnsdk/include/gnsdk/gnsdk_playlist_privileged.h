/** Gracenote SDK: Playlist public header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_PLAYLIST_PRIVILEGED_H_
/** gnsdk_playlist_privileged.h: Privileged interface for the Playlist SDK.
*/
#define _GNSDK_PLAYLIST_PRIVILEGED_H_

#ifdef __cplusplus
extern "C"{
#endif



/** <unfinished>
  *
  * gnsdk_playlist_attribute_operator_t
  * Summary:
  *   Playlist Rule Expansion
  *
  *
*/
 typedef enum
{
	gnsdk_playlist_operator_unknown			= 0,/** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_unknown
	  * Summary:
	  *   \ \
	*/



	gnsdk_playlist_operator_equal			= 10, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_equal
	  * Summary:
	  *   \ \
	*/

	gnsdk_playlist_operator_notequal, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_notequal
	  * Summary:
	  *   \ \
	*/

	gnsdk_playlist_operator_greaterthan, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_greaterthan
	  * Summary:
	  *   \ \
	*/

	gnsdk_playlist_operator_greaterequal, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_greaterequal
	  * Summary:
	  *   \ \
	*/

	gnsdk_playlist_operator_lessthan, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_lessthan
	  * Summary:
	  *   \ \
	*/

	gnsdk_playlist_operator_lessequal, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_lessequal
	  * Summary:
	  *   \ \
	*/



	gnsdk_playlist_operator_similar			= 20, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_similar
	  * Summary:
	  *   \ \
	  * Ignore Text:
	  *   \ \
	  *    \orig text: similarity
	*/

	gnsdk_playlist_operator_notsimilar, /** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_notsimilar
	  * Summary:
	  *   \ \
	*/



	gnsdk_playlist_operator_begins			= 30,/** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_begins
	  * Summary:
	  *   \ \
	  * Ignore Text:
	  *         \orig text: substring
	*/

	gnsdk_playlist_operator_contains/** <unfinished>
	  *
	  * gnsdk_playlist_attribute_operator_t@1::gnsdk_playlist_operator_contains
	  * Summary:
	  *   \ \
	*/


} gnsdk_playlist_attribute_operator_t;



/** <unfinished>
  *
  * _gnsdk_playlist_data_collection_interface_s
  * Summary:
  *   \ \
*/
typedef struct _gnsdk_playlist_data_collection_interface_s
{
	gnsdk_error_t	(GNSDK_CALLBACK_API *get_media_ident)			(gnsdk_void_t* collector_data, gnsdk_cstr_t* p_media_ident);
	gnsdk_error_t	(GNSDK_CALLBACK_API *get_media_gdo)				(gnsdk_void_t* collector_data, gnsdk_gdo_handle_t* p_media_gdo);
	gnsdk_error_t	(GNSDK_CALLBACK_API *get_media_list_element)	(gnsdk_void_t* collector_data, gnsdk_list_element_handle_t* p_list_element);

	gnsdk_error_t	(GNSDK_CALLBACK_API *set_integer_data)			(gnsdk_void_t* collector_data, gnsdk_uint32_t attribute_data);
	gnsdk_error_t	(GNSDK_CALLBACK_API *set_string_data)			(gnsdk_void_t* collector_data, gnsdk_cstr_t attribute_data);

} gnsdk_playlist_data_collection_interface_t;



/** <unfinished>
  *
  * _gnsdk_playlist_attribute_provider_interface_s
  * Summary:
  *   \ \
*/
typedef struct _gnsdk_playlist_attribute_provider_interface_s
{
	gnsdk_error_t	(GNSDK_CALLBACK_API *attribute_name)			(gnsdk_cstr_t* p_attribute_name);
	gnsdk_error_t	(GNSDK_CALLBACK_API *supported_operators)		(gnsdk_uint32_t index, gnsdk_playlist_attribute_operator_t* p_attr_operator);
	gnsdk_error_t	(GNSDK_CALLBACK_API *collect_attribute_data)	(gnsdk_void_t* collector_data, gnsdk_playlist_data_collection_interface_t* p_collector);

	gnsdk_error_t	(GNSDK_CALLBACK_API *create_instance)			(gnsdk_void_t** pp_attribute_inst);
	gnsdk_error_t	(GNSDK_CALLBACK_API *set_string_criteria)		(gnsdk_void_t* p_attribute_inst, gnsdk_playlist_attribute_operator_t attr_operator, gnsdk_cstr_t criteria_value, gcsl_int32_t* p_default_score_threshold);
	gnsdk_error_t	(GNSDK_CALLBACK_API *set_seed_criteria)			(gnsdk_void_t* p_attribute_inst, gnsdk_playlist_attribute_operator_t attr_operator, gnsdk_gdo_handle_t h_gdo_seed, gcsl_int32_t* p_default_score_threshold);
	gnsdk_error_t	(GNSDK_CALLBACK_API *compare_integer_data)		(gnsdk_void_t* p_attribute_inst, gnsdk_uint32_t comparison_value, gnsdk_int32_t* p_score);
	gnsdk_error_t	(GNSDK_CALLBACK_API *compare_string_data)		(gnsdk_void_t* p_attribute_inst, gnsdk_cstr_t comparison_value, gnsdk_int32_t* p_score);
	gnsdk_error_t	(GNSDK_CALLBACK_API *value_from_integer_data)	(gnsdk_void_t* p_attribute_inst, gnsdk_uint32_t attr_value, gnsdk_cstr_t gdo_value_key, gnsdk_locale_handle_t locale_handle, gnsdk_cstr_t* psz_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *value_from_string_data)	(gnsdk_void_t* p_attribute_inst, gnsdk_cstr_t attr_value, gnsdk_cstr_t gdo_value_key, gnsdk_locale_handle_t locale_handle, gnsdk_cstr_t* psz_value);
	gnsdk_error_t	(GNSDK_CALLBACK_API *release_instance)			(gnsdk_void_t* p_attribute_inst);

} gnsdk_playlist_attribute_provider_interface_t;


/** <unfinished>
  *
  * gnsdk_playlist_register_attribute_provider
  * Summary:
  *   \ \
  * Parameters:
  *   p_attribute_provider_intf:  [out] Pointer to an attribute provider
  *                               interface
  *
*/
gnsdk_error_t GNSDK_API
gnsdk_playlist_register_attribute_provider	(gnsdk_playlist_attribute_provider_interface_t* p_attribute_provider_intf);




#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_PLAYLIST_PRIVILEGED_H_ */

