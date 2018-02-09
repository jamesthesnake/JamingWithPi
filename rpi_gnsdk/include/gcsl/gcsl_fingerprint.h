/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_fingerprint.h - FingerPrint Extraction functions
 */

#ifndef	_GCSL_FINGERPRINT_H_
#define _GCSL_FINGERPRINT_H_

#include "gcsl_defines.h"
#include "gcsl_time.h"

#ifdef __cplusplus
extern "C"{
#endif 

#if 0
/* NB: if you enable this, know that the back end is unprepared to receive these and the format details have yet to be worked out. */
#define GCSL_FINGRERPRINT_ENABLE_MICRO_NANO_REFERENCE
#endif

/* Algorithms
*/

typedef enum
{
	gcsl_fingerprint_algorithm_id_unknown = 0,

	gcsl_fingerprint_algorithm_id_fapi_query_3svlq,  /* audio: 3 seconds, very low quality (mobile audio) */
	gcsl_fingerprint_algorithm_id_fapi_query_3smq,   /* audio: 3 seconds, medium quality (media monitoring) */
	gcsl_fingerprint_algorithm_id_fapi_query_6smq,   /* audio: 6 seconds, medium quality (media monitoring) */
	gcsl_fingerprint_algorithm_id_fapi_submit,       /* audio: philips reference fingerprint - callback on complete */
	gcsl_fingerprint_algorithm_id_fapi_submit_subfp, /* audio: philips reference fingerprint - callback on subfp */
	gcsl_fingerprint_algorithm_id_fhg_5x3,           /* video: 5 fps, 3 seconds (media monitoring) */
	gcsl_fingerprint_algorithm_id_cx_float,          /* audio: 15 seconds, high quality (file identification) */
	gcsl_fingerprint_algorithm_id_cx_float_submit,	 /* audio: reference file identification fingerprint */
	gcsl_fingerprint_algorithm_id_s12t,              /* audio features: s12t algorithm */
	gcsl_fingerprint_algorithm_id_s12t_v2,           /* audio features: s12t_v2 algorithm */
	gcsl_fingerprint_algorithm_id_fex_1_1,               /* audio features: fex algorithm version 1.1.0*/
	gcsl_fingerprint_algorithm_id_fex_2_0,               /* audio features: fex algorithm version 2.0.0*/
	gcsl_fingerprint_algorithm_id_afx3,              /* audio features: afx3 algorithm */
	gcsl_fingerprint_algorithm_id_chroma,            /* audio features: chroma algorithm */
	gcsl_fingerprint_algorithm_id_micro_fapi_query,  /* audio:  */
	gcsl_fingerprint_algorithm_id_nano_fapi_query,   /* audio:  */
#ifdef GCSL_FINGRERPRINT_ENABLE_MICRO_NANO_REFERENCE
	gcsl_fingerprint_algorithm_id_micro_fapi_submit, /* audio:  */
	gcsl_fingerprint_algorithm_id_nano_fapi_submit,  /* audio:  */
#endif
	gcsl_fingerprint_algorithm_id_patchfp,			 /* video: 1 fp per frame */
	gcsl_fingerprint_algorithm_id_fake = 99
}
gcsl_fingerprint_algorithm_id_t;

typedef enum
{
	gcsl_fingerprint_format_unknown = 0,

	gcsl_fingerprint_format_xml,  
	gcsl_fingerprint_format_binary_compressed
}
gcsl_fingerprint_format_t;

/* Fingerprint opaque handles
*/
typedef gcsl_handle_t gcsl_fingerprinter_handle_t;

typedef gcsl_handle_t gcsl_fingerprint_data_handle_t;

typedef gcsl_uint32_t gcsl_fingerprint_qualities_t;

#define	GCSL_FINGERPRINT_QUALITY_DEFAULT		0x0000
#define GCSL_FINGERPRINT_QUALITY_SHORT			0x0001
#define GCSL_FINGERPRINT_QUALITY_SILENT			0x0002

typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_fingerprint_callback_fn)(
	const gcsl_void_t*				userdata,
	gcsl_fingerprinter_handle_t		fingerprinter_handle,
	gcsl_fingerprint_data_handle_t	fingerprint_data_handle
	);

