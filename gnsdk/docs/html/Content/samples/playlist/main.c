/*
* Copyright (c) 2000-2012 Gracenote.
*
* This software may not be used in any way or distributed without
* permission. All rights reserved.
*
* Some code herein may be covered by US and international patents.
*/

/*
*	Name: Playlist
*	Description: 
*	Playlist is the GNSDK library that generates playlists when integrated with the GNSDK MusicID or MusicID-File 
*	library (or both). Playlist APIs enable an application to:
*	01. Create, administer, populate, and synchronize a collection summary.
*	02. Store a collection summary within a local storage solution.
*	03. Validate PDL statements.
*	04. Generate Playlists using either the More Like This function or the general playlist generation function.
*	05. Manage results.
*	Streamline your Playlist implementation by using the provided More Like This function 
*	(gnsdk_playlist_generate_morelikethis), which contains the More Like This algorithm to generate 
*	optimal playlist results and eliminates the need to create and validate Playlist Definition 
*	Language statements. 
*	Steps:
*	See inline comments below.
*
*	Command-line Syntax:
 *	sample client_id client_id_tag license
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
#define GNSDK_PLAYLIST			1
#define GNSDK_MUSICID			1
#define GNSDK_STORAGE_SQLITE	1
#if USE_LOCAL
#define	GNSDK_LOOKUP_LOCAL				1
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
_perform_sample_playlist(
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
			/* Perform a sample album TOC query */
			_perform_sample_playlist(user_handle);

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
		GNSDK_LOCALE_GROUP_PLAYLIST,	/* Locale group */
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

	/* Initialize the Playlist Library */
	if (0 == rc)
	{
		error = gnsdk_playlist_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_playlist_initialize() failed", error);
			rc = -1;
		}
		else
		{
			/* Specify the location for our collection store. */
			error = gnsdk_playlist_storage_location_set(".");
			if (GNSDK_SUCCESS != error)
			{
				_display_error(__LINE__, "gnsdk_playlist_storage_location_set() failed", error);
				rc = -1;
			}
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
	gnsdk_playlist_shutdown();
	gnsdk_storage_sqlite_shutdown();
	gnsdk_manager_shutdown();
}

