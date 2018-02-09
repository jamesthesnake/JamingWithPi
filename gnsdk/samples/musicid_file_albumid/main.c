/*
 * Copyright (c) 2000-2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	Name: musicid_file_albumid
 *	Description:
 *	AlbumID processing provides an advanced method of media file recognition. The context of the media files 
 *	(their folder location and similarity with other media files) are used to achieve more accurate media recognition. 
 *	This method is best used for groups of media files where the grouping of the results matters as much as obtaining 
 *	accurate, individual results. The gnsdk_musicidfile_query_do_albumid API provides AlbumID processing.
 *
 *	Command-line Syntax:
 *  sample client_id client_id_tag license
*/

/* Online vs Local queries
 *	Set to 0 to have the sample perform online queries.
 *  Set to 1 to have the sample perform local queries.
 *    For local queries, a Gracenote local database must be present.
 */
#ifndef USE_LOCAL
	#define USE_LOCAL					0
#endif

/* GNSDK headers
 *
 * Define the modules your application needs.
 * These constants enable inclusion of headers and symbols in gnsdk.h.
 */
#define GNSDK_MUSICID_FILE			1
#define GNSDK_DSP					1
#define GNSDK_STORAGE_SQLITE		1
#if USE_LOCAL
	#define GNSDK_LOOKUP_LOCAL			1
#endif
#include "gnsdk.h"

/* Standard C headers - used by the sample app, but not required for GNSDK */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if USE_LOCAL
#define MIDF_QUERY_FLAG		GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_MATCHES
#else
#define MIDF_QUERY_FLAG		GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_ALBUMS
#endif

/* Files used by this sample app */
#define			MYAPP_SAMPLE_FILE_1		"data/01_stone_roses.wav"
#define			MYAPP_SAMPLE_FILE_2		"data/04_stone_roses.wav"
#define			MYAPP_SAMPLE_FILE_3		"data/stone roses live.wav"
#define			MYAPP_SAMPLE_FILE_4		"data/Dock Boggs - Sugar Baby - 01.wav"
#define			MYAPP_SAMPLE_FILE_5		"data/kardinal_offishall_01_3s.wav"
#define			MYAPP_SAMPLE_FILE_6		"data/Kardinal Offishall - Quest For Fire - 15 - Go Ahead Den.wav"

/*
 * Local function declarations
 */
static int
_init_gnsdk(
	const char*				client_id,
	const char*				client_id_tag,
	const char*				client_app_version,
	const char*				license_path,
	gnsdk_user_handle_t*	p_user_handle
	);
	
static void
_shutdown_gnsdk(
	gnsdk_user_handle_t		user_handle,
	const char*				client_id
	);

static int				
_do_sample_albumid(
	gnsdk_user_handle_t		user_handle,
	gnsdk_uint32_t			midf_options
	);

/*
* Sample app start (main)
 */
int
main(int argc, char* argv[])
{
	gnsdk_user_handle_t		user_handle			= GNSDK_NULL;
	const char*				client_id			= NULL;
	const char*				client_id_tag		= NULL;
	const char*				client_app_version	= "1";
	const char*				license_path		= NULL;
	int						rc					= 0;
	
	/* Client ID, Client ID Tag and License file must be passed in */
	
	if (argc == 4)
	{
		client_id = argv[1];
		client_id_tag = argv[2];
		license_path = argv[3];
		
		/* GNSDK initialization */
		rc = _init_gnsdk(
				client_id, 
				client_id_tag, 
				client_app_version, 
				license_path, 
				&user_handle
				);

		/* Perform two MusicID-File TrackID lookups,
		 * first with RETURN_SINGLE,
		 * second with RETURN_ALL.
		 */
		if (0 == rc)
		{
			printf("-------AlbumID with 'RETURN_SINGLE' option:-------\n");
			rc = _do_sample_albumid(
					user_handle,
					GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_SINGLE | MIDF_QUERY_FLAG
					);
					
			if (0 == rc)
			{
				printf("-------AlbumID with 'RETURN_ALL' option:-------\n");
				rc = _do_sample_albumid(
						user_handle,
						GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_ALL | MIDF_QUERY_FLAG
						);
			}

			/* Clean up and shutdown */
			_shutdown_gnsdk(user_handle, client_id);
		}
	}
	else
	{
		printf("\nUsage:\n%s clientid clientidtag license\n", argv[0]);
		rc = -1;
	}

	return rc;
}


