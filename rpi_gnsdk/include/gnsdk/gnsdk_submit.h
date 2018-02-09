/* Gracenote SDK: Submit public header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

/** @internal gnsdk_submit.h @endinternal
 * Primary interface for the Submit SDK.
* @ingroup Submit_HeaderFile
*/

#ifndef _GNSDK_SUBMIT_H_
#define _GNSDK_SUBMIT_H_

#ifdef __cplusplus
extern "C"{
#endif

/******************************************************************************
 * Typedefs
 ******************************************************************************/

/** @internal gnsdk_submit_parcel_handle_t @endinternal
*  Handle to Submit parcel. Created by gnsdk_submit_parcel_create, the application must create this
handle to execute a submit.
* @ingroup Submit_TypesEnums
*/
GNSDK_DECLARE_HANDLE( gnsdk_submit_parcel_handle_t );

/** @internal gnsdk_submit_status_t @endinternal
*  The Submit callback function status values; indicates the status value of the submission or the
feature lookup, passed to gnsdk_submit_callback_fn.
* @ingroup Submit_TypesEnums
*/
typedef enum
{
/** @internal gnsdk_submit_status_unknown @endinternal
*   Submission status is unknown; this is the initial callback state.
* @ingroup Submit_TypesEnums
*/
  gnsdk_submit_status_unknown = 0,

/** @internal gnsdk_submit_status_submit_begin @endinternal
*   Indicates Submit is beginning a new network transaction.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_status_submit_begin = 10,

/** @internal gnsdk_submit_status_connecting @endinternal
*   Indicates Submit is connecting.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_status_connecting = 20,


/** @internal gnsdk_submit_status_sending @endinternal
*   Indicates Submit is sending parcel data.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_status_sending = 30,

/** @internal gnsdk_submit_status_receiving @endinternal
*   Indicates Submit is receiving parcel data.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_status_receiving = 40,

	/** @internal gnsdk_submit_status_disconnected @endinternal
	 *   Indicates Submit is disconnecting a network connection
	 * @ingroup Music_MusicID_TypesEnums
*/
	gnsdk_submit_status_disconnected = 50,

	/** @internal gnsdk_submit_status_submit_complete @endinternal
*   Indicates Submit has completed the network transaction.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_status_submit_complete = 100

} gnsdk_submit_status_t;

/** @internal gnsdk_submit_callback_fn @endinternal
*  Retrieve Submit status updates as content.
*  @param user_data [in] Pointer to data passed in to the gnsdk_submit_parcel_create function
through the callback_userdata parameter. This pointer must be cast from the gnsdk_void_t type to its
original type to be accessed properly.
*  @param parcel_handle [in] Submit parcel handle that the callback operates on
*  @param status [in] One of gnsdk_submit_status_t values
*  @param bytes_done [in] Current number of bytes transferred. Set to a value greater than 0 to
indicate progress, or 0 to indicate no progress.
*  @param bytes_total [in] Total number of bytes to be transferred. Set to a value greater than 0 to
indicate progress, or 0 to indicate no progress.
*  @param p_abort [out] Set dereferenced value to GNSDK_TRUE to abort the operation that is calling
the callback
* @ingroup Submit_Callbacks
*/
typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_submit_callback_fn)(
	const gnsdk_void_t*				user_data,
	gnsdk_submit_parcel_handle_t	parcel_handle,
	gnsdk_submit_status_t			status,
	gnsdk_size_t					bytes_done,
	gnsdk_size_t					bytes_total,
	gnsdk_bool_t*					p_abort
	);

/** @internal gnsdk_submit_state_t @endinternal
  *
  *   Indicates the submit state of the parcel data.
* @ingroup Submit_TypesEnums
*/
typedef enum
{
/** @internal gnsdk_submit_state_unknown @endinternal
*
*   Parcel data submittal state is unknown; this is the initial state.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_unknown	= 0,

/** @internal gnsdk_submit_state_nothing_to_do @endinternal
*
*   No useful data to submit and process from the track.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_nothing_to_do,

/** @internal gnsdk_submit_state_ready_for_audio @endinternal
*
*   Parcel data is ready for audio data.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_ready_for_audio,

/** @internal gnsdk_submit_state_processing_error @endinternal
*
*   An error was encountered during processing of the data.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_processing_error,

/** @internal gnsdk_submit_state_ready_to_upload @endinternal
*
*   Parcel data is ready for uploading.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_ready_to_upload,

/** @internal gnsdk_submit_state_upload_succeeded @endinternal
*
*   Parcel data submittal succeeded.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_upload_succeeded,

/** @internal gnsdk_submit_state_upload_partially_succeeded @endinternal
*
*   Parcel data submittal partially succeeded.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_upload_partially_succeeded,

/** @internal gnsdk_submit_state_upload_failed @endinternal
*
*   Parcel data submittal failed.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_state_upload_failed

} gnsdk_submit_state_t;

/** @internal gnsdk_submit_audio_format_t @endinternal
*  Audio format types
* @ingroup Submit_TypesEnums
*/

typedef enum
{
/** @internal gnsdk_submit_audio_format_unknown @endinternal
*   Unknown audio format; this is the initial state, prior to obtaining
*   format information.
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_audio_format_unknown = 0,

/** @internal gnsdk_submit_audio_format_pcm16 @endinternal
*   Audio format of PCM 16
* @ingroup Submit_TypesEnums
*/
	gnsdk_submit_audio_format_pcm16

} gnsdk_submit_audio_format_t;

/** @internal gnsdk_submit_initialize @endinternal
*  Initializes the GNSDK Submit library.
*  @param sdkmgr_handle [in] Handle from a successful gnsdk_manager_initialize call
*  @return SUBMITERR_InvalidArg Given sdkmgr_handle parameter is null
*  @return SUBMITERR_HandleObjectInvalid Given sdkmgr_handle is not a valid GNSDK Manager handle
*  @return SUBMITERR_InitFailed Initialization failed
*  @return SUBMITERR_NoError Initialization succeeded
*  <p><b>Remarks:</b></p>
*  This function must be successfully called before any other Submit APIs will succeed.
*  This function can be called multiple times, however, all successful calls must be paired with a
call to gnsdk_submit_shutdown.
*  If gnsdk_submit_initialize returns an error, then gnsdk_submit_shutdown must not be called.
* @ingroup Submit_InitializationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_initialize(
	gnsdk_manager_handle_t sdkmgr_handle
	);

/** @internal gnsdk_submit_shutdown @endinternal
*  Shuts down and releases resources for the Submit library.
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_NoError Shut down succeeded
*  <p><b>Remarks:</b></p>
*  All gnsdk_submit_shutdown calls must be paired with an initial call to gnsdk_submit_initialize.
*  The final gnsdk_submit_shutdown call results in the library being completely shut down; all
Submit APIs cease to function until the library is again initialized.
* @ingroup Submit_InitializationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_shutdown(void);

/** @internal gnsdk_submit_get_version @endinternal
*  Retrieves version string of Submit library.
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
*  Major: New functionality
*  Minor: New or changed features
*  Improvement: Improvements and fixes
*  Build: Internal build number
* @ingroup Submit_InitializationFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_submit_get_version(void);

/** @internal gnsdk_submit_get_build_date @endinternal
*  Retrieves build date string of Submit library.
*  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example
*  Example build date string: 2008-02-12 00:41 UTC
* @ingroup Submit_InitializationFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_submit_get_build_date(void);

/******************************************************************************
 * Submit Parcel Handle - for the life of the Submit parcel
 ******************************************************************************/

/** @internal gnsdk_submit_parcel_create @endinternal
*  Creates a handle to a parcel. A single parcel can contain multiple types of data.
*  @param user_handle [in] User handle for the user making the submit request
*  @param callback_fn [in_opt] Callback function for status and progress
*  @param callback_userdata [in_opt] Data that is passed back to calls to the callback function
*  @param p_parcel_handle [out] Pointer to receive the parcel handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given p_submit_handle or user_handle parameter is null
*  @return SUBMITERR_NoError Parcel was successfully created
*  <p><b>Remarks:</b></p>
*  Use this function to create an empty, editable parcel for subsequent uploading to Gracenote
Service.
*  A parcel is a Submit container, requiring further input before the parcel is uploaded. Complete
the parcel using the gndsk_submit_parcel_data_* and gnsdk_submit_parcel_feature_* functions to add
GDOs and features.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_create(
	gnsdk_user_handle_t				user_handle,
	gnsdk_submit_callback_fn		callback_fn,
	gnsdk_void_t*					callback_userdata,
	gnsdk_submit_parcel_handle_t*	p_parcel_handle
	);

/** @internal gnsdk_submit_parcel_release @endinternal
*  Invalidates and releases resources for a given Submit handle.
*  @param parcel_handle [in] Handle to a parcel to release
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_NoError Parcel was successfully released, or given parcel_handle parameter is
null
*  <p><b>Remarks:</b></p>
*  All parcel handles created with gnsdk_submit_parcel_create must eventually be released to free
its resources.
*  Passing a null handle returns SUBMITERR_NoError.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_release(
	gnsdk_submit_parcel_handle_t	parcel_handle
	);

/** @internal gnsdk_submit_parcel_data_add_gdo @endinternal
*  Adds a GDO containing metadata to a parcel for submission to Gracenote Service.
*  @param parcel_handle [in] Handle to a parcel
*  @param gdo [in] Handle to a GDO of a supported context
*  @param data_ident [in] String to uniquely identify the data contained in the parcel
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given data_ident parameter is empty
*  @return SUBMITERR_NotEditable Given edit_gdo_handle parameter is a handle to a non-editable GDO,
instead of an editable GDO
*  @return SUBMITERR_Unsupported Given child_gdo_handle parameter is not supported for the parent
GDO context
*  @return SUBMITERR_NoError GDO for parcel data was successfully added
*  <p><b>Remarks:</b></p>
*  Use this function to add a GDO to a parcel prior to subsequently uploading the parcel to
Gracenote Service, such as passing in an editable Album GDO with metadata to a parcel. The
data_ident parameter is used with the gnsdk_submit_parcel_data_get_state function to report the
upload state of a specific parcel.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_data_add_gdo(
	gnsdk_submit_parcel_handle_t	parcel_handle,
	gnsdk_gdo_handle_t				gdo,
	gnsdk_cstr_t					data_ident /* a string to uniquely identify this data inside the parcel */
);

/******************************************************************************
 * Submit Parcel audio Feature APIs - for the generation and submission of
 * features generated from audio streams.
 ******************************************************************************/

/** @internal gnsdk_submit_parcel_data_init_features @endinternal
*  Prepares a parcel for gathering and generating features.
*  @param parcel_handle [in] Handle to a parcel
*  @param gdo [in] Handle to a GDO; note that these are generally not editable GDOs
*  @param flags [in] One of the available Submit Parcel Flags
*  @param p_something_to_do [out] Pointer to receive a boolean value indicating whether there is any
processing work required
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given p_something_to_do parameter is null or invalid
*  @return SUBMITERR_Busy System is busy
*  @return SUBMITERR_NoError Feature data was successfully initialized
*  <p><b>Remarks:</b></p>
*  Use this function to initialize the generation process for features contained in a parcel; this
enables Gracenote Service to determine if it requires specific feature data from the parcel, such as
a particular audio stream (Track).
*  The function first checks whether the application's license has been enabled for Submit. If not,
the function cancels.
*  You can submit Track feature data only for Album GDOs that are generated from a TOC lookup. For
an example of performing a TOC lookup, see Example: MusicID TOC Lookup.
*  <p><b>Important:</b></p>
*  Be sure to call gnsdk_submit_parcel_data_init_features only once per Album.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_data_init_features(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_gdo_handle_t					gdo,
	gnsdk_uint32_t						flags,
	gnsdk_bool_t*						p_something_to_do
	);

/** @internal GNSDK_SUBMIT_PARCEL_FEATURE_FLAG_DEFAULT @endinternal
*  Default features initialize flag.
* @ingroup Submit_ParcelSubmission_Flags
*/
#define	GNSDK_SUBMIT_PARCEL_FEATURE_FLAG_DEFAULT			0x00

/** @internal gnsdk_submit_parcel_feature_init_audio @endinternal
*  Initializes the generation of features for a specific audio stream.
*  @param parcel_handle [in] Handle to a parcel
*  @param data_id [in] Unique identifier for the audio stream
*  @param track_num [in] Ordinal for the audio stream (for albums, this is the track number)
*  @param audio_rate [in] Sample rate of audio to be provided ( for example: 44100)
*  @param audio_format [in] The audio format
*  @param audio_channels [in] Number of channels for audio to be provided (for example: 2)
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Returns for any of the following reasons: Given stream_id parameter
is empty; Given audio_format parameter is unknown; Given ordinal parameter is zero (0) or greater
than 99; Given audio_channels parameter or audio_rate parameter is zero (0)
*  @return SUBMITERR_IncorrectUsage gnsdk_submit_parcel_data_init_features must be successfully
initiated prior to calling this function
*  @return SUBMITERR_LibraryNotLoaded GNSDK DSP library has not been successfully initialized
*  @return SUBMITERR_OutofRange Ordinal value exceeds valid maximum value of 99
*  @return SUBMITERR_NoError Audio data for a parcel feature was successfully initialized
*  <p><b>Remarks:</b></p>
*  Use this function to initialize the generation of a specific audio stream (track). You must
ensure the following successfully happens before calling this function:
*  Calling the gnsdk_submit_parcel_data_init_features function, so the Gracenote Service can
identify which audio streams require processing.
*  Initializing the DSP library, in preparation for track fingerprint generation.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_feature_init_audio(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						data_id,		/* a way to uniquely identify the audio stream */
	gnsdk_uint32_t						track_num,		/* the track number for this stream */
	gnsdk_uint32_t						audio_rate,
	gnsdk_submit_audio_format_t			audio_format,
	gnsdk_uint32_t						audio_channels
	);