/* 
*    Here we are doing basic MusicID queries on CDTOCs to populate a 
*    Playlist Collection Summary.
*    Any GNSDK result GDO can be used for Collection Summary 
*    population.
*/
static gnsdk_error_t
_playlist_collection_populate(
	gnsdk_user_handle_t					user_handle,
	gnsdk_playlist_collection_handle_t	h_playlist_collection
	)
{
	gnsdk_error_t					error			= GNSDK_SUCCESS;
	gnsdk_size_t					count			= 0;
	gnsdk_uint32_t					count_ordinal	= 0;
	gnsdk_uint32_t					ident_count		= 0;
	gnsdk_musicid_query_handle_t	query_handle	= GNSDK_NULL;
	gnsdk_gdo_handle_t				response_gdo	= GNSDK_NULL;
	gnsdk_gdo_handle_t				album_gdo		= GNSDK_NULL;
	gnsdk_cstr_t					input_query_tocs[] =  {
		"150 13224 54343 71791 91348 103567 116709 132142 141174 157219 175674 197098 238987 257905",
		"182 23637 47507 63692 79615 98742 117937 133712 151660 170112 189281",
		"182 14035 25710 40955 55975 71650 85445 99680 115902 129747 144332 156122 170507",
		"150 10705 19417 30005 40877 50745 62252 72627 84955 99245 109657 119062 131692 141827 152207 164085 173597 187090 204152 219687 229957 261790 276195 289657 303247 322635 339947 356272",
		"150 14112 25007 41402 54705 69572 87335 98945 112902 131902 144055 157985 176900 189260 203342",
		"150 1307 15551 31744 45022 57486 72947 85253 100214 115073 128384 141948 152951 167014",
		"183 69633 96258 149208 174783 213408 317508",
		"150 19831 36808 56383 70533 87138 105157 121415 135112 151619 169903 189073",
		"182 10970 29265 38470 59517 74487 83422 100987 113777 137640 150052 162445 173390 196295 221582",
		"150 52977 87922 128260 167245 187902 215777 248265",
		"183 40758 66708 69893 75408 78598 82983 87633 91608 98690 103233 108950 111640 117633 124343 126883 132298 138783 144708 152358 175233 189408 201408 214758 239808",
		"150 92100 135622 183410 251160 293700 334140",
		"150 17710 33797 65680 86977 116362 150932 166355 183640 193035",
		"150 26235 51960 73111 93906 115911 142086 161361 185586 205986 227820 249300 277275 333000",
		"150 1032 27551 53742 75281 96399 118691 145295 165029 189661 210477 232501 254342 282525",
		"150 26650 52737 74200 95325 117675 144287 163975 188650 209350 231300 253137 281525 337875",
		"150 19335 35855 59943 78183 96553 111115 125647 145635 163062 188810 214233 223010 241800 271197",
		"150 17942 32115 47037 63500 79055 96837 117772 131940 148382 163417 181167 201745",
		"150 17820 29895 41775 52915 69407 93767 105292 137857 161617 171547 182482 204637 239630 250692 282942 299695 311092 319080",
		"182 21995 45882 53607 71945 80495 94445 119270 141845 166445 174432 187295 210395 230270 240057 255770 277745 305382 318020 335795 356120",
		"187 34360 64007 81050 122800 157925 195707 230030 255537 279212 291562 301852 310601",
		"150 72403 124298 165585 226668 260273 291185"
	};



	count = sizeof(input_query_tocs) / sizeof(input_query_tocs[0]);
	printf( "\nPopulating Collection Summary from sample TOCs" );
	/* Create the query handle */
	error = gnsdk_musicid_query_create(
		user_handle,
		GNSDK_NULL,     /* User callback function */
		GNSDK_NULL,     /* Optional data to be passed to the callback */
		&query_handle
		);

	/* 
	Set the option for retrieving DSP attributes.
	Note: Please note that these attributes are entitlements to your user id. You must have them enabled in your licence.
	*/
	if (!error)
	{
		error =  gnsdk_musicid_query_option_set(
							query_handle, 
							GNSDK_MUSICID_OPTION_ENABLE_SONIC_DATA, 
							GNSDK_VALUE_TRUE
							);
	}
	/* 
	Set the option for retrieving Playlist attributes.
	Note: Please note that these attributes are entitlements to your user id. You must have them enabled in your licence.
	*/
	if (!error)
	{
		error =  gnsdk_musicid_query_option_set(
							query_handle, 
							GNSDK_MUSICID_OPTION_ENABLE_PLAYLIST, 
							GNSDK_VALUE_TRUE
							);
	}

#if USE_LOCAL
	printf(" LOCAL lookup...");
	if (!error)
	{
		error = gnsdk_musicid_query_option_set(
			query_handle,
			GNSDK_MUSICID_OPTION_LOOKUP_MODE,
			GNSDK_LOOKUP_MODE_LOCAL
			);
	}
#else 
	printf(" ONLINE lookup..."); 
#endif
	for (count_ordinal = 0; count_ordinal < count; ++count_ordinal)
	{

		/*Set the input TOC*/
		error = gnsdk_musicid_query_set_toc_string(query_handle,input_query_tocs[count_ordinal]);

		if (!error)
		{
			error = gnsdk_musicid_query_find_albums(query_handle, &response_gdo);
		}

		if (!error)
		{
			error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_ALBUM, 1, &album_gdo);
		}

		/*  Add MusicID result to Playlist   */
		if (!error)
		{
			gnsdk_uint32_t track_count				= 0;
			gnsdk_uint32_t track_ordinal			= 0;
			gnsdk_gdo_handle_t	track_gdo			= GNSDK_NULL;
			gnsdk_char_t		unique_ident[256]	= {0};

			error = gnsdk_manager_gdo_child_count(album_gdo, GNSDK_GDO_CHILD_TRACK, &track_count);
			
			/*  To make playlist of tracks we add each and every track in the album to the collection summary */
			for(track_ordinal=1; track_ordinal <= track_count && !error; ++track_ordinal)
			{
				error = gnsdk_manager_gdo_child_get(album_gdo, GNSDK_GDO_CHILD_TRACK, track_ordinal, &track_gdo);
				
				if (!error)
				{
					/* create a unique ident for every track that is added to the playlist. 
					   Ideally the ident allows for the identification of which track it is. 
					   e.g. path/filename.ext , or an id that can be externally looked up.
					*/
					if (sprintf(unique_ident,"%d_%d",count_ordinal,track_ordinal) > -1)
					{
						/* 
							Add the the Album and Track GDO for the same ident so that we can 
							query the Playlist Collection with both track and album level attributes.
						*/
						error = gnsdk_playlist_collection_add_gdo(h_playlist_collection, unique_ident, album_gdo);
						error = gnsdk_playlist_collection_add_gdo(h_playlist_collection, unique_ident, track_gdo);
					}
				}
				if (!error)
				{
					printf("..");
				}
				gnsdk_manager_gdo_release(track_gdo);
				track_gdo =  GNSDK_NULL;
			}
			gnsdk_manager_gdo_release(album_gdo);
			album_gdo = GNSDK_NULL;
		}

		/* cleanup */
		gnsdk_manager_gdo_release(response_gdo);
		response_gdo = GNSDK_NULL;
	}
	gnsdk_musicid_query_release(query_handle);

	/* count the albums recognized */
	error = gnsdk_playlist_collection_ident_count(h_playlist_collection, &ident_count);
	printf("\n Recognized %d tracks out of %d Album TOCS",ident_count, count);
	
	printf("\n Finished Recognition \n");

	return  error;
}


