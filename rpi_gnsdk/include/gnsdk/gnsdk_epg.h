/* Gracenote SDK: EPG public header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_EPG_H_
/* gnsdk_epg.h: primary interface for the EPG SDK
*/
#define _GNSDK_EPG_H_

#ifdef __cplusplus
#include <gnsdk_defines.h>
extern "C"{
#endif

/** @internal gnsdk_epg.h @endinternal
 * Primary interface for EPG SDK.
 * @ingroup Epg_HeaderFile
*/

/* Typedefs */

GNSDK_DECLARE_HANDLE( gnsdk_epg_query_handle_t );


#define GNSDK_EPG_POSTALCODE_COUNTRY_USA		"usa"
#define GNSDK_EPG_POSTALCODE_COUNTRY_CANADA		"can"
#define GNSDK_EPG_CHANNEL_ID_TYPE_DVB			"dvb"
#define GNSDK_EPG_SEARCH_FIELD_PROGRAM_TITLE	"epg_search_program_title"
#define GNSDK_EPG_OPTION_RESULT_RANGE_START		"epg_option_range_start"
#define GNSDK_EPG_OPTION_RESULT_RANGE_SIZE		"epg_option_range_size"


/** @internal GNSDK_EPG_OPTION_ENABLE_LINK_DATA @endinternal
*  Indicates whether a response includes any Link data (third-party metadata).
*  <p><b>Remarks:</b></p>
*  Link data is third-party metadata associated with the results (such as an Amazon ID or cover art
ID), configured specifically for your application. Contact your Gracenote Professional Services
representative about enabling this option.
*
*  Link data is supported in the following contexts:
*  <ul>
*  <li>GNSDK_GDO_TYPE_TVPROGRAM</li>
*  <li>GNSDK_GDO_TYPE_TVCHANNEL</li>
*  </ul>
*  All the listed contexts support these child and value GDOs:
*  <ul>
*  <li>GNSDK_GDO_CHILD_EXTERNAL_ID</li>
*  <li>GNSDK_GDO_VALUE_EXTERNALID_SOURCE</li>
*  <li>GNSDK_GDO_VALUE_EXTERNALID_TYPE</li>
*  <li>GNSDK_GDO_VALUE_EXTERNALID_VALUE</li>
*  </ul>
*
* @ingroup Video_Options
*/
#define GNSDK_EPG_OPTION_ENABLE_LINK_DATA				"gnsdk_epg_option_enable_link"


/** @internal gnsdk_epg_status_t @endinternal
  *   The status value of the current query, passed to
  *   gnsdk_epg_callback_fn.
* @ingroup Epg_TypesEnums
*/
typedef enum
{
	gnsdk_epg_status_unknown = 0,

	gnsdk_epg_status_query_begin = 10,
	gnsdk_epg_status_connecting = 20,
	gnsdk_epg_status_sending = 30,
	gnsdk_epg_status_receiving = 40,
	gnsdk_epg_status_query_complete = 100,
	gnsdk_epg_status_query_delete = 999

} gnsdk_epg_status_t;

/** @internal gnsdk_epg_callback_fn @endinternal
  *   Receive status updates as EPG data is retrieved.
  *   @param callback_userdata [in] Pointer to data passed in to the
  *                        <code>gnsdk_epg_query_create</code> function through the
  *                        <code>callback_userdata</code> parameter. This pointer must be
  *                        cast from the <code>gnsdk_void_t</code> type to its original type
  *                        to be accessed properly.
  *   @param epg_query_handle [in] EPG query handle that the callback operates on
  *   @param  status [in] One of <code>gnsdk_epg_status_t</code> values
  *   @param bytes_done [in] Current number of bytes transferred. Set to a
  *                        value greater than 0 to indicate progress, or 0 to
  *                        indicate no progress.
  *   @param bytes_total [in] Total number of bytes to be transferred. Set to
  *                        a value greater than 0 to indicate progress, or 0 to
  *                        indicate no progress.
  *   @param p_abort [out] Set dereferenced value to GNSDK_TRUE to abort
  *                        the operation invoking the callback
  *
* @ingroup Epg_Callbacks
*/
typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_epg_callback_fn)(
	const gnsdk_void_t*			callback_userdata,
	gnsdk_epg_query_handle_t	epg_query_handle,
	gnsdk_epg_status_t		status,
	gnsdk_size_t				bytes_done,
	gnsdk_size_t				bytes_total,
	gnsdk_bool_t*				p_abort
	);

