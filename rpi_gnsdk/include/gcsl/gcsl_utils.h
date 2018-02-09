/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
#ifndef _GCSL_UTILS_H_
#define _GCSL_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

gcsl_error_t	gcsl_utils_initialize		(void);
gcsl_error_t	gcsl_utils_shutdown			(void);

gcsl_cstr_t		gcsl_utils_get_version		(void);
gcsl_cstr_t		gcsl_utils_get_build_date	(void);

/* jmctodo base64 should return chars, not bytes. we should change types. FIXME. */

/******* base64 *******/

/*  gcsl_utils_base64_decode_size
 * Description: Calculates the size need to decode base64 encode data
 *
 * Args:	input_len	- base64 encoded input
 *			output_len	- length needed for decoded output
 *			b_null		- include a NULL terminator in the size calucation
 *
 * Returns:	UTILERR_NoError upon success or an error.
 *			Failure conditions include:
 *				invalid input
 */
gcsl_error_t
gcsl_utils_base64_decode_size(
	gcsl_size_t		input_len,
	gcsl_size_t*	output_len,
	gcsl_bool_t		b_null
	);


/*  gcsl_utils_base64_encode_size
 * Description: Calculates the size need to encode data into base64
 *
 * Args:	input_len	- decoded input
 *			output_len	- length needed for base64 encoded output
 *			b_null		- include a NULL terminator in the size calucation
 *
 * Returns:	UTILERR_NoError upon success or an error.
 *			Failure conditions include:
 *				invalid input
 */
gcsl_error_t
gcsl_utils_base64_encode_size(
	gcsl_size_t		input_len,
	gcsl_size_t*	output_len,
	gcsl_bool_t		b_null
	);


/*  gcsl_utils_base64_decode
 * Description: Decode base64 encoded data.
 *				This function allocates memory for the decoded output.
 *
 * Args:	buf		- base64 encoded input
 *			len		- length of base64 encoded input
 *			nbuf	- decoded output
 *			nlen	- length of decoded output
 *			b_null	- add a NULL terminator to the decoded output
 *
 * Returns:	UTILERR_NoError upon success or an error.
 *			Failure conditions include:
 *				memory allocation error
 *				invalid input
 *				internal error
 */
gcsl_error_t
gcsl_utils_base64_decode(
	const gcsl_byte_t*	buf,
	gcsl_size_t			len,
	gcsl_byte_t**		nbuf,
	gcsl_size_t*		nlen,
	gcsl_bool_t			b_null
	);

gcsl_error_t
gcsl_utils_base64_decode_ex(
	const gcsl_byte_t*	buf,
	gcsl_size_t			len,
	gcsl_byte_t**		nbuf,
	gcsl_size_t*		nlen,
	gcsl_bool_t			b_null,
	gcsl_cstr_t			ex_chars
	);


/*  gcsl_utils_base64_encode
 * Description: Encode data into base64
 *				This function allocates memory for the base64 encoded output.
 *
 * Args:	buf		- decoded input
 *			len		- length of decoded input
 *			nbuf	- base64 encoded output
 *			nlen	- length of base64 encoded output
 *			b_null	- add a NULL terminator to the base64 encoded output
 *
 * Returns:	UTILERR_NoError upon success or an error.
 *			Failure conditions include:
 *				memory allocation error
 */
gcsl_error_t
gcsl_utils_base64_encode(
	const gcsl_byte_t*	buf,
	gcsl_size_t			len,
	gcsl_byte_t**		nbuf,
	gcsl_size_t*		nlen,
	gcsl_bool_t			b_null
	);

gcsl_error_t
gcsl_utils_base64_encode_ex(
	const gcsl_byte_t*	buf,
	gcsl_size_t			len,
	gcsl_byte_t**		nbuf,
	gcsl_size_t*		nlen,
	gcsl_bool_t			b_null,
	gcsl_bool_t			b_pad,
	gcsl_cstr_t			ex_chars
	);

/*  gcsl_utils_base64_freebuf
 * Description: Frees buffers returned from gcsl_utils_base64_decode and 
 *				gcsl_utils_base64_encode.
 */
gcsl_error_t
gcsl_utils_base64_freebuf(
	gcsl_byte_t*		nbuf
	);

/********* Cyclic Redundancy Check *******/

gcsl_error_t 
gcsl_utils_crc32(
	const gcsl_void_t*			p_input,
	gcsl_size_t					p_input_size,
	gcsl_uint32_t*				p_crc,
	gcsl_size_t*				p_crc_len 
	);


/********* TAGID **********/

/*
 *  gcsl_utils_tui_to_tagid
 * Description: Combines a Track Number, TUI, and TUITAG into a TagID
 *				Upon successfuly return, p_tui_id and p_tui_id_tag are allocated.
 *
 * Args:	tui_id		- input TUI
 *			tui_id_tag	- input TUI Tag
 *			p_tag_id	- output TUI Tag
 *
 * Returns:	GCSLERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Invalid argument
 */
