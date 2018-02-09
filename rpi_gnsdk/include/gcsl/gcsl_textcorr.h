/*
 * Copyright (c) 2007 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_textcorr.h - definition for text normalization and correlation APIs
 */

#ifndef _GCSL_TEXTCORR_H_
#define _GCSL_TEXTCORR_H_

#include "gcsl_datatypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/*
 * Types
 */

#define GCSL_NTF_BASIC				0x0000000  /* Basic conversion - standard normalizer operation, not nt lib equivalent flag */
/* velow copied directly and renamed from nt.h, so we don't require other modules include nt.h */
#define GCSL_NTF_REMOVE				0x00000001 /* Remove certain words. */
#define GCSL_NTF_CONTRACT			0x00000002 /* Nuke some leading contractions. */
#define GCSL_NTF_REPLACE			0x00000004 /* Replace certain words. */
#define GCSL_NTF_REMOVE_S			0x00000008 /* Remove trailing 's', if alone. */
#define GCSL_NTF_CONSOLIDATE		0x00000010 /* Consolidate one-letter words. */
#define GCSL_NTF_NUMERALS			0x00000020 /* Convert numbers to English. */
#define GCSL_NTF_ROMAN_NUMERALS		0x00000040 /* Convert roman #s to English. */
#define GCSL_NTF_REMOVE_DOUBLES		0x00000080 /* Remove repeated letters. */
#define GCSL_NTF_PUNCTUATION		0x00000100 /* Do punctuation modifications. */
#define GCSL_NTF_DOALL				0xFFFFFFFF

#define GCSL_NOF_NONE				0x00000000 /* No overrides (default). */
#define GCSL_NOF_TOK				0x00000001 /* Use tokenizer overrides. */

/*
 * Initialization
 */

gcsl_error_t	gcsl_textcorr_initialize		(void);
gcsl_error_t	gcsl_textcorr_shutdown			(void);

gcsl_cstr_t		gcsl_textcorr_get_version		(void);
gcsl_cstr_t		gcsl_textcorr_get_build_date	(void);

/*
 * Text Normalization
 */

/* Normalize a unicode string */
gcsl_error_t	gcsl_textcorr_normalize_text			(gcsl_cunistr_t utf16_src, gcsl_unistr_t* utf16_result, gcsl_cunistr_t except, gcsl_uint32_t flags, gcsl_uint32_t override);

/* Normalize a unicode string */
gcsl_error_t	gcsl_textcorr_normalize_utf8_text		(gcsl_cstr_t utf8_str, gcsl_str_t* mnormstr, gcsl_uint32_t flags, gcsl_uint32_t override);

/* Number to Text conversion */
gcsl_error_t	gcsl_textcorr_normalize_num_to_word		(gcsl_cstr_t num, gcsl_char_t *word, gcsl_size_t size);
gcsl_error_t	gcsl_textcorr_normalize_num_to_word_prim(gcsl_cstr_t num, gcsl_char_t *word, gcsl_size_t size, gcsl_bool_t bare);


/*
 * Levenshtein
 */

/* computes the edit distance between the two strings */

gcsl_uint32_t	gcsl_textcorr_levenshtein_str_distance	(gcsl_cstr_t a, gcsl_cstr_t b);
gcsl_uint32_t	gcsl_textcorr_levenshtein_buf_distance	(gcsl_cstr_t a, gcsl_size_t a_len, gcsl_cstr_t b, gcsl_size_t b_len);


/* computes the "percent difference" between the two strings.  This is calculated using the */
/* edit distance and normalizing it by dividing it by the length of the longest input string */

gcsl_uint32_t	gcsl_textcorr_str_percent_different		(gcsl_cstr_t a, gcsl_cstr_t b);
gcsl_uint32_t	gcsl_textcorr_buf_percent_different		(gcsl_cstr_t a, gcsl_size_t a_len, gcsl_cstr_t b, gcsl_size_t b_len);


/* computes the "levenshtein correlation" between the two strings.  Unlike the "percent difference" */
/* above, this scores the similarity on a 0-100 scale.  This is calculated using the */
/* edit distance and normalizing it by dividing it by the average length of the input strings */

gcsl_uint32_t	gcsl_textcorr_get_levenshtein_correlation_str(gcsl_cstr_t a, gcsl_cstr_t b);
gcsl_uint32_t	gcsl_textcorr_get_levenshtein_correlation_buf(gcsl_cstr_t a, gcsl_size_t a_len, gcsl_cstr_t b, gcsl_size_t b_len);


/*
 * Text Correlation Functions (Greedy String Tiling)
 */


#define gcsl_textcorr_get_gst_correlation_utf8(str1, str2) \
	gcsl_textcorr_get_gst_correlation_utf8_prim((str1), (str2), DEF_MINTILELEN)

#define gcsl_textcorr_get_gst_correlation_utf8_buff(str1, len1, str2, len2) \
	gcsl_textcorr_get_gst_correlation_utf8_buff_prim((str1), (len1), (str2), (len2), DEF_MINTILELEN)

#define gcsl_textcorr_getcorrelation_uni(str1, str2) \
	gcsl_textcorr_get_gst_correlation_uni_prim((str1), (str2), DEF_MINTILELEN)


gcsl_int32_t	gcsl_textcorr_get_gst_correlation_utf8_buff_prim	(gcsl_cstr_t str1_utf8, gcsl_size_t str1_utf8_sz, gcsl_cstr_t str2_utf8, gcsl_size_t str2_utf8_sz, gcsl_int32_t mintilelen);
gcsl_int32_t	gcsl_textcorr_get_gst_correlation_utf8_prim			(gcsl_char_t* utf8str1, gcsl_char_t* utf8str2, gcsl_int32_t mintilelen);
gcsl_int32_t	gcsl_textcorr_get_gst_correlation_uni_prim			(gcsl_uint16_t* unistr1, gcsl_uint16_t* unistr2, gcsl_int32_t mintilelen);


gcsl_error_t
gcsl_textcorr_tokenize_string(
	 gcsl_cstr_t			string,
	 gcsl_vector_handle_t*	p_token_vector
	 );


#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_TEXTCORR_H_ */