/* 
* Echo the error and information.
*/
static void
_display_error(
	int				line_num,
	const char*		info,
	gnsdk_error_t	error_code
	)
{
	const gnsdk_error_info_t*       error_info = gnsdk_manager_error_info();

	/* Error_info will never be GNSDK_NULL. 
	 * The SDK will always return a pointer to a populated error info structure. 
	 */
	printf(
		"\n%s\nError 0x%08x - %s\n\tline %d\n",
		info,
		error_info->error_code,
		error_info->error_description,
		line_num
		);
}

/* 
*    Load existing user handle, or register new one.
* 
*    GNSDK requires a user handle instance to perform queries. 
*    User handles encapsulate your Gracenote provided Client ID which is unique for your
*    application. User handles are registered once with Gracenote then must be saved by
*    your application and reused on future invocations.
*/ 
static int
_get_user_handle(
	const char*				client_id,
	const char*				client_id_tag,
	const char*				client_app_version,
	gnsdk_user_handle_t*	p_user_handle
	)
{
	gnsdk_error_t		error				= GNSDK_SUCCESS;
	gnsdk_user_handle_t	user_handle			= GNSDK_NULL;
	char*				user_filename		= NULL;
	size_t				user_filename_len	= 0;
	int					rc					= 0;
	FILE*				file				= NULL;
	
	user_filename_len = strlen(client_id)+strlen("_user.txt")+1;
	user_filename = malloc(user_filename_len);
	
	if (NULL != user_filename)
	{
		strcpy(user_filename,client_id);
		strcat(user_filename,"_user.txt");

		/* Do we have a user saved locally? */
		file = fopen(user_filename, "r");
		if (NULL != file)
		{
			gnsdk_char_t serialized_user_string[1024] = {0};
		
			if (NULL != (fgets(serialized_user_string, 1024, file)))
			{
				/* Create the user handle from the saved user */
				error = gnsdk_manager_user_create(serialized_user_string, &user_handle);
				if (GNSDK_SUCCESS != error)
				{
					_display_error(__LINE__, "gnsdk_manager_user_create()", error);
					rc = -1;
				}
			}
			else
			{
				printf("Error reading user file into buffer.\n");
				rc = -1;
			}
			fclose(file);
		}
		else
		{
			printf("\nInfo: No stored user - this must be the app's first run.\n");
		}

		/* If not, create new one*/
		if (GNSDK_NULL == user_handle)
		{
			error = gnsdk_manager_user_create_new(
						client_id, 
						client_id_tag, 
						client_app_version,
						&user_handle
						);
			if (GNSDK_SUCCESS != error)
			{
				_display_error(__LINE__, "gnsdk_manager_user_create_new()", error);
				rc = -1;
			}
		}
		
		free(user_filename);
	}
	else
	{
		printf("Error allocating memory.\n");
		rc = -1;
	}

	if (rc == 0)
	{
		*p_user_handle = user_handle;
	}

	return rc;
}

#if USE_LOCAL
/* 
*    Display local Gracenote DB information.
*/
static void
_display_embedded_db_info(void)
{
	gnsdk_error_t	error				= GNSDK_SUCCESS;
	gnsdk_cstr_t	format_version		= GNSDK_NULL;
	gnsdk_cstr_t	source_db_id		= GNSDK_NULL;
	gnsdk_cstr_t	source_app_version	= GNSDK_NULL;
	gnsdk_cstr_t	source_sdk_version	= GNSDK_NULL;

	error = gnsdk_lookup_local_storage_version_get(GNSDK_LOOKUP_LOCAL_STORAGE_METADATA, &format_version, &source_db_id, &source_app_version, &source_sdk_version);
	if (!error)
	{
		printf("GracenoteDB Source DB ID : %s\n", source_db_id);
	}
	else
	{
		_display_error(__LINE__, "gnsdk_lookup_local_storage_version_get()", error); 
	}
}
#endif

