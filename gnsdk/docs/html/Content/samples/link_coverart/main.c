/*
 * Copyright (c) 2000-2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	Name: link_coverart
 *	Description:
 *  Retrieves a coverart image using Link starting with a serialized GDO as source.
 *
 *  Command-line Syntax:
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
#define GNSDK_LINK					1
#define GNSDK_STORAGE_SQLITE		1
#if USE_LOCAL
#define GNSDK_LOOKUP_LOCAL				1
#endif
#include "gnsdk.h"

/* Standard C headers - used by the sample app, but not required for GNSDK */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

static void 
_perform_sample_query(
	gnsdk_user_handle_t		user_handle
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
		if (0 == rc)
		{
			/* Perform a sample query */
			_perform_sample_query(user_handle);
			
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
	const	gnsdk_error_info_t*	error_info = gnsdk_manager_error_info();
	
	/* Error_info will never be GNSDK_NULL. 
	 * The SDK will always return a pointer to a populated error info structure. 
	 */
	printf(
		"\nerror 0x%08x - %s\n\tline %d, info %s\n",
		error_code,
		error_info->error_description,
		line_num,
		info
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
				GNSDK_DESCRIPTOR_SIMPLIFIED,		/* Descriptor */
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

	/* Initialize the Link Content Library */
	if (0 == rc)
	{
		error = gnsdk_link_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_link_initialize()", error); 
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
	gnsdk_link_shutdown();
	gnsdk_storage_sqlite_shutdown();
	gnsdk_manager_shutdown();
}

static int
_fetch_image(
	gnsdk_link_query_handle_t	query_handle,
	gnsdk_link_content_type_t	image_type,
	gnsdk_char_t*				image_type_str
	)
{
	gnsdk_link_data_type_t	data_type	= gnsdk_link_data_unknown;
	gnsdk_byte_t*			buffer		= GNSDK_NULL;
	gnsdk_size_t			buffer_size	= 0;
	int						rc			= 0;
	gnsdk_error_t			error		= GNSDK_SUCCESS;
	
	error = gnsdk_link_query_content_retrieve(
				query_handle, 
				image_type, 
				1,
				&data_type, 
				&buffer, 
				&buffer_size);

	if (GNSDK_SUCCESS == error)
	{
		/* data_type will always be == gnsdk_link_data_image_jpeg */

		/* Do something with the image, e.g. display, save, etc. Here we just print the size. */
		printf("\nRETRIEVED: %s image: %d byte JPEG\n", image_type_str, (gnsdk_uint32_t)buffer_size);

		/* free the data when you are done with it */
		error = gnsdk_link_query_content_free(buffer);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_link_query_content_free()", error);
			rc = -1;
		}
	}
	else
	{
		if (GNSDKERR_NotFound != GNSDKERR_ERROR_CODE(error))
		{
			_display_error(__LINE__, "gnsdk_link_query_content_retrieve()", error);
			rc = -1;
		}
		else
		{
			/* Do not return error code for not found. */
			/* For image to be fetched, it must exist in the size specified and you must be entitled to fetch images. */
			printf("\nNOT FOUND: %s image\n", image_type_str);
		}
	}

	return rc;
}

static void
_perform_sample_query(
	gnsdk_user_handle_t			user_handle
	)
{
	gnsdk_gdo_handle_t			input_gdo = GNSDK_NULL;
	gnsdk_link_query_handle_t	query_handle = GNSDK_NULL;
	gnsdk_error_t				error = GNSDK_SUCCESS;

	printf("\n*****Sample Link Album Query*****\n");

	/* Create the query handle. Do not include a callback or callback data (2nd & 3rd args are GNSDK_NULL). */
	error = gnsdk_link_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "gnsdk_link_query_create()", error);
		return;
	}

	/* Set the input GDO */
	if (GNSDK_SUCCESS == error)
	{
		gnsdk_cstr_t		serialized_gdo	= "WEcxAQacioDe8w1fwXyW/BAOhtLnvu0mrWYFDxSlWybQT87DbOSfnixu0+q/JG9M+EnWhnd8n2xJaEgj1RxGf73+b9hmJb4Q+/Z+oT9EpY+5mqrZu+VxeW7CY3o8pz7l0us+o550pL0z8GE4rpp8aNIPCGfiUak1PT4fOaOp53KBVoiSvfO+HkymFN5Q3dOIuzr0AR8QOygen9tx7zXd7mIjkkh4iiJTtG/AyUhYCJdUIAKBgBi79f7rsIzJDuApKCeWRpLXFT0dFx62P7Bz8/696zJqhkRoHJJ2jYkiTtsURQ==";

	    /* Typically, the GDO passed in to a Link query will come from the output of a GNSDK query.
	     * For an example of how to perform a query and get a GDO please refer to the documentation
	     * or other sample applications.
	     * The below serialized GDO was an 1-track album result from another GNSDK query.
	     */
	    error = gnsdk_manager_gdo_deserialize(serialized_gdo, &input_gdo);
	    if (GNSDK_SUCCESS == error)
	    {
		    error = gnsdk_link_query_set_gdo(query_handle, input_gdo);
		    if (GNSDK_SUCCESS != error)
		    {
			    _display_error(__LINE__, "gnsdk_link_query_set_gdo()", error);
		    }
		    
			gnsdk_manager_gdo_release(input_gdo);
	    }
	    else
	    {
		    _display_error(__LINE__, "gnsdk_manager_gdo_deserialize()", error);
	    }
	}

	/* Specify the desired image size */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_link_query_option_set(
					query_handle, 
					GNSDK_LINK_OPTION_KEY_IMAGE_SIZE, 
					GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_170
					);
		if (GNSDK_SUCCESS != error)
	    {
		    _display_error(__LINE__, "gnsdk_link_query_option_set()", error);
	    }
	}

	/* Perform the image fetches */
	if (GNSDK_SUCCESS == error)
	{
		_fetch_image(query_handle, gnsdk_link_content_cover_art, "cover art");
		_fetch_image(query_handle, gnsdk_link_content_image_artist, "artist");
	}


	/* release the Link query handle */
	gnsdk_link_query_release(query_handle);
}
