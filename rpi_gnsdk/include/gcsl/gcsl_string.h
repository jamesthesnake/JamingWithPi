/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_string.h - String Manipulation functions
 */

#ifndef	_GCSL_STRING_H_
#define _GCSL_STRING_H_

#ifdef __cplusplus
extern "C"{
#endif 


/*
 * Macros
 */

/* Define the range of values for the string similarity functions.
 * Currently the bigram_cmp and fuzzycmp functions.
 */
#define GCSL_STRING_SIMILARITY_NONE		0
#define GCSL_STRING_SIMILARITY_EXACT	100

/*
 * Initialization
 */

gcsl_error_t	gcsl_string_initialize		(void);
gcsl_error_t	gcsl_string_shutdown		(void);

gcsl_cstr_t		gcsl_string_get_version		(void);
gcsl_cstr_t		gcsl_string_get_build_date	(void);

/*
** Comparison
*/

/* Compare string for being equal (optional case sensitive) */
gcsl_bool_t		gcsl_string_equal(gcsl_cstr_t stringa, gcsl_cstr_t stringb, gcsl_bool_t b_ignore_case);

/* Compare the strings (case sensitive) */
gcsl_int16_t	gcsl_string_strcmp(gcsl_cstr_t stringa, gcsl_cstr_t stringb);

/* Compare the strings (case insensitive) */
gcsl_int16_t	gcsl_string_stricmp(gcsl_cstr_t stringa, gcsl_cstr_t stringb);

/* Compare the strings to specified size (case sensitive) */
gcsl_int16_t	gcsl_string_strncmp(gcsl_cstr_t stringa, gcsl_cstr_t stringb, gcsl_size_t count);

/* Compare the strings to specified size (case insensitive)*/
gcsl_int16_t	gcsl_string_strnicmp(gcsl_cstr_t stringa, gcsl_cstr_t stringb, gcsl_size_t count);

/* Compare the strings up to first mismatch and return matched char count.
** (case sensitive) */
gcsl_size_t		gcsl_string_strcmp_len(gcsl_cstr_t stringa, gcsl_cstr_t stringb, gcsl_cstr_t* p_str_pos_a, gcsl_cstr_t* p_str_pos_b);

/* Compare the strings up to first mismatch and return matched char count.
** (case insensitive) */
gcsl_size_t		gcsl_string_stricmp_len(gcsl_cstr_t stringa, gcsl_cstr_t stringb, gcsl_cstr_t* p_str_pos_a, gcsl_cstr_t* p_str_pos_b);

/*
** Fuzzy Comparison
*/

typedef struct
{
	gcsl_uint32_t	count;
	gcsl_uint32_t*	bigrams;

} gcsl_string_bigram_table_t;


/*	Create a bi-gram table from a string.  On success returns a pointer to the allocated
 *	table.  The user is responsible for releasing the table with gcsl_memory_free.
 */
gcsl_error_t
gcsl_string_create_bigram_table(
	gcsl_cstr_t						str,
	gcsl_bool_t						b_ignore_space,
	gcsl_string_bigram_table_t**	pp_bigram
	);


/*	Compare two bi-gram tables.  Returns 0 for no similarity upto 100 for exact match.
 * Note the existence of the GCSL_STRING_SIMILARITY_EXACT and GCSL_STRING_SIMILARITY_NONE macros.
 */
gcsl_uint32_t
gcsl_string_bigram_table_cmp(
	gcsl_string_bigram_table_t*		p_bigrama,
	gcsl_string_bigram_table_t*		p_bigramb
	);


/* Compare string similarity. Returns 0 for no sim -> 100 for exact 
 * Note the existence of the GCSL_STRING_SIMILARITY_EXACT and GCSL_STRING_SIMILARITY_NONE macros.
 */
gcsl_uint32_t	gcsl_string_fuzzycmp_ex(gcsl_cstr_t stringa, gcsl_cstr_t stringb, gcsl_bool_t b_ignore_space, gcsl_uint32_t* p_ainb, gcsl_uint32_t* p_bina);

#define			gcsl_string_fuzzycmp(stringa, stringb, b_ignore_space) \
					gcsl_string_fuzzycmp_ex(stringa, stringb, b_ignore_space, GCSL_NULL, GCSL_NULL)


/*
** Copying
*/

/* Copy the string from source to destination (always null terminates). 
** source string will be truncated if it does not fit dest buffer */
gcsl_str_t		gcsl_string_strcpy(gcsl_str_t dest, gcsl_size_t dest_size, gcsl_cstr_t src);

/* Copy the first n characters of source to destination (always null 
terminates). source string will be truncated if it does not fit dest buffer
NB: unlike some strnpy's, this will not pad 'dest' with zeros if the 'src' string is shorter than 'src_count.' */
gcsl_str_t		gcsl_string_strncpy(gcsl_str_t dest, gcsl_size_t dest_size, gcsl_cstr_t src, gcsl_size_t src_count);

/* gcsl_string_strdup
 *
 * Duplicates a gcsl string (use gcsl_string_free to deallocate the string).
 * Returns a pointer to a copy of the given string or null if the
 * allocation failed or if the given string is null.
 */
gcsl_str_t		gcsl_string_strdup(gcsl_cstr_t str);

/* gcsl_string_strdupn
 *
 * Duplicates a gcsl string to a given fixed sized buffer.
 * Returns a pointer to a copy of the given string or null if the
 * allocation failed or if the given string is null.
 */
gcsl_str_t		gcsl_string_strdupn(gcsl_cstr_t str, gcsl_size_t fixed_len, gcsl_char_t pad_char);

/* gcsl_string_strndup
 *
 * Duplicates a gcsl string up to src_count characters (use gcsl_string_free
 * to deallocate the string). Returns a pointer to a copy of the given 
 * string or null if the allocation failed or if the given string is null.
 */
gcsl_str_t		gcsl_string_strndup(gcsl_cstr_t str, gcsl_size_t src_count);

/* gcsl_string_worddup
 *
 * Duplicates a gcsl string up to the next whitespace. If string starts on 
 * whitespace, duplication starts on next non-whitespace.
 */
gcsl_str_t		gcsl_string_worddup(gcsl_cstr_t str);


/* gcsl_string_free
 *
 * Frees string allocated by gcsl_string library.
 */
gcsl_void_t		gcsl_string_free(gcsl_str_t str);

/*
** Length
*/

/* Length of the string in bytes including NULL byte.
 * NULL strings return length of 0.
 * Empty "" strings return length of 1.
 */
gcsl_size_t		gcsl_string_bytelen(gcsl_cstr_t string);

/* Length of the string in bytes including NULL byte, counting up to the given bytes in string
 * NULL strings return length of 0.
 * Empty "" strings return length of 1.
 */
gcsl_size_t		gcsl_string_bytenlen(gcsl_cstr_t string, gcsl_size_t uptobytes);

/* Number of bytes of the first count characters in string
 * NULL strings return length of 0.
 * Empty "" strings return length of 0.
 */
gcsl_size_t		gcsl_string_byteclen(gcsl_cstr_t string, gcsl_size_t count);

/* Length of the string in bytes NOT including NULL byte.
 * NULL and empty strings return length of 0
 */
gcsl_size_t		gcsl_string_bytelen_nonull(gcsl_cstr_t string);

/* Length of the string in bytes NOT including NULL byte, counting up to the given bytes in string
 * NULL and empty strings return length of 0
 */
gcsl_size_t		gcsl_string_bytenlen_nonull(gcsl_cstr_t string, gcsl_size_t uptobytes);

/* Length of the string in characters
 * NULL and empty strings return length of 0
 * Invalid UTF8 strings will count up to invalid character
 */
gcsl_size_t		gcsl_string_charlen(gcsl_cstr_t string);

/* Length of the string in characters, counting up to the given bytes in string
 * NULL and empty strings return length of 0
 * Invalid UTF8 strings will count up to invalid character
 */
gcsl_size_t		gcsl_string_charnlen(gcsl_cstr_t string, gcsl_size_t uptobytes);

/* Test for empty string
 * Empty string is NULL or 0 characters
 */
gcsl_bool_t		gcsl_string_isempty(gcsl_cstr_t string);

/* Test for valid string (ensure in proper encoding, ie: UTF-8)
 * Empty string is considered valid
 */
gcsl_bool_t		gcsl_string_isvalid(gcsl_cstr_t string);

/*
** Concatenation
*/

/* concatenate src string to destination string. source string will be
** truncated if it does not fit dest buffer */
gcsl_str_t		gcsl_string_strcat(gcsl_str_t dest, gcsl_size_t dest_size, gcsl_cstr_t src);

/* concatenate count characters of src string to destination string. source 
** string will be truncated if it does not fit dest buffer */
gcsl_str_t		gcsl_string_strncat(gcsl_str_t dest, gcsl_size_t dest_size, gcsl_cstr_t src, gcsl_size_t src_count);

/* accumulate strings into single string buffer (efficient concatenation) */
GCSL_DECLARE_HANDLE( gcsl_string_accum_handle_t );

gcsl_error_t	gcsl_string_accum_create		(gcsl_string_accum_handle_t* p_accum_handle, gcsl_str_t initial_static_buf, gcsl_size_t initial_buf_size);
gcsl_error_t	gcsl_string_accum_append		(gcsl_string_accum_handle_t accum_handle, gcsl_cstr_t string, gcsl_cstr_t* p_full_str);
gcsl_error_t	gcsl_string_accum_append_chars	(gcsl_string_accum_handle_t accum_handle, gcsl_cstr_t string, gcsl_size_t count, gcsl_cstr_t* p_full_str);
gcsl_error_t	gcsl_string_accum_append_bytes	(gcsl_string_accum_handle_t accum_handle, const gcsl_byte_t* bytes, gcsl_size_t byte_len, gcsl_cstr_t* p_full_str);
gcsl_error_t	gcsl_string_accum_append_format	(gcsl_string_accum_handle_t accum_handle, gcsl_cstr_t format, ...);
gcsl_error_t	gcsl_string_accum_append_vformat(gcsl_string_accum_handle_t accum_handle, gcsl_cstr_t format, va_list argptr);
gcsl_error_t	gcsl_string_accum_bytelen		(gcsl_string_accum_handle_t accum_handle, gcsl_size_t* p_byte_len);
gcsl_error_t	gcsl_string_accum_get_string	(gcsl_string_accum_handle_t accum_handle, gcsl_cstr_t* p_full_str, gcsl_size_t* p_byte_len);
gcsl_error_t	gcsl_string_accum_detach		(gcsl_string_accum_handle_t accum_handle, gcsl_str_t* p_full_str, gcsl_size_t* p_byte_len);
gcsl_error_t	gcsl_string_accum_clear			(gcsl_string_accum_handle_t accum_handle);
gcsl_error_t	gcsl_string_accum_delete		(gcsl_string_accum_handle_t accum_handle);

/*
** Searching
*/

/* Find first occurrence of specified character in string */
gcsl_cstr_t		gcsl_string_strchr(gcsl_cstr_t string, gcsl_uint32_t c);

/* Find last occurrence of specified character in string */
gcsl_cstr_t		gcsl_string_strrchr(gcsl_cstr_t string, gcsl_uint32_t c);

/* Finds the pattern in the string (returns pointer to pattern in string) */
gcsl_cstr_t		gcsl_string_strstr(gcsl_cstr_t string, gcsl_cstr_t pattern);

/* Finds the pattern in the string (return pointer to after pattern in string) */
gcsl_cstr_t		gcsl_string_strrstr(gcsl_cstr_t string, gcsl_cstr_t pattern);

/*	Search string for substring.  If found, returns a pointer to the beginning of the substring in string,
 *	sets p_end to point to the character after substring, and sets p_count to the number of characters that matched.
 *  p_end and p_count are optional and if set to null this API is functionally the same as gcsl_string_strstr.
 */
gcsl_cstr_t
gcsl_string_substring(
	gcsl_cstr_t		string,
	gcsl_cstr_t		substring,
	gcsl_cstr_t*	p_end,
	gcsl_size_t*	p_count
	);

/*
** Parsing
*/

/* Tokenise the string (re-enterant) */
gcsl_str_t		gcsl_string_strtok(gcsl_str_t string, gcsl_cstr_t delimiters, gcsl_str_t* last_pos, gcsl_char_t* delim_hit);

/* Get next character
 * Character returned as gcsl_uint32_t since it could be multi-byte.
 * Parameter p automatically advanced to next character.
 */
gcsl_uint32_t	gcsl_string_charnext(const gcsl_char_t** p, gcsl_size_t* p_byte_size);

/* Set character to buffer
 * Writes wide character 'c' to utf8 buffer
 * Returns pointer to dest
 */
gcsl_cstr_t 	gcsl_string_setchar(gcsl_char_t* dest, gcsl_size_t dest_size, gcsl_uint32_t c, gcsl_size_t* p_char_bytes);

/* Get next character size
 * returns the number of bytes the character in the string is
 */
gcsl_size_t		gcsl_string_nextcharsize(gcsl_cstr_t p);

/*
** Reversing 
*/

/* in place and keeps UTF8 intact */
gcsl_str_t		gcsl_string_reverse(gcsl_str_t string);

/*
** Case Conversion
*/
/* Convert (in place) a string to lower case */
gcsl_str_t		gcsl_string_tolower(gcsl_str_t str);
/* Convert (in place) a string to upper case */
gcsl_str_t		gcsl_string_toupper(gcsl_str_t str);


/*
** Formatting
*/

/* format string into given buffer */
gcsl_size_t		gcsl_string_snprintf(gcsl_str_t s, gcsl_size_t dest_size, gcsl_cstr_t format, ...);
gcsl_size_t		gcsl_string_vsnprintf(gcsl_str_t s, gcsl_size_t dest_size, gcsl_cstr_t format, va_list argptr);

/* format string into allocated buffer. Use gcsl_string_free() to free returned string */
gcsl_str_t		gcsl_string_mprintf(gcsl_cstr_t format, ...);
gcsl_str_t		gcsl_string_vmprintf(gcsl_cstr_t format, va_list argptr);

/* remove leading and trailing whitespace (performed in-place) */
gcsl_str_t		gcsl_string_trim(gcsl_str_t s);

/*
** Conversion
*/
gcsl_int32_t	gcsl_string_atoi32(gcsl_cstr_t s);
gcsl_uint32_t	gcsl_string_atou32(gcsl_cstr_t s);
gcsl_uint64_t	gcsl_string_atou64(gcsl_cstr_t s);
gcsl_flt64_t	gcsl_string_atof64(gcsl_cstr_t s);

gcsl_str_t		gcsl_string_i32toa(gcsl_int32_t n, gcsl_str_t s, gcsl_size_t size);
gcsl_str_t		gcsl_string_u32toa(gcsl_uint32_t n, gcsl_str_t s, gcsl_size_t size);

gcsl_int32_t	gcsl_string_strtol(gcsl_cstr_t s, const gcsl_char_t** endp, gcsl_int16_t base);
gcsl_uint32_t	gcsl_string_strtoul(gcsl_cstr_t s, const gcsl_char_t** endp, gcsl_int16_t base);
gcsl_uint64_t	gcsl_string_strtoull(gcsl_cstr_t s, const gcsl_char_t** endp, gcsl_int16_t base);

gcsl_bool_t		gcsl_string_atobool(gcsl_cstr_t s);

/*
** Character tests
*/
gcsl_int32_t	gcsl_string_isalpha(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_isalnum(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_isdigit(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_isspace(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_isxdigit(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_isprint(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_islower(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_isupper(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_char_tolower(gcsl_int32_t c);
gcsl_int32_t	gcsl_string_char_toupper(gcsl_int32_t c);

/*
 * Unicode support
 */

#define GCSL_UCS2_TO_UTF8_BUFSIZ(ucs_sz)	((ucs_sz + 2) * 4)
#define GCSL_UTF8_TO_UCS2_BUFSIZ(utf_sz)	((utf_sz + 2) * 4)


gcsl_error_t	gcsl_string_utf8_to_ucs2	(gcsl_cstr_t utf8_str, gcsl_unistr_t* p_ucs2_str, gcsl_bool_t bSwap);
gcsl_error_t	gcsl_string_utf8_to_ucs2_buf(gcsl_cstr_t utf8_str, gcsl_size_t utf8_sz, gcsl_unistr_t ucs2_str, gcsl_size_t* p_ucs2_sz, gcsl_bool_t bSwap);
gcsl_error_t	gcsl_string_ucs2_to_utf8	(gcsl_cunistr_t ucs2_str, gcsl_str_t* p_utf8_str, gcsl_bool_t bSwap);
gcsl_error_t	gcsl_string_ucs2_to_utf8_buf(gcsl_cunistr_t ucs2_str, gcsl_size_t ucs2_sz, gcsl_str_t utf8_str, gcsl_size_t* p_utf8_sz, gcsl_bool_t bSwap);
gcsl_size_t		gcsl_string_bytelen_uni		(gcsl_cunistr_t ucs2_str);
gcsl_size_t		gcsl_string_charlen_uni		(gcsl_cunistr_t ucs2_str);



#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_STRING_H_ */
