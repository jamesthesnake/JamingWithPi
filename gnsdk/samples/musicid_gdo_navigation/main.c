/*
 * Copyright (c) 2000-2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	Name: musicid_gdo_navigation
 *	Description:
 *	This application uses MusicID to look up Album GDO content,	including Album	artist,	credits, title,	year, and genre. 
 *	It demonstrates	how	to navigate	the	album GDO that returns basic track information,	including artist, credits, title, track	number,	and	genre.
 *	Notes:
 *	For	clarity	and	simplicity error handling in not shown here. 
 *	Refer "logging"	sample to learn	about GNSDK	error handling.
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
	#define USE_LOCAL				0
#endif

/* GNSDK headers 
 *
 * Define the modules your application needs.
 * These constants enable inclusion of headers and symbols in gnsdk.h.
 */
#define GNSDK_MUSICID               1
#define GNSDK_STORAGE_SQLITE        1
#if USE_LOCAL
	#define GNSDK_LOOKUP_LOCAL      1
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


static void	_do_sample_tui_lookups(
	gnsdk_user_handle_t		user_handle
	);

static void	_navigate_album_response_gdo(
	gnsdk_gdo_handle_t				response_gdo
	);

static void	_navigate_track_gdo(
	gnsdk_gdo_handle_t				parent_gdo,
	gnsdk_uint32_t					track_ordinal,
	gnsdk_uint32_t					tab_index
	);

static void	_navigate_contributor_gdo(
	gnsdk_gdo_handle_t				parent_gdo,
	gnsdk_uint32_t					tab_index
	);

static void	_navigate_name_official_gdo(
	gnsdk_gdo_handle_t				parent_gdo,
	gnsdk_uint32_t					tab_index
	);

static void	_navigate_credit_gdo(
	gnsdk_gdo_handle_t				parent_gdo,
	gnsdk_cstr_t					credit_type_key,
	gnsdk_uint32_t					tab_index
	);

static void	_display_gdo_value(
	gnsdk_gdo_handle_t				parent_gdo,
	gnsdk_cstr_t					gdo_value_key,
	gnsdk_cstr_t					name_string,
	gnsdk_uint32_t					tab_index
	);

