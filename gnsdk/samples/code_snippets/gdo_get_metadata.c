#include "gnsdk.h"

//** Standard C headers used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//** Local function declarations
static int
_init_gnsdk(
	gnsdk_cstr_t			client_id,
	gnsdk_cstr_t			client_id_tag,
	gnsdk_cstr_t			client_id_app_version,
	gnsdk_cstr_t			license_path,
	gnsdk_user_handle_t*	p_user_handle,
	gnsdk_locale_handle_t*	p_locale_handle
	);

static int
_get_user_handle(
	gnsdk_cstr_t client_id,
	gnsdk_cstr_t client_id_tag,
	gnsdk_cstr_t app_version,
	gnsdk_user_handle_t*	p_user_handle
	);


//******************************************************************
//**
//**   M A I N
//**
//******************************************************************
int main(int argc, char* argv[])
{
	gnsdk_error_t					error				= GNSDK_SUCCESS;
	gnsdk_cstr_t					client_id			= GNSDK_NULL;
	gnsdk_cstr_t					client_id_tag		= GNSDK_NULL;
	gnsdk_cstr_t					license_path		= GNSDK_NULL;
	gnsdk_user_handle_t				user_handle			= GNSDK_NULL;
	gnsdk_locale_handle_t			locale_handle		= GNSDK_NULL;
	gnsdk_musicid_query_handle_t	query_handle		= GNSDK_NULL;
	gnsdk_gdo_handle_t				input_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				album_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				album_title_gdo		= GNSDK_NULL;
	gnsdk_gdo_handle_t				response_gdo		= GNSDK_NULL;
	gnsdk_cstr_t					response_type		= GNSDK_NULL;
	gnsdk_uint32_t					track_count			= 0;
	gnsdk_str_t		updated_serialized_user_string	= GNSDK_NULL;

	//** Display SDK Versions
	printf("\ngnsdk_manager: v%s \t(built %s)\n", gnsdk_manager_get_version(), gnsdk_manager_get_build_date());
	printf(  "gnsdk_musicid:    v%s \t(built %s)\n\n", gnsdk_musicid_get_version(), gnsdk_musicid_get_build_date());

	//** Client ID and License file must be passed in
	if (argc < 4)
	{
		printf("usage:\n\n\t\tsample.exe clientid clientidtag license\n");
		return -1;
	}
	client_id = argv[1];
	client_id_tag = argv[2];
	license_path = argv[3];

	if (0 == _init_gnsdk(client_id, client_id_tag, "1", license_path, &user_handle, &locale_handle))
	{

		//** Create musicid query handle
		printf("\nCreating musicid query\n");
		error = gnsdk_musicid_query_create(	user_handle,GNSDK_NULL,	GNSDK_NULL, &query_handle);

		//** Get GDO  for query
		//** You can either deserialze gdo from serialized GDO string or use live GDO
		error =	 gnsdk_manager_gdo_deserialize("WEcxAwpU57x6ijap4RVINrN7Uui/UEzqC7RJqnLkGzfPBYPZAIQR3ZNCbN78yxFd+uKAIOeqqVYNQSg90E9jWpzS3dCNtKaLSmSQQGJFVEtwdIe6tCPYme+bCSsN9qzj1xSnrNTwwf5HUof9PPlX4d71JWGUczplR50Bh4I2b4tvmW2xpdZ1O91gMfxVZYU=",&input_gdo);

		printf("\nSetting query GDO\n");
		error = gnsdk_musicid_query_set_gdo(query_handle, input_gdo);

		//** Perform the query
		printf("\nDoing MusicID...\n");
		error = gnsdk_musicid_query_find_albums(query_handle,&response_gdo);

		//** Display GDO type
		error = gnsdk_manager_gdo_get_type(response_gdo,&response_type);
		printf("\nGDO type : %s\n",response_type);

		//** Get 1st Album GDO from response_gdo. Use gnsdk_manager_gdo_child_count(...)
		//** to get how may album children the response has. Typically, a text search will
		//** result in a multi match.
		error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_ALBUM, 1,  &album_gdo);

		if(!error)
		{
			gnsdk_str_t			out			         = 0;
			gnsdk_uint32_t		i			         = 0;

			//** Value Keys for metadata we are going to retrieve
			gnsdk_char_t*		album_keys[] = {	GNSDK_GDO_VALUE_ALBUM_COMPILATION,
													GNSDK_GDO_VALUE_ALBUM_DISC_IN_SET,
													GNSDK_GDO_VALUE_ALBUM_LABEL,
													GNSDK_GDO_VALUE_ALBUM_TOTAL_IN_SET,
													GNSDK_GDO_VALUE_ALBUM_TRACK_COUNT,
													GNSDK_GDO_VALUE_CLASSICAL_DATA,
													GNSDK_GDO_VALUE_FULL_RESULT,
													GNSDK_GDO_VALUE_GLOBALID,
													GNSDK_GDO_VALUE_GNID,
													GNSDK_GDO_VALUE_GNUID,
													GNSDK_GDO_VALUE_YEAR,
													GNSDK_GDO_VALUE_PACKAGE_LANGUAGE,
													GNSDK_GDO_VALUE_PACKAGE_LANGUAGE_DISPLAY,
													GNSDK_GDO_VALUE_PRODUCTID,
													GNSDK_GDO_VALUE_TUI,
													GNSDK_GDO_VALUE_TUI_TAG
												};

			//** Labels for metadata we are going to get
			gnsdk_char_t*			album_key_names[] = {
													"ALBUM_COMPILATION",
													"ALBUM_DISC_IN_SET",
													"ALBUM_LABEL",
													"ALBUM_TOTAL_IN_SET",
													"ALBUM_TRACK_COUNT",
													"CLASSICAL_DATA",
													"FULL_RESULT",
													"GLOBALID",
													"GNID",
													"GNUID",
													"YEAR",
													"PACKAGE_LANGUAGE",
													"PACKAGE_LANGUAGE_DISPLAY",
													"PRODUCTID",
													"TUI",
													"TUI_TAG"
													};

			//** Get album title GDO
			error = gnsdk_manager_gdo_child_get(album_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1,  &album_title_gdo);
			if (!error)
			{
			    //** Get Album Title
				error = gnsdk_manager_gdo_value_get(album_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &out);
				if (!error)
				   printf("%s:\t%s \n", "Album Title:",  out);
			}

			//** Loop thru all value keys in our array
			for (i=0;i <  (sizeof(album_keys)/sizeof(album_keys[0])) ;i++)
			{
				gnsdk_uint32_t		vcount	 =0;
				gnsdk_uint32_t		j		 = 1;
				gnsdk_error_t		alb_error	 = GNSDK_SUCCESS;

				error=	gnsdk_manager_gdo_value_count(album_gdo, album_keys[i], &vcount);
				if(GNSDK_SUCCESS != error)
				{
					continue;
				}

				while(alb_error == GNSDK_SUCCESS)
				{
					alb_error =	gnsdk_manager_gdo_value_get(album_gdo, album_keys[i], j, &out);
					if (alb_error == GNSDK_SUCCESS)
					{
						printf("\t%s:\t%s \n", album_key_names[i],  out);
						j++;
					}
				}
			} //** for
		} //** if (!error)


		//** Get Album track information

		//** How may tracks on this album?
		error = gnsdk_manager_gdo_child_count(album_gdo, GNSDK_GDO_CHILD_TRACK, &track_count);

		printf("\n%s\n", "Track Titles:");
		if(!error)
		{
			gnsdk_uint32_t		track_index 	= 	 0;
			gnsdk_gdo_handle_t	track_gdo		=	 GNSDK_NULL;
			gnsdk_gdo_handle_t	track_title_gdo	=	 GNSDK_NULL;

			//** Loop thru all Child Track GDOs
			for (track_index = 1; track_index <= track_count; track_index++)
			{
				//** Get Child Track GDO
				error = gnsdk_manager_gdo_child_get(album_gdo, GNSDK_GDO_CHILD_TRACK, track_index, &track_gdo);

				if (!error)
				{
				   //** Get Child Track Title GDO
				   error = gnsdk_manager_gdo_child_get(track_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &track_title_gdo);
				}

				if(!error)
				{
					gnsdk_str_t			out			         = 0;
					gnsdk_uint32_t		i			         = 0;
					gnsdk_char_t*			track_keys[] = {GNSDK_GDO_VALUE_DISPLAY};
					gnsdk_char_t*			track_key_names[] = {"Title"};

					for (i=0;i<  sizeof(track_keys)/sizeof(track_keys[0]);i++)
					{
						gnsdk_uint32_t		vcount	= 0;
						gnsdk_uint32_t		j		= 1;
						gnsdk_error_t		track_error  = GNSDK_SUCCESS;

						error=	gnsdk_manager_gdo_value_count(track_title_gdo, track_keys[i], &vcount);
						if(GNSDK_SUCCESS != error)
						{
							continue;
						}

						while(!track_error)
						{
							track_error	=gnsdk_manager_gdo_value_get(track_title_gdo, track_keys[i], j, &out);
							if (!track_error){
								printf("\tTrack - %d : %s:\t%s \n", track_index, track_key_names[i],  out);
								j++;
							}

						} //*** while
					} //** for
				} //** if (!error)

				gnsdk_manager_gdo_release(track_gdo);
				gnsdk_manager_gdo_release(track_title_gdo);
			} //** for
		} //** if (!error)
		else
		   printf("\nError Getting Track Count: 0x%x\n",error);

	}   //** If init ok


	printf("\nShutting down GNSDK\n");

	//** S H U T D O W N
	gnsdk_manager_gdo_release(album_gdo);
	gnsdk_manager_gdo_release(album_title_gdo);
	gnsdk_manager_gdo_release(input_gdo);
	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
	gnsdk_manager_locale_release(locale_handle);
	gnsdk_musicid_query_release(query_handle);
	gnsdk_musicid_shutdown();
	gnsdk_manager_shutdown();

	return 0;

} //** main()


