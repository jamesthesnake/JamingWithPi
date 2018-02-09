#include "gnsdk.h"  // Standard GNSDK header

//** Standard C headers - used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//** Local function declarations
static int _init_gnsdk(
	gnsdk_cstr_t			client_id,
	gnsdk_cstr_t			client_id_tag,
	gnsdk_cstr_t			client_id_app_version,
	gnsdk_cstr_t			license_path,
	gnsdk_user_handle_t*	p_user_handle,
	gnsdk_locale_handle_t*	p_locale_handle);

static int _get_user_handle(
	gnsdk_cstr_t client_id,
	gnsdk_cstr_t client_id_tag,
	gnsdk_cstr_t app_version,
	gnsdk_user_handle_t*	p_user_handle);

static void _display_error(
	int				line_num,
	const char*		info,
	gnsdk_error_t	error_code);

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
	gnsdk_gdo_handle_t				response_gdo		= GNSDK_NULL;
	gnsdk_cstr_t					response_type		= GNSDK_NULL;
	gnsdk_str_t		  updated_serialized_user_string	= GNSDK_NULL;


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

	//** Initialize GNSDK - get SDK handle, User handle, initialize MusicID and load locale
	if(0 == _init_gnsdk(client_id, client_id_tag, "1", license_path, &user_handle, &locale_handle))
	{

		//** Create musicid query handle
		printf("\nCreating musicid query\n");
		error = gnsdk_musicid_query_create(	user_handle,GNSDK_NULL,	GNSDK_NULL, &query_handle);

		//** Get GDO  for query. You can either deserialze gdo from serialized GDO string or use live GDO
		error =	 gnsdk_manager_gdo_deserialize("WEcxAwpU57x6ijap4RVINrN7Uui/UEzqC7RJqnLkGzfPBYPZAIQR3ZNCbN78yxFd+uKAIOeqqVYNQSg90E9jWpzS3dCNtKaLSmSQQGJFVEtwdIe6tCPYme+bCSsN9qzj1xSnrNTwwf5HUof9PPlX4d71JWGUczplR50Bh4I2b4tvmW2xpdZ1O91gMfxVZYU=",&input_gdo);

		printf("\nSetting query GDO\n");
		error = gnsdk_musicid_query_set_gdo(query_handle, input_gdo);

		//** Perform the query
		printf("\nDoing MusicID find albums query...\n");
		error = gnsdk_musicid_query_find_albums(query_handle,&response_gdo);

		//** Display GDO type
		error = gnsdk_manager_gdo_get_type(response_gdo,&response_type);
		printf("\nGDO type : %s\n",response_type);


		//** Get 1st Album GDO from response_gdo. Use gnsdk_manager_gdo_child_count(...)
		//** get how may album children the response has. Typically text search will
		//** result in multi match.
		error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_ALBUM, 1,  &album_gdo);

		//** Serialize ALbum GDO
		if(!error)
		{
			gnsdk_str_t		serialized_album_gdo_str =	 GNSDK_NULL;

			printf("\nSerializing album GDO:\n");
			error = gnsdk_manager_gdo_serialize(album_gdo, &serialized_album_gdo_str);

			if(!error)
			{
				printf("\n%s\n",serialized_album_gdo_str);
				gnsdk_manager_string_free(serialized_album_gdo_str);  // not managed by gnsdk, you have to free it*
			}

		}
		if(error) printf("\nError : 0x%x\n",error);

	}  //** end if init gnsdk ok

	printf("\nShutting down GNSDK\n");

	//** S H U T D O W N
	gnsdk_manager_gdo_release(album_gdo);
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
	gnsdk_locale_handle_t*	p_locale_handle
	)
{
	gnsdk_manager_handle_t		sdkmgr_handle		= GNSDK_NULL;
	gnsdk_error_t				error				= GNSDK_SUCCESS;
	gnsdk_user_handle_t			user_handle			= GNSDK_NULL;
	gnsdk_locale_handle_t		locale_handle		= GNSDK_NULL;

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
	//** Get user handle - Refer sample "initialization" to learn more
	//**
	error = _get_user_handle(client_id, client_id_tag, client_id_app_version,&user_handle);
	if(!error)
	{
		*p_user_handle = user_handle;
		return 0;
	}

	//**
	//** Setting the 'locale' to return locale-specifc values in English
	//**
	printf("\nLoading Locale...\n");
	if(!error)
	{
		error = gnsdk_manager_locale_load(
					GNSDK_LOCALE_GROUP_MUSIC,
					GNSDK_LANG_ENGLISH,
					GNSDK_REGION_DEFAULT,
					GNSDK_DESCRIPTOR_DETAILED,
					user_handle,
					GNSDK_NULL, /*[optional] callback to find status of local download progress*/
					0,			 /*[optional] callback user data*/
					&locale_handle
				);
	}
	if(!error)
	{
		*p_locale_handle = locale_handle;
	}
	else
	{
		printf("\nError loading music locale -0X%x\n",error);
	}

	return error;

} //** _init_gnsdk()



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
//**   your application and reused on future invocations.
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

		//**
		//** If not, create new one
		//**
		if (GNSDK_NULL == user_handle)
		{
			error = gnsdk_manager_user_create_new(client_id, client_id_tag,	client_app_version,	&user_handle);
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

} //** _get_user_handle()

//******************************************************************
//**
//**   _ D I S P L A Y _ E R R O R
//**
//**   Echo the error and information.
//******************************************************************
static void _display_error(
	int				line_num,
	const char*		info,
	gnsdk_error_t	error_code
	)
{
	const	gnsdk_error_info_t*	error_info = gnsdk_manager_error_info();

	//**
	//** Error_info will never be GNSDK_NULL.
	//** The SDK will always return a pointer to a populated error info structure.
	//**
	printf(
		   "\nerror 0x%08x - %s\n\tline %d, info %s\n",
		   error_code,
		   error_info->error_description,
		   line_num,
		   info
		   );

} //** _display_error()


/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/