static void	_create_tab_string(
	gnsdk_uint32_t	tab_index,
	gnsdk_char_t*	tab_string
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
			/* Perform a sample	album lookup from an input GDO */
			_do_sample_tui_lookups(user_handle);

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
	gnsdk_error_t	error	= GNSDK_SUCCESS;
	int				rc		= 0;
	
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

	/* Initialize the MusicID Library */
	if (0 == rc)
	{
		error = gnsdk_musicid_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicid_initialize()", error); 
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
	gnsdk_musicid_shutdown();
	gnsdk_storage_sqlite_shutdown();
	gnsdk_manager_shutdown();
}


/*
 *	Function: _create_tab_string
 *
 *	Description: This function prepares	a string of	tabs needed	to display the given level
 *	of the GDO being displayed.	It fills the 'tab_string' argument with	the	number of tabs
 *	specified by the 'tab_index' argument.
 */
static void	_create_tab_string(
							   gnsdk_uint32_t  tab_index,
							   gnsdk_char_t*   tab_string
							)
{
	gnsdk_uint32_t		index		= 0;
	
	for	(index=0; index<tab_index; index++)
	{
		strcat(tab_string, "\t"); 
	}
}

/*
 *	Function: _display_gdo_value
 *
 *	Description: This function retrieves and displays a	GDO	value from the 'parent_gdo'
 *	argument. It retrieves the value specified by the 'gdo_value_key' argument.
 */
static void	_display_gdo_value(
							   gnsdk_gdo_handle_t			   parent_gdo,
							   gnsdk_cstr_t					   gdo_value_key,
							   gnsdk_cstr_t					   name_string,
							   gnsdk_uint32_t				   tab_index
							   )
{
	gnsdk_error_t			error							= GNSDK_SUCCESS;
	gnsdk_uint32_t			value_count						= 0;
	gnsdk_cstr_t			value_string					= "";
	gnsdk_char_t			error_string[1024]				= "";
	gnsdk_char_t			tab_string[256]					= "";
	gnsdk_uint32_t			ordinal							= 1;

	_create_tab_string(tab_index, tab_string);
	
	/* Retrieve	the	artist type	value string from the contributor GDO */
	error =	gnsdk_manager_gdo_value_count(parent_gdo, gdo_value_key, &value_count);
	
	if (GNSDK_SUCCESS != error)
	{
		strcat(error_string, tab_string);
		strcat(error_string, "Error	Retrieving \"");
		strcat(error_string, gdo_value_key);
		strcat(error_string, "\" GDO Value Count");
		_display_error(__LINE__, error_string, error);
		return;
	}
	else if	(value_count > 1)
	{
		for	(ordinal=1; ordinal<=value_count; ordinal++)
		{
			error =	gnsdk_manager_gdo_value_get(parent_gdo,	gdo_value_key, ordinal,	&value_string);
			
			if (GNSDK_SUCCESS == error)
			{
				printf("%s%s %d: %s\n",	tab_string,	name_string, ordinal, value_string);
			}
			else
			{
				strcat(error_string, tab_string);
				strcat(error_string, "Error	Retrieving \"");
				strcat(error_string, gdo_value_key);
				strcat(error_string, "\" GDO Value");
				_display_error(__LINE__, error_string, error);
				return;
			}  
		}
	}
	else if	(value_count > 0)
	{		 
		error =	gnsdk_manager_gdo_value_get(parent_gdo,	gdo_value_key, 1, &value_string);
		
		if (GNSDK_SUCCESS == error)
		{
			printf("%s%s: %s\n", tab_string, name_string, value_string);
		}
		else
		{
			strcat(error_string, tab_string);
			strcat(error_string, "Error	Retrieving \"");
			strcat(error_string, gdo_value_key);
			strcat(error_string, "\" GDO Value");
			_display_error(__LINE__, error_string, error);
			return;
		}		 
	}
}

/*
 *	Function: _navigate_name_official_gdo
 *
 *	Description: This function demonstrates	how	to navigate	a 'Name	Official'
 *		GDO	retrieved from a parent	GDO. It	takes a	parent GDO as its argument.
 */
static void	_navigate_name_official_gdo(
						gnsdk_gdo_handle_t				parent_gdo,
						gnsdk_uint32_t					tab_index
						)
{
	gnsdk_error_t		error								= GNSDK_SUCCESS;
	gnsdk_gdo_handle_t	name_official_gdo					= GNSDK_NULL;
	gnsdk_uint32_t		child_count							= 0;
	gnsdk_char_t		tab_string[1024]					= "";
		
	_create_tab_string(tab_index, tab_string);	  
	tab_index += 1;
	
	/* Get the 'Name Official' GDO from	the	contributor	GDO	*/
	error =	gnsdk_manager_gdo_child_count(parent_gdo, GNSDK_GDO_CHILD_NAME_OFFICIAL, &child_count);
	
	if (child_count	> 0)
	{
		error =	gnsdk_manager_gdo_child_get(parent_gdo,	GNSDK_GDO_CHILD_NAME_OFFICIAL, 1, &name_official_gdo);
		
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "Error	Retrieving Name	Official GDO\n", error);
			return;
		}
	}
	else
	{
		/* Child GDO doesn't exist,	exit function */
		return;
	}

	/* Navigate	Name Official GDO */
	printf("%sName Official:\n", tab_string);
	
	/* Retrieve	the	display	value string from the 'Name	Official' GDO */
	_display_gdo_value(name_official_gdo, GNSDK_GDO_VALUE_DISPLAY, "Display", tab_index);

	gnsdk_manager_gdo_release(name_official_gdo);
}

/*
 *	Function: _navigate_contributor_gdo
 *
 *	Description: This function demonstrates	how	to navigate	a contributor
 *		GDO	retrieved from a parent	GDO.
 */
