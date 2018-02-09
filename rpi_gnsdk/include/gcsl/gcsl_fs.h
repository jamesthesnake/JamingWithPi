/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_fs.h - File system interface for abstraction layer 
 */

#ifndef	_GCSL_FS_H_
#define _GCSL_FS_H_

#ifdef __cplusplus
extern "C"{
#endif 


#if (defined GCSL_CREATE_IMPORTS)
	#define CENTRALIZED_FILE_API		GCSL_IMPORTED_API
#elif (defined GCSL_CREATE_EXPORTS)
	#define CENTRALIZED_FILE_API		GCSL_EXPORTED_API
#else
	#define CENTRALIZED_FILE_API
#endif

#ifndef GCSL_FS_TEST
	#ifdef _DEBUG
		#define GCSL_FS_TEST    1
	#endif
#endif


/*
 * File and Directory handles
 */

GCSL_DECLARE_HANDLE( gcsl_fs_file_handle_t );
GCSL_DECLARE_HANDLE( gcsl_fs_dir_handle_t );


/*
 * Prototypes.
 */

/* initialize file system subsystem */
gcsl_error_t	gcsl_fs_initialize		(void);
gcsl_error_t	gcsl_fs_shutdown		(void);

gcsl_cstr_t		gcsl_fs_get_version		(void);
gcsl_cstr_t		gcsl_fs_get_build_date	(void);

/*
** Global FS Options APIs
*/
gcsl_error_t	gcsl_fs_option_set			(gcsl_cstr_t option_name, gcsl_cstr_t option_value);
gcsl_error_t	gcsl_fs_option_get			(gcsl_cstr_t option_name, gcsl_cstr_t* p_option_value);

#define GCSL_FS_OPTION_MAX_HANDLES			"gcsl_fs_max_handles"

/*
** File Name based APIs
*/
gcsl_error_t	gcsl_fs_file_delete			(gcsl_cstr_t filename);
gcsl_error_t	gcsl_fs_file_exists			(gcsl_cstr_t filename, gcsl_bool_t* pb_exists);
gcsl_error_t	gcsl_fs_file_copy			(gcsl_cstr_t source_file, gcsl_cstr_t dest_file, gcsl_bool_t b_fail_if_exists);
gcsl_error_t	gcsl_fs_file_rename			(gcsl_cstr_t old_file, gcsl_cstr_t new_file);
gcsl_error_t	gcsl_fs_file_get_attributes	(gcsl_cstr_t filename, gcsl_uint32_t* p_attributes);
gcsl_error_t	gcsl_fs_file_set_attributes	(gcsl_cstr_t filename, gcsl_uint32_t attributes);
gcsl_error_t	gcsl_fs_file_get_size		(gcsl_cstr_t filename, gcsl_uint64_t* p_file_size);
gcsl_error_t	gcsl_fs_file_read_to_buffer	(gcsl_cstr_t filename, gcsl_void_t** p_data, gcsl_size_t* p_data_size, gcsl_bool_t b_null_term);
gcsl_error_t	gcsl_fs_file_write_to_file	(gcsl_cstr_t filename, const gcsl_void_t* p_data, gcsl_size_t data_size, gcsl_bool_t b_append);

/*
** File Open APIs
*/
gcsl_error_t	gcsl_fs_file_open			(gcsl_cstr_t filename, gcsl_uint32_t mode, gcsl_uint32_t attributes, gcsl_fs_file_handle_t* p_file_handle);
#ifdef _GCSL_IOSTREAM_H_
gcsl_error_t	gcsl_fs_file_open_stream	(gcsl_cstr_t filename, gcsl_uint32_t mode, gcsl_uint32_t attributes, gcsl_iostream_handle_t* ph_iostream);
#endif

/* open/create modes */
#define GCSL_FSMODE_Read			0x0000001
#define GCSL_FSMODE_Write			0x0000002
#define GCSL_FSMODE_Append			0x0000004
#define GCSL_FSMODE_Create			0x0000010
#define GCSL_FSMODE_Truncate		0x0000020
#define GCSL_FSMODE_Exclusive		0x0000100

/* file attributes */
#define GCSL_FSATTR_Read			0x0001
#define GCSL_FSATTR_Write			0x0002
#define GCSL_FSATTR_ReadWrite		(GCSL_FSATTR_Read|GCSL_FSATTR_Write)

/* defined filename values */
#define GCSL_FSNAME_STDIN			"gcsl_fsname_stdin"
#define GCSL_FSNAME_STDOUT			"gcsl_fsname_stdout"
#define GCSL_FSNAME_STDERR			"gcsl_fsname_stderr"

/*
** File Handle based APIs
*/
gcsl_error_t	gcsl_fs_file_read			(gcsl_fs_file_handle_t file_handle, gcsl_void_t* buffer, gcsl_size_t size, gcsl_size_t* p_bytes_read);
gcsl_error_t	gcsl_fs_file_read_at		(gcsl_fs_file_handle_t file_handle, gcsl_uint64_t offset, gcsl_void_t* buffer, gcsl_size_t size, gcsl_size_t* p_bytes_read);
gcsl_error_t	gcsl_fs_file_read_line		(gcsl_fs_file_handle_t file_handle, gcsl_char_t* buffer, gcsl_size_t size);
gcsl_error_t	gcsl_fs_file_write			(gcsl_fs_file_handle_t file_handle, const gcsl_void_t* buffer, gcsl_size_t size, gcsl_size_t* p_bytes_written);
gcsl_error_t	gcsl_fs_file_vwrite			(gcsl_fs_file_handle_t file_handle, gcsl_cstr_t format, va_list argptr, gcsl_size_t* p_bytes_written);
gcsl_error_t	gcsl_fs_file_write_at		(gcsl_fs_file_handle_t file_handle, gcsl_uint64_t offset, const gcsl_void_t* buffer, gcsl_size_t size, gcsl_size_t* p_bytes_written);
gcsl_error_t	gcsl_fs_file_seek			(gcsl_fs_file_handle_t file_handle, gcsl_uint64_t offset, gcsl_uint32_t origin);

/* seek origin values */
#define GCSL_FS_SEEK_START			1
#define GCSL_FS_SEEK_CURRENT		2
#define GCSL_FS_SEEK_END			3

gcsl_error_t	gcsl_fs_file_get_name		(gcsl_fs_file_handle_t file_handle, gcsl_cstr_t* p_filename);
gcsl_error_t	gcsl_fs_file_get_position	(gcsl_fs_file_handle_t file_handle, gcsl_uint64_t* p_offset);
gcsl_error_t	gcsl_fs_file_get_eof		(gcsl_fs_file_handle_t file_handle, gcsl_bool_t* pb_eof);
gcsl_error_t	gcsl_fs_file_truncate		(gcsl_fs_file_handle_t file_handle, gcsl_uint64_t offset);
gcsl_error_t	gcsl_fs_file_size			(gcsl_fs_file_handle_t file_handle, gcsl_uint64_t* p_file_size);
gcsl_error_t	gcsl_fs_file_attributes		(gcsl_fs_file_handle_t file_handle, gcsl_uint32_t* p_attributes);
gcsl_error_t	gcsl_fs_file_commit			(gcsl_fs_file_handle_t file_handle);
gcsl_error_t	gcsl_fs_file_close			(gcsl_fs_file_handle_t file_handle);

#ifdef _GCSL_IOSTREAM_H_
gcsl_error_t	gcsl_fs_file_get_stream		(gcsl_fs_file_handle_t file_handle, gcsl_iostream_handle_t* ph_iostream);
#endif

/*
** Directory Browsing APIs
*/
gcsl_error_t	gcsl_fs_dir_open			(gcsl_cstr_t path, gcsl_fs_dir_handle_t* p_dir_handle);
gcsl_error_t	gcsl_fs_dir_create			(gcsl_cstr_t path, /* optional */ gcsl_fs_dir_handle_t* p_dir_handle);
gcsl_error_t	gcsl_fs_dir_delete			(gcsl_cstr_t path, gcsl_bool_t b_recurse);
gcsl_error_t	gcsl_fs_dir_exists			(gcsl_cstr_t path, gcsl_bool_t* pb_exists);
gcsl_error_t	gcsl_fs_dir_next_entry		(gcsl_fs_dir_handle_t dir_handle, gcsl_cstr_t* p_entry_name, gcsl_uint32_t* p_entry_type);

/* directory entry types */
#define GCSL_FSTYPE_Unknown			0x00
#define GCSL_FSTYPE_Dir				0x04
#define GCSL_FSTYPE_File			0x08
#define GCSL_FSTYPE_Link			0x10

gcsl_error_t	gcsl_fs_dir_close			(gcsl_fs_dir_handle_t dir_handle);


/*
** GCSL_FS Metrics
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_fs_marker_status_callback_fn)(
	const gcsl_void_t*	app_data,
	gcsl_cstr_t			filename,
	gcsl_size_t			write_count,
	gcsl_size_t			write_bytes,
	gcsl_size_t			write_largest,
	gcsl_size_t			read_count,
	gcsl_size_t			read_bytes,
	gcsl_size_t			read_larest,
	gcsl_size_t			seek_count,
	gcsl_bool_t			b_file_opened,
	gcsl_bool_t			b_file_closed
	);

CENTRALIZED_FILE_API gcsl_void_t		gcsl_fs_marker_initialize	(gcsl_fs_marker_status_callback_fn callback_fn);
CENTRALIZED_FILE_API gcsl_void_t		gcsl_fs_marker_start		(const gcsl_void_t* app_data, gcsl_void_t** p_marker_data);
CENTRALIZED_FILE_API gcsl_void_t		gcsl_fs_marker_end			(gcsl_void_t* marker_data);

#define GCSL_FS_MARKSTART(app_data)		{ gcsl_void_t* __p_fs_marker; gcsl_fs_marker_start(app_data, &__p_fs_marker);
#define GCSL_FS_MARKEND					gcsl_fs_marker_end(__p_fs_marker); }


#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_FS_H_ */

