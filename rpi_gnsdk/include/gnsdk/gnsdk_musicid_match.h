/* Gracenote SDK MusicID Match public header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_MUSICID_MATCH_H_
#define _GNSDK_MUSICID_MATCH_H_

/* @internal gnsdk_musicid_match.h @endinternal
 *
 * Gracenote MusicID Match provides audio recognition features to compare a
 * user's music collection against a set of known tracks in another collection,
 * such as a music library used for cloud-based music services.
 * MusicID Match implements a two-phased approach:
 * <ol>
 * <li>Generate a set of track identifiers from a base music library using Cantametrix fingerprinting.
 * <li>Generate full-length fingerprints (microFAPI and nanoFAPI) for a users music collection,
 *		and compare the corresponding track identifiers to the base music library.
 * </ol>
 * Possible return values are:
 * <ul>
 *  <li> Exact: Compared files are an exact match.
 *  <li> NoMatch: Compared files do not match.
 *  <li> NonExist: Gracenote Service does not have a corresponding external ID for the comparison.
 *  <li> Undefined: Not a comparison query. Lookup queries will always return a value of Undefined.
 * </ul>
 * @ingroup Music_MusicIDMatch_HeaderFile
*/

#ifdef __cplusplus
extern "C"{
#endif

/******************************************************************************
 * Typedefs
 ******************************************************************************/

/** @internal gnsdk_musicidmatch_query_handle_t @endinternal
  *
  * Handle to MusicID Match query. Created by gnsdk_musicidmatch_query_create API, the
  * application must create this handle to perform any MusicID Match queries it
  *  wishes to execute.
* @ingroup Music_MusicIDMatch_TypesEnums
*/
GNSDK_DECLARE_HANDLE( gnsdk_musicidmatch_query_handle_t );

/** @internal gnsdk_musicidmatch_status_t @endinternal
  *
  * MusicID Match callback function status values
  * @ingroup Music_MusicIDFile_TypesEnums
*/
typedef enum
{
	/** @internal gnsdk_musicidmatch_status_unknown @endinternal
	 *
	 * MusicID Match query status is unknown.
	 * @ingroup Music_MusicIDMatch_TypesEnums
*/
	gnsdk_musicidmatch_status_unknown = 0,

	/** @internal gnsdk_musicidmatch_query_begin @endinternal
	 *
	 * MusicID Match query is starting.
	 * @ingroup Music_MusicIDMatch_QueryFunctions
*/
	gnsdk_musicidmatch_status_query_begin = 10,

	/** @internal gnsdk_musicidmatch_status_connecting @endinternal
	 *
	 * MusicID Match query is starting a network connection
	 * @ingroup Music_MusicIDMatch_TypesEnums
*/
	gnsdk_musicidmatch_status_connecting = 20,

	/** @internal gnsdk_musicidmatch_status_sending @endinternal
	 *
	 * MusicID Match is sending query data.
	 * @ingroup Music_MusicIDMatch_TypesEnums
*/
	gnsdk_musicidmatch_status_sending = 30,

	/** @internal gnsdk_musicidmatch_status_receiving @endinternal
	 *
	 * MusicID Match is receiving query data.
	 * @ingroup Music_MusicIDMatch_TypesEnums
*/
	gnsdk_musicidmatch_status_receiving = 40,

	/** @internal gnsdk_musicidmatch_status_query_complete @endinternal
	 *
	 * MusicID Match query handle is completing the query process.
	 * @ingroup Music_MusicIDMatch_TypesEnums
*/
	gnsdk_musicidmatch_status_query_complete = 100,

	/** @internal gnsdk_musicidmatch_status_query_delete @endinternal
	 *
	 * MusicID Match query handle is about to be deleted.
	 * @ingroup Music_MusicIDMatch_TypesEnums
*/
	gnsdk_musicidmatch_status_query_delete = 999

} gnsdk_musicidmatch_status_t;


/** @internal gnsdk_musicidmatch_callback_fn @endinternal
  *
  * MusicID Match callback function for status updates as content is retrieved.
  *
  * @param user_data	[in] Pointer to data passed in to gnsdk_musicidmatch_query_create
  *                        function through the callback_userdata parameter.
  *                        You must cast this pointer from the gnsdk_void_t type to its original
  *                        type to be accessed properly.
  * @param musicid_match_query_handle	[in] The query handle that the callback operates on.
  * @param status	[in] One of gnsdk_musicidmatch_query_status_t values.
  * @param bytes_done	[in] Current number of bytes transferred. Set to a value greater than 0 to
  *                         indicate progress, or 0 to indicate no progress.
  * @param bytes_total	[in] Total number of bytes to be transferred.
  *                           Set to a value greater than 0 to indicate progress, or 0 to indicate no progress.
  * @param p_abort	[out] Set dereferenced value to GNSDK_TRUE to abort the operation that calls the callback.
  *
* @ingroup Music_MusicIDMatch_Callbacks
*/
typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_musicidmatch_callback_fn)(
	gnsdk_void_t*						user_data,
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_musicidmatch_status_t		status,
	gnsdk_size_t						bytes_done,
	gnsdk_size_t						bytes_total,
	gnsdk_bool_t*						p_abort
	);