static void	_navigate_contributor_gdo(
						gnsdk_gdo_handle_t				parent_gdo,
						gnsdk_uint32_t					tab_index
						)
{
	gnsdk_error_t		error										= GNSDK_SUCCESS;
	gnsdk_gdo_handle_t	contributor_gdo								= GNSDK_NULL;
	gnsdk_gdo_handle_t	collaborator_gdo							= GNSDK_NULL;
	gnsdk_char_t		tab_string[1024]							= "";
	gnsdk_uint32_t		child_count									= 0;
	gnsdk_uint32_t		n											= 0;
	gnsdk_uint32_t		collab_count								= 0;
	
	_create_tab_string(tab_index, tab_string);
	tab_index += 1;
	
	/* Get the contributor GDO from	the	parent GDO */
	error =	gnsdk_manager_gdo_child_count(parent_gdo, GNSDK_GDO_CHILD_CONTRIBUTOR, &child_count);
	
	if (child_count	> 0)
	{
		error =	gnsdk_manager_gdo_child_get(parent_gdo,	GNSDK_GDO_CHILD_CONTRIBUTOR, 1,	&contributor_gdo);

		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "Error	Retrieving Contributor GDO\n", error);
			return;
		}
		error = gnsdk_manager_gdo_child_count(contributor_gdo, GNSDK_GDO_CHILD_CONTRIBUTOR, &collab_count);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "Error	Retrieving Contributor GDO\n", error);
			return;
		}
	}
	else
	{
		/* Child GDO doesn't exist,	exit function */
		return;
	}	

	/* Navigate	Contributor	GDO	*/
	printf("%sContributor:\n", tab_string);

	
	/* Get the 'Name Official' GDO from	the	contributor	GDO	*/
	_navigate_name_official_gdo(contributor_gdo, tab_index);
	
	/* Display the origin value	string(s) from the contributor GDO */
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL1, "Origin Level 1", tab_index);
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL2, "Origin Level 2", tab_index);
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL3, "Origin Level 3", tab_index);
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL4, "Origin Level 4", tab_index);
	
	/* Display the era value string	from the contributor GDO */				   
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ERA_LEVEL1,	"Era Level 1", tab_index);
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ERA_LEVEL2,	"Era Level 2", tab_index);
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ERA_LEVEL3,	"Era Level 3",	tab_index);
	
	/* Display the artist type value string	from the contributor GDO */
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ARTISTTYPE_LEVEL1, "Artist Type	Level 1", tab_index);
	_display_gdo_value(contributor_gdo,	GNSDK_GDO_VALUE_ARTISTTYPE_LEVEL2, "Artist Type	Level 2", tab_index);

	if (collab_count > 0)
	{
		printf("%sThis Contributor is a Collaborative Contributor\n", tab_string);
		n = 1;
		while (!error)
		{
			error = gnsdk_manager_gdo_child_get(contributor_gdo, GNSDK_GDO_CHILD_CONTRIBUTOR, n, &collaborator_gdo);
			if (!error)
			{
				/* Navigate	Contributor	GDO	*/
				if (1 == n)
				{
					printf("%sPrimary Collaborator:\n", tab_string);
				}
				else
				{
					printf("%sCollaborator %d:\n", tab_string, n-1);
				}
	
				/* Get the 'Name Official' GDO from	the	collaborator GDO	*/
				_navigate_name_official_gdo(collaborator_gdo, tab_index);
	
				/* Display the origin value	string(s) from the collaborator GDO */
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL1, "Origin Level 1", tab_index+2);
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL2, "Origin Level 2", tab_index+2);
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL3, "Origin Level 3", tab_index+2);
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ORIGIN_LEVEL4, "Origin Level 4", tab_index+2);
	
				/* Display the era value string	from the collaborator GDO */				   
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ERA_LEVEL1,	"Era Level 1", tab_index+2);
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ERA_LEVEL2,	"Era Level 2", tab_index+2);
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ERA_LEVEL3,	"Era Level 3",	tab_index+2);
	
				/* Display the artist type value string	from the collaborator GDO */
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ARTISTTYPE_LEVEL1, "Artist Type	Level 1", tab_index+2);
				_display_gdo_value(collaborator_gdo,	GNSDK_GDO_VALUE_ARTISTTYPE_LEVEL2, "Artist Type	Level 2", tab_index+2);
	
				gnsdk_manager_gdo_release(collaborator_gdo);
			}
			n++;
		}
	}
	gnsdk_manager_gdo_release(contributor_gdo);
}

/*
 *	Function: _navigate_credit_gdo
 *
 *	Description: This function demonstrates	how	to navigate	a credit GDO
 *		retrieved from a parent	GDO. It	takes as arguments the parent GDO
 *		and	a string key that represents the type of credit	GDO	that will
 *		be retrieved
 *		(GNSDK_GDO_CHILD_CREDIT	or GNSDK_GDO_CHILD_CREDIT_ARTIST.)
 */
