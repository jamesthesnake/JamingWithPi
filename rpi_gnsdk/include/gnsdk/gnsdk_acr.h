/* Gracenote SDK: ACR public header file
  * Author:
  *   Copyright (c) 2011 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_ACR_H_
/* gnsdk_acr.h: primary interface for the ACR SDK.
 *  This is based on the gnsdk_streamid implementation.
*/
#define _GNSDK_ACR_H_

#ifdef __cplusplus
extern "C"{
#endif

/******************************************************************************
 * Typedefs
 ******************************************************************************/

/** @internal gnsdk_acr_query_handle_t @endinternal
  *
  * ACR Query Handle
  *
  * @ingroup Acr_TypesEnums
*/
GNSDK_DECLARE_HANDLE( gnsdk_acr_query_handle_t );

/** @internal gnsdk_acr_status_t @endinternal
  *
  * Status values passed to <code>gnsdk_acr_callback_status_fn</code> callback function.
* @ingroup Acr_TypesEnums
*/
typedef enum
{
/** @internal gnsdk_acr_status_debug @endinternal
* ACR status type of debug, for reporting debug information.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_debug				= 0,

/** @internal gnsdk_acr_status_query_begin @endinternal
* ACR query process is beginning.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_query_begin			= 10,

/** @internal gnsdk_acr_status_connecting @endinternal
* Connecting to the Gracenote Service.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_connecting				= 20,

/** @internal gnsdk_acr_status_sending @endinternal
* Sending ACR query data to the Gracenote Service.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_sending				= 30,

/** @internal gnsdk_acr_status_receiving @endinternal
* Receiving ACR result data from the Gracenote Service.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_receiving				= 40,

/** @internal gnsdk_acr_status_audio_fp_started @endinternal
* ACR audio fingerprint generation has started.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_audio_fp_started		= 45,

/** @internal gnsdk_acr_status_audio_fp_generated @endinternal
* ACR audio fingerprint status has been generated.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_audio_fp_generated		= 50,

/** @internal gnsdk_acr_status_audio_silent @endinternal
* The audio volume is determined to be silent.
* Fingerprinting will not take place.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_audio_silent			= 70,

/** @internal gnsdk_acr_status_silence_ratio @endinternal
*
* The silence to sound ratio.
* @ingroup Acr_TypesEnums
*
*/
	gnsdk_acr_status_silence_ratio			= 80,

/** @internal gnsdk_acr_status_non_pitched @endinternal
*
* Percentage of audio over the last several seconds that is non pitched
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_non_pitched			= 81,

/** @internal gnsdk_acr_status_music @endinternal
*
* Percentage of audio over the last several seconds that is music
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_music					= 82,

/** @internal gnsdk_acr_status_speech @endinternal
*
* Percentage of audio over the last several seconds that is speech
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_speech			= 83,

/** @internal gnsdk_acr_status_query_complete_local @endinternal
*
* ACR local authority query processing is complete.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_query_complete_local	= 100,

/** @internal gnsdk_acr_status_query_complete_online @endinternal
*
* ACR online authority query processing is complete.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_query_complete_online	= 110,

/** @internal gnsdk_acr_status_normal_match_mode @endinternal
*
* The SDK has switched out of No Match Mode
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_normal_match_mode			= 200,

/** @internal gnsdk_acr_status_no_match_mode @endinternal
*
*   There have been enough no matches that the SDK has switched
*   into "No Match" mode, where it does lookups less frequently.
*   This mode is desabled when a match happens or a manual
*   lookup is requested.
*   When this callback is sent, the "value1" parameter will contain
*   the current no match delay in seconds.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_no_match_mode				= 210,

/** @internal gnsdk_acr_status_error @endinternal
*
*   ACR status has an error.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_error					= 600,

/** @internal gnsdk_acr_status_transition @endinternal
*
*   ACR detected an audio transition.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_status_transition					= 700

} gnsdk_acr_status_t;



/** @internal gnsdk_acr_audio_alg_t @endinternal
*
*   Indicates the audio recognition algorithm.
* @ingroup Acr_TypesEnums
*/
typedef enum
{
/** @internal gnsdk_acr_audio_alg_unknown @endinternal
*
*   Audio algorithm type of unknown, the default state.
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_audio_alg_unknown	= 0,

/** @internal gnsdk_acr_audio_alg_1_3svlq @endinternal
*
*   Audio: 3-second blocks, very low quality (mobile audio).
* @ingroup Acr_TypesEnums
*/
	gnsdk_acr_audio_alg_1_3svlq,

	/** @internal gnsdk_acr_audio_alg_1_3smq @endinternal
	 *
	 *   Audio: 3-second blocks, medium quality (media monitoring).
	 * @ingroup Acr_TypesEnums
*/
	gnsdk_acr_audio_alg_1_3smq,

} gnsdk_acr_audio_alg_t;


/** @internal gnsdk_acr_video_alg_t @endinternal
*
*   Indicates the video recognition algorithm.
* @ingroup Acr_TypesEnums
*/
typedef enum
{
	/** @internal gnsdk_acr_video_alg_unknown @endinternal
	*
	*   Video algorithm type of unknown, the default state.
	* @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_video_alg_unknown	= 0,

	/** @internal gnsdk_acr_video_alg_1 @endinternal
	*
	*   Default.
	* @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_video_alg_1
} gnsdk_acr_video_alg_t;


/** @internal gnsdk_acr_audio_sample_format_t @endinternal
*
*   Indicates the application's audio sample format.
* @ingroup Acr_TypesEnums
*/
typedef enum
{
	/** @internal gnsdk_acr_audio_sample_format_pcm8 @endinternal
	 *
	 * Signed 8-bit PCM samples.
	 * @ingroup Acr_TypesEnums
*/
	gnsdk_acr_audio_sample_format_pcm8,

	/** @internal gnsdk_acr_audio_sample_format_pcm16 @endinternal
	 *
	 *   Signed 16-bit PCM samples.
	 * @ingroup Acr_TypesEnums
*/
	gnsdk_acr_audio_sample_format_pcm16,

} gnsdk_acr_audio_sample_format_t;


/** @internal gnsdk_acr_video_frame_format_t @endinternal
*
*   Indicates the application's video frame format.
* @ingroup Acr_TypesEnums
*/
typedef enum
{
	/** @internal gnsdk_acr_video_frame_format_grayscale @endinternal
	 *
	 * 1 channel 8 BPP
	 * @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_video_frame_format_grayscale,

	/** @internal gnsdk_acr_video_frame_format_rgb24 @endinternal
	 *
	 *   RGB 3 Channel 8 BPP
	 * @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_video_frame_format_rgb24,

	/** @internal gnsdk_acr_video_frame_format_bgr24 @endinternal
	 *
	 *   BGR 3 Channel 8 BPP
	 * @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_video_frame_format_bgr24,

	/** @internal gnsdk_acr_video_frame_format_rgba24 @endinternal
	 *
	 *   RGBA 4 Channel 8 BPP
	 * @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_video_frame_format_rgba24,

	/** @internal gnsdk_acr_video_frame_format_yuv422 @endinternal
	 *
	 *   YUK422 3 channel 2 bytes per pixel 8 BPP
	 * @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_video_frame_format_yuv422
} gnsdk_acr_video_frame_format_t;


/** @internal gnsdk_acr_match_source_t @endinternal
*
*   Indicates the source of the fingerprint match.
* @ingroup Acr_TypesEnums
*/
typedef enum
{
	/** @internal gnsdk_acr_match_source_none @endinternal
	*
	*   Fingerprint not matched.
	* @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_match_source_none = 0,

	/** @internal gnsdk_acr_match_source_online @endinternal
	*
	*   Fingerprint matched online through the Gracenote Service.
	* @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_match_source_online,

	/** @internal gnsdk_acr_match_source_local @endinternal
	*
	*   Fingerprint matched from local storage.
	* @ingroup Acr_TypesEnums
	*/
	gnsdk_acr_match_source_local

} gnsdk_acr_match_source_t ;


/** @internal gnsdk_acr_callback_status_fn @endinternal
  *
  * Callback function declaration for ACR progress status.
  * @param callback_userdata [in]  Value passed to the callback_userdata parameter of
  *                           the function this callback was passed to
  * @param acr_query_handle [in] ACR query handle that the callback
  *                           operates on
  * @param acr_status [in] One of the gnsdk_acr_status_t values
  * @param value1
  * @param value2
  * @param value3
  * @param error
  * @param message
  *
* @ingroup Acr_Callbacks
*/
typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_acr_callback_status_fn)(
	const gnsdk_void_t*				callback_userdata,
	gnsdk_acr_query_handle_t		acr_query_handle,
	gnsdk_acr_status_t				acr_status,
	gnsdk_size_t					value1,
	gnsdk_size_t					value2,
	gnsdk_flt32_t                   value3,
	gnsdk_error_t					error,
	gnsdk_cstr_t					message
	);

/** @internal gnsdk_acr_callback_result_fn @endinternal
  *
  * Parameter values vary, depending on the match result.
  *
  * @param callback_userdata      [in] Value passed to the <code>callback_userdata</code> parameter of
  *                               the function this callback was passed to
  * @param  acr_query_handle      [in] ACR query handle that the callback
  *                               operates on
  * @param  result_gdo            [in] GDO handle of match result
  * @param  match_source          [in] One of <code>gnsdk_acr_match_source_t</code> values
  * @param  match_count           [in] Total count of match results
  * @param  no_match_duration     [in] Duration of no match, in seconds
  *
* @ingroup Acr_Callbacks
*/

typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_acr_callback_result_fn)(
	const gnsdk_void_t*				callback_userdata,
	gnsdk_acr_query_handle_t		acr_query_handle,	/* stream instance */
	gnsdk_gdo_handle_t				result_gdo,			/* match result */
	gnsdk_acr_match_source_t		match_source,		/* match source*/
	gnsdk_uint32_t					match_count,		/* total of match results */
	gnsdk_flt32_t					no_match_duration	/* duration of no match */
	);



/** @internal gnsdk_acr_callbacks_s @endinternal
  *
  * Structure of callback functions for gnsdk_acr_query_create.
* @ingroup Acr_Callbacks
*/
typedef struct _gnsdk_acr_callbacks_s
{
	/** @internal callback_status @endinternal
	  *
	  * Status of callback.
	*/
	gnsdk_acr_callback_status_fn		callback_status;

	/** @internal callback_result @endinternal
	  *
	  * Result of callback.
	*/
	gnsdk_acr_callback_result_fn		callback_result;


} gnsdk_acr_callbacks_t;


/******************************************************************************
 * Initialization APIs
 ******************************************************************************/

/** @internal gnsdk_acr_initialize @endinternal
  *
  * Initializes the Gracenote ACR library.
  *
  * @param sdkmgr_handle   [in] Handle from successful <code>gnsdk_manager_initialize</code>
  *                   call
  *
* @ingroup Acr_Initialization_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_initialize(
	gnsdk_manager_handle_t sdkmgr_handle
	);

/** @internal gnsdk_acr_shutdown @endinternal
  *
  * Shuts down and releases resources for the ACR library.
* @ingroup Acr_Initialization_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_shutdown(void);

/** @internal gnsdk_acr_get_version @endinternal
  *
  * Retrieves the ACR library's version string.
* @ingroup Acr_Initialization_Functions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_acr_get_version(void);

/** @internal gnsdk_acr_get_build_date @endinternal
  *
  * Retrieves the ACR library's build date string.
* @ingroup Acr_Initialization_Functions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_acr_get_build_date(void);


/******************************************************************************
 * ACR Instance Handles
 ******************************************************************************/

/** @internal gnsdk_acr_query_create @endinternal
  *
  * Creates an ACR query handle.
  *
  * @param user_handle     [in] User handle for the user requesting the query
  * @param callbacks       [in_opt] Callback functions for status and results
  * @param callback_userdata  [in_opt] Data that is passed back through calls to
  *                        the callback functions
  * @param p_acr_query_handle [out] Pointer to receive the ACR query handle
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_create(
	gnsdk_user_handle_t				user_handle,
	gnsdk_acr_callbacks_t*			callbacks,
	const gnsdk_void_t*				callback_userdata,
	gnsdk_acr_query_handle_t*		p_acr_query_handle
	);

/** @internal gnsdk_acr_query_wait_for_complete @endinternal
  *
  * Waits for all pending input audio data to complete processing for an ACR
  * query handle before retrieving results.
  *
  * @param acr_query_handle   [in] ACR query handle to wait for
  * @param timeout            [in] Length of time to wait in milliseconds or an
  *                      infinite wait set with GNSDK_ACR_TIMEOUT_INFINITE
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_wait_for_complete(
	gnsdk_acr_query_handle_t		acr_query_handle,
	gnsdk_uint32_t					timeout
	);

/** @internal GNSDK_ACR_TIMEOUT_INFINITE @endinternal
  *
  * Value for infinite wait in call to <code>gnsdk_acr_query_wait_for_complete</code>.
  *
  *
* @ingroup Acr_Flags
*/
#define GNSDK_ACR_TIMEOUT_INFINITE					0xffffffff


/** @internal gnsdk_acr_query_release @endinternal
  *
  * Invalidates and releases resources for a given ACR query handle.
  *
  * @param acr_query_handle    [in] ACR query handle to release
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_release(
	gnsdk_acr_query_handle_t	acr_query_handle
	);


/******************************************************************************
 * ACR Option APIs
 ******************************************************************************/

/** @internal gnsdk_acr_query_option_set @endinternal
  *
  * Sets an option for a given ACR query handle.
  *
  * @param acr_query_handle   [in] ACR query handle to set option for
  * @param option_key         [in] An option from the available ACR query options
  * @param option_value       [in] String value that corresponds to the defined
  *                      option key
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_option_set(
	gnsdk_acr_query_handle_t	acr_query_handle,
	gnsdk_cstr_t					option_key,
	gnsdk_cstr_t					option_value
	);

/** @internal gnsdk_acr_query_option_get @endinternal
  *
  * Retrieves an option for a given ACR query handle.
  *
  * @param acr_query_handle  [in] ACR query handle to retrieve option from
  * @param option_key        [in] An option from the available ACR query options
  * @param p_option_value    [out] Pointer to receive option value
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_option_get(
	gnsdk_acr_query_handle_t	acr_query_handle,
	gnsdk_cstr_t					option_key,
	gnsdk_cstr_t*					p_option_value
	);




/* @internal GNSDK_ACR_OPTION_QUERY_BATCHSIZE @endinternal
  *
  *   Value for the number of fingerprint blocks to process for a fingerprint
  *   lookup.
  *
  *   Default is "1". This equals three seconds of audio.
  *
  * TODO - Make these internal (at least batchsize and trans sensitivity)
* @ingroup Acr_Options_Query
*/
//#define GNSDK_ACR_OPTION_QUERY_BATCHSIZE				"gnsdk_acr_query_batchsize"

/** @internal GNSDK_ACR_OPTION_MAXIMUM_TIME_BETWEEN_LOOKUPS @endinternal
  * @ingroup Acr_Options_Query
  */
#define GNSDK_ACR_OPTION_MAXIMUM_TIME_BETWEEN_LOOKUPS			"gnsdk_acr_max_time_btwn_lookup"

/** @internal GNSDK_ACR_OPTION_MAXIMUM_TIME_BETWEEN_LOCAL_LOOKUPS @endinternal
  * @ingroup Acr_Options_Query
  */
#define GNSDK_ACR_OPTION_MAXIMUM_TIME_BETWEEN_LOCAL_LOOKUPS		"gnsdk_acr_max_time_btwn_local_lookup"

/** @internal GNSDK_ACR_OPTION_TRANSITION_SENTIVITY @endinternal
  * @ingroup Acr_Options_Query
  */
#define GNSDK_ACR_OPTION_TRANSITION_SENTIVITY			"gnsdk_acr_trans_sensitivity"


/** @internal GNSDK_ACR_OPTION_NO_MATCH_COUNT @endinternal
  *
  *   Configurable number of no matches before increasing back off timer
  *
  *   Default is "60". This means after 60 no matches the SDK will go into
  *   no match mode
* @ingroup Acr_Options_NoMatch
*/
#define GNSDK_ACR_OPTION_NO_MATCH_COUNT					"gnsdk_acr_no_match_count"

/** @internal GNSDK_ACR_OPTION_NO_MATCH_TIME_INCREMEMNT @endinternal
  *
  *   Configurable time increment to add to back off timer
  *
  *   Default is "60". This means 60 seconds will be added to the time between
  *   lookups every time we have NO_MATCH_COUNT no matches.
  *
  *   Valid range is 8 to 2592000 seconds (30 days)
* @ingroup Acr_Options_NoMatch
*/
#define GNSDK_ACR_OPTION_NO_MATCH_TIME_INCREMEMNT		"gnsdk_acr_no_match_time_increment"

/** @internal GNSDK_ACR_OPTION_NO_MATCH_MAX_TIME @endinternal
  *
  *   Configurable maximum time for no match mode
  *
  *   Default value is 300 seconds (5 minutes). This means that we will stop applying the
  *   GNSD_ACR_OPTION_NO_MATCH_TIME_INCREMENT value after we have reached 300 seconds.
  *
  *   Valid range is 60 to 5184000 seconds (60 days)
* @ingroup Acr_Options_NoMatch
*/
#define GNSDK_ACR_OPTION_NO_MATCH_MAX_TIME				"gnsdk_acr_no_match_max_time"


/** @internal GNSDK_ACR_OPTION_OPTIMIZE @endinternal
  *
  *   Sets ACR queries to be optimized for speed or accuracy
  *
  *   Default value is for accuracy. Optimizing for speed could result in
  *   slightly faster responses but they will not be as accurate.
*/
#define GNSDK_ACR_OPTION_OPTIMIZE						"gnsdk_acr_optimize"

/** @internal GNSDK_ACR_VALUE_OPTIMIZE_FOR_DEFAULT @endinternal
  *
  *   Sets ACR queries to be optimized to the default (accuracy)
  *
  *   Default value is for accuracy. Optimizing for speed could result in
  *   slightly faster responses but they will not be as accurate.
*/
#define GNSDK_ACR_VALUE_OPTIMIZE_FOR_DEFAULT			"default"

/** @internal GNSDK_ACR_VALUE_OPTIMIZE_FOR_ACCURACY @endinternal
  *
  *   Sets if ACR queries should be optimized for accuracy.
  *
  *   Default value is for accuracy. Optimizing for speed could result in
  *   slightly faster responses but they will not be as accurate.
*/
#define GNSDK_ACR_VALUE_OPTIMIZE_FOR_ACCURACY			"accuracy"

/** @internal GNSDK_ACR_VALUE_OPTIMIZE_FOR_SPEED @endinternal
  *
  *   Sets if ACR queries should be optimized for speed.
  *
  *   Default value is for accuracy. Optimizing for speed could result in
  *   slightly faster responses but they will not be as accurate.
*/
#define GNSDK_ACR_VALUE_OPTIMIZE_FOR_SPEED				"speed"

/** @internal GNSDK_ACR_VALUE_OPTIMIZE_FOR_ADAPTIVE @endinternal
  *
  *   Sets if ACR queries should be optimized for adaptive querying.
  *
  *   Default value is for accuracy. Optimizing for speed could result in
  *   slightly faster responses but they will not be as accurate.
*/
#define GNSDK_ACR_VALUE_OPTIMIZE_FOR_ADAPTIVE			"adaptive"


/** @internal GNSDK_ACR_OPTION_LOOKUP_CACHE_ONLY @endinternal
  *
  *   Sets if ACR queries should lookup in the local cache only or cache and online
  *
  *   The value parameter would be either GNSDK_VALUE_TRUE or GNSDK_VALUE_FALSE
  *
  *   The default value if unset is GNSDK_VALUE_FALSE
  *
*/
#define GNSDK_ACR_OPTION_LOOKUP_CACHE_ONLY				"lookup_location_cache_only"



/******************************************************************************
 * ACR Streaming Inputs APIs
 ******************************************************************************/

/** @internal gnsdk_acr_query_init_audio_stream @endinternal
  *
  * Prepares query handle to receive audio data for recognition.
  *
  * @param acr_query_handle  [in] ACR query handle to initialize for
  *                           audio recognition
  * @param audio_alg              [in] One of <code>gnsdk_acr_audio_alg_t</code> values
  *                           that best describes the audio source
  * @param audio_sample_rate      [in] Sample rate of decoded audio data that is
  *                           written to the query handle
  * @param audio_sample_format    [in] One of <code>gnsdk_acr_audio_sample_format_t</code>
  *                           values that matches the sample format of the
  *                           decoded source audio data
  * @param audio_channels         [in] Number of audio channels for the audio data
  *                           that is written to the query handle
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_init_audio_stream(
	gnsdk_acr_query_handle_t			acr_query_handle,
	gnsdk_acr_audio_alg_t				audio_alg,
	gnsdk_uint32_t						audio_sample_rate,
	gnsdk_acr_audio_sample_format_t		audio_sample_format,
	gnsdk_uint32_t						audio_channels
	);


/** @internal gnsdk_acr_query_write_audio_data @endinternal
  *
  * Writes a buffer of decoded audio data to an ACR query handle for
  * recognition.
  *
  * @param  acr_query_handle  [in] ACR query handle to write audio data to
  * @param  audio_data        [in] Pointer to buffer of decoded audio data
  * @param  audio_data_bytes  [in] Size of buffer in bytes pointed to by <code>audio_data</code>
  * @param  timestamp         [in_opt] Time in seconds of the <code>audio_data</code> buffer's
  *                      starting point, relative to the time audio started
  *                      being written. For best results, enter 0.
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_write_audio_data(
	gnsdk_acr_query_handle_t	acr_query_handle,
	const gnsdk_void_t*			audio_data,
	gnsdk_size_t				audio_data_bytes,
	gnsdk_time_us_t				timestamp
	);


/** @internal gnsdk_acr_query_write_complete @endinternal
  *
  * Declares that the source audio data is complete, and there is no more
  * data for an ACR query handle.
  *
  * @param acr_query_handle  [in] ACR query handle
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_write_complete(
	gnsdk_acr_query_handle_t	acr_query_handle
	);

/** @internal gnsdk_acr_query_manual_lookup @endinternal
  *
  *  Declares that a fingerprint should be generated and a lookup performed
  *  as soon as possible.
  *
  * @param acr_query_handle  [in] ACR query handle
  *
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_manual_lookup(
	gnsdk_acr_query_handle_t	acr_query_handle
	);


/******************************************************************************
 * Fingerprint Input APIs
 ******************************************************************************/

/** @internal gnsdk_acr_query_set_fp_data @endinternal
  *
  * Allows setting of an existing precomputed fingerprint for ACR
  * processing.
  *
  * @param acr_query_handle  [in] ACR query handle
  * @param fp_data           _nt_
  * @param fp_data_type      _nt_
* @ingroup Acr_Query_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_acr_query_set_fp_data(
	gnsdk_acr_query_handle_t	acr_query_handle,
	gnsdk_cstr_t				fp_data,
	gnsdk_cstr_t				fp_data_type
	);


#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_ACR_H_ */