/* 
*    Display product version information.
*/
static void
_display_gnsdk_product_info(void)
{
	/* Display GNSDK Version infomation */
	printf("\nGNSDK Product Version    : %s \t(built %s)\n", gnsdk_manager_get_product_version(), gnsdk_manager_get_build_date());
}

/* 
*  Enable Logging
*/ 
static int
_enable_logging(void)
{
	gnsdk_error_t			error			= GNSDK_SUCCESS;
	int						rc				= 0;

	error = gnsdk_manager_logging_enable(
				"sample.log",									/* Log file path */					
				GNSDK_LOG_PKG_ALL,								/* Include entries for all packages and subsystems */
				GNSDK_LOG_LEVEL_ERROR|GNSDK_LOG_LEVEL_WARNING,	/* Include only error and warning entries */
				GNSDK_LOG_OPTION_ALL,							/* All logging options: timestamps, thread IDs, etc */
				0,												/* Max size of log: 0 means a new log file will be created each run */
				GNSDK_FALSE										/* GNSDK_TRUE = old logs will be renamed and saved */
				);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_manager_logging_enable()", error); 
		rc = -1;
	}

	return rc;
}

/* 
* Set the application Locale.
*/ 
static int
_set_locale(
	gnsdk_user_handle_t		user_handle
	)
{
	gnsdk_locale_handle_t	locale_handle	= GNSDK_NULL;
	gnsdk_error_t			error			= GNSDK_SUCCESS;
	int						rc				= 0;

	error = gnsdk_manager_locale_load(
				GNSDK_LOCALE_GROUP_MUSIC,		/* Locale group */
				GNSDK_LANG_ENGLISH,				/* Languae */
				GNSDK_REGION_DEFAULT,			/* Region */
				GNSDK_DESCRIPTOR_SIMPLIFIED,	/* Descriptor */
				user_handle,					/* User handle */
				GNSDK_NULL,						/* User callback function */
				0,								/* Optional data for user callback function */
				&locale_handle					/* Return handle */
				);
	if (GNSDK_SUCCESS == error)
	{
		/* Setting the 'locale' as default 
		 * If default not set, no locale-specific results would be available 
		 */
		error = gnsdk_manager_locale_set_group_default(locale_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_manager_locale_set_group_default()", error); 
			rc = -1;
		}
			
		/* The manager will hold onto the locale when set as default
			* so it's ok to release our reference to it here
			*/
		gnsdk_manager_locale_release(locale_handle);
	}
	else
	{
		_display_error(__LINE__, "gnsdk_manager_locale_load()", error);
		rc = -1;
	}

	return rc;
}

/* 
*     Initializing the GNSDK is required before any other APIs can be called.
*     First step is to always initialize the Manager module, then use the returned
*     handle to initialize any modules to be used by the application.
*
*     For this sample, we also load a locale which is used by GNSDK to provide 
*     appropriate locale-sensitive metadata for certain metadata values. Loading of the
*     locale is done here for sample convenience but can be done at anytime in your 
*     application.
*/ 
static int
_init_gnsdk(
	const char*				client_id,
	const char*				client_id_tag,
	const char*				client_app_version,
	const char*				license_path,
	gnsdk_user_handle_t*	p_user_handle
	)
{
	gnsdk_manager_handle_t	sdkmgr_handle	= GNSDK_NULL;
	gnsdk_error_t			error			= GNSDK_SUCCESS;
	gnsdk_user_handle_t		user_handle		= GNSDK_NULL;
	int						rc				= 0;
	
	/* Display GNSDK Product Version Info */
	_display_gnsdk_product_info();

	/* Initialize the GNSDK Manager */
	error = gnsdk_manager_initialize(
				&sdkmgr_handle, 
				license_path, 
				GNSDK_MANAGER_LICENSEDATA_FILENAME
				);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_manager_initialize()", error); 
		rc = -1;
	}

	/* Enable logging */
	if (0 == rc)
	{
		rc = _enable_logging();
	}

	/* Initialize the Storage SQLite Library */
	if (0 == rc)
	{
		error = gnsdk_storage_sqlite_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_storage_sqlite_initialize()", error); 
			rc = -1;
		}
	}