/** @internal gnsdk_submit_parcel_feature_option_set @endinternal
*  Sets an option for a specific audio stream in a parcel.
*  @param parcel_handle [in] Handle to a parcel
*  @param data_id [in] Unique identifier for an audio stream
*  @param option_key [in] One of the available Submit feature option keys
*  @param option_value [in] One of the available Submit feature option values that corresponds to
the selected option key
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given stream_id, option_key, or option_value parameter is empty
*  @return SUBMITERR_IncorrectUsage gnsdk_submit_parcel_feature_init_audio must be successfully
initiated prior to calling this function
*  @return SUBMITERR_NoError Feature option was successfully set
*  <p><b>Remarks:</b></p>
*  Use this function to define the general characteristics (such as an identifier and bitrate) of an
audio stream contained in a parcel.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_feature_option_set(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						data_id,		/* a way to uniquely identify the audio stream */
	gnsdk_cstr_t						option_key,
	gnsdk_cstr_t						option_value
	);

/** @internal gnsdk_submit_parcel_feature_option_get @endinternal
*  Retrieves an option for a specific audio stream in a parcel.
*  @param parcel_handle [in] Handle to a parcel
*  @param data_id [in] Unique identifier for an audio stream
*  @param option_key [in] One of the available Submit feature option keys
*  @param p_option_value [out] The value for the specified key
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given stream_id or option_key parameter is empty, or p_option_value
parameter is NULL
*  @return SUBMITERR_IncorrectUsage gnsdk_submit_parcel_feature_init_audio must be successfully
initiated prior to calling this function
*  @return SUBMITERR_NoError Feature option was successfully retrieved
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_feature_option_get(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						data_id,		/* a way to uniquely identify the audio stream */
	gnsdk_cstr_t						option_key,
	gnsdk_cstr_t*						p_option_value
	);

