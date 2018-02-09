/* Gracenote SDK: GNSDK Manager Public Header File
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by USA and international patents.
*/

/* gnsdk_manager.h: Primary interface for the GNSDK Manager.
*/

#ifndef _GNSDK_MANAGER_H_
#define _GNSDK_MANAGER_H_

#ifdef __cplusplus
extern "C"{
#endif



/******************************************************************************
 * Typedefs
 ******************************************************************************/

/** @internal gnsdk_manager_handle_t @endinternal
*  Primary handle to GNSDK Manager. Retrieved from GNSDK Manager's gnsdk_manager_initialize() API. An
application must pass this handle to each Gracenote SDK on initialization.
*  This handle does not have to be released.
* @ingroup Manager_TypesEnums
*/
GNSDK_DECLARE_HANDLE( gnsdk_manager_handle_t );

/** @internal gnsdk_user_handle_t @endinternal
*  Handle to user identification. Created by the gnsdk_manager_user_create() APIs. An application must create this handle for each unique user
that calls the SDKs.
*  This handle must be released by gnsdk_manager_user_release().
* @ingroup Setup_Users_TypesEnums
*/
GNSDK_DECLARE_HANDLE( gnsdk_user_handle_t );


/******************************************************************************
 * SDK Manager APIs
 ******************************************************************************/

/** @internal gnsdk_manager_initialize @endinternal
*  Initializes the GNSDK Manager and retrieves the GNSDK Manager handle. You must initialize the
GNSDK Manager prior to calling any other GNSDK library.
*  This function can be called multiple times, however, all successful calls to
gnsdk_manager_initialize() must be paired with a call to gnsdk_manager_shutdown(). If
gnsdk_manager_initialize() returns an error, then gnsdk_manager_shutdown() must not be called. The final
call to gnsdk_manager_shutdown() releases the resources used by the GNSDK Manager.
*  As the GNSDK Manager manages the memory for the sdkmgr_handle value, the returned sdkmgr_handle
value does need not be released.
*  You can call this function with GNSDK_NULL for the p_sdkmgr_handle parameter if the GNSDK Manager
handle is not required to be returned at initialization.
*  The license_data and license_data_len parameters may be set to GNSDK_NULL and zero (0),
respectively, which initializes the SDK but does not apply the license data. This is necessary to
retrieve the sdkmgr_handle value for later SDK initializations. You must pass in valid license data
to this function before performing any queries with the any other GNSDK APIs.
*  Gracenote Professional Services provides a GNSDK license with the SDK.
*  @param p_manager_handle [out] Pointer to gnsdk_manager_handle_t that receives a GNSDK Manager
handle
*  @param license_data [in_opt] Text of a GNSDK license
*  @param  license_data_len [in_opt] Length of text of GNSDK license (in bytes) or one of the
Manager Initialization Flags.
*  @return SDKMGRERR_InvalidArg license_data_len parameter is 0 or overly large
*  @return SDKMGRERR_HandleObjectInvalid Given p_manager_handle is not a valid GNSDK Manager handle
*  @return SDKMGRERR_NoMemory System is out of memory
*  @return SDKMGRERR_InitFailed Initialization of one of the subsystems failed
*  @return SDKMGRERR_NoError Initialization succeeded
* @ingroup Setup_Initialization_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_initialize(
	gnsdk_manager_handle_t*		p_manager_handle,
	const gnsdk_char_t*			license_data,
	gnsdk_size_t				license_data_len
	);

/** @internal GNSDK_MANAGER_LICENSEDATA_NULLTERMSTRING @endinternal
*  Indicates the provided license data is a properly null-terminated string.
*  Passing this value to gnsdk_manager_initialize() for the license_data_len parameter indicates the
license_data parameter points to a valid null-terminated string containing the full license data.
The length of the license data is computed by the SDK.
*  Example
*  error = gnsdk_manager_initialize(&sdkmgr_handle, license_data,
GNSDK_MANAGER_LICENSEDATA_NULLTERMSTRING);
* @ingroup Setup_Initialization_LicenseDataFlags
*/
#define GNSDK_MANAGER_LICENSEDATA_NULLTERMSTRING	(gnsdk_size_t)-1

/** @internal GNSDK_MANAGER_LICENSEDATA_FILENAME @endinternal
*  Indicates the provided license data is a relative or absolute path and filename to the license
file.
*  GNSDK_MANAGER_LICENSEDATA_FILENAME
*  Passing this value to gnsdk_manager_initialize() for the license_data_len parameter indicates the
license_data parameter points to a valid null-terminated string containing the path of a file
containing the license data. The file contents are read by the SDK and applied as license data.
*  Example
*  error = gnsdk_manager_initialize(&sdkmgr_handle, "path/my_license.txt",
GNSDK_MANAGER_LICENSEDATA_FILENAME);
* @ingroup Setup_Initialization_LicenseDataFlags
*/
#define GNSDK_MANAGER_LICENSEDATA_FILENAME			(gnsdk_size_t)-2

/** @internal GNSDK_MANAGER_LICENSEDATA_STDIN @endinternal
*  Indicates license data is provided through standard input (stdin).
*  Passing this value to gnsdk_manager_initialize for the license_data_len parameter
*  indicates that license data is provided through stdin; in this case, the license_data parameter
is ignored. The SDK reads from stdin and applies any received data as license data.
*  Example
*  error = gnsdk_manager_initialize(&sdkmgr_handle, GNSDK_NULL, GNSDK_MANAGER_LICENSEDATA_STDIN);
* @ingroup Setup_Initialization_LicenseDataFlags
*/
#define GNSDK_MANAGER_LICENSEDATA_STDIN				(gnsdk_size_t)-3


/** @internal gnsdk_manager_shutdown @endinternal
*  Shuts down and releases resources used by the GNSDK Manager.
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_NoError Shut down succeeded
*  All gnsdk_manager_shutdown calls must be paired with a previous call to gnsdk_manager_initialize().
The final gnsdk_manager_shutdown call results in the GNSDK Manager and all other GNSDK libraries
being shut down; all GNSDK APIs cease to function until the GNSDK Manager and libraries are again
initialized.
* @ingroup Setup_Initialization_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_shutdown(void);

/** @internal gnsdk_manager_get_version @endinternal
*  Retrieves the GNSDK Manager version string.
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
*  Major: New functionality
*  Minor: New or changed features
*  Improvement: Improvements and fixes
*  Build: Internal build number
* @ingroup Setup_Initialization_Functions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_manager_get_version(void);

/** @internal gnsdk_manager_get_product_version @endinternal
*  Retrieves the product version string.
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
*  Major: New functionality
*  Minor: New or changed features
*  Improvement: Improvements and fixes
*  Build: Internal build number
* @ingroup Setup_Initialization_Functions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_manager_get_product_version(void);

/** @internal gnsdk_manager_get_build_date @endinternal
*  Retrieves the GNSDK Manager's build date string.
*  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example: 2008-02-12 00:41 UTC
* @ingroup Setup_UtilityFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_manager_get_build_date(void);

/** @internal gnsdk_manager_get_globalid_magic @endinternal
*  Retrieves the GNSDK Manager Global-ID Magic number string.
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example: GNN1
* @ingroup Setup_UtilityFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_manager_get_globalid_magic(void);

/** @internal gnsdk_manager_string_free @endinternal
*  Frees the memory associated with an GNSDK Manager-provided serialized string or XML string.
*  Passing a null string value returns SDKMGRERR_NoError.
*  @param string [in] Pointer to string buffer to free
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize() was not successfully initiated
*  @return SDKMGRERR_HandleObjectInvalid Given string parameter is not a string value returned by
GNSDK that should be freed
*  @return SDKMGRERR_NoError String was successfully freed
* @ingroup Manager_UtilityFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_string_free(
	gnsdk_str_t				string
	);

/******************************************************************************
 * SDK Manager 'User Handle' APIs
 ******************************************************************************/

/** @internal gnsdk_manager_user_create @endinternal
*  Reconstitutes user handle from serialized user handle data.
*  Use this function to reconstitute a previously serialized user handle. Reconstitution does not
count towards the user count for your client in Gracenote Service.
*  @param serialized_user [in] String of serialized user handle data
*  @param p_user_handle [out] Pointer to receive user handle
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize() was not successfully initiated
*  @return SDKMGRERR_InvalidArg Serialized user string is empty, or given value for p_user_handle is
null
*  @return SDKMGRERR_InvalidFormat Serialized user string is invalid
*  @return SDKMGRERR_NoError User handle was successfully created
* @ingroup Setup_Users_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_user_create(
	gnsdk_cstr_t				serialized_user,
	gnsdk_user_handle_t*		p_user_handle
	);

/** @internal gnsdk_manager_user_create_new @endinternal
*  Creates a new user and also increments the user's Client ID user count with Gracenote Service.
*  Use this function to create a new user; when successful, this call registers a new user user for
a specified client in Gracenote Service. Once the new user is registered and the user count
incremented in Gracenote Service, the count cannot be reduced, nor can the same user be
re-retrieved.
*  Newly registered user handles must be serialized and stored locally for that user to be used
again for future queries; failing to do this quickly depletes the client's allotted user quota
within Gracenote Service.
*  @param client_id [in] Client ID that initiates requests with this handle; value provided by
Gracenote
*  @param client_id_tag [in] Client ID tag value that matches client ID; value provided by Gracenote
*  @param client_app_ver [in] Client application version; numeric value provided by application, and
this value is required
*  @param p_user_handle [out] Pointer to receive new user handle
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize() was not successfully initiated
*  @return SDKMGRERR_InvalidArg Given value for p_user_handle is invalid
*  @return SDKMGRERR_HandleObjectInvalid Given client handle is not a valid handle
*  @return SDKMGRERR_HandleObjectWrongType Given client handle is not a valid client handle type
*  @return SDKMGRERR_CommunicationsError Connection to Gracenote Service failed
*  @return SDKMGRERR_NoError New user registration was successfully created
* @ingroup Setup_Users_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_user_create_new(
	gnsdk_cstr_t			client_id,
	gnsdk_cstr_t			client_id_tag,
	gnsdk_cstr_t			client_app_ver,
	gnsdk_user_handle_t*	p_user_handle
	);

/** @internal gnsdk_manager_user_serialize @endinternal
*  Serializes a user handle into encrypted text that the application can store locally for future
use.
*  Applications must use this function to serialize newly registered user handles in order to store
the user handle locally for use in future queries. Failing to do this will quickly use up your
client's allotted user quota with Gracenote Service.
*  Use gnsdk_manager_string_free() to free the serialized string when application is finished using
it.
*  @param user_handle [in] User handle to serialize
*  @param p_serialized_user [out] Pointer to receive serialized user handle string
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize() was not successfully initiated
*  @return SDKMGRERR_InvalidArg Given value for p_serialzed_user is null
*  @return SDKMGRERR_HandleObjectInvalid Given user handle is not a valid handle
*  @return SDKMGRERR_HandleObjectWrongType Given user handle is not a valid user handle type
*  @return SDKMGRERR_NoError User handle was successfully serialized
* @ingroup Setup_Users_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_user_serialize(
	gnsdk_user_handle_t	user_handle,
	gnsdk_str_t*		p_serialized_user
	);

/** @internal gnsdk_manager_user_option_set @endinternal
*  Sets an option for a given user handle.
*  Options can be set per user handle, or globally.
*  @param user_handle [in] User handle that this option applies to. To apply this option globally,
set this parameter to GNSDK_NULL
*  @param option_name [in] A defined User Options name
*  @param option_value [in] Value to set for the given option
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize() was not successfully initiated
*  @return SDKMGRERR_HandleObjectInvalid Given user handle is not a valid handle
*  @return SDKMGRERR_HandleObjectWrongType Given user handle is not a valid user handle type
*  @return SDKMGRERR_NoError User option was successfully set
* <p><b>Note:</b></p>
*   Options set globally apply only to user handles created after the global option is set.
* @ingroup Setup_Users_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_user_option_set(
	gnsdk_user_handle_t	user_handle,
	gnsdk_cstr_t		option_name,
	gnsdk_cstr_t		option_value
	);

/** @internal gnsdk_manager_user_option_get @endinternal
*  Retrieves an option for a given user handle.
*  Options set globally are retrieved when the user handle parameter is set to GNSDK_NULL,
otherwise, options are retrieved for given a valid user handle.
*  @param user_handle [in] User handle to retrieve option from. To retrieve a global option, set
this parameter to GNSDK_NULL
*  @param option_name [in] A defined User Options name
*  @param p_option_value [out] Pointer to value set for the given option
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize() was not successfully initiated
*  @return SDKMGRERR_HandleObjectInvalid Given user handle is not a valid handle
*  @return SDKMGRERR_HandleObjectWrongType Given user handle is not a valid user handle type
*  @return SDKMGRERR_NoError User option was successfully retrieved
* @ingroup Setup_Users_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_user_option_get(
	gnsdk_user_handle_t	user_handle,
	gnsdk_cstr_t		option_name,
	gnsdk_cstr_t*		p_option_value
	);

/** @internal GNSDK_USER_OPTION_LOOKUP_MODE @endinternal
  * Sets the user option for lookups. Possible options are #GNSDK_LOOKUP_MODE_ONLINE, #GNSDK_LOOKUP_MODE_ONLINE_NOCACHE,
  * and #GNSDK_LOOKUP_MODE_LOCAL.
  * @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_LOOKUP_MODE			"gnsdk_useroption_lookup_mode"

/** @internal GNSDK_LOOKUP_MODE_ONLINE @endinternal
  * This is the default mode. If a cache exists, the query checks it first for a match.
  * If a no match is found in the cache, then the online Gracenote Service is queried.
  * If a result is found there, it is stored in the local cache.  If no online provider exists, the query will fail.
  * Use the #GNSDK_USER_OPTION_CACHE_EXPIRATION option to set the length of time before a
  * cache lookup times out.
  * @ingroup Setup_Users_Options
*/
	#define GNSDK_LOOKUP_MODE_ONLINE				"gnsdk_lookupmode_online"

/** @internal GNSDK_LOOKUP_MODE_ONLINE_NOCACHE @endinternal
  * This mode forces the query to be done online only and will not perform a local cache lookup first.
  * If no online provider exists, the query will fail. If a storage provider has been initialized,
  * queries and lists are immediately written to local storage, but are never read unless the lookup mode is changed.
  * @ingroup Setup_Users_Options
*/
	#define GNSDK_LOOKUP_MODE_ONLINE_NOCACHE		"gnsdk_lookupmode_online_nocache"

/** @internal GNSDK_LOOKUP_MODE_LOCAL @endinternal
  * This mode forces the lookup to be done against the local database only. Local lookups and local caches are used.
  * If no local database exists, the query will fail.
  * Use the #GNSDK_USER_OPTION_CACHE_EXPIRATION option to set the length of time before a
  * cache lookup times out.
  * @ingroup Setup_Users_Options
*/
	#define GNSDK_LOOKUP_MODE_LOCAL					"gnsdk_lookupmode_local"


/** @internal GNSDK_USER_OPTION_PROXY_HOST @endinternal
*  Sets host name for proxy to route GNSDK queries through.
*  To be used as option_name parameter for gnsdk_manager_user_option_set()
*  and gnsdk_manager_user_option_get().
*  Value for this option is a fully qualified host name with optional port number. If no port number
is given the default port number is assumed to be 80.
*  Example Option Values http://proxy.mycompany.com:8080/ proxy.mycompany.com:8080
*  proxy.mycompany.com
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_PROXY_HOST			"gnsdk_useroption_proxy_host"

/** @internal GNSDK_USER_OPTION_PROXY_USER @endinternal
*  Sets user name for proxy to route GNSDK queries through.
*  To be used as option_name parameter for gnsdk_manager_user_option_set()
*  and gnsdk_manager_user_option_get().
*  Value for this option is the valid user name for the proxy server. Do not set this option if a
user name is not required.
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_PROXY_USER			"gnsdk_useroption_proxy_username"

/** @internal GNSDK_USER_OPTION_PROXY_PASS @endinternal
*  Sets password for proxy to route GNSDK queries through.
*  To be used as option_name parameter for gnsdk_manager_user_option_set()
*  and gnsdk_manager_user_option_get().
*  Value for this option is the valid password for the proxy server. Do not set this option if a
password is not required.
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_PROXY_PASS			"gnsdk_useroption_proxy_password"

/** @internal GNSDK_USER_OPTION_NETWORK_TIMEOUT @endinternal
*  Sets the network timeout for all GNSDK queries. Option value is in milliseconds.
*  To be used as option_name parameter for gnsdk_manager_user_option_set()
*  and gnsdk_manager_user_option_get().
*  Value for this option is a string with a numeric value that indicates the number of milliseconds
to set for network timeouts.
*  Example Option Values
*  For 30-second timeout, set option value as "30000."
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_NETWORK_TIMEOUT		"gnsdk_useroption_network_timeout"

/** @internal GNSDK_USER_OPTION_NETWORK_LOADBALANCE @endinternal
*  Enables distributing queries across multiple Gracenote co-location facilities. When not enabled,
queries will generally resolve to a single co-location.
*  To implement load balancing, enable the GNSDK_USER_OPTION_NETWORK_LOADBALANCE option with the
gnsdk_manager_user_option_set() and gnsdk_manager_user_option_get() functions.
*  Value to enable this option must be a boolean value that indicates true.
* <p><b>Note:</b></p>
*   Ensure that any security settings (such as a firewall) in your network infrastructure do not
affect outbound access and prevent GNSDK from transmitting queries to various hosts with unique IP
addresses.
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_NETWORK_LOADBALANCE	"gnsdk_useroption_network_loadbalance"

/** @internal GNSDK_USER_OPTION_LOCATION_ID @endinternal
*  Sets an IP address or country code to represent the location of user performing requests.
*  To be used as option_name parameter for gnsdk_manager_user_option_set()
*  and gnsdk_manager_user_option_get().
*  Value for this option is a string with the IP address, or a 3-character country code for the
client making the request. This is generally required when setting a proxy for GNSDK queries.
*  Example Option Values
*  "192.168.1.1" "usa"
*  "jpn"
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_LOCATION_ID			"gnsdk_useroption_location_id"

/** @internal GNSDK_USER_OPTION_INFO_SDK @endinternal
  * Sets the SDK version of the device running the SDK. Used mostly by Gracenote Service to collect runtime statistics.
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_INFO_SDK				"gnsdk_useroption_info_sdk"

/** @internal GNSDK_USER_OPTION_INFO_MFG @endinternal
  * Sets the manufacturer of the device running the SDK. Used mostly by Gracenote Service to collect runtime statistics.
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_INFO_MFG				"gnsdk_useroption_info_mfg"

/** @internal GNSDK_USER_OPTION_INFO_OS @endinternal
  * Sets the OS version of the device running the SDK. Used mostly by Gracenote Service to collect runtime statistics.
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_INFO_OS				"gnsdk_useroption_info_os"

/** @internal GNSDK_USER_OPTION_INFO_UID @endinternal
  * Sets the Unique ID of the device running the SDK, such as ESN. Used mostly by Gracenote Service to collect runtime statistics.
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_INFO_UID				"gnsdk_useroption_info_uid"

/** @internal GNSDK_USER_OPTION_CACHE_EXPIRATION @endinternal
*  Sets the maximum duration for which an item in the GNSDK query cache is valid. This duration is in
seconds, and must exceed one day.
*  To be used as an option_name parameter for gnsdk_manager_user_option_set()
*  and gnsdk_manager_user_option_get().
*  The value set for this option is a string with a numeric value that indicates the number of
seconds to set for the expiration of cached queries. The maximum duration is set by Gracenote and
varies by requirements.
* <p><b>Note:</b></p>
*  Setting this option to a zero value (0) causes the cache to start deleting records upon cache
hit, and not write new or updated records to the cache; in short, the cache effectively flushes
itself. The cache will start caching records again once this option is set to a value greater than
0. Setting this option to a value less than 0 (for example: -1) causes the cache to use default
expiration values.
*  This value only has an effect if the application initializes a GNSDK caching library. See SQLite
for information on a caching implementation.
*  Example Option Values
*  For a one day expiration, set an option value of "86400" (60 seconds * 60 minutes * 24 hours).
*  For a seven day expiration set an option value of "604800" (60 seconds * 60 minutes * 24 hours *
7 days).
* @ingroup Setup_Users_Options
*/
#define GNSDK_USER_OPTION_CACHE_EXPIRATION		"gnsdk_useroption_cache_expiration"



/** @internal gnsdk_manager_user_release @endinternal
*  Releases resources for a user handle.
*  This function only frees handle resources; it has no affect on the user count in Gracenote
Service. Passing a null handle returns SDKMGRERR_NoError.
*  @param user_handle [in] User handle to release
*  @param p_serialized_user [in] Serialized user handle data
*  @return SDKMGRERR_NotInited gnsdk_manager_initialize was not successfully initiated
*  @return SDKMGRERR_HandleObjectInvalid Given user handle is not a valid handle
*  @return SDKMGRERR_HandleObjectWrongType Given user handle is not a valid user handle type
*  @return SDKMGRERR_NoError User handle was successfully released
* @ingroup Setup_Users_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_manager_user_release(
	gnsdk_user_handle_t	user_handle,
	gnsdk_str_t*		p_serialized_user
	);



/******************************************************************************
 * SDK Manager 'Error Info' APIs
 ******************************************************************************/

/** @internal gnsdk_error_info_t @endinternal
*  Error Info structure returned by the gnsdk_manager_error_info() API.
*  This structure does not have to be released.
* <p><b>Note:</b></p>
*   Ensure that callback functions that access the same global variable(s) use serialized access
methods to the shared variable(s).
* @ingroup Manager_ErrorManagement_TypesEnums
*/
typedef struct
{
	/** @internal error_code @endinternal
	  *
	  *   Last error code for given handle.
	  * @ingroup Manager_ErrorManagement_TypesEnums
	*/
	gnsdk_error_t	error_code;

	/** @internal source_error_code @endinternal
	  *
	  *   Source error code - internal to SDK error code.
	  * @ingroup Manager_ErrorManagement_TypesEnums
	*/
	gnsdk_error_t	source_error_code;

	/** @internal error_description @endinternal
	  *
	  *   String description for error code.
	  * @ingroup Manager_ErrorManagement_TypesEnums
	*/
	gnsdk_cstr_t	error_description;

	/** @internal error_api @endinternal
	  *
	  *   Error API.
	  * @ingroup Manager_ErrorManagement_TypesEnums
	*/
	gnsdk_cstr_t	error_api;

} gnsdk_error_info_t;


/** @internal gnsdk_manager_error_info @endinternal
*  Retrieves any available extended error information for the current thread.
*  To retrieve any extended error information, the application must call this function immediately
after receiving an error from a Gracenote SDK API. Though not all APIs provide extended error
information, at a minimum, the structure contains the description string for the error.
*  @return Note Returns a pointer to the populated gnsdk_error_info_t structure.
* @ingroup Manager_ErrorManagement_Functions
*/
const gnsdk_error_info_t* GNSDK_API
gnsdk_manager_error_info(void);

/*
 * Languages - (based on ISO 639-2 language identifiers - including some locally defined by Gracenote)
 */

/** @internal GNSDK_LANG_ENGLISH @endinternal
*  Language value for English.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_ENGLISH				"eng"

/** @internal GNSDK_LANG_CHINESE_SIMP @endinternal
*  Language value for Simplified Chinese.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_CHINESE_SIMP			"qtb"

/** @internal GNSDK_LANG_CHINESE_TRAD @endinternal
*  Language value for Traditional Chinese.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_CHINESE_TRAD			"qtd"

/** @internal GNSDK_LANG_DUTCH @endinternal
*  Language value for Dutch.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_DUTCH				"dut"

/** @internal GNSDK_LANG_FRENCH @endinternal
*  Language value for French.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_FRENCH				"fre"

/** @internal GNSDK_LANG_GERMAN @endinternal
*  Language value for German.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_GERMAN				"ger"

/** @internal GNSDK_LANG_ITALIAN @endinternal
*  Language value for Italian.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_ITALIAN				"ita"

/** @internal GNSDK_LANG_JAPANESE @endinternal
*  Language value for Japanese.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_JAPANESE				"jpn"

/** @internal GNSDK_LANG_KOREAN @endinternal
*  Language value for Korean.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_KOREAN				"kor"
/** @internal GNSDK_LANG_PORTUGUESE_BRAZIL @endinternal
*  Language value for Brazilian Portuguese.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_PORTUGUESE_BRAZIL	"por"

/** @internal GNSDK_LANG_RUSSIAN @endinternal
*  Language value for Russian.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_RUSSIAN				"rus"

/** @internal GNSDK_LANG_SPANISH @endinternal
*  Language value for Spanish.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_SPANISH				"spa"

/** @internal GNSDK_LANG_SWEDISH @endinternal
*  Language value for Swedish.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_SWEDISH				"swe"

/** @internal GNSDK_LANG_THAI @endinternal
*  Language value for Thai.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_THAI					"tha"

/** @internal GNSDK_LANG_TURKISH @endinternal
*  Language value for Turkish.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_TURKISH				"tur"

/** @internal GNSDK_LANG_POLISH @endinternal
*  Language value for Polish.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_POLISH				"pol"

/** @internal GNSDK_LANG_FARSI @endinternal
*  Language value for Farsi.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_FARSI				"per"

/** @internal GNSDK_LANG_VIETNAMESE @endinternal
*  Language value for Vietnamese.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_VIETNAMESE			"vie"

/** @internal GNSDK_LANG_HUNGARIAN @endinternal
*  Language value for Hungarian.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_HUNGARIAN			"hun"

/** @internal GNSDK_LANG_CZECH @endinternal
*  Language value for Czech.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_CZECH				"cze"

/** @internal GNSDK_LANG_SLOVAK @endinternal
*  Language value for Slovak.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_SLOVAK				"slo"

/** @internal GNSDK_LANG_ROMANIAN @endinternal
*  Language value for Romanian.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_ROMANIAN				"rum"

/** @internal GNSDK_LANG_GREEK @endinternal
*  Language value for Greek.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_GREEK				"gre"

/** @internal GNSDK_LANG_ARABIC @endinternal
*  Language value for Arabic.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_ARABIC				"ara"

/** @internal GNSDK_LANG_BAHASA_INDONESIA @endinternal
*  Language value for Indonesian Bahasa.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_BAHASA_INDONESIA		"ind"

/** @internal GNSDK_LANG_FINNISH @endinternal
*  Language value for Finnish.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_FINNISH				"fin"

/** @internal GNSDK_LANG_NORWEGIAN @endinternal
*  Language value for Norwegian.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_NORWEGIAN			"nor"

/** @internal GNSDK_LANG_CROATIAN @endinternal
*  Language value for Croatian.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_CROATIAN				"scr"

/** @internal GNSDK_LANG_BULGARIAN @endinternal
*  Language value for Bulgaria.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_BULGARIAN			"bul"

/** @internal GNSDK_LANG_SERBIAN @endinternal
*  Language value for Serbian.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_SERBIAN				"scc"

/** @internal GNSDK_LANG_DANISH @endinternal
*  Language value for Danish.
*  The library uses these language values to request a preferred language for metadata, which is
retrieved from Gracenote. Currently, gnsdk_manager_list_retrieve() uses these values.
* @ingroup Manager_DisplayLanguages
*/
#define			GNSDK_LANG_DANISH				"dan"

/*
 * Regions
 */

/** @internal GNSDK_REGION_DEFAULT @endinternal
*  The default region for a list.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_DEFAULT			GNSDK_NULL

/** @internal GNSDK_REGION_GLOBAL @endinternal
*  The list is not related to any one specific region. This key is the GNSDK default locale region.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_GLOBAL				"gnsdk_region_global"

/** @internal GNSDK_REGION_US @endinternal
*  The list is related to the USA region.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_US					"gnsdk_region_us"

/** @internal GNSDK_REGION_JAPAN @endinternal
*  The list is related to the Japanese region.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_JAPAN				"gnsdk_region_japan"

/** @internal GNSDK_REGION_CHINA @endinternal
*  The list is related to the Chinese region.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_CHINA				"gnsdk_region_china"

/** @internal GNSDK_REGION_TAIWAN @endinternal
*  The list is related to the Taiwanese region.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_TAIWAN				"gnsdk_region_taiwan"

/** @internal GNSDK_REGION_KOREA @endinternal
*  The list is related to the Korean region.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_KOREA				"gnsdk_region_korea"

/** @internal GNSDK_REGION_EUROPE @endinternal
*  The list is related to the European region.
*  The SDK uses region, country, desciptor (how verbose) and group (e.g., Music) to specify what lists and
locale-dependent metadata should be returned from the Gracenote service. Currently, gnsdk_manager_list_retrieve() and
gnsdk_manager_load_locale() uses these values.
* @ingroup ListsandLocales_Regions
*/
#define			GNSDK_REGION_EUROPE				"gnsdk_region_europe"

/*
 * Descriptors
 */

/** @internal GNSDK_DESCRIPTOR_DEFAULT @endinternal
*  Retrieves default information for the locale.
* @ingroup ListsandLocales_Descriptors
*/
#define			GNSDK_DESCRIPTOR_DEFAULT		GNSDK_NULL

/** @internal GNSDK_DESCRIPTOR_SIMPLIFIED @endinternal
*  Retrieves simplified information for the locale.
* @ingroup ListsandLocales_Descriptors
*/
#define			GNSDK_DESCRIPTOR_SIMPLIFIED		"gnsdk_desc_simplified"

/** @internal GNSDK_DESCRIPTOR_DETAILED @endinternal
*  Retrieves detailed information for the locale.
* @ingroup ListsandLocales_Descriptors
*/
#define			GNSDK_DESCRIPTOR_DETAILED		"gnsdk_desc_detailed"




#ifdef __cplusplus
}
#endif

#endif /** @internal _GNSDK_MANAGER_H_ @endinternal
*  Primary interface for the GNSDK Manager.
*/