#if USE_LOCAL
	/* Set the storage path to ../sample_db as there is where the sample GracenoteDB lives. */
	if (0 == rc)
	{
		error = gnsdk_storage_sqlite_option_set(GNSDK_STORAGE_SQLITE_OPTION_STORAGE_FOLDER, "../sample_db");
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_storage_sqlite_option_set()", error); 
			rc = -1;
		}              
	}

	/* Initialize the Lookup Local Library */
	if (0 == rc)
	{
		error = gnsdk_lookup_local_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_lookup_local_initialize()", error); 
			rc = -1;
		}
		else
		{
			/* Display information about our local EDB */
			_display_embedded_db_info();
		}
	}
#endif

	/* Initialize the DSP library - used for fingerprint generation. */
	if (0 == rc)
	{
		error = gnsdk_dsp_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_dsp_initialize()", error); 
			rc = -1;
		}
	}

	/* Initialize the MusicID-File library */
	if (0 == rc)
	{
		error = gnsdk_musicidfile_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicidfile_initialize()", error); 
			rc = -1;
		}
	}

	/* Get a user handle for our client ID.  This will be passed in for all queries */
	if (0 == rc)
	{
		rc = _get_user_handle(
					client_id, 
					client_id_tag, 
					client_app_version, 
					&user_handle
					);
	}
	
#if USE_LOCAL
	/* Set the user option to use our local Gracenote DB unless overridden. */
	if (0 == rc)
	{
		error = gnsdk_manager_user_option_set(
					user_handle,
					GNSDK_USER_OPTION_LOOKUP_MODE,
					GNSDK_LOOKUP_MODE_LOCAL
					);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_manager_user_option_set()", error);
			rc = -1;
		}
	}
#endif

	/* Set the 'locale' to return locale-specifc results values. This examples loads an English locale. */
	if (0 == rc)
	{
		rc = _set_locale(user_handle);
	}

	if (0 != rc)
	{
		/* Clean up on failure. */
		_shutdown_gnsdk(user_handle, client_id);
	}
	else
	{
		/* return the User handle for use at query time */
		*p_user_handle = user_handle;
	}

	return rc;
}

/* 
*     Call shutdown all initialized GNSDK modules.
*     Release all existing handles before shutting down any of the modules.
*     Shutting down the Manager module should occur last, but the shutdown ordering of
*     all other modules does not matter.
*/
static void
_shutdown_gnsdk(
	gnsdk_user_handle_t		user_handle,
	const char*				client_id
	)
{
	gnsdk_error_t	error							= GNSDK_SUCCESS;
	gnsdk_str_t		updated_serialized_user_string	= GNSDK_NULL;
	char*			user_filename					= GNSDK_NULL;
	size_t			user_filename_len				= 0;
	int				rc								= 0;
	int				return_value					= 0;
	FILE*			file							= NULL;

	/* Release our user handle and see if we need to update our stored version */
	error = gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_manager_user_release()", error); 
	}
	else if (GNSDK_NULL != updated_serialized_user_string)
	{
		user_filename_len = strlen(client_id)+strlen("_user.txt")+1;
		user_filename = malloc(user_filename_len);

		if (NULL != user_filename)
		{
			strcpy(user_filename,client_id);
			strcat(user_filename,"_user.txt");

			file = fopen(user_filename, "w");
			if (NULL != file)
			{
				return_value = fputs(updated_serialized_user_string, file);
				if (0 > return_value)
				{
					printf("Error writing user registration file from buffer.\n");
					rc = -1;
				}
				fclose(file);
			}
			else
			{
				printf("\nError: Failed to open the user filename for use in saving the updated serialized user. (%s)\n", user_filename);
			}
			free(user_filename);
		}
		else
		{
			printf("\nError: Failed to allocated user filename for us in saving the updated serialized user.\n");
		}
		gnsdk_manager_string_free(updated_serialized_user_string);
	}

	/* Shutdown the libraries */
