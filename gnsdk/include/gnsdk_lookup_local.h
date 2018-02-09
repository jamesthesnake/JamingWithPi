/* Gracenote SDK: Lookup Local public header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
  */

#ifndef _GNSDK_LOOKUP_LOCAL_H_
/* gnsdk_lookup_local.h: Primary interface for the Lookup Local module.
 */
#define _GNSDK_LOOKUP_LOCAL_H_

#include "gnsdk_manager.h"

#ifdef __cplusplus
extern "C"{
#endif


/******************************************************************************
 * Initialization APIs
 ******************************************************************************/

/** @internal gnsdk_lookup_local_initialize @endinternal
  * Initializes the Lookup Local module.
  * This function must be successfully called before any calls to other Lookup Local APIs will succeed.
  * @param sdkmgr_handle [in] Handle from a successful gnsdk_manager_initialize() call.
  *
  * @return GNSDK_SUCCESS Initialization succeeded
  * @return error Initialization failed
  *
  * @ingroup Setup_LookupLocal_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_lookup_local_initialize(
	gnsdk_manager_handle_t sdkmgr_handle
	);

/** @internal gnsdk_lookup_local_shutdown @endinternal
  * Shuts down and release resources for the Lookup Local module.
  * gnsdk_lookup_local_shutdown must be called to shutdown this module;
  * all Lookup Local APIs cease to function until the module is again initialized.
  * @return GNSDK_SUCCESS Shutdown succeeded
  * @return error Shutdown failed
  *
  * @ingroup Setup_LookupLocal_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_lookup_local_shutdown(void);

/** @internal gnsdk_lookup_local_get_version @endinternal
  * Retrieves the Lookup Local module version string.
  * This API can be called at any time, even before initialization and after shutdown.
  * @return  Returns the version string for this module
  *
  * @ingroup Setup_LookupLocal_Functions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_lookup_local_get_version(void);

/** @internal gnsdk_lookup_local_get_build_date @endinternal
  * Retrieves the Lookup Local module's build date string.
  * This API can be called at any time, even before initialization and after shutdown.
  * @return Returns the build date string for this module
  *
  * @ingroup Setup_LookupLocal_Functions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_lookup_local_get_build_date(void);

/******************************************************************************
 * Lookup local storage management APIs
 ******************************************************************************/

/** @internal gnsdk_lookup_local_storage_compact @endinternal
  * Performs compaction on named local storage.
  * See @link StorageandCaching_General_StorageIDs Storage IDs @endlink for possible storage names.
  * @param storage_name [in] Local storage name
  * @return GNSDK_SUCCESS
  * @return error
  * @ingroup Storage_LookupLocal_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_lookup_local_storage_compact(
	gnsdk_cstr_t	storage_name
	);

/** @internal gnsdk_lookup_local_storage_location_set @endinternal
  * Set location for named local storage.
  * See @link StorageandCaching_General_StorageIDs Storage IDs @endlink for possible storage names.
  * <p><b>Remarks:</b></p>
  *  Storage location path can be absolute or relative.
  *  However, Windows CE developers will need to set the full path, since relative path is not supported in Windows CE.
  * @param storage_name [in] Local storage name
  * @param storage_location [in] String value of path to indicate location of storage
  * @return GNSDK_SUCCESS
  * @return error
  * @ingroup Storage_LookupLocal_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_lookup_local_storage_location_set(
	gnsdk_cstr_t	storage_name,
	gnsdk_cstr_t	storage_location
	);

/** @internal gnsdk_lookup_local_storage_validate @endinternal
  * Performs validation on named local storage.
  * @param storage_name [in] Local storage name
  * @param p_valid [out] Boolean value to indicate whether the storage is valid.
  * @return GNSDK_SUCCESS
  * @return error
  * @ingroup Storage_LookupLocal_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_lookup_local_storage_validate(
	gnsdk_cstr_t	storage_name,
	gnsdk_bool_t*	p_valid
	);

/** @internal gnsdk_lookup_local_storage_version_get @endinternal
  * Get version on named local storage.
  * @param storage_name [in] Local storage name
  * @param p_format_version [out] String value for format version.
  * @param p_source_db_id [out] String value for source Gracenote database version.
  * @param p_source_app_version [out] String value for source product or application version.
  * @param p_source_sdk_version [out] String value for underlying GNSDK version.
  * @return GNSDK_SUCCESS
  * @return error
  * @ingroup Storage_LookupLocal_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_lookup_local_storage_version_get(
	gnsdk_cstr_t	storage_name,
	gnsdk_cstr_t*	p_format_version,
	gnsdk_cstr_t*	p_source_db_id,
	gnsdk_cstr_t*	p_source_app_version,
	gnsdk_cstr_t*	p_source_sdk_version
	);

/** @internal GNSDK_LOOKUP_LOCAL_STORAGE_CONTENT @endinternal
  * Name of the local storage the SDK uses to query Gracenote Content.
  * @ingroup Storage_LookupLocal_StorageIDs
*/
#define GNSDK_LOOKUP_LOCAL_STORAGE_CONTENT			"gnsdk_lookup_local_stgcontent"

/** @internal GNSDK_LOOKUP_LOCAL_STORAGE_METADATA @endinternal
  * Name of the local storage the SDK uses to query Gracenote Metadata.
  * @ingroup Storage_LookupLocal_StorageIDs
*/
#define GNSDK_LOOKUP_LOCAL_STORAGE_METADATA			"gnsdk_lookup_local_stgmdata"

/** @internal GNSDK_LOOKUP_LOCAL_STORAGE_INDICES @endinternal
  * Name of the local storage the SDK uses to query Gracenote Indices.
  * @ingroup Storage_LookupLocal_StorageIDs
*/
#define GNSDK_LOOKUP_LOCAL_STORAGE_INDICES			"gnsdk_lookup_local_stgindex"

#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_LOOKUP_LOCAL_H_ */