static void
_navigate_credit_gdo(
					 gnsdk_gdo_handle_t			parent_gdo,
					 gnsdk_cstr_t				credit_type_key,
					 gnsdk_uint32_t				tab_index
					 )
{
	gnsdk_error_t		error										= GNSDK_SUCCESS;
	gnsdk_gdo_handle_t	credit_gdo									= GNSDK_NULL;
	gnsdk_char_t		tab_string[1024]							= "";
	gnsdk_uint32_t		child_count									= 0;
	
	_create_tab_string(tab_index, tab_string);
	tab_index += 1;
		
	/* Get the credit GDO from the parent GDO */
	error =	gnsdk_manager_gdo_child_count(parent_gdo, credit_type_key, &child_count);
	
	if (child_count	> 0)
	{
		error =	gnsdk_manager_gdo_child_get(parent_gdo,	credit_type_key, 1,	&credit_gdo);
		
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "Error	Retrieving Credit GDO\n", error);
			return;
		}
	}
	else
	{
		/* Child GDO doesn't exist,	exit function */
		return;
	}
	   
	/* Navigate	Credit GDO */
	printf("%sCredit:\n", tab_string);
	
	/* Navigate	the	contributor	GDO	from the credit	GDO	*/
	_navigate_contributor_gdo(credit_gdo, tab_index);
	
	gnsdk_manager_gdo_release(credit_gdo);
}

/*
 *	Function: _navigate_title_official_gdo
 *
 *	Description: This function demonstrates	how	to navigate	a 'Title Official'
 *		GDO	retrieved from a parent	GDO.
 */
static void	_navigate_title_official_gdo(
					gnsdk_gdo_handle_t				parent_gdo,
					gnsdk_uint32_t					tab_index
					)
{
	gnsdk_error_t		error									=	GNSDK_SUCCESS;
	gnsdk_gdo_handle_t	title_official_gdo						=	GNSDK_NULL;
	gnsdk_uint32_t		child_count								=	0;
	gnsdk_char_t		tab_string[1024]						=	"";

	_create_tab_string(tab_index, tab_string);
	tab_index += 1;

	/* Get the title official GDO from the parent GDO */
	error =	gnsdk_manager_gdo_child_count(parent_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, &child_count);
	
	if (child_count	> 0)
	{
		error =	gnsdk_manager_gdo_child_get(parent_gdo,	GNSDK_GDO_CHILD_TITLE_OFFICIAL,	1, &title_official_gdo);
		
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "Error	Retrieving Title Official GDO\n", error);
			return;
		}	  
	}
	else
	{
		/* Child GDO doesn't exist,	exit function */
		return;
	}
	
	/* Navigate	Title Official GDO */
	printf("%sTitle	Official:\n", tab_string);
	
	/* Retrieve	the	display	value string from the 'Title Offical' GDO */
	_display_gdo_value(title_official_gdo, GNSDK_GDO_VALUE_DISPLAY,	"Display", tab_index);
	
	/* Retrieve	the	display	sortable value string from the 'Title Official'	GDO	*/
	_display_gdo_value(title_official_gdo, GNSDK_GDO_VALUE_SORTABLE, "Sortable", tab_index);
 
	gnsdk_manager_gdo_release(title_official_gdo);
}

/*
 *	Function: _navigate_track_gdo
 *
 *	Description: This function demonstrates	how	to navigate	a track	GDO
 *		retrieved from an album	GDO.
 */