/** @internal gnsdk_musicidmatch_initialize @endinternal
  *
  * Initialize the Gracenote MusicID Match SDK.
  *
  *  @param	sdkmgr	Handle from successful gnsdk_sdkmanager_initialize call
  *
  * @ingroup Music_MusicIDMatch_InitializationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_initialize(
	gnsdk_manager_handle_t sdkmgr
	);

/** @internal gnsdk_musicidmatch_shutdown @endinternal
  *
  * Shut down the MusicID Match SDK.
  * @ingroup Music_MusicIDMatch_InitializationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_shutdown(void);

/** @internal gnsdk_musicidmatch_get_version @endinternal
  *
  * Retrieve the MusicID Match SDK's version string.
* @ingroup Music_MusicIDMatch_InitializationFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_musicidmatch_get_version(void);

/** @internal gnsdk_musicidmatch_get_build_date @endinternal
  *
  * Retrieve MusicID Match SDK's build date string.
* @ingroup Music_MusicIDMatch_InitializationFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_musicidmatch_get_build_date(void);


/******************************************************************************
 * MusicID Match Query Handle - for the life of the query
 ******************************************************************************/

/** @internal gnsdk_musicidmatch_query_create @endinternal
  *
  * Create a MusicID Match query handle.
  *
  * @param user_handle	User handle for the user requesting the query
  * @param callback_fn	(Optional) Callback function for status and
  *                         progress
  * @param callback_userdata	(Optional) Data that is passed back through calls
  *                         to the callback function
  * @param  p_musicid_match_query_handle	Pointer to receive the MusicID Match query handle
  *
* @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_create(
	gnsdk_user_handle_t			user_handle,
	gnsdk_musicidmatch_callback_fn		callback_fn,
	gnsdk_void_t*				callback_userdata,
	gnsdk_musicidmatch_query_handle_t*	p_musicid_match_query_handle
	);

/** @internal gnsdk_musicidmatch_query_release @endinternal
  *
  * Invalidate and release resources for a given MusicID Match query handle.
  *
  * @param  musicid_match_query_handle	  MusicID Match query handle to release
  *
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_release(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle
	);


/** @internal gnsdk_musicidmatch_query_set_id_datasource @endinternal
  *
  * Set the id data source for which the entire query operates in. This determines the id context of the
  * query response.
  *
  * @param  musicid_match_query_handle		MusicID Match query handle this lookup request applies to
  *	@param  id_source						the id source for which the results will be returned.
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_set_id_datasource(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_cstr_t						id_source
	);



/** @internal gnsdk_musicidmatch_query_set_lookup_fp @endinternal
  *
  * Set fingerprint data for a lookup request for a MusicID Match query.
  *
  * @param  musicid_match_query_handle		MusicID Match query handle this lookup request applies to
  * @param  ident								[in] identity string that must be unique for a query.
  *	@param  fp_data							[in] String representation of fingerprint data,
  *													must be a cantametrix fingerprint.
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_set_lookup_fp(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_cstr_t						ident,
	gnsdk_cstr_t						fp_data
	);


/** @internal gnsdk_musicidmatch_query_set_compare_fp @endinternal
  *
  * Set fingerprint data for a compare request for a MusicID Match query.
  *
  * @param  musicid_match_query_handle      MusicID Match query handle this compare request applies to
  * @param  ident                           [in] identity string that must be unique for a query.
  * @param  fp_data                         [in] String representation of fingerprint data,
  *													must be a Phillips macro fingerprint.
  *
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_set_compare_fp(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_cstr_t						ident,
	gnsdk_cstr_t						fp_data
	);


/** @internal gnsdk_musicidmatch_query_set_compare_data @endinternal
  * Set id data for a compare request for a MusicID Match query.
  *
  * @param  musicid_match_query_handle      MusicID Match query handle this compare request applies to
  * @param  ident                           [in] identity string that corresponds to the ident and fingerprint data set
  *													with gnsdk_musicidmatch_query_set_compare_fp
  *	@param id_data                          [in] the id data which has to be compared.
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_set_compare_data(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_cstr_t						ident,
	gnsdk_cstr_t						id_data
	);



/** @internal gnsdk_musicidmatch_query_option_set @endinternal
  *
  * Set an option for a given MusicID Match query handle.
  *
  * @param  musicid_match_query_handle	  MusicID Match query handle this option applies to
  * @param  option_key					  An option from the available MusicID Match option list.
  * @param  option_value				  Value to set for given option
  *
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_option_set(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_cstr_t						option_key,
	gnsdk_cstr_t						option_value
	);


/** @internal gnsdk_musicidmatch_query_option_get @endinternal
  *
  * Retrieve an option for a given MusicID Match query handle.
  *
  * @param  musicid_match_query_handle	   MusicID Match query handle to retrieve option from
  * @param  option_key					   An option from the available MusicID Match option list.
  * @param  p_option_value				   Pointer to value set for given option
  *
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_option_get(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_cstr_t						option_key,
	gnsdk_cstr_t*						p_option_value
	);



/** @internal gnsdk_musicidmatch_query_find_matches @endinternal
  *
  * Performs a MusicID Match query for the added lookup and compare requests.
  *
  * @param musicid_match_query_handle		[in] MusicID Match query handle to perform the query with
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_find_matches(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle
	);


/** @internal gnsdk_musicidmatch_query_get_response @endinternal
  *
  * Gets the result gdo for a given ident in a MusicID Match query.
  *
  * @param musicid_match_query_handle		[in] MusicID Match query handle to perform query with
  * @param ident								[in] ident used for adding requests to the query
  * @param p_response_gdo					[out] response gdo
  * @ingroup Music_MusicIDMatch_QueryFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_musicidmatch_query_get_response(
	gnsdk_musicidmatch_query_handle_t	musicid_match_query_handle,
	gnsdk_cstr_t						ident,
	gnsdk_gdo_handle_t*				p_response_gdo
	);



#ifdef __cplusplus
}
#endif

#endif /*_GNSDK_MUSICID_MATCH_H_*/