/** @internal gnsdk_epg_initialize @endinternal
  *   Initializes the Gracenote EPG
  *   @param sdkmgr_handle [in] Handle from a successful <code>gnsdk_manager_initialize</code>
  *                   call
  *
* @ingroup Epg_Initialization_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_initialize(
	gnsdk_manager_handle_t sdkmgr_handle
	);

/** @internal gnsdk_epg_shutdown @endinternal
  *   Shuts down and release resources for the EPG
  *   library.
* @ingroup Epg_Initialization_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_shutdown(void);

/** @internal gnsdk_epg_get_version @endinternal
  *   Retrieves the EPG library's version string.
* @ingroup Epg_Initialization_Functions
*/
gnsdk_cstr_t	GNSDK_API	gnsdk_epg_get_version(void);

/** @internal gnsdk_epg_get_build_date @endinternal
  *   Retrieves the EPG library's build date string.
* @ingroup Epg_Initialization_Functions
*/
gnsdk_cstr_t	GNSDK_API	gnsdk_epg_get_build_date(void);

/******************************************************************************
 * EPG Query Handle
 ******************************************************************************/

/** @internal gnsdk_epg_query_create @endinternal
  *   Creates a EPG query handle.
  *   @param user_handle [in] User handle for the user requesting the
  *                            query
  *   @param callback_fn [in_opt] Callback function for status and
  *                            progress
  *   @param callback_userdata [in_opt] Data that is passed back through calls
  *                            to the callback functions
  *   @param p_epg_query_handle [out] Pointer to receive the EPG query handle
  *
* @ingroup Epg_Query_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_query_create(
	gnsdk_user_handle_t			user_handle,
	gnsdk_epg_callback_fn		callback_fn,
	const gnsdk_void_t*			callback_userdata,
	gnsdk_epg_query_handle_t*	p_epg_query_handle
	);

/** @internal gnsdk_epg_query_release @endinternal
  *   Invalidates and releases resources for a given EPG query handle.
  *   @param epg_query_handle [in] epg query handle to release
  *
* @ingroup Epg_Query_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_query_release(
	gnsdk_epg_query_handle_t	epg_query_handle
	);

/** @internal gnsdk_epg_query_option_set @endinternal
  *   Sets an option for a given EPG query handle.
  *   @param query_handle [in] EPG query handle to set option
  *                  for
  *   @param option_key [in] An option from the available EPG option keys
  *   @param option_value [in] A value that corresponds to the defined option key;
  *                  may be an alphabetical or numeric value, or one of the
  *                  available epg option keys
  *
* @ingroup Epg_Query_Functions
*/

gnsdk_error_t	GNSDK_API	gnsdk_epg_query_option_set(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_cstr_t				option_key,
	gnsdk_cstr_t				option_value
	);

/** @internal gnsdk_epg_query_option_get @endinternal
  *   Retrieves an option for a given EPG query handle
  *   @param query_handle [in] EPG query handle to retrieve
  *                    option from
  *   @param option_key [in] One of the EPG
  *                    to retrieve an option value for
  *   @param p_option_value [out] Pointer to receive an option value
  *
* @ingroup Epg_Query_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_query_option_get(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_cstr_t				option_key,
	gnsdk_cstr_t*				p_option_value
	);



/* SETTING QUERY PARAMETERS */


/** @internal gnsdk_epg_query_add_postalcode @endinternal
  *    Adds a postalcode to an EPG find_providers query.
  *   @param query_handle  [in] VideoID or Video Explore query handle this
  *                          text applies to
  *   @param postalcode_country [in] country postalcode applies to (Currently only GNSDK_EPG_POSTALCODE_COUNTRY_USA is supported
  *   @param postalcode [in] postalcode
  *
* @ingroup Epg_Query_Functions
*/

gnsdk_error_t	GNSDK_API	gnsdk_epg_query_set_postalcode(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_cstr_t				postalcode_country,
	gnsdk_cstr_t				postalcode
	);


/** @internal gnsdk_epg_query_add_channel_id @endinternal
  *    Adds a channel dvb triplet as input to an EPG <code>find_channels</code> query.  Multiple channels may be specified through subsequent calls to <code>gnsdk_epg_query_add_dvb</code>.
  *   @param query_handle  [in] EPG query handle
  *   @param id [in] ID string.  For DVB ids, the format is <pre>{@code {dvb|dvbs|dvbt|dbvc}://{onid}.{tsid}.{sid} }</pre>
  *   @param type [in] Type of channel id.  GNSDK_EPG_CHANNEL_ID_TYPE_DVB is currently the only supported value.
  *	  @param ident [in] Optional string indentifier, returned in the TVCHANNEL gdo, if this DVB triplet results in a match.
  *
* @ingroup Epg_Query_Functions
*/