/* _playlist_collection_create
*    Here we attempt to load an existing Playlist Collection Summary from the GNSDK
*    storage if one was previously stored. If not, we create a new Collection Summary
*    (which initially is empty) and populate it with media. We then store this 
*    Collection Summary in the GNSDK storage.
*/ 
static gnsdk_error_t
_playlist_collection_create( 
	gnsdk_user_handle_t					user_handle,
	gnsdk_playlist_collection_handle_t*	p_playlist_collection
	)
{
	gnsdk_error_t						error				= GNSDK_SUCCESS;
	gnsdk_playlist_collection_handle_t	playlist_collection	= GNSDK_NULL;
	gnsdk_uint32_t						count				= 0;
	gnsdk_char_t						collection_name[300];


	error = gnsdk_playlist_storage_count_collections(&count);

	printf("\nCurrently stored collections :%d", count);

	if (count == 0)
	{
		printf("\nCreating a new collection");
		error = gnsdk_playlist_collection_create("sample_collection", &playlist_collection);

		if (!error)
		{
			error  = _playlist_collection_populate(user_handle, playlist_collection);
		}
		if (!error)
		{
			printf("\nStoring collection... ");
			error = gnsdk_playlist_storage_store_collection(playlist_collection);
		}

		/*	Release the collection we created. */
		gnsdk_playlist_collection_release(playlist_collection);
	}

	/* get the count again */
	if (!error)
	{
		error = gnsdk_playlist_storage_count_collections(&count);
		printf("\nCurrently stored collections :%d", count);
	}

	if (!error)
	{
		error = gnsdk_playlist_storage_enum_collections(0,collection_name,sizeof(collection_name));
	}

	if (!error)
	{

		error = gnsdk_playlist_storage_load_collection(collection_name,&playlist_collection);
	}

	if (!error)
	{
		printf("\n Loading Collection '%s' from store",collection_name);
		*p_playlist_collection = playlist_collection;
	}
	else
	{
		printf("\n Failed to load Collection '%s' from store",collection_name);
		_display_error(__LINE__, "_playlist_collection_create() failed", error);
	}

	return 	error;
}

/* _playlist_attribute_enum
*     Here we display the Playlist Attributes supported by this version of GNSDK Playlist
*     as well as the Playlist Attributes currently employed in the Collection Summary.
*     The sets of Attributes in these cases may differ if the Collection Summary was 
*     generated by a different version of GNSDK (however such differences will occur
*     infrequently if ever).
*/
static gnsdk_error_t
_playlist_attribute_enum(
	gnsdk_playlist_collection_handle_t	h_playlist_collection
	)
{
	gnsdk_error_t	error				= GNSDK_SUCCESS;
	gnsdk_cstr_t	collection_name		= GNSDK_NULL;
	gnsdk_cstr_t	attr_name			= GNSDK_NULL;
	gnsdk_uint32_t	count				= 0;
	gnsdk_uint32_t	ident_count			= 0;
	gnsdk_uint32_t	count_ordinal		= 0;

	printf("\nAll Playlist Attributes:\n");

	error = gnsdk_playlist_attributes_count(&count);
	for (count_ordinal = 0; count_ordinal < count && !error; count_ordinal++)
	{
		error = gnsdk_playlist_attributes_enum(count_ordinal, &attr_name);
		if (!error)
		{
			printf("\t%s\n", attr_name);
		}
	}
	
	if(!error)
	{
		error = gnsdk_playlist_collection_ident_count(h_playlist_collection, &ident_count);
	}

	if (!error)
	{
		error = gnsdk_playlist_collection_get_name(h_playlist_collection, &collection_name);
	}

	printf("Collection Attributes: \'%s\' (%d idents)\n", collection_name, ident_count);
	count = 0;
	if (!error)
	{	
		error = gnsdk_playlist_collection_attributes_count(h_playlist_collection, &count);
	}

	
	for (count_ordinal = 0; count_ordinal < count && !error; count_ordinal++)
	{
		error = gnsdk_playlist_collection_attributes_enum(h_playlist_collection, count_ordinal, &attr_name);
		if (!error)
		{
			printf("\t%s\n", attr_name);
		}
	}

	return error;
}