typedef enum
{
	gcsl_fingerprint_audio_format_unknown = 0,

	gcsl_fingerprint_audio_format_pcm8,
	gcsl_fingerprint_audio_format_pcm16,
	gcsl_fingerprint_audio_format_pcm32_float,
	gcsl_fingerprint_audio_format_ALaw,
	gcsl_fingerprint_audio_format_uLaw
}
gcsl_fingerprint_audio_format_t;

typedef enum
{
	gcsl_fingerprint_pixel_format_unknown = 0,

	gcsl_fingerprint_pixel_format_rgb24,
	gcsl_fingerprint_pixel_format_bgr24,        /* Windows "RGB24" is really BGR */
	gcsl_fingerprint_pixel_format_rgba32,
	gcsl_fingerprint_pixel_format_yuv422_32,
	gcsl_fingerprint_pixel_format_grayscale
}
gcsl_fingerprint_pixel_format_t;

typedef enum
{
	gcsl_fingerprint_frame_origin_unknown = 0,

	gcsl_fingerprint_frame_origin_lower_left,  /* Windows bitmaps are this way */
	gcsl_fingerprint_frame_origin_upper_left
}
gcsl_fingerprint_frame_origin_t;


/*
 * Initialization
 */

gcsl_error_t   gcsl_fingerprint_initialize		(void);
gcsl_error_t   gcsl_fingerprint_shutdown		(void);

gcsl_cstr_t    gcsl_fingerprint_get_version		(void);
gcsl_cstr_t    gcsl_fingerprint_get_build_date	(void);


/*
** Fingerprinter Creation
*/
gcsl_error_t gcsl_fingerprint_create_audio_fingerprinter(
	gcsl_fingerprint_algorithm_id_t  algorithm_id,
	gcsl_uint32_t                    sample_rate,
	gcsl_fingerprint_audio_format_t  sample_format,
	gcsl_uint32_t                    channels,
	gcsl_cstr_t                      config_options,
	gcsl_fingerprint_callback_fn     callback,
	gcsl_void_t*                     callback_userdata,
	gcsl_fingerprinter_handle_t*     p_fingerprinter_handle
	);

#define GCSL_FINGERPRINT_CONFIG_BLOCK_SIZE     "gcsl_cfg_block_size"
#define GCSL_FINGERPRINT_CONFIG_SILENCE_MODE   "gcsl_cfg_silence_mode"
#define GCSL_FINGERPRINT_CONFIG_WEAK_BIT_MODE  "gcsl_cfg_weak_bit_mode"

gcsl_error_t gcsl_fingerprint_create_video_fingerprinter(
	gcsl_fingerprint_algorithm_id_t  algorithm_id,
	gcsl_fingerprint_pixel_format_t  pixel_format,
	gcsl_fingerprint_frame_origin_t  frame_origin,
	gcsl_cstr_t                      config_options,
	gcsl_fingerprint_callback_fn     callback,
	gcsl_void_t*                     callback_userdata,
	gcsl_fingerprinter_handle_t*     p_fingerprinter_handle
	);

/* TODO: create config values for fhg feature set */
#define GCSL_FINGERPRINT_CONFIG_FHG_FEATURE_  "gcsl_cfg_feature_"


gcsl_error_t gcsl_fingerprint_add_audio_buffer(
	gcsl_fingerprinter_handle_t      fingerprinter_handle,
	const gcsl_byte_t*               audio_data,
	gcsl_size_t                      audio_data_bytes,
	gcsl_time_us_t                   timestamp,
	gcsl_bool_t*                     finished
	);


gcsl_error_t gcsl_fingerprint_add_video_frame(
	gcsl_fingerprinter_handle_t      fingerprinter_handle,
	const gcsl_byte_t*               frame_data,
	gcsl_uint32_t                    frame_width,
	gcsl_uint32_t                    frame_height,
	gcsl_time_us_t                   timestamp,
	gcsl_bool_t*                     finished
	);

gcsl_error_t gcsl_fingerprint_flush(
	gcsl_fingerprinter_handle_t		fingerprinter_handle,
	gcsl_fingerprint_qualities_t*	p_qualities
	);