/** @internal gnsdk_submit_parcel_feature_write_audio_data @endinternal
*  Processes audio stream data contained in a parcel.
*  @param parcel_handle [in] Handle to a parcel
*  @param data_id [in] Unique identifier for an audio stream
*  @param audio_data [in] Pointer to audio data buffer that matches the audio format described to
gnsdk_submit_parcel_feature_init_audio
*  @param audio_data_bytes [in] Number of audio data bytes in this sample
*  @param p_complete [out] Pointer to receive boolean value as to whether the write process has
received enough data
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Returns for any of the following reasons: Given audio_data,
p_complete, or parcel_handle parameter is null; Given stream_id parameter is empty; Given
audio_data_bytes parameter is zero (0)
*  @return SUBMITERR_IncorrectUsage gnsdk_submit_parcel_feature_init_audio must be successfully
initiated prior to calling this function
*  @return SUBMITERR_NoError Audio data for a parcel feature was successfully written
*  <p><b>Remarks:</b></p>
*  Use this function to pass in a parcel's audio data for processing.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_feature_write_audio_data(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						data_id,		/* a way to uniquely identify the audio stream */
	const gnsdk_void_t*					audio_data,
	gnsdk_size_t						audio_data_bytes,
	gnsdk_bool_t*						p_complete
	);

