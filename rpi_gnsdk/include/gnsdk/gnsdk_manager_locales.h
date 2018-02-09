/* Gracenote SDK: GNSDK Manager Public Header File
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by USA and international patents.
*/

/* gnsdk_manager_locales.h: Primary interface for the GNSDK Manager.
*/

#ifndef _GNSDK_MANAGER_LOCALES_H_
#define _GNSDK_MANAGER_LOCALES_H_

#include "gnsdk_manager.h"

#ifdef __cplusplus
extern "C"{
#endif



/******************************************************************************
 * Typedefs
 ******************************************************************************/

/** @internal gnsdk_locale_handle_t @endinternal
*  Handle to a locale.
* @ingroup ListsandLocales_Locale_TypesEnums
*/
GNSDK_DECLARE_HANDLE( gnsdk_locale_handle_t );


/******************************************************************************
 * Locale APIs
 ******************************************************************************/

/** @internal gnsdk_manager_query_status_t @endinternal
*  List callback function status values. An application receives these values when implementing the
gnsdk_manager_query_callback_fn.
* @ingroup Manager_TypesEnums
*/
typedef enum
{
	/** @internal gnsdk_manager_query_status_unknown @endinternal
	  *
	  *   Invalid status
	* @ingroup Manager_TypesEnums
*/
	gnsdk_manager_query_status_unknown = 0,
	/** @internal gnsdk_manager_query_status_query_begin @endinternal
	  *
	  *   Building request to download list from Gracenote.
	* @ingroup Manager_TypesEnums
*/
	gnsdk_manager_query_status_query_begin,
	/** @internal gnsdk_manager_query_status_connecting @endinternal
	  *
	  *   Connecting to the Gracenote Service.
	* @ingroup Manager_TypesEnums
*/
	gnsdk_manager_query_status_connecting,
	/** @internal gnsdk_manager_query_status_sending @endinternal
	  *
	  *   Sending request.
	 * @ingroup Manager_TypesEnums
*/
	gnsdk_manager_query_status_sending,
	/** @internal gnsdk_manager_query_status_receiving @endinternal
	  *
	  *   Receiving data.
	* @ingroup Manager_TypesEnums
*/
	gnsdk_manager_query_status_receiving,
	/** nsdk_manager_query_status_disconnected
	  *
	  *   Disconnected.
	*/
	gnsdk_manager_query_status_disconnected,
	/** @internal gnsdk_manager_query_status_query_complete @endinternal
	  *
	  *   Done with request.
	* @ingroup Manager_TypesEnums
*/
	gnsdk_manager_query_status_query_complete
} gnsdk_manager_query_status_t;

/** @internal gnsdk_manager_query_callback_fn @endinternal
*  Receive status updates as List data is retrieved.
*  @param user_data [in] Pointer to data passed in to various GNSDK libraries' functions through the
callback_userdata parameter. This pointer must be cast from the gnsdk_void_t type to its original
type to be accessed properly.
*  @param status [in] One of gnsdk_manager_query_status_t values
*  @return bytes_done [in] Current number of bytes transferred. Set to a value greater than 0 to
indicate progress, or 0 to indicate no progress.
*  @return bytes_total [in] Total number of bytes to be transferred. Set to a value greater than 0
to indicate progress, or 0 to indicate no progress.
*  @return p_abort [out] Set dereferenced value to GNSDK_TRUE to abort the operation that is calling
the callback
*  <p><b>Remarks:</b></p>
*  This callback can be provided to the following APIs: gnsdk_manager_list_retrieve and
gnsdk_manager_list_update.
* @ingroup Manager_Callbacks
*/
typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_manager_query_callback_fn)(
	const gnsdk_void_t*				user_data,
	gnsdk_manager_query_status_t	status,
	gnsdk_size_t					bytes_done,
	gnsdk_size_t					bytes_total,
	gnsdk_bool_t*					p_abort
	);




