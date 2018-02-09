/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_pathsh - gcsl_paths header
 */

#ifndef _GCSL_PATHS_H_
#define _GCSL_PATHS_H_

#ifdef	__cplusplus
extern "C" {
#endif


/*
 * Initialization
 */

gcsl_error_t	gcsl_paths_initialize		(void);
gcsl_error_t	gcsl_paths_shutdown			(void);

gcsl_cstr_t		gcsl_paths_get_version		(void);
gcsl_cstr_t		gcsl_paths_get_build_date	(void);

/*
 * gcsl_paths_cleanse
 * replaces non-legal chars with appropriate alternatives (in-place)
 */
gcsl_error_t	gcsl_paths_cleanse(gcsl_cstr_t filename);

/*
 * gcsl_paths_pathcompare
 * compare full path and filename with respect to case sensitivity of local filesystem
 */
gcsl_int16_t	gcsl_paths_pathcompare(gcsl_cstr_t path1, gcsl_cstr_t path2);

/*
 * gcsl_paths_foldercompare
 * compare folders (regardless of filenames) with respect to case sensitivity of local filesystem
 */
gcsl_int16_t	gcsl_paths_foldercompare(gcsl_cstr_t path1, gcsl_cstr_t path2);

/*
 * gcsl_paths_filenamecompare
 * compare filenames (regardless of folders) with respect to case sensitivity of local filesystem
 */
gcsl_int16_t	gcsl_paths_filenamecompare(gcsl_cstr_t path1, gcsl_cstr_t path2);


/*
 * gcsl_paths_splitpath
 * divide full path into folder, filename and extension components
 */
gcsl_error_t	gcsl_paths_splitpath(gcsl_cstr_t path, gcsl_str_t folder_part, gcsl_size_t foldersize, gcsl_str_t file_part, gcsl_size_t filesize, gcsl_str_t ext_part, gcsl_size_t extsize);

/*
 * gcsl_paths_makepath
 * combine folder, filename and extension components into full path
 */
gcsl_error_t	gcsl_paths_makepath(gcsl_str_t path, gcsl_size_t pathsize, gcsl_cstr_t folder_part, gcsl_cstr_t file_part, gcsl_cstr_t ext_part);


/*
 * gcsl_paths_filename_find_template
 * Returns template index and format for given filename
 */
gcsl_error_t	gcsl_paths_filename_find_template(gcsl_cstr_t filename, gcsl_int32_t* p_best_template_index, gcsl_cstr_t* p_template_format);

/*
 * gcsl_paths_parse_filename
 * Parse filename into classified fragments
 * Set template_index to -1 if not yet determined
 */
gcsl_error_t	gcsl_paths_filename_parse(gcsl_cstr_t filename, gcsl_int32_t template_index, gcsl_stringmap_handle_t results);

/* keys to retrieve field values from gcsl_paths_parse_filename results */
#define		GCSL_PATHS_FIELD_TITLE			"_path_field_title"
#define		GCSL_PATHS_FIELD_ARTIST_ALB		"_path_field_artist_alb"
#define		GCSL_PATHS_FIELD_ARTIST_TRK		"_path_field_artist_trk"
#define		GCSL_PATHS_FIELD_ALBUM			"_path_field_album"
#define		GCSL_PATHS_FIELD_TRACKNUM		"_path_field_tracknum"
#define		GCSL_PATHS_FIELD_DISCNUM		"_path_field_discnum"
#define		GCSL_PATHS_FIELD_YEAR			"_path_field_year"
#define		GCSL_PATHS_FIELD_GENRE			"_path_field_genre"





#ifdef	__cplusplus
}
#endif

#endif /* _GCSL_PATHS_H_ */