/* _playlist_get_attribute_value
*     
*/
static void
_playlist_get_attribute_value(
	gnsdk_playlist_collection_handle_t	h_playlist_collection,
	gnsdk_gdo_handle_t					h_gdo_attr
	)
{
	gnsdk_error_t		error			= GNSDK_SUCCESS;
	gnsdk_uint32_t		attr_ordinal	= 0;
	gnsdk_uint32_t		attr_count		= 0;
	gnsdk_cstr_t		attr_name		= GNSDK_NULL;
	gnsdk_cstr_t		attr_value		= GNSDK_NULL;

	error = gnsdk_playlist_collection_attributes_count(h_playlist_collection,&attr_count);

	for (attr_ordinal = 0; attr_ordinal < attr_count; ++attr_ordinal)
	{
		error = gnsdk_playlist_collection_attributes_enum(h_playlist_collection, attr_ordinal, &attr_name);
		if (!error)
		{
			error = gnsdk_manager_gdo_value_get(h_gdo_attr, attr_name, 1, &attr_value);
		}
		if (!error)
		{
			printf("\t\t%s:%s\n", attr_name, attr_value);
		}
	}
}

/* _enumerate_playlist_results
*     The following illustrates how to get each  ident and its associated GDO from a results handle.
*    
*/
static void
_enumerate_playlist_results(
	gnsdk_playlist_collection_handle_t	h_playlist_collection,
	gnsdk_playlist_results_handle_t		h_playlist_results
	)
{
	gnsdk_error_t						error					= GNSDK_SUCCESS;
	gnsdk_gdo_handle_t					h_gdo_attr				= GNSDK_NULL;
	gnsdk_cstr_t						ident					= GNSDK_NULL;
	gnsdk_cstr_t						collection_name			= GNSDK_NULL;
	gnsdk_uint32_t						count_ordinal			= 0;
	gnsdk_uint32_t						results_count			= 0;
	gnsdk_playlist_collection_handle_t	h_temp_collection		= GNSDK_NULL;

	error = gnsdk_playlist_results_count(h_playlist_results, &results_count);
	printf("Generated Playlist: %d\n", results_count);

	for (count_ordinal = 0; count_ordinal < results_count; ++count_ordinal)
	{
		error = gnsdk_playlist_results_enum(h_playlist_results,count_ordinal,&ident,&collection_name);
		printf("    %d: %s Collection Name:%s\n", count_ordinal+1, ident, collection_name);

		/*	The following illustrates how to get a collection handle 
		from the collection name string in the results enum function call. 
		It ensures that Joined collections as well as non joined collections will work with minimal overhead. 
		*/
		if(!error)
		{
			error = gnsdk_playlist_collection_join_get_by_name(h_playlist_collection,collection_name,&h_temp_collection);
		}

		if(!error)
		{
			error = gnsdk_playlist_collection_ident_get_gdo(h_temp_collection,ident,&h_gdo_attr);
		}

		if (!error)
		{
			_playlist_get_attribute_value(h_temp_collection,h_gdo_attr);
		}

		/* cleanup */
		gnsdk_manager_gdo_release(h_gdo_attr);
		gnsdk_playlist_collection_release(h_temp_collection);
		h_temp_collection = GNSDK_NULL;
		h_gdo_attr		  = GNSDK_NULL;
	}
}