/** @internal gnsdk_submit_parcel_feature_finalize @endinternal
*  Finalizes the processing of the audio for the given stream.
*  @param parcel_handle [in] Handle to a parcel
*  @param data_id [in] Unique identifier for an audio stream
*  @param abort [in] Boolean value to indicate whether the finalization process must stop operating,
due to processing errors
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given parcel_handle parameter is null, or given stream_id parameter
is empty
*  @return SUBMITERR_IncorrectUsage gnsdk_submit_parcel_feature_init_audio must be successfully
initiated prior to calling this function
*  @return SUBMITERR_NoError Parcel feature was successfully finalized
*  <p><b>Remarks:</b></p>
*  Use this function to finalize write processing for a feature. This function must be called before
the feature can be uploaded.
*  If your application receives an error or aborts while calling this function, be sure the
application calls the upload function (gnsdk_submit_parcel_upload). This ensures sending important
information to Gracenote that is useful for error resolution.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_feature_finalize(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						data_id,		/* a way to uniquely identify the audio stream */
	gnsdk_bool_t						abort 			/* to differentiate between success and stopping do to an error */
	);

/** @internal GNSDK_SUBMIT_PARCEL_UPLOAD_FLAG_DEFAULT @endinternal
*  Flag to indicate that the parcel data is being uploaded to Gracenote Service.
* @ingroup Submit_ParcelSubmission_Flags
*/
#define	GNSDK_SUBMIT_PARCEL_UPLOAD_FLAG_DEFAULT			0x00

