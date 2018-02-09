/*
 * Copyright (c) 2009 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_SUBMIT_PRIVILEGED_H_
#define _GNSDK_SUBMIT_PRIVILEGED_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _DEBUG
#define SUBMIT_DEBUG			1 /* enable special debugging output */
#endif

/* Raw (opaque) Submit */

/* A couple predefined opaque submit types we know about. To use one not defined
here just pass in the TYPE string you agreed upon with the DB group. */
#define GNSDK_SUBMIT_RAW_TYPE_TRACK_SUBMIT_XML			"TRACK_SUBMIT" /* raw data formatted as TRACK_SUBMIT xml */

#define	GNSDK_SUBMIT_PARCEL_RAW_FLAG_STATIC				0x10 /* the SDK does not need to copy the data as it is guaranteed to remain until the handle is released */
#define	GNSDK_SUBMIT_PARCEL_RAW_FLAG_BASE64_STRING		0x20 /* the raw buffer is already a BASE64 nul terminated string */

/* Input XML will be entity encoded and added to the DATA GCSP element */
gnsdk_error_t	gnsdk_submit_parcel_data_add_raw_xml(
	gnsdk_submit_parcel_handle_t	parcel_handle,
	gnsdk_cstr_t					type,		/* TYPE attribute */
	gnsdk_cstr_t					ident,		/* IDENT attribute */
	gnsdk_cstr_t					data,		/* DATA */
	gnsdk_cstr_t					data_ident, /* a string to uniquely identify this data inside the parcel */
	gnsdk_uint32_t					flags /* pass in the 'static' flag defined above to keep the SDK from making a copy of your data */
	);

/* Input raw data that can be any format.  The input data will be base64'd
and added to the DATA GCSP element */
gnsdk_error_t	gnsdk_submit_parcel_data_add_raw_binary(
	gnsdk_submit_parcel_handle_t	parcel_handle,
	gnsdk_cstr_t					type,		/* TYPE attribute */
	gnsdk_cstr_t					ident,		/* IDENT attribute */
	gnsdk_byte_t*					data,		/* DATA */
	gnsdk_size_t					data_size,
	gnsdk_cstr_t					data_ident, /* a string to uniquely identify this data inside the parcel */
	gnsdk_uint32_t					flags
	);

gnsdk_error_t	gnsdk_submit_parcel_feature_data_get(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						stream_id,		/* a way to uniquely identify the audio stream */
	gnsdk_cstr_t						data_key,
	gnsdk_byte_t**						p_data_buffer,	/* pointer to feature data. format depends on algorithm. free returned buffer with gnsdk_submit_parcel_feature_data_free */
	gnsdk_size_t*						p_data_size		/* number of bytes for feature data */
	);

gnsdk_error_t	gnsdk_submit_parcel_feature_data_free(
	gnsdk_byte_t*						data_buffer		/* pointer to feature data. format depends on algorithm */
	);

#define GNSDK_SUBMIT_OPTION_FEATURES_DO_ALWAYS		"gnsdk_submit_option_feats_do_always"
#define GNSDK_SUBMIT_OPTION_FEATURES_SKIP			"gnsdk_submit_option_feats_skip" /* list each algorithm alias plus a semicolon: "ALG1;ALG2;" */

#define GNSDK_SUBMIT_FEATURE_OPTION_GENERATE_DATA	"gnsdk_submit_feature_generate_data"

/* no public options defined ATM */
gnsdk_error_t	gnsdk_submit_parcel_option_set(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						option_key,
	gnsdk_cstr_t						option_value
	);
gnsdk_error_t	gnsdk_submit_parcel_option_get(
	gnsdk_submit_parcel_handle_t		parcel_handle,
	gnsdk_cstr_t						option_key,
	gnsdk_cstr_t*						p_option_value
	);

#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_SUBMIT_PRIVILEGED_H_ */