/* _print_playlist_morelikethis_options
*     The following illustrates how to get the various morelikethis options.
*    
*/
static void 
_print_playlist_morelikethis_options(
	gnsdk_playlist_collection_handle_t	h_playlist_collection
	)
{
	gnsdk_cstr_t		value		= GNSDK_NULL;

	gnsdk_playlist_morelikethis_option_get(
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS, 
			&value
			);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS :%s", value);

	gnsdk_playlist_morelikethis_option_get(
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST,	
			&value
			);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST :%s", value);

	gnsdk_playlist_morelikethis_option_get(
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM,	
			&value
			);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM :%s", value);

	gnsdk_playlist_morelikethis_option_get(
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOM,	
			&value
			);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOM :%s \n", value);

}

/* _do_playlist_pdl
*    Here we perform playlist generation from our created Collection Summary via 
*    custom PDL (Playlist Definition Language) statements.
*/
static void
_do_playlist_pdl(
	gnsdk_user_handle_t					user_handle,
	gnsdk_playlist_collection_handle_t	h_playlist_collection
	)
{
	gnsdk_error_t						error				= GNSDK_SUCCESS;
	gnsdk_uint32_t						stmt_idx			= 0;
	gnsdk_uint32_t						pdlstmt_count		= 0;
	gnsdk_bool_t						b_seed_required		= GNSDK_FALSE;
	gnsdk_playlist_results_handle_t		h_playlist_results	= GNSDK_NULL;
	gnsdk_gdo_handle_t					h_gdo_seed			= GNSDK_NULL;
	gnsdk_cstr_t						pdl_statements[]	= 
	{	
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 0",   	/* like pop with a low score threshold (0)*/
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 300", 	/* like pop with a reasonable score threshold (300)*/
		"GENERATE PLAYLIST WHERE GN_Genre = 2929", 				/* exactly pop */
		"GENERATE PLAYLIST WHERE GN_Genre = 2821",    			/* exactly rock */
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 0",     /* like rock with a low score threshold (0)*/
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 300",  	/* like rock with a reasonable score threshold (300)*/
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE SEED) > 300 LIMIT 20 RESULTS",
		"GENERATE PLAYLIST WHERE (GN_ArtistName LIKE 'Green Day') > 300 LIMIT 20 RESULTS,2 PER GN_ArtistName;",
	};

	pdlstmt_count = sizeof(pdl_statements) / sizeof(pdl_statements[0]);



	for (stmt_idx = 0; stmt_idx < pdlstmt_count; stmt_idx++)
	{
		printf("\n PDL %d: %s \n",stmt_idx, pdl_statements[stmt_idx]);

		error = gnsdk_playlist_statement_validate(pdl_statements[stmt_idx],h_playlist_collection,&b_seed_required);
		if (error)
		{
			_display_error(__LINE__, "gnsdk_playlist_generate_playlist", error); 
		}

		/*
			A seed gdo can be any recognized media gdo. 
			In this example we are using the a gdo from a track in the playlist collection summary 
		*/
		if (!error && b_seed_required)
		{
			gnsdk_cstr_t seed_ident = GNSDK_NULL;
			/* In this case , randomly selecting the 5th element */
			error = gnsdk_playlist_collection_ident_enum(h_playlist_collection, 4 , &seed_ident);
			if (!error)
			{
				error = gnsdk_playlist_collection_ident_get_gdo(h_playlist_collection, seed_ident, &h_gdo_seed);
			}
		}

		if (!error)
		{
			error = gnsdk_playlist_generate_playlist(
				user_handle, 
				pdl_statements[stmt_idx], 
				h_playlist_collection, 
				h_gdo_seed, 
				&h_playlist_results
				);
			if (!error)
			{
				_enumerate_playlist_results(h_playlist_collection, h_playlist_results);

				gnsdk_playlist_results_release(h_playlist_results);
			}
			else
			{
				_display_error(__LINE__, "gnsdk_playlist_generate_playlist", error); 
			}
		}

		gnsdk_manager_gdo_release(h_gdo_seed);
		h_gdo_seed = GNSDK_NULL;
	}
}


