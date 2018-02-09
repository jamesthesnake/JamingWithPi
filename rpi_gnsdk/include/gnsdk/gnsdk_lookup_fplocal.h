/* Gracenote SDK: Lookup Fingerprint Local public header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
  */

#ifndef _GNSDK_LOOKUP_FPLOCAL_H_
/* gnsdk_lookup_local.h: Primary interface for the Lookup Fingerprint Local module.
 */
#define _GNSDK_LOOKUP_FPLOCAL_H_

#include "gnsdk_manager.h"

#ifdef __cplusplus
extern "C"{
#endif


#define GNSDK_LOOKUP_FPCACHE_STORAGE_METADATA			"gnsdk_lookup_fpcache_stgmdata"


/******************************************************************************
 * Initialization APIs
 ******************************************************************************/


gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_initialize(
	gnsdk_manager_handle_t sdkmgr_handle
	);

gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_shutdown(void);

gnsdk_cstr_t GNSDK_API
gnsdk_lookup_fplocal_get_version(void);

gnsdk_cstr_t GNSDK_API
gnsdk_lookup_fplocal_get_build_date(void);

/******************************************************************************
 * Lookup fingerprint local storage management APIs
 ******************************************************************************/

gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_deserialize_user_data(
	gnsdk_cstr_t serialized_user_data,
	gnsdk_byte_t **deserialized_user_data,
	gnsdk_uint32_t *deserialized_user_data_size
	);

gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_deserialize_free(
	gnsdk_byte_t *deserialized_user_data
	);


gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_storage_location_set(
	gnsdk_cstr_t storage_name,
	gnsdk_cstr_t storage_location
	);



typedef void
(GNSDK_CALLBACK_API *gnsdk_lookup_fplocal_bundle_read_fn)(
	gnsdk_void_t*	callback_data,
	gnsdk_byte_t*	buffer,
	gnsdk_size_t	buffer_size,
	gnsdk_size_t*	p_bytes_read,
	gnsdk_bool_t*   abort
	);


gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_bundle_ingest(
	gnsdk_void_t*						callback_data,
	gnsdk_lookup_fplocal_bundle_read_fn	bundle_read_fn
	);


gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_cache_clear(
	void
	);


gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_cache_count(
	gnsdk_uint32_t*	p_count
	);


gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_cache_enum(
	gnsdk_uint32_t	index,
	gnsdk_cstr_t*	p_bundle_id
	);


gnsdk_error_t GNSDK_API
gnsdk_lookup_fplocal_cache_delete(
	gnsdk_cstr_t	bundle_id
	);

#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_LOOKUP_FPLOCAL_H_ */