/** @internal GNSDK_SUBMIT_PARCEL_UPLOAD_FLAG_TEST_MODE @endinternal
*  Flag for development test purposes only, used to validate the submission logic without
inadvertently adding invalid data to the
*  Gracenote Service.
*  After Gracenote validates the application's submission logic, clear this flag to enable active
submittals.
* @ingroup Submit_ParcelSubmission_Flags
*/
#define	GNSDK_SUBMIT_PARCEL_UPLOAD_FLAG_TEST_MODE		0x01

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_NAME @endinternal
*  Indicates the feature source name.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_NAME				"gnsdk_submit_feature_source_name"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_ID @endinternal
*  Indicates the feature source ID.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_ID				"gnsdk_submit_feature_source_id"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_DESC @endinternal
*  Indicates the feature source description.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_DESC				"gnsdk_submit_feature_source_desc"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_BITRATE @endinternal
*  Indicates the bitrate source.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_BITRATE			"gnsdk_submit_feature_source_bps"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_BITRATE_TYPE @endinternal
*  Indicates the bitrate type source.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_SOURCE_BITRATE_TYPE		"gnsdk_submit_feature_source_bps_type"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_NAME_CDDA @endinternal
*  Represents a feature source name of CDDA.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_NAME_CDDA				"CD Track"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_ID_CDDA @endinternal
*  Represents a feature source ID of CDDA.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_ID_CDDA				"CDDA"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_DESC_CDDA @endinternal
*  Represents a feature source description of CDDA.
*  GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_DESC_CDDA
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_DESC_CDDA				"CD Audio"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_BITRATE_1411200 @endinternal
*  Macro
*  Represents a feature source bitrate of 1,411,200 bit/s.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_BITRATE_1411200		"1411200"

