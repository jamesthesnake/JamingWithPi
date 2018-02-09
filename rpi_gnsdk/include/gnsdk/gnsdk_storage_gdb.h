/** Gracenote SDK: Gary-DB public header file
  * Author:
  *   Copyright (c) 2011 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_GDB_H_
/** gnsdk_gdb.h: primary interface for the Gary-DB SDK
*/
#define _GNSDK_GDB_H_

#ifdef __cplusplus
extern "C"{
#endif

/*
 * gnsdk_gdb.h:	Gary-DB implementation of gnsdk_storage_provider_interface_t
 *
 */

/******************************************************************************
 * Typdefs
 ******************************************************************************/

/******************************************************************************
 * GNSDK DB Initialization * Access APIs
 ******************************************************************************/

/** gnsdk_storage_gdb_initialize
  * Summary:
  *   Initializes the DB library.
  * Parameters:
  *   sdkmgr_handle:  [in] Handle from successful gnsdk_manager_initialize
  *
*/
gnsdk_error_t	gnsdk_storage_gdb_initialize(
	gnsdk_manager_handle_t	sdkmgr_handle
    );

/** gnsdk_storage_gdb_shutdown
  * Summary:
  *   Shuts down and releases resources for the DB library.
*/
gnsdk_error_t	gnsdk_storage_gdb_shutdown();

/** gnsdk_storage_gdb_get_version
  * Summary:
  *   Retrieves the version string of DB for GNSDK.
*/
gnsdk_cstr_t	gnsdk_storage_gdb_get_version();

/** gnsdk_storage_gdb_get_build_date
  * Summary:
  *   Retrieves the build date string of DB for GNSDK.
*/
gnsdk_cstr_t	gnsdk_storage_gdb_get_build_date();

/** gnsdk_storage_gdb_get_db_version
  * Summary:
  *   Retrieves version string of GDB engine.
*/
gnsdk_cstr_t	gnsdk_storage_gdb_get_db_version();

/** gnsdk_storage_gdb_option_set
  * Summary:
  *   Sets an option specific to the GDB library.
  * Parameters:
  *   option_name:   [in] One of the available <link !!MACROS_gdb_option_keys, GDB option keys>
  *   option_value:  [in] Value to set for option name
  *
*/
gnsdk_error_t	gnsdk_storage_gdb_option_set(gnsdk_cstr_t option_name, gnsdk_cstr_t option_value);

/** gnsdk_storage_gdb_option_get
  * Summary:
  *   Retrieves an option set to the GDB library.
  * Parameters:
  *   option_name:     [in] One of the available <link !!MACROS_gdb_option_keys, GDB option keys>
  *   p_option_value:  [out] Pointer to receive the value set for option name
  *
*/
gnsdk_error_t	gnsdk_storage_gdb_option_get(gnsdk_cstr_t option_name, gnsdk_cstr_t* p_option_value);

/** GNSDK_GDB_OPTION_STORAGE_FOLDER
  * Summary:
  *
*/
#define	GNSDK_STORAGE_GDB_OPTION_STORAGE_FOLDER				"gnsdk_storage_gdb_storage_folder"



#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_GDB_H_ */