static void	_navigate_track_gdo(
					gnsdk_gdo_handle_t				parent_gdo,
					gnsdk_uint32_t					track_ordinal,
					gnsdk_uint32_t					tab_index
					)
{
	gnsdk_error_t		error										= GNSDK_SUCCESS;
	gnsdk_gdo_handle_t	track_gdo									= GNSDK_NULL;
	gnsdk_char_t		tab_string[1024]							= "";
		
	_create_tab_string(tab_index, tab_string); 
	tab_index += 1;
	
	/* Get the Track GDO from the Parent GDO */
	error =	gnsdk_manager_gdo_child_get(parent_gdo,	GNSDK_GDO_CHILD_TRACK, track_ordinal, &track_gdo);
	
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "Error	Retrieving Track GDO\n", error);
		return;
	}
	
	/* Navigate	Track Official GDO */
	printf("%sTrack:\n", tab_string);
	
	/* Display the TUI for this track GDO */
	_display_gdo_value(track_gdo, GNSDK_GDO_VALUE_TUI, "Track TUI",	tab_index);
	
	/* Display the track number	string for this	track GDO */
	_display_gdo_value(track_gdo, GNSDK_GDO_VALUE_TRACK_NUMBER,	"Track Number",	tab_index);
	
	/* Navigate	the	credit GDO from	this track GDO */
	_navigate_credit_gdo(track_gdo, GNSDK_GDO_CHILD_ARTIST, tab_index);
	
	/* Navigate	the	'Title Official' GDO from the track	GDO	*/
	_navigate_title_official_gdo(track_gdo,	tab_index);
	
	/* Display genre level 1 from the track	GDO	*/
	_display_gdo_value(track_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL1,	"Genre Level 1", tab_index);

	/* Display genre level 2 from the track	GDO	*/
	_display_gdo_value(track_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL2,	"Genre Level 2", tab_index);
	
	/* Display genre level 3 from the track	GDO	*/
	_display_gdo_value(track_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL3,	"Genre Level 3", tab_index);

	/* Display the year	from the track GDO */
	_display_gdo_value(track_gdo, GNSDK_GDO_VALUE_YEAR,	"Year",	tab_index);
	
	gnsdk_manager_gdo_release(track_gdo);
}

/*
 *	Function: _navigate_album_response_gdo
 *
 *	Description: This function demonstrates	how	to navigate	the	response GDO
 *		from an	Album-ID match.	It takes a response GDO from an Album	ID match
 *		as an argument.
 */
static void
_navigate_album_response_gdo(
								  gnsdk_gdo_handle_t response_gdo
								 )
{
	gnsdk_error_t		error										= GNSDK_SUCCESS;
	gnsdk_uint32_t		child_count									= 0;
	gnsdk_uint32_t		track_count									= 0;
	gnsdk_gdo_handle_t	album_gdo									= GNSDK_NULL;
	gnsdk_uint32_t		track_ordinal								= 1;
	gnsdk_uint32_t		tab_index									= 1;
	
	printf("\n***Navigating	Result GDO***\n");
	
	printf("Album:\n");
		
	/* Get the album GDO from the match	response */
	error =	gnsdk_manager_gdo_child_count(response_gdo, GNSDK_GDO_CHILD_ALBUM, &child_count);
	
	if (child_count	> 0)
	{
		error =	gnsdk_manager_gdo_child_get(response_gdo,	GNSDK_GDO_CHILD_ALBUM, 1, &album_gdo);
		
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__,"Failed	to Retrieve	Album GDO\n", error);
			return;
		}		 
	}
	else
	{
		/* Child GDO doesn't exist,	exit function */
		return;
	}
		
	/* Display the package language	for	this album GDO */
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_PACKAGE_LANGUAGE_DISPLAY,	"Package Language",	tab_index);
	
	/* Navigate	the	credit artist GDO from the album GDO */
	_navigate_credit_gdo(album_gdo,	GNSDK_GDO_CHILD_ARTIST,	tab_index);
	
	/* Navigate	the	'Title Official' GDO from the album	GDO	*/
	_navigate_title_official_gdo(album_gdo,	tab_index);
	
	/* Display the year	value string from the album	GDO	*/
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_YEAR,	"Year",	tab_index);
	
	/* Display genre level 1 from the album	GDO	*/
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL1,	"Genre Level 1", tab_index);
		
	/* Display genre level 2 from the album	GDO	*/
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL2,	"Genre Level 2", tab_index);

	/* Display genre level 3 from the album	GDO	*/
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL3,	"Genre Level 3", tab_index);

	/* Retrieve	the	album label	value string from the album	GDO	*/
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_ALBUM_LABEL, "Album Label", tab_index);
	
	/* Retrieve	the	'Total in Set' value string	from the album GDO */
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_ALBUM_TOTAL_IN_SET, "Total In	Set", tab_index);
	
	/* Retrieve	the	'Disc in Set' value	string from	the	album GDO */
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_ALBUM_DISC_IN_SET, "Disc In Set",	tab_index);
	
	/* Retrieve	the	track count	value string from the album	GDO	*/
	_display_gdo_value(album_gdo, GNSDK_GDO_VALUE_ALBUM_TRACK_COUNT, "Track	Count",	tab_index);

	/* Get the track GDO child count from the album	GDO	*/
	error =	gnsdk_manager_gdo_child_count(album_gdo, GNSDK_GDO_CHILD_TRACK,	&child_count);
	
	if (GNSDK_SUCCESS != error)
	{
		_display_error(__LINE__, "Error	Retrieving Track Child Count\n", error);
		return;
	}
		
	track_count	= child_count;

	/* Navigate	each track GDO from	the	album GDO for the track	count */
	for	(track_ordinal=1; track_ordinal<=track_count; track_ordinal++)
	{
		_navigate_track_gdo(album_gdo, track_ordinal, tab_index);
	}
	
	gnsdk_manager_gdo_release(album_gdo);
}