/** @internal GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_BITRATE_TYPE_CONSTANT @endinternal
*  Macro
*  Represents a feature source constant bitrate type.
* @ingroup Submit_AudioFeatureOptions
*/
#define GNSDK_SUBMIT_FEATURE_OPTION_VALUE_SOURCE_BITRATE_TYPE_CONSTANT	"CONSTANT"

/** @internal gnsdk_submit_parcel_upload @endinternal
*  Uploads a parcel to Gracenote Service.
*  @param parcel_handle [in] Handle to a parcel to upload
*  @param flags [in] An available Submit parcel flag
*  @param p_state [out] Pointer to receive a submit state
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_IncorrectUsage gnsdk_submit_parcel_feature_init_audio must be successfully
initiated prior to calling this function
*  @return SUBMITERR_NoError Indicates the function successfully completed. The application must
check the returned state to determine the result of the parcel upload (such as success, partial
success, or failure) and take the appropriate action.
*  <p><b>Remarks:</b></p>
*  Use this function to submit a completed parcel to Gracenote Service.
*  If your application receives an error or aborts while calling the finalization function
(gnsdk_submit_parcel_feature_finalize), be sure the application calls the upload function. This
ensures sending important information to Gracenote that is useful for error resolution.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_upload(
	gnsdk_submit_parcel_handle_t	parcel_handle,
	gnsdk_uint32_t					flags,
	gnsdk_submit_state_t*			p_state
	);

/** @internal gnsdk_submit_parcel_data_get_state @endinternal
*  Retrieves the state of an individual data item in a parcel being uploaded.
*  @param parcel_handle [in] Handle to a parcel
*  @param id [in] Identifier for either a data_ident or data_id string
*  @param p_state [out] Pointer to a parcel state
*  @param p_error [out] Pointer to receive an error
*  @param p_info [out] Pointer to receive an information string; note this string is tied to the
parcel and is not guaranteed to exist after the parcel is freed
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given p_state parameter is null, or given data_ident parameter is
empty
*  @return SUBMITERR_NoError Data item's state was successfully retrieved
*  <p><b>Remarks:</b></p>
*  Use this function to retrieve the status of an individual piece of data in a parcel, in each
stage of the upload process - pre-process, process, and post-process.
* @ingroup Submit_ParcelSubmission_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_parcel_data_get_state(
	gnsdk_submit_parcel_handle_t	parcel_handle,
	gnsdk_cstr_t					id,			/* data_ident or stream_id */
	gnsdk_submit_state_t*			p_state,
	gnsdk_error_t*					p_error,	/* optional */
	gnsdk_cstr_t*					p_info		/* optional - note this string is tied to the parcel and is not guaranteed to exist once the parcel has been freed */
	);



#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_SUBMIT_H_ */