//******************************************************************
//**
//**   _ I N I T _ G N S D K
//**
//******************************************************************
static int _init_gnsdk(
	gnsdk_cstr_t			client_id,
	gnsdk_cstr_t			client_id_tag,
	gnsdk_cstr_t			client_id_app_version,
	gnsdk_cstr_t			license_path,
	gnsdk_user_handle_t*	p_user_handle,
	gnsdk_locale_handle_t*	p_music_locale_handle
	)
{
	gnsdk_manager_handle_t		sdkmgr_handle		= GNSDK_NULL;
	gnsdk_error_t				error				= GNSDK_SUCCESS;
	gnsdk_user_handle_t			user_handle			= GNSDK_NULL;
	gnsdk_locale_handle_t		music_locale_handle = GNSDK_NULL;

	printf("\nInitializing GNSDK\n");
	error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);

	//**
	//** Initialize musicid
	//**
	if(!error)
	{
		error = gnsdk_musicid_initialize(sdkmgr_handle);
	}

	//**
	//** Get user handle
	//**
	error = _get_user_handle(client_id, client_id_tag, client_id_app_version, &user_handle);
	if(!error)
	{
		*p_user_handle = user_handle;
	}
	else
	{
		printf("\nError getting user_handle -0X%x\n",error);
	}

	//**
	//** Loading the 'locale' to return locale-specifc values in English
	//**
	if(!error)
	{
		printf("\nLoading Locale...\n");
		error = gnsdk_manager_locale_load(
					GNSDK_LOCALE_GROUP_MUSIC,
					GNSDK_LANG_ENGLISH,
					GNSDK_REGION_DEFAULT,
					GNSDK_DESCRIPTOR_DETAILED,
					user_handle,
					GNSDK_NULL ,	       // [optional]callback to find status of local download progress
					0,				       // [optional] callback user data
					&music_locale_handle
				);
	}
	if(GNSDK_SUCCESS != error)
	{
		printf("\nError loading music locale -0X%x\n",error);

	}
	else
	{
		gnsdk_manager_locale_set_group_default(music_locale_handle);
		*p_music_locale_handle = music_locale_handle;
	}

	return error;

}  //** _init_gnsdk()


//*****************************************************************************************
//**
//**   _ G E T _ U S E R _ H A N D L E
//**
//**
//**    Load existing user handle, or register new one.
//**
//**    GNSDK requires a user handle instance to perform queries.
//**    User handles encapsulate your Gracenote provided Client ID which is unique for your
//**    application. User handles are registered once with Gracenote then must be saved by
//**    your application and reused on future invocations.
//**
//*******************************************************************************************
static int _get_user_handle(
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

		//**
		//** Do we have a user saved locally?
		//**
		file = fopen(user_filename, "r");
		if (NULL != file)
		{
			gnsdk_char_t serialized_user_string[1024] = {0};

			if (NULL != (fgets(serialized_user_string, 1024, file)))
			{
				//**
				//** Create the user handle from the saved user
				//**
				error = gnsdk_manager_user_create(serialized_user_string, &user_handle);
				if (GNSDK_SUCCESS != error)
				{
					printf("gnsdk_manager_user_create() failed, Error : 0x%x",error);
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

		//**
		//** If not, create new one
		//**
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
				printf("gnsdk_manager_user_create_new() failed, Error : 0x%x",error);
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

} //** _get_user_handle()

/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code in this file may be covered by US and international patents.
*/