/* _do_playlist_morelikethis
*    Here we perform playlist 'morelikethis' generation from our created Collection Summary.
*/
static void
_do_playlist_morelikethis(
	gnsdk_user_handle_t					user_handle,
	gnsdk_playlist_collection_handle_t	h_playlist_collection
	)
{
	gnsdk_error_t						error				= GNSDK_SUCCESS;
	gnsdk_playlist_results_handle_t		h_playlist_results	= GNSDK_NULL;
	gnsdk_gdo_handle_t					h_gdo_seed			= GNSDK_NULL;
	gnsdk_uint32_t						result_count		= 0;
	gnsdk_cstr_t seed_ident = GNSDK_NULL;
	

	/* 
	A seed gdo can be any recognized media gdo. 
	In this example we are using the a gdo from a random track in the playlist collection summary 
	*/
	error = gnsdk_playlist_collection_ident_enum(h_playlist_collection, 4 , &seed_ident);
	if (!error)
	{
		error = gnsdk_playlist_collection_ident_get_gdo(h_playlist_collection, seed_ident, &h_gdo_seed);
	}

	if (error)
	{
		_display_error(__LINE__, "gnsdk_playlist_collection_ident_get_gdo", error); 
	}

	printf ("\n MoreLikeThis tests\n MoreLikeThis Seed details:\n");

	_playlist_get_attribute_value(h_playlist_collection, h_gdo_seed);
	
	/* Generate a more Like this with the default settings */
	printf("\n MoreLikeThis with Default Options \n");

	/* Print the default More Like This options */
	_print_playlist_morelikethis_options(h_playlist_collection);

	error = gnsdk_playlist_generate_morelikethis(
				user_handle, 
				h_playlist_collection, 
				h_gdo_seed, 
				&h_playlist_results
				);

	if (!error)
	{
		_enumerate_playlist_results(h_playlist_collection, h_playlist_results);
	}
	else
	{
		_display_error(__LINE__, "gnsdk_playlist_generate_morelikethis", error); 
	}

	/* cleanup */	
	gnsdk_playlist_results_release(h_playlist_results);
	

	/* Generate a more Like this with the custom settings */
	printf("\n MoreLikeThis with Custom Options \n");

	/* Change the possible result set to be a maximum of 30 tracks.*/
	gnsdk_playlist_morelikethis_option_set( 
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS,
			"30"
			);

	/* Change the max per artist to be 20 */
	gnsdk_playlist_morelikethis_option_set( 
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST,
			"10"
			);

	/* Change the max per album to be 5 */
	gnsdk_playlist_morelikethis_option_set( 
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM,
			"5"
			);

	/* Change the random result to be 1 so that there is no randomization*/
	gnsdk_playlist_morelikethis_option_set( 
			h_playlist_collection,
			GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOM,
			"1"
			);

	/* Print the customized More Like This options */
	_print_playlist_morelikethis_options(h_playlist_collection);

	error = gnsdk_playlist_generate_morelikethis(
				user_handle, 
				h_playlist_collection, 
				h_gdo_seed, 
				&h_playlist_results
				);

	if (!error)
	{
		_enumerate_playlist_results(h_playlist_collection, h_playlist_results);
	}
	else
	{
		_display_error(__LINE__, "gnsdk_playlist_generate_morelikethis", error); 
	}

	/* cleanup */	
	gnsdk_playlist_results_release(h_playlist_results);
	

	gnsdk_manager_gdo_release(h_gdo_seed);
	h_gdo_seed = GNSDK_NULL;
	result_count = 0;
			
}

/* _perform_sample_playlist
*     Our top level function that calls the required Playlist routines
*/
static void
_perform_sample_playlist(gnsdk_user_handle_t	user_handle)
{
	gnsdk_playlist_collection_handle_t	playlist_collection	= GNSDK_NULL;
	gnsdk_error_t						error				= GNSDK_SUCCESS;

	error = _playlist_collection_create(user_handle,&playlist_collection);
	

	if (!error)
	{
		error = _playlist_attribute_enum(playlist_collection);
	}
	else
	{
		printf("\n Sample failed to create a collection");
	}

	if (!error)
	{
		/* demonstrate PDL usage */
		_do_playlist_pdl(user_handle, playlist_collection);

		/* demonstrate MoreLike usage*/
		_do_playlist_morelikethis(user_handle, playlist_collection);
	}
	else
	{
		printf("\n Sample failed to enumerate attributes ");
	}
	

	/* cleanup */
	gnsdk_playlist_collection_release(playlist_collection);
}