#if USE_LOCAL
	gnsdk_lookup_local_shutdown();
#endif
	gnsdk_dsp_shutdown();
	gnsdk_musicidfile_shutdown();
	gnsdk_storage_sqlite_shutdown();
	gnsdk_manager_shutdown();
}

static int
_set_fingerprint(
	gnsdk_musicidfile_fileinfo_handle_t	fileinfo_handle	
	)
{
	gnsdk_error_t				error					= GNSDK_SUCCESS;
	gnsdk_bool_t				complete				= GNSDK_FALSE;
	gnsdk_cstr_t				file					= GNSDK_NULL;
	size_t						read					= 0;
	FILE*						p_file					= NULL;
	char						pcm_audio[2048]			= {0};

	/* get the file */
	error = gnsdk_musicidfile_fileinfo_metadata_get(fileinfo_handle, GNSDK_MUSICIDFILE_FILEINFO_VALUE_FILENAME, &file, GNSDK_NULL);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_metadata_get() failed", error);
		return -1;
	}

	/* check file for existence */
	p_file = fopen(file, "rb");
	if (p_file == NULL)
	{
		printf("\n\nError: Failed to open input file: %s\n\n", file);
		return -1;
	}
	else
	{
		/* skip the wave header (first 44 bytes). we know the format of our sample files, but please
		be aware that many wav file headers are larger then 44 bytes! */
		if (0 != fseek(p_file, 44, SEEK_SET))
		{
			printf("\n\nError: Failed to seek past header: %s\n\n", file);
		}
		else
		{
			/* initialize the fingerprinter
			Note: Our sample files are non-standard 11025 Hz 16-bit mono to save on file size */
			error = gnsdk_musicidfile_fileinfo_fingerprint_begin(fileinfo_handle, 11025, 16, 1);
			if (GNSDK_SUCCESS != error)
			{
				_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_fingerprint_begin() failed", error);
			}
			else
			{
				read = fread(pcm_audio, sizeof(char), 2048, p_file);
				while (read > 0)
				{
					/* write audio to the fingerprinter */
					error = gnsdk_musicidfile_fileinfo_fingerprint_write(
								fileinfo_handle,
								pcm_audio,
								read,
								&complete
								);
					if (GNSDK_SUCCESS != error)
					{
						if (GNSDKERR_SEVERE(error)) /* 'aborted' warnings could come back from write which should be expected */
							_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_fingerprint_write() failed", error);
						break;
					}

					/* does the fingerprinter have enough audio? */
					if (GNSDK_TRUE == complete)
					{
						break;
					}

					read = fread(pcm_audio, sizeof(char), 2048, p_file);
				}
			}
		}
		fclose(p_file);
	}

	/* signal that we are done */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_musicidfile_fileinfo_fingerprint_end(fileinfo_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_fingerprint_end() failed", error);
		}
	}

	if (GNSDK_TRUE != complete)
	{
		/* Fingerprinter doesn't have enough data to generate a fingerprint. 
			Note that the sample data does include one track that is too short to fingerprint. */
		printf("Warning: input file does contain enough data to generate a fingerprint:\n%s\n", file);
	}
	
	return 0;
}
	