/** @internal GNSDK_LOCALE_GROUP_MUSIC @endinternal
*  Locale value for the GNSDK music products. Set this when creating a locale used with the MusicID
and MusicID -File libraries.
* @ingroup ListsandLocales_Locale_Groups
*/
#define GNSDK_LOCALE_GROUP_MUSIC			"gnsdk_locale_music"
/** @internal GNSDK_LOCALE_GROUP_VIDEO @endinternal
*  Locale value for the GNSDK video products. Set this when creating a locale used with the VideoID
or Video Explore libraries (or both).
* @ingroup ListsandLocales_Locale_Groups
*/
#define GNSDK_LOCALE_GROUP_VIDEO			"gnsdk_locale_video"
/** @internal GNSDK_LOCALE_GROUP_PLAYLIST @endinternal
*  Locale value for the GNSDK Playlist product. Set this when creating a locale used with the
Playlist
*  library.
* @ingroup ListsandLocales_Locale_Groups
*/
#define GNSDK_LOCALE_GROUP_PLAYLIST			"gnsdk_locale_playlist"

/** @internal GNSDK_LOCALE_GROUP_EPG @endinternal
  * Locale value for the EPG product. Set this when creating a locale used with the
  * EPG library.
  *
* @ingroup ListsandLocales_Locale_Groups
*/
#define GNSDK_LOCALE_GROUP_EPG				"gnsdk_locale_epg"