gcsl_error_t
gcsl_utils_tui_to_tagid(
	gcsl_cstr_t		tui_id,
	gcsl_cstr_t		tui_id_tag,
	gcsl_str_t*		p_tag_id
	);

/*
 *  gcsl_utils_tagid_to_tui
 * Description: Splits a TagID into TUI and TUITAG
 *				Upon successfuly return, p_tui_id and p_tui_id_tag are allocated.
 *
 * Args:	tag_id			- input tag_id
 *			p_tui_id		- output TUI
 *			p_tui_id_tag	- output TUI Tag
 *
 * Returns:	GCSLERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Invalid argument
 */
gcsl_error_t
gcsl_utils_tagid_to_tui(
	gcsl_cstr_t		tag_id,
	gcsl_str_t*		p_tui_id,
	gcsl_str_t*		p_tui_id_tag
	);

/*
 *  gcsl_utils_cddb_ids_to_mui_and_mediaid
 * Description: Splits CDDB IDs (formatted from iTunes: "NUM_TRACKS+MuiID+[MediaID]") into track number, MUI, and MediaID
 *				Upon successfuly return, p_mui and p_mediaid are allocated.
 *
 * Args:	cddb_ids	- input tag_id
 *			p_track_num	- output track number
 *			p_mui		- output MUI
 *			p_mediaid	- output MediaID
 *
 * Returns:	GCSLERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Invalid argument
 */
gcsl_error_t
gcsl_utils_cddb_ids_to_mui_and_mediaid(
	gcsl_cstr_t		cddb_ids,
	gcsl_uint32_t*	p_track_num,
	gcsl_str_t*		p_mui,
	gcsl_str_t*		p_mediaid
	);


/*
 * Create GNUID from TUI/Tag/Type
 */
gcsl_error_t
gcsl_utils_gnuid_create(
	gcsl_uint32_t	tui_id,
	gcsl_cstr_t		tui_id_tag,
	gcsl_uint32_t	gnuid_type,
	gcsl_char_t*	gnuid_buf,
	gcsl_size_t		gnuid_buf_size
	);

#define GNUID_BUFFER_SIZE	17


/*
 * Retrieve GNUID Type
 */
gcsl_error_t
gcsl_utils_gnuid_parse(
	gcsl_cstr_t		gnuid_str,
	gcsl_uint32_t*	p_tui_id,
	gcsl_uint32_t*	p_gnuid_type
	);

#define GCSL_UTILS_GNUID_UNKNOWN			0
#define GCSL_UTILS_GNUID_ALBUM_TUI			1	/* ALBUM */
#define GCSL_UTILS_GNUID_DVD_TUI			2	/* DVDCASE */
#define GCSL_UTILS_GNUID_LYRIC_TUI			3	/* LYRIC */
#define GCSL_UTILS_GNUID_MEDIA_OBJECT_TUI	4	/* MEDIA_OBJECT */
#define GCSL_UTILS_GNUID_CONTRIBUTOR_TUI	5	/* CONTRIBUTOR */
#define GCSL_UTILS_GNUID_SERIES_TUI			6	/* SERIES */
#define GCSL_UTILS_GNUID_SEASON_TUI			7	/* SEASON */
#define GCSL_UTILS_GNUID_TVPROGRAM_TUI		8	/* TVPROGRAM */
#define GCSL_UTILS_GNUID_TVCHANNEL_TUI		9	/* TVCHANNEL */
#define GCSL_UTILS_GNUID_TRACK_TUI			10	/* TRACK */


/******************************************************************************
* gcsl_utils_quicksort
* General array sorting routine using QuickSort
*/
typedef gcsl_int32_t (GCSL_CALLBACK_API *gcsl_utils_qsort_compare_fn)(const gcsl_void_t* value1, const gcsl_void_t* value2, const gcsl_void_t* compare_fn_data);

gcsl_error_t
gcsl_utils_qsort(
	gcsl_void_t*				base,
	gcsl_size_t					nmemb,
	gcsl_size_t					size,
	gcsl_utils_qsort_compare_fn	compare_fn,
	const gcsl_void_t*			compare_fn_data
	);


/******************************************************************************
* gcsl_utils_asc2bin
* convert ascii string to binary equivalent
*/
gcsl_error_t
gcsl_utils_asc2bin(
	gcsl_cstr_t		asc,
	gcsl_size_t		asc_size,
	gcsl_byte_t*	bin,
	gcsl_size_t		bin_size
	);



#ifdef __cplusplus
}
#endif

#endif /* _GCSL_UTILS_H_ */