static int
_set_metadata(
	gnsdk_musicidfile_fileinfo_handle_t	fileinfo_handle
	)
{
	gnsdk_error_t	error		= GNSDK_SUCCESS;
	gnsdk_cstr_t	file		= GNSDK_NULL;

	/* get the file's identifier */
	error = gnsdk_musicidfile_fileinfo_metadata_get(fileinfo_handle, GNSDK_MUSICIDFILE_FILEINFO_VALUE_IDENT, &file, GNSDK_NULL);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_metadata_get() failed", error);
		return -1;
	}

	/*
	 * A typical use for this callback is to read file tags (ID3, etc) for the basic
	 * metadata of the track.  To keep the sample code simple, we went with .wav files
	 * and hardcoded in metadata for just one of the sample tracks.  (MYAPP_SAMPLE_FILE_5)
	 */

	/* So, if this isn't the correct sample track, return.*/
	if (0 != strcmp(MYAPP_SAMPLE_FILE_5, file))
	{
		return 0;
	}

	error = gnsdk_musicidfile_fileinfo_metadata_set(
				fileinfo_handle,
				GNSDK_MUSICIDFILE_FILEINFO_VALUE_ALBUMARTIST,
				"kardinal offishall"
				);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_metadata_set() failed", error);
	}

	error = gnsdk_musicidfile_fileinfo_metadata_set(
				fileinfo_handle,
				GNSDK_MUSICIDFILE_FILEINFO_VALUE_ALBUMTITLE,
				"quest for fire"
				);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_metadata_set() failed", error);
	}

	error = gnsdk_musicidfile_fileinfo_metadata_set(
				fileinfo_handle,
				GNSDK_MUSICIDFILE_FILEINFO_VALUE_TRACKTITLE,
				"intro"
				);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_metadata_set() failed", error);
	}

	return 0;
}	
	
static int
_add_file(
	gnsdk_musicidfile_query_handle_t	query_handle,
	const char*							file_path
	)
{
	gnsdk_error_t						error			= GNSDK_SUCCESS;
	gnsdk_musicidfile_fileinfo_handle_t	fileinfo_handle	= GNSDK_NULL;
	int									rc = 0;

	error = gnsdk_musicidfile_query_fileinfo_create(
				query_handle,
				file_path, /* identifier string - we'll use the file path, which is unique */
				GNSDK_NULL,
				GNSDK_NULL,
				&fileinfo_handle
				);
	if (GNSDK_SUCCESS == error)
	{
		/* Set the file path in the fileinfo */
		error = gnsdk_musicidfile_fileinfo_metadata_set(fileinfo_handle, GNSDK_MUSICIDFILE_FILEINFO_VALUE_FILENAME, file_path);
		/* The created fileinfo are managed by the query handle and won't need to be explicitly released */
		if (GNSDK_SUCCESS == error)
		{
			rc = _set_fingerprint(fileinfo_handle);
			if (0 == rc)
			{
				rc = _set_metadata(fileinfo_handle);
			}
		}
		else
		{
			_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_metadata_set() failed", error);
			rc = -1;
		}
	}
	else
	{
		_display_error(__LINE__, "gnsdk_musicidfile_query_fileinfo_create() failed", error);
		rc = -1;
	}

	if (0 != rc)
	{
		printf("\nError: Failed to add file %s to the query", file_path);
	}
	return rc;
}

static int
_set_query_data(
	gnsdk_musicidfile_query_handle_t	query_handle
	)
{
	int									rc = 0;

	/* add our 6 sample files to the query */
	rc = _add_file(query_handle, MYAPP_SAMPLE_FILE_1);
	if (0 == rc)
	{
		rc = _add_file(query_handle, MYAPP_SAMPLE_FILE_2);
	}
	if (0 == rc)
	{
		rc = _add_file(query_handle, MYAPP_SAMPLE_FILE_3);
	}
	if (0 == rc)
	{
		rc = _add_file(query_handle, MYAPP_SAMPLE_FILE_4);
	}
	if (0 == rc)
	{
		rc = _add_file(query_handle, MYAPP_SAMPLE_FILE_5);
	}
	if (0 == rc)
	{
		rc = _add_file(query_handle, MYAPP_SAMPLE_FILE_6);
	}

	return rc;
}