/** @internal gnsdk_manager_locale_load @endinternal
*  Loads the specified locale. Locale lists not currently in memory are loaded from the
*  Gracenote Service or local storage according to the configuration of user lookup option.
*  See #GNSDK_USER_OPTION_LOOKUP_MODE for more information.
*
*  Note: This function blocks the current thread until the download is complete;
*  set a status callback function to receive progress messages.
*  @param locale_group [in] Locale GNSDK product group defined for locale handle
*  @param language [in] Language defined for locale handle
*  @param region [in] Region defined for locale handle
*  @param descriptor [in] Descriptor defined for locale handle
*  @param user_handle [in] User handle for the user requesting the query
*  @param callback_fn [in_opt] Callback function for status and progress
*  @param callback_userdata [in_opt] Data that is passed back through calls to the callback function
*  @param p_locale_handle [out] Pointer to receive locale handle
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_InvalidArg Given language parameter is empty, given p_locale_handle is null, or
given locale_group is not a valid GNSDK locale group
*  @return SDKMGRERR_NoError Locale was successfully loaded
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_load(
	gnsdk_cstr_t					locale_group,
	gnsdk_cstr_t					language,
	gnsdk_cstr_t					region,
	gnsdk_cstr_t					descriptor,
	gnsdk_user_handle_t				user_handle,
	gnsdk_manager_query_callback_fn	callback_fn,
	const gnsdk_void_t*				callback_userdata,
	gnsdk_locale_handle_t*			p_locale_handle
	);

/** @internal gnsdk_manager_locale_set_group_default @endinternal
*  Use this function to set global group defaults for a locale. The group type of the locale
*  is inferred from the locale handle. For example, if you pass the handle of a locale with a
*  group property of #GNSDK_LOCALE_GROUP_MUSIC, this function sets the locale for 
*  all music-related objects. All GDOs in this group will use this locale unless
*  specifically overwritten by gnsdk_manager_gdo_set_locale().
*  Global default options are #GNSDK_LOCALE_GROUP_MUSIC, #GNSDK_LOCALE_GROUP_PLAYLIST, 
*  #GNSDK_LOCALE_GROUP_VIDEO, and #GNSDK_LOCALE_GROUP_EPG.
*  @param locale_handle [in] Locale handle to set group default for
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_NoError Locale default group was successfully set
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_set_group_default(
	gnsdk_locale_handle_t			locale_handle
	);

/** @internal gnsdk_manager_locale_unset_group_default @endinternal
*  Releases the default reference to the locale.
*  @param locale_group [in] Locale GNSDK product group to clear from locale handle
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_NoError Locale group default was successfully cleared
*  <p><b>Remarks:</b></p>
*  Use this function to ensure maximum efficient memory management with locale groups. It clears
from memory a locale group set as a default.
*  To clear a default locale group from memory requires calling this function and
gnsdk_manager_locale_release, to release any GDOs that still hold a reference to the locale.
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_unset_group_default(
	gnsdk_cstr_t					locale_group
	);

/** @internal gnsdk_manager_locale_info @endinternal
*  Retrieves information about the locale contained in a locale handle.
*  @param locale_handle [in] Locale handle to retrieve information for
*  @param p_group [out] Pointer to string to receive the locale group
*  @param p_language [out] Pointer to string to receive the locale language
*  @param p_region [out] Pointer to string to receive the locale region
*  @param p_descriptor [out] Pointer to string to receive the locale descriptor
*  @param p_revision [out] Pointer to string to receive the locale revision
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_NoError Locale information was successfully retrieved
*  <p><b>Remarks:</b></p>
*  Use this function to retrieve locale information about an unknown or unrecognized locale handle.
For example, in cases when the application may need to deserialize an unfamiliar locale, this
function retrieves basic descriptive information.
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_info(
	gnsdk_locale_handle_t			locale_handle,
	gnsdk_cstr_t*					p_group,
	gnsdk_cstr_t*					p_language,
	gnsdk_cstr_t*					p_region,
	gnsdk_cstr_t*					p_descriptor,
	gnsdk_cstr_t*                   p_revision
	);

/** @internal gnsdk_manager_locale_deserialize @endinternal
*  Reconstitutes locale from serialized locale data.
*  @param serialized_locale_data [in] String of serialized locale handle data
*  @param p_locale_handle [out] Pointer to receive handle of deserialized locale data
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_InvalidArg Given serialized_locale_data parameter is empty, or given p_locale_handle
is null
*  @return SDKMGRERR_NoError Locale was successfully deserialized
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_deserialize(
	gnsdk_cstr_t					serialized_locale_data,
	gnsdk_locale_handle_t*			p_locale_handle
	);

/** @internal gnsdk_manager_locale_serialize @endinternal
* Serializes a locale into encrypted text that the application can store locally for later use.
*
* Note: If the application is using a GNSDK local storage solution, locale lists are automatically stored
* and reteived from a local store according to the configuration of user lookup option. See #GNSDK_USER_OPTION_LOOKUP_MODE
* for more information.
* Applications implementing their own local storage functionality can use gnsdk_manager_locale_serialize() to
* render a list into a format that can be stored persistently and restored at a later time using gnsdk_manager_locale_deserialize().
*  @param locale_handle [in] Locale handle to serialize
*  @param p_serialized_locale_data [out] Pointer to string to receive serialized locale data
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_InvalidArg Given p_serialized_locale_data parameter is null
*  @return SDKMGRERR_NoError Locale was successfully serialized
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_serialize(
	gnsdk_locale_handle_t			locale_handle,
	gnsdk_str_t*					p_serialized_locale_data
	);

/** @internal gnsdk_manager_locale_release @endinternal
*  Releases resources for a locale handle.
*  @param locale_handle [in] Locale handle to release
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_NoError Locale was successfully released
*  <p><b>Remarks:</b></p>
*  Use this function to release a locale handle.
*  To clear a default locale group from memory, the application must also call
gnsdk_manager_locale_unset_group_default.
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_release(
	gnsdk_locale_handle_t			locale_handle
	);

/** @internal gnsdk_manager_locale_update @endinternal
*  Updates a locale with new versions of the locale lists, if available.
*  The application must ensure the Locale module can contact the Gracenote Service
*  to test for a new list version by appropriately configuring the user lookup option to allow online access.
*  See #GNSDK_USER_OPTION_LOOKUP_MODE for more information.
*
*  Note: This function blocks the current thread until the download is complete;
*  set a status callback function to receive progress messages.
*  @param locale_handle [in] Locale handle to update
*  @param user_handle [in] User handle for the user requesting the query
*  @param callback_fn [in_opt] Callback function for status and progress
*  @param callback_userdata [in_opt] Data that is passed back through calls to the callback function
*  @param p_updated [out] Pointer to receive boolean value if the locale has been updated
(GNSDK_TRUE) or not (GNSDK_FALSE)
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_InvalidArg Given p_updated is null, or given locale_group is not a valid
*  GNSDK locale group
*  @return SDKMGRERR_NoError Boolean value was successfully retrieved
* @ingroup ListsandLocales_Locale_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_locale_update(
	gnsdk_locale_handle_t			locale_handle,
	gnsdk_user_handle_t				user_handle,
	gnsdk_manager_query_callback_fn	callback_fn,
	const gnsdk_void_t*				callback_userdata,
	gnsdk_bool_t*					p_updated
	);


#ifdef __cplusplus
}
#endif

#endif /** @internal _GNSDK_MANAGER_LOCALES_H_ @endinternal
*  Primary interface for the GNSDK Manager.
*/