gnsdk_error_t	GNSDK_API	gnsdk_epg_query_add_channel_id(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_cstr_t				type,
	gnsdk_cstr_t				id,
	gnsdk_cstr_t				ident
	);


/** @internal gnsdk_epg_query_add_channel @endinternal
  *    Adds a channel GDO as input to <code>find_airings</code> query.  Multiple channels may be specified through subsequent calls to <code>gnsdk_epg_query_add_channel</code>.
  *   @param query_handle  [in] EPG query handle this
  *                          text applies to
  *   @param channel_gdo [in] GDO that identifies a TV channel
  *   @param ident [in] optional identifier that gets passed back with this channel
  *
* @ingroup Epg_Query_Functions
*/

gnsdk_error_t	GNSDK_API	gnsdk_epg_query_add_tvchannel_gdo(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_gdo_handle_t			channel_gdo,
	gnsdk_cstr_t				ident
	);



/** @internal gnsdk_epg_query_set_gdo @endinternal
  *   Sets a GDO as input to an EPG <code>find_programs</code>, <code>find_airings</code> or <code>find_channels</code> query.
  *   @param query_handle  [in] EPG query handle
  *   @param query_gdo [in] GDO that identifies an EPG object (such as a
  *                          	 	program)
  * @ingroup Epg_Query_Functions
*/

gnsdk_error_t	GNSDK_API	gnsdk_epg_query_set_gdo(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_gdo_handle_t			query_gdo
	);




/** @internal gnsdk_epg_query_set_text @endinternal
  *   Sets a text as input to an EPG reques.
  *   @param query_handle [in] EPG query handle
  *   @param field [in] Which field to search on. Currently only GNSDK_EPG_SEARCH_FIELD_PROGRAM_TITLE is supported
  *   @param text [in] Text to search for
  * @ingroup Epg_Query_Functions
*/


gnsdk_error_t	GNSDK_API	gnsdk_epg_query_set_text(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_str_t					field,
	gnsdk_str_t					text
	);


/** @internal gnsdk_epg_query_set_time_start @endinternal
  *    Adds a start time range to EPG <code>find_airings</code> query
  *   @param query_handle [in] EPG query handle
  *   @param year [in] 		four digit year
  *   @param month [in]
  *   @param day [in]
  *   @param hour [in] 0 to 23.  Time is in UTC
  *   @param minute [in]
* @ingroup Epg_Query_Functions
*/



gnsdk_error_t	GNSDK_API	gnsdk_epg_query_set_time_start(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_uint32_t year,
	gnsdk_uint32_t month,
	gnsdk_uint32_t day,
	gnsdk_uint32_t hour,
	gnsdk_uint32_t minute
	);

/** @internal gnsdk_epg_query_set_time_end @endinternal
  *
  *    Adds a start end range to EPG <code>find_airings</code> query
  *
  *  @param  query_handle [in] EPG query handle
  *  @param  year [in]
  *  @param  month [in]
  *  @param  day [in]
  *  @param  hour [in] 0 to 23.  Time is in UTC
  *  @param  minute [in]
  * @ingroup Epg_Query_Functions
*/

gnsdk_error_t	GNSDK_API	gnsdk_epg_query_set_time_end(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_uint32_t year,
	gnsdk_uint32_t month,
	gnsdk_uint32_t day,
	gnsdk_uint32_t hour,
	gnsdk_uint32_t minute
	);


/* Time functions */

/* gnsdk_epg_timestamp_parse
 *
 * 		Converts a gnsdk timestamp string taken from a GDO into a set of integer values.
 *
 * @param 		timestamp 	[in] A timestamp value taken from a GDO.
 * 	@param 	year [out]	4 digit year
 * 	@param 	month [out]
 * 	@param 	day [out]
 * 	@param 	hour [out]	0-23  UTC time
 * 	@param 	minute [out]
 * 	@param 	second [out]
 */

gnsdk_error_t GNSDK_API	gnsdk_epg_timestamp_parse(
	gnsdk_cstr_t* timestamp,
	gnsdk_uint32_t* year,
	gnsdk_uint32_t* month,
	gnsdk_uint32_t* day,
	gnsdk_uint32_t* hour,
	gnsdk_uint32_t* minute,
	gnsdk_uint32_t* second
	);



/* FIND APIS */

