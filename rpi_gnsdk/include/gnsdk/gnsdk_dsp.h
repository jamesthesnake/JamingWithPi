/* Gracenote SDK: DSP public header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_DSP_H_
/* @internal gnsdk_dsp.h @endinternal
 * The primary interface for the DSP SDK
 * The GNSDK DSP library is an internal library that provides digital signal processing functionality
 * used by other GNSDK libraries. When implementing audio feature generation in the Submit library or digital
 * music recognition in the MusicID and MusicID-File libraries, the application must initialize GNSDK libraries
 * in the following order to ensure correct signal processing:
 * <ol>
 * <li>GNSDK Manager
 * <li>DSP
 * <li>The specific GNSDK library (or libraries)
 * </ol>
* @ingroup Music_Fingerprinting_HeaderFile
*/
#define _GNSDK_DSP_H_

#include "gnsdk_manager.h"

#ifdef __cplusplus
extern "C"{
#endif

/*
 * gnsdk_dsp.h:	Fingerprinting and other DSP implementations
 *
 */

/* GNSDK DSP Initialization APIs */

/** @internal gnsdk_dsp_initialize @endinternal
*  Initializes the DSP for GNSDK
*  @param sdkmgr_handle [in] Handle from a successful gnsdk_manager_initialize call
*  @return DSPERR_InvalidArg Given sdkmgr_handle parameter is null
*  @return DSPERR_HandleObjectInvalid Given sdkmgr_handle is not a valid GNSDK Manager handle
*  @return DSPERR_InitFailed Initialization failed
*  @return DSPERR_NoError Initialization succeeded
*  <p><b>Remarks:</b></p>
*  This function must be successfully called before any other DSP APIs will succeed.
*  This function can be called multiple times, however, all successful calls must be paired with a
call to gnsdk_dsp_shutdown.
*  If gnsdk_dsp_initialize returns an error, then gnsdk_dsp_shutdown must not be called.
* @ingroup Music_Fingerprinting_InitializationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_dsp_initialize(
	gnsdk_manager_handle_t	sdkmgr_handle
	);

/** @internal gnsdk_dsp_shutdown @endinternal
*  Shut downs and releases resources for the DSP library.
*  @return DSPERR_NotInited gnsdk_dsp_initialize was not successfully initiated
*  @return DSPERR_NoError Shut down succeeded
*  <p><b>Remarks:</b></p>
*  All gnsdk_dsp_shutdown calls must be paired with an initial call to gnsdk_dsp_initialize.
*  The final gnsdk_dsp_shutdown call results in the library being completely shut down; all DSP APIs
cease to function until the library is again initialized.
* @ingroup Music_Fingerprinting_InitializationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_dsp_shutdown(void);

/** @internal gnsdk_dsp_get_version @endinternal
*  Retrieves DSP's version string for GNSDK.
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
*  Major: New functionality
*  Minor: New or changed features
*  Improvement: Improvements and fixes
*  Build: Internal build number
* @ingroup Music_Fingerprinting_InitializationFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_dsp_get_version(void);

/** @internal gnsdk_dsp_get_build_date @endinternal
*  Retrieves the DSP 's build date string for GNSDK.
*  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, even before initialization and after shutdown. The returned
string is a constant. Do not attempt to modify or delete.
*  Example
*  Example build date string: 2008-02-12 00:41 UTC
* @ingroup Music_Fingerprinting_InitializationFunctions
*/
gnsdk_cstr_t GNSDK_API
gnsdk_dsp_get_build_date(void);

/* Direct DSP Feature Creation APIs */

/**  @internal gnsdk_dsp_feature_handle_t @endinternal
 * The handle for the DSP feature
* @ingroup Music_Fingerprinting_TypesEnums
*/
typedef gnsdk_handle_t		gnsdk_dsp_feature_handle_t;

/** @internal gnsdk_dsp_feature_qualities_t @endinternal
*  The DSP feature quality type definition.
* @ingroup Music_Fingerprinting_TypesEnums
*/
typedef gnsdk_uint32_t		gnsdk_dsp_feature_qualities_t;

/** @internal GNSDK_DSP_FEATURE_QUALITY_DEFAULT @endinternal
  * Indicates the DSP feature quality of the source audio is default.
  * @ingroup Music_Fingerprinting_FeatureQuality
*/
#define GNSDK_DSP_FEATURE_QUALITY_DEFAULT		0x0

/** @internal GNSDK_DSP_FEATURE_QUALITY_SHORT @endinternal
  * Indicates the source audio is short, and therefore the quality of the generated DSP feature is also short.
  * @ingroup Music_Fingerprinting_FeatureQuality
*/
#define GNSDK_DSP_FEATURE_QUALITY_SHORT			0x1

/** @internal GNSDK_DSP_FEATURE_QUALITY_SILENT @endinternal
  * Indicates the source audio is silent, and therefore the quality of the generated DSP feature is silent.
  * @ingroup Music_Fingerprinting_FeatureQuality
*/
#define GNSDK_DSP_FEATURE_QUALITY_SILENT		0x2



/** @internal gnsdk_dsp_feature_audio_begin @endinternal
  * Start creating the DSP feature.
  * @param user_handle  The user handle
  * @param feature_type The kind of DSP feature, for example a fingerprint.
  * @param audio_sample_rate The source audio sample rate.
  * @param audio_sample_size The source audio sample size.
  * @param audio_channels The source audio channels
  * @param p_feature_handle The handle of the generated DSP feature
* @ingroup Music_Fingerprinting_FeatureGenerationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_dsp_feature_audio_begin(
	gnsdk_user_handle_t				user_handle,
	gnsdk_cstr_t					feature_type,
	gnsdk_uint32_t					audio_sample_rate,
	gnsdk_uint32_t					audio_sample_size,
	gnsdk_uint32_t					audio_channels,
	gnsdk_dsp_feature_handle_t*		p_feature_handle
	);

/** @internal gnsdk_dsp_feature_audio_write @endinternal
	 *
	 * @ingroup Music_Fingerprinting_FeatureGenerationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_dsp_feature_audio_write(
	gnsdk_dsp_feature_handle_t		feature_handle,
	const gnsdk_void_t*				audio_data,
	gnsdk_size_t					audio_data_bytes,
	gnsdk_bool_t*					pb_complete
	);

/** @internal gnsdk_dsp_feature_end_of_write @endinternal
	 * Indicates the the DSP feature has reached the end of the write operation.
	 * @ingroup Music_Fingerprinting_FeatureGenerationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_dsp_feature_end_of_write(
	gnsdk_dsp_feature_handle_t		feature_handle
	);

/** @internal gnsdk_dsp_feature_retrieve_data @endinternal
	 * Get the DSP feature qualities and data
	 * @ingroup Music_Fingerprinting_FeatureGenerationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_dsp_feature_retrieve_data(
	gnsdk_dsp_feature_handle_t		feature_handle,
	gnsdk_dsp_feature_qualities_t*	p_feature_qualities,
	gnsdk_cstr_t*					p_feature_data
	);

/** @internal gnsdk_dsp_feature_release @endinternal
	 * Release the DSP feature handle.
	 * @ingroup Music_Fingerprinting_FeatureGenerationFunctions
*/
gnsdk_error_t GNSDK_API
gnsdk_dsp_feature_release(
	gnsdk_dsp_feature_handle_t		feature_handle
	);


#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_DSP_H_ */