/*
 *	Function: _perform_sample_album_tui_lookup
 *
 *	Description: This function looks up	an album by	its	TUI. Upon successful single	matches, it
 *	will call the _navigate_album_response_gdo to navigate and display the album GDO.
 */
static void
_perform_sample_album_tui_lookup(
						   gnsdk_user_handle_t		user_handle,
						   gnsdk_cstr_t				input_tui_id,
						   gnsdk_cstr_t				input_tui_tag
						   )
{
	gnsdk_error_t					error				= GNSDK_SUCCESS;
	gnsdk_musicid_query_handle_t	query_handle		= GNSDK_NULL;
	gnsdk_gdo_handle_t				query_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				response_gdo		= GNSDK_NULL;
	gnsdk_gdo_handle_t				album_gdo			= GNSDK_NULL;
	gnsdk_uint32_t					album_count			= 0;
	gnsdk_cstr_t					value_string		= "";
	
	printf("\n*****Sample MusicID Query*****\n");
	
	/* Create the query	handle */
	error = gnsdk_musicid_query_create(
				user_handle,
				GNSDK_NULL,		/* User callback function */
				GNSDK_NULL,		/* Optional data to be passed to the callback */
				&query_handle
				);
	if (GNSDK_SUCCESS == error)
	{
		/* Obtain GDO Handle */
		error = gnsdk_manager_gdo_create_from_id(
					input_tui_id,
					input_tui_tag,
					GNSDK_ID_SOURCE_ALBUM,
					&query_gdo
					);	
		if (GNSDK_SUCCESS == error)
		{
			/* Set the input GDO */
			error = gnsdk_musicid_query_set_gdo(
						query_handle, 
						query_gdo
						);	
			if (GNSDK_SUCCESS == error)
			{
#if USE_LOCAL
				error = gnsdk_musicid_query_option_set(
							query_handle,
							GNSDK_MUSICID_OPTION_LOOKUP_MODE,
							GNSDK_LOOKUP_MODE_LOCAL
							);
				if (GNSDK_SUCCESS == error)
				{
#endif
					/* Perform the query */
					error = gnsdk_musicid_query_find_albums(
								query_handle,
								&response_gdo
								);

					if (GNSDK_SUCCESS == error)
					{
						error =	gnsdk_manager_gdo_value_get(response_gdo,	GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT, 1, &value_string);
												
						album_count = value_string	? atoi(value_string) : 0;
						
						if (album_count > 0)
						{  
							/* Match */
							printf("Match.\n");
							
							/* Get first album GDO and check if	it's a partial album */
							error =	gnsdk_manager_gdo_child_get(response_gdo,	GNSDK_GDO_CHILD_ALBUM, 1, &album_gdo);
							
							if (GNSDK_SUCCESS != error)
							{
								_display_error(__LINE__, "gnsdk_manager_gdo_child_get(): Error retrieving album	GDO", error);
							}
							else
							{
								/* Is this a partial album? */
								error =	gnsdk_manager_gdo_value_get(album_gdo, GNSDK_GDO_VALUE_FULL_RESULT, 1, &value_string);
																
								if (GNSDK_SUCCESS == error && atoi(value_string) ==	0)
								{
									printf("retrieving FULL	RESULT\n");
									/* Set match back to the existing query	handle */
									error =	gnsdk_musicid_query_set_gdo(query_handle, album_gdo);
									
									/* OK to release selected match	now	(query handle has it) */
									error =	gnsdk_manager_gdo_release(response_gdo);
									
									/* Query for this match	in full	*/
									error =	gnsdk_musicid_query_find_albums(query_handle, &response_gdo);
									
									/* Full	album match	retrieved. Now we navigate the full	album GDO */
									if (GNSDK_SUCCESS == error)
									{
										_navigate_album_response_gdo(response_gdo);
									}
								}
								else
								{
									_navigate_album_response_gdo(response_gdo);
								}
								
								gnsdk_manager_gdo_release(album_gdo);
							}
						}
						else
						{
							/* No Matches */
							printf("No matches.\n");   
						}
                        
						/* Clean up */
						/* Release the response */
						gnsdk_manager_gdo_release(response_gdo);
					}
					else
					{
						_display_error(__LINE__, "gnsdk_musicid_query_find_albums()",error);
					}
#if USE_LOCAL
				}
				else
				{
					_display_error(__LINE__, "gnsdk_musicid_query_option_set()",error);
				}
#endif
			}
			else
			{
				_display_error(__LINE__, "gnsdk_musicid_query_set_gdo()",error);
			}
			/* Clean up */			
			/* Release the query gdo */
			gnsdk_manager_gdo_release(query_gdo);	
		}
		else
		{
			_display_error(__LINE__, "gnsdk_manager_gdo_create_from_id()",error);
		}
		/* Release the query handle */
		gnsdk_musicid_query_release(query_handle);
	}			
	else	
	{
		_display_error(__LINE__, "gnsdk_musicid_query_create()",error);
	}
}