/** @internal gnsdk_epg_query_find_programs @endinternal
  *
  *   Performs an EPG query for programs.
  *
  *   <p><b>Acceptable inputs</b></p>
  *
  * 	<code>gnsdk_epg_query_set_gdo</code> with GNSDK_GDO_TYPE_TVPROGRAM or GNSDK_GDO_TYPE_EXTENDED_DATA with TUI_TYPE=TVPROGRAM
  *
  *   <p><b>GDO Response</b></p>
  *   	GNSDK_GDO_TYPE_RESPONSE_TVPROGRAM with 1 or none GNSDK_GDO_TYPE_TVPROGRAM
  *
  *  @param  query_handle [in] EPG query handle to perform query
  *  @param  p_response_gdo [out] Pointer to receive the GDO handle with the
  *                          response
  *
* @ingroup Epg_Query_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_query_find_programs(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_gdo_handle_t*			p_response_gdo
	);





/** @internal gnsdk_epg_query_find_tvproviders @endinternal
  *
  *   Performs an EPG query for television providers.  Only for NA data.
  *
  *   <p><b>Acceptable inputs</b></p>
  *
  * 	<code>gnsdk_epg_query_set_postalcode</code>
  *
  * 	Response GDO type  GNSDK_GDO_TYPE_RESPONSE_TV_PROVIDER, containing potentially multiple GNSDK_GDO_TYPE_TV_PROVIDER
  *
  *
  * @param   query_handle [in] EPG query handle to perform query
  * @param   p_response_gdo [out] Pointer to receive the GDO handle with the
  *                         response
  *
* @ingroup Epg_Query_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_query_find_tvproviders(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_gdo_handle_t*			p_response_gdo
	);




/** @internal gnsdk_epg_query_find_channels @endinternal
  *
  *   Performs an EPG query for television channels.
  *
  *   <p><b>Acceptable inputs</b></p>
  *
  * 	<p><b>North America:</b></p>
  *		 	<code>gnsdk_epg_query_set_gdo</code> with GNSDK_GDO_TYPE_TV_PROVIDER
  *
  * 	<p><b>Europe:</b></p>
  * 		<code>gnsdk_epg_query_add_dvb</code> with 1 or more sets of DVB information
  *
  *
  * 	<p><b>GDO Response:</b></p>
  * 		GNSDK_GDO_TYPE_RESPONSE_TV_CHANNEL with many GNSDK_GDO_TYPE_RESPONSE_TV_CHANNEL
  *
  *  @param  query_handle [in] EPG query handle to perform query
  *  @param  p_response_gdo [out] Pointer to receive the GDO handle with the
  *                          response
  *
* @ingroup Epg_Query_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_query_find_channels(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_gdo_handle_t*			p_response_gdo
	);







/** @internal gnsdk_epg_query_find_tvairings @endinternal
  *
  *   Performs an EPG query for television airings.
  *
  *   <p><b>Required inputs</b></p>
  *		<code>gnsdk_epg_query_set_time_range</code> - Needs start and end time for 'tv grid data'<br>
  *		<code>gnsdk_epg_query_add_channel</code> - At least 1 channel must be added to the query
  *
  *
  *	  <p><b>Optional inputs (these are mutually exclusive)</b></p>
  *	    <code>gnsdk_epg_query_set_text</code> - Set text to search TITLEs for<br>
  *	    <code>gnsdk_epg_query_set_gdo</code> - Searches 'TV Grid' for TVAIRINGS that reference a particular
  *	    								GNSDK_GDO_TYPE_AV_WORK, GNSDK_GDO_TYPE_CONTRIBUTOR OR GNSDK_GDO_TYPE_SERIES
  *
  *
  * 	<p><b>GDO Response</b></p>
  * 		GNSDK_GDO_TYPE_RESPONSE_TV_AIRING with many GNSDK_GDO_TYPE_RESPONSE_TV_AIRING.
  *
  * 		Each airing contains  Program start and end time, channel, partial GNSDK_GDO_TYPE_TVPROGRAM
  *
  *
  *  @param   query_handle [in] EPG query handle to perform query
  *  @param  p_response_gdo [out] Pointer to receive the GDO handle with the
  *                          response
  *
* @ingroup Epg_Query_Functions
*/
gnsdk_error_t	GNSDK_API	gnsdk_epg_query_find_tvairings(
	gnsdk_epg_query_handle_t	query_handle,
	gnsdk_gdo_handle_t*			p_response_gdo
	);






#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_EPG_H_ */