static int
_set_query_options(
	gnsdk_musicidfile_query_handle_t	query_handle
	)
{
	int				rc		= 0;

	/* To use the local data stores for this query, set the 'use local lookup' 
	 * query option to true. 
	 * By default, the lookup will be handled online but many applications
	 * will want to start with a local query and then fall back to an online
	 * query for anything not matched. See the "musicid_lookup_album_local_online"
	 * sample for an example of this 'hybrid' approach.
	 */
#if USE_LOCAL
	gnsdk_error_t	error	= GNSDK_SUCCESS;

	error = gnsdk_musicidfile_query_option_set(
				query_handle, 
				GNSDK_MUSICIDFILE_OPTION_LOOKUP_MODE, 
				GNSDK_LOOKUP_MODE_LOCAL
				);
	if (GNSDK_SUCCESS != error)
	{
		rc = -1;
		_display_error(__LINE__, "gnsdk_musicidfile_query_option_set(GNSDK_MUSICIDFILE_OPTION_USE_LOOKUP_LOCAL) failed", error);
	}
#else
	/* Quiet the compiler warning about this unused param */
	(void)query_handle;
#endif

	return rc;
}

static int
_display_gdo_results(
	gnsdk_gdo_handle_t		results_gdo
	)
{
	gnsdk_error_t			error = GNSDK_SUCCESS;
	gnsdk_uint32_t			album_count = 0;
	gnsdk_uint32_t			alb = 0;
	int						rc = 0;

	if (0 == rc)
	{
		error = gnsdk_manager_gdo_child_count(
					results_gdo,
					GNSDK_GDO_CHILD_ALBUM,
					&album_count
					);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_manager_gdo_child_count() failed", error);
		}
		else
		{
			printf("\tAlbum count: %d\n", album_count);

			/* Note that the GDO accessors below are *ordinal* based, not index based.  so the 'first' of
			anything has a one-based ordinal of '1' - *not* an index of '0' */
			for (alb = 1; alb <= album_count; alb++)
			{
				gnsdk_gdo_handle_t		album_gdo = GNSDK_NULL;

				/* get the album GDO */
				error = gnsdk_manager_gdo_child_get(results_gdo, GNSDK_GDO_CHILD_ALBUM, alb, &album_gdo);
				if (GNSDK_SUCCESS != error)
				{
					_display_error(__LINE__, "gnsdk_manager_gdo_child_get(GNSDK_GDO_CHILD_ALBUM) failed", error);
					rc = -1;
				}
				else
				{
					gnsdk_gdo_handle_t	title_gdo	= GNSDK_NULL;

					/* get the album's official title GDO */
					error = gnsdk_manager_gdo_child_get( album_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &title_gdo );
					if (GNSDK_SUCCESS != error)
					{
						_display_error(__LINE__, "gnsdk_manager_gdo_child_get(GNSDK_GDO_CHILD_TITLE_OFFICIAL) failed", error);
						rc = -1;
					}
					else
					{
						gnsdk_cstr_t			value = GNSDK_NULL;
	
						/* get the display string for the title */
						error = gnsdk_manager_gdo_value_get(title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value);
						if (GNSDK_SUCCESS != error)
						{
							_display_error(__LINE__, "gnsdk_manager_gdo_value_get(GNSDK_GDO_VALUE_DISPLAY) failed", error);
						}
						if (GNSDK_SUCCESS == error)
						{
							printf("\tMatch %d - Album title:\t\t%s\n", alb, value);
						}
						/* release our reference to the title GDO */
						gnsdk_manager_gdo_release(title_gdo);
					}
	
					/* release the current album */
					gnsdk_manager_gdo_release(album_gdo);
				} /* for each album */
			}
		}
	}

	return rc;
}