/*
 *	Function: _do_sample_tui_lookups
 *
 *	Description: This function performs	TUI	lookups	for	several	different albums.
 */
static void
_do_sample_tui_lookups(
					gnsdk_user_handle_t		user_handle
					)
{
	gnsdk_cstr_t					input_tui_id		= GNSDK_NULL;
	gnsdk_cstr_t					input_tui_tag		= GNSDK_NULL;

	/* Lookup album: Nelly -	Nellyville to demonstrate collaborative artist navigation in track level (track#12)*/
	input_tui_id	= "30716057";
	input_tui_tag	= "BB402408B507485074CC8B3C6D313616";

	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);

	/* Lookup album: Dido -	Life for Rent */
	input_tui_id	= "46508189";
	input_tui_tag	= "951407B37F9D8EAE68F74B0B5C5E1224";

	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);
	
	/* Lookup album: Jean-Pierre Rampal	- Portrait Of Rampal */
	input_tui_id	= "3020551";
	input_tui_tag	= "CAA37D27FD12337073B54F8E597A11D3";	 

	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);
	
	/* Lookup album: Various Artists - Grieg: Piano	Concerto, Peer Gynth Suites	#1 */
	input_tui_id	= "2971440";
	input_tui_tag	= "7F6C280498E077330B1732086C3AAD8F";	 
	
	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);
	
	/* Lookup album: Stephen Kovacevich	- Brahms: Rhapsodies, Waltzes &	Piano Pieces*/
	input_tui_id	= "2972852";
	input_tui_tag	= "EC246BB5B359D88BEBDC1EF55873311E";	 
	
	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);
	
	/* Lookup album: Nirvana - Nevermind */
	input_tui_id	= "2897699";
	input_tui_tag	= "2FAE8F59CCECBA288810EC27DCD56A0A";	 
	
	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);
	
	/* Lookup album: Eminem	- Encore */
	input_tui_id	= "68056434";
	input_tui_tag	= "C6E3634DF05EF343E3D22CE3A28A901A";	 
	
	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);

	/* Lookup Japanese album: 川澄綾子 - 藍より青し -音絵巻- */
	/* NOTE: In	order to correctly see the Japanese	metadata results for this lookup, */
	/* this	program	will need to write out to UTF-8	*/
	input_tui_id	= "16391605";
	input_tui_tag	= "F272BD764FDEB344A54F53D0756DC3FD";	 
	
	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);
	
	/* Lookup Chinese album: 蘇芮	- 蘇芮經典 */
	/* NOTE: In	order to correctly see the Chinese metadata	results	for	this lookup, */
	/* this	program	will need to write out to UTF-8	*/
	input_tui_id	= "3798282";
	input_tui_tag	= "6BF6849840A77C987E8D3AF675129F33";	 
	
	_perform_sample_album_tui_lookup(user_handle, input_tui_id,	input_tui_tag);
}