gcsl_error_t gcsl_fingerprint_get_info(
	gcsl_fingerprinter_handle_t      fingerprinter_handle,
	gcsl_cstr_t                      info_key,
	gcsl_cstr_t*                     info_value
	);

#define GCSL_FINGERPRINT_INFO_ALG_NAME					"gcsl_fingerprint_alg_name"
#define GCSL_FINGERPRINT_INFO_ALG_VERSION				"gcsl_fingerprint_alg_version"
#define GCSL_FINGERPRINT_INFO_ALG_BUILD					"gcsl_fingerprint_alg_build"

#define GCSL_FINGERPRINT_INFO_MIN_BLOCKS_REQUIRED		"gcsl_fingerprint_min_blocks"
#define GCSL_FINGERPRINT_INFO_MAX_BLOCKS_REQUIRED		"gcsl_fingerprint_max_blocks"


gcsl_error_t gcsl_fingerprint_delete(
	gcsl_fingerprinter_handle_t      fingerprinter_handle
	);


/*
** Fingerprint Data Access
*/
gcsl_error_t gcsl_fingerprint_data_get_data(
	gcsl_fingerprint_data_handle_t fingerprint_data_handle,
	const gcsl_void_t**              data,     /* opaque data */
	gcsl_size_t*                     length,   /* in bytes */
	gcsl_time_us_t*                  duration, /* in microseconds */
	gcsl_time_us_t*                  offset,   /* in microseconds */
	gcsl_bool_t*                     is_discontinuity,
	gcsl_uint32_t*                   block_id
	);

#define GCSL_FINGERPRINT_DATA_INFO_ /*TODO*/

/* TBD REC: If the data handle owns the values, where should they be stored? */
gcsl_error_t gcsl_fingerprint_data_get_info(
	gcsl_fingerprint_data_handle_t   fingerprint_data_handle,
	gcsl_cstr_t                      info_key,
	gcsl_cstr_t*                     info_value
	);

#define GCSL_FINGERPRINT_DATA_FORMAT_ /*TODO*/

gcsl_error_t gcsl_fingerprint_data_format(
	gcsl_fingerprint_data_handle_t   fingerprint_data_handle,
	gcsl_cstr_t                      format,
	gcsl_str_t*                      result
	);

gcsl_error_t gcsl_fingerprint_data_delete(
	gcsl_fingerprint_data_handle_t fingerprint_data_handle
	);


/*
** Query Support
*/

gcsl_error_t
gcsl_fingerprint_render_data(
	gcsl_fingerprinter_handle_t			fingerprinter_handle,
	gcsl_fingerprint_data_handle_t*		fingerprint_data_handles,
	gcsl_size_t							data_handle_count,
	gcsl_str_t*							p_result
	);

gcsl_error_t
gcsl_fingerprint_render_data_free(
	gcsl_str_t							result
	);

/*
** Algorithm Discovery
 */

typedef enum
{
	gcsl_fingerprint_algorithm_type_unknown = 0,

	gcsl_fingerprint_algorithm_type_query	= 1,
	gcsl_fingerprint_algorithm_type_submit	= 2
}
gcsl_fingerprint_algorithm_type_t;


gcsl_error_t
gcsl_fingerprint_algorithm_count(
	gcsl_uint32_t*	p_count
	);

gcsl_error_t
gcsl_fingerprint_algorithm_enum(
	gcsl_uint32_t						index,
	gcsl_fingerprint_algorithm_id_t*	p_alg_id,
	gcsl_fingerprint_algorithm_type_t*	p_alg_type,
	gcsl_cstr_t*						p_alg_name,
	gcsl_cstr_t*						p_alg_ver,
	gcsl_cstr_t*						p_alg_alias
	);

/*
** Conversion Support
*/

/* free resultant output data with render_data_free() */
gcsl_error_t
gcsl_fingerprint_convert_data(
	gcsl_fingerprint_algorithm_id_t		input_type,
	gcsl_fingerprint_format_t			input_format,
	gcsl_byte_t*						input_buffer,
	gcsl_size_t							input_size,
	gcsl_fingerprint_algorithm_id_t		output_type,
	gcsl_str_t*							p_output
	);

#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_FINGERPRINT_H_ */