static int
_display_file_results(
	gnsdk_musicidfile_fileinfo_handle_t	midf_fileinfo
	)
{
	gnsdk_error_t						error = GNSDK_SUCCESS;
	gnsdk_gdo_handle_t					results_gdo = GNSDK_NULL;
	gnsdk_musicidfile_fileinfo_status_t	fileinfo_status = gnsdk_musicidfile_fileinfo_unprocessed;
	gnsdk_error_info_t*					p_error_info = GNSDK_NULL;
	int									rc	= 0;

	if (midf_fileinfo == GNSDK_NULL)
	{
		return -1;
	}

	/* Display the fileinfo's status */
	error = gnsdk_musicidfile_fileinfo_status(midf_fileinfo, &fileinfo_status, &p_error_info);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_status() failed", error);
		return -1;
	}

	if (gnsdk_musicidfile_fileinfo_unprocessed == fileinfo_status)
	{
		printf("\tFile unprocessed. Please retry.\n");
	}
	else if (gnsdk_musicidfile_fileinfo_error == fileinfo_status)
	{
		printf("\tProcessing error (0x%08x %s). Please retry.\n", p_error_info->error_code, p_error_info->error_description);
	}
	else if (gnsdk_musicidfile_fileinfo_result_none == fileinfo_status)
	{
		printf("\tNo results.\n");
	}
	else if ((gnsdk_musicidfile_fileinfo_result_single == fileinfo_status) || (gnsdk_musicidfile_fileinfo_result_all == fileinfo_status))
	{
		if (gnsdk_musicidfile_fileinfo_result_single == fileinfo_status)
		{
			printf("\tSingle result.\n");
		}
		else
		{
			printf("\tMultiple results.\n");
		}
		
		error = gnsdk_musicidfile_fileinfo_get_response_gdo(midf_fileinfo, &results_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicidfile_fileinfo_get_response_gdo() failed", error);
			return -1;
		}

		rc = _display_gdo_results(results_gdo);

		error = gnsdk_manager_gdo_release(results_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_manager_gdo_release() failed", error);
			return -1;
		}
	}

	return rc;
}

static int
_do_sample_albumid(
	gnsdk_user_handle_t					user_handle,
	gnsdk_uint32_t						midf_options
	)
{
	int									rc			= 0;
	gnsdk_error_t						error		= GNSDK_SUCCESS;
	gnsdk_uint32_t						count		= 0;
	gnsdk_uint32_t						i			= 0;
	gnsdk_musicidfile_fileinfo_handle_t	fileinfo_handle	= GNSDK_NULL;
	gnsdk_musicidfile_query_handle_t	query_handle	= GNSDK_NULL;

	/* create the MusicID-File handle */
	error = gnsdk_musicidfile_query_create(
			  user_handle,
			  GNSDK_NULL,
			  GNSDK_NULL,	/* not using callbacks in this sample */
			  &query_handle
			  );
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_query_create() failed", error);
		rc = -1;
	}

	/* Add our sample files to the query. Metadata and fingerprints will be set in the callbacks. */
	if (0 == rc)
	{
		rc = _set_query_data(query_handle);
	}

	/* Set any options */
	if (0 == rc)
	{
		rc = _set_query_options(query_handle);
	}

	/* Perform the Query */
	if (0 == rc)
	{
		error = gnsdk_musicidfile_query_do_albumid(query_handle, midf_options);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicidfile_query_do_albumid() failed", error);
			rc = -1;
		}
	}

	/* Ensure everything is finished. */
	if (0 == rc)
	{
		error = gnsdk_musicidfile_query_wait_for_complete(query_handle, GNSDK_MUSICIDFILE_TIMEOUT_INFINITE, GNSDK_NULL);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicidfile_query_wait_for_complete() failed", error);
			rc = -1;
		}
	}

	/* display the results for each file */
	if (0 == rc)
	{
		error = gnsdk_musicidfile_query_fileinfo_count(query_handle, &count);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicidfile_query_fileinfo_count() failed", error);
			rc = -1;
		}
		else
		{
			printf("\nPrinting results for %u files:\n", count);

			/* for each file in the query... */
			for (i = 0; i < count; i++)
			{
				error = gnsdk_musicidfile_query_fileinfo_get_by_index(query_handle, i, &fileinfo_handle);
				if (GNSDK_SUCCESS != error)
				{
					_display_error(__LINE__, "gnsdk_musicidfile_query_fileinfo_get_by_index() failed", error);
					rc = -1;
					break;
				}

				printf("\n*File %u of %u*\n\n", i + 1, count);
				rc = _display_file_results(fileinfo_handle);
				if (0 != rc)
				{
					break;
				}
			}
			printf("\n\n");
		}
	}

	/* release the query handle */
	error = gnsdk_musicidfile_query_release(query_handle);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_musicidfile_query_release() failed", error);
		rc = -1;
	}

	return rc;
}
