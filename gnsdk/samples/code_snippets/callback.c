
#include "gnsdk.h"

//** Standard C headers - used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//** Local function declarations
static int _get_user_handle(
	gnsdk_cstr_t				client_id,
	gnsdk_cstr_t				client_id_tag,
	gnsdk_cstr_t				app_version,
	gnsdk_user_handle_t*		p_user_handle);


//** MusicID query status callback
GNSDK_EXTERN_C static gnsdk_void_t GNSDK_CALLBACK_API
  _musicid_status_callback_fn(
	const gnsdk_void_t*					user_data,
	gnsdk_musicid_query_handle_t		musicid_query_handle,
	gnsdk_musicid_query_status_t		status,
	gnsdk_size_t						bytes_done,
	gnsdk_size_t						bytes_total,
	gnsdk_bool_t*						p_abort);

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
	gnsdk_manager_handle_t			sdkmgr_handle		= GNSDK_NULL;
	gnsdk_user_handle_t				user_handle			= GNSDK_NULL;
	gnsdk_musicid_query_handle_t	query_handle		= GNSDK_NULL;
	gnsdk_gdo_handle_t				input_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				result_gdo			= GNSDK_NULL;
	gnsdk_str_t		updated_serialized_user_string	= GNSDK_NULL;


	//** Client ID and License file must be passed in
	if (argc < 4)
	{
		printf("usage:\n\n\t\tsample.exe clientid clientidtag licensePath\n");
		return -1;
	}
	client_id = argv[1];
	client_id_tag = argv[2];
	license_path = argv[3];

	//** Display SDK Versions
	printf("\ngnsdk_manager: v%s \t(built %s)\n", gnsdk_manager_get_version(), gnsdk_manager_get_build_date());
	printf(  "gnsdk_musicid:    v%s \t(built %s)\n\n", gnsdk_musicid_get_version(), gnsdk_musicid_get_build_date());

	printf("\nInitializing SDK Manager\n");
	error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);

	if(!error)
	{
		printf("\nInitializing MusicID\n");
		error = gnsdk_musicid_initialize(sdkmgr_handle);
	}

	//** Get user handle
	if (!error)
	{
		printf("\nGetting User handle\n");
		error = _get_user_handle(client_id, client_id_tag, "1",	&user_handle);
	}

	//** Create MusicID query handle with status callback
	if(!error)
	{
		printf("\nCreating musicid query\n");
		error = gnsdk_musicid_query_create(user_handle,	_musicid_status_callback_fn, GNSDK_NULL, &query_handle);
	}

	//** Get GDO  for query
	//** You can either deserialze gdo from serialized GDO string or use live GDO
	if(!error)
	{
		printf("\nDeserializing GDO\n");
		error =	 gnsdk_manager_gdo_deserialize(
					"WEcxAwpU57x6ijap4RVINrN7Uui/UEzqC7RJqnLkGzfPBYPZAIQR3ZNCbN78yxFd+uKAIOeqqVYNQSg90E9jWpzS3dCNtKaLSmSQQGJFVEtwdIe6tCPYme+bCSsN9qzj1xSnrNTwwf5HUof9PPlX4d71JWGUczplR50Bh4I2b4tvmW2xpdZ1O91gMfxVZYU=",
					&input_gdo
					);
	}

	if(!error)
	{
		printf("\nSetting query GDO\n");
		error = gnsdk_musicid_query_set_gdo(query_handle, input_gdo);
	}

	//** Set one or more the search options [optional]
	//** Refer to GNSDK reference guide for more options you can set
	//** for MusicID query
	if(!error)
	{
		printf("\nSetting query options\n");
		error = gnsdk_musicid_query_option_set(query_handle, GNSDK_MUSICID_OPTION_ENABLE_LINK_DATA, GNSDK_VALUE_TRUE);
	}

	//** Perform the query
	if(!error)
	{
		printf("\nDoing MusicID find albums query...\n");
		error = gnsdk_musicid_query_find_albums(query_handle, &result_gdo);
	}

	(!error) ? printf("\nDone MusicID.\n") : printf("\nError : 0x%x\n",error);

	//**
	//** CLEAN UP and SHUT DOWN
	//**
	gnsdk_manager_gdo_release(input_gdo);
	gnsdk_manager_gdo_release(result_gdo);
	gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
	gnsdk_musicid_query_release(query_handle);
	gnsdk_musicid_shutdown();
	gnsdk_manager_shutdown();

	return 0;

}  //** main()


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

		//** If not, create new one
		if (GNSDK_NULL == user_handle)
		{
			error = gnsdk_manager_user_create_new(client_id, client_id_tag, client_app_version,&user_handle	);
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


//*****************************************************************************
//**
//**   _ M U S I C I D _ S T A T U S _ C A L L B A C K _ F N
//**
//** This is the status callback function - useful for displaying progress of
//** network actions and for allowing cancellation of large transactions
//**
//*****************************************************************************
static gnsdk_void_t  _musicid_status_callback_fn(
	const gnsdk_void_t*				user_data,
	gnsdk_musicid_query_handle_t	musicid_query_handle,
	gnsdk_musicid_query_status_t	status,
	gnsdk_size_t					bytes_done,
	gnsdk_size_t					bytes_total,
	gnsdk_bool_t*					p_abort
	)
{
	switch(status)
	{
		case gnsdk_musicid_status_query_begin:
			printf("\nMusicID query : Performing \n");
			break;
		case gnsdk_musicid_status_query_complete:
			printf("\nMusicID query : Done.\n");
			break;
		case gnsdk_musicid_status_sending:
			printf("\nMusicID query : Sending\n");
			break;
		case gnsdk_musicid_status_receiving:
			printf("\nMusicID query : Receiving\n");
			break;
		default:
			break;
	}

	//**
	//** This app doesn't allow a user to cancel but you could use this parameter
	//** to allow cancellation of the query
	//**
	*p_abort = GNSDK_FALSE;

	//**
	//** This is to quiet compiler warnings about un-used parameters in this simplified sample callback.
	//**
	user_data = 0;
	bytes_done = 0;
	bytes_total = 0;
	musicid_query_handle = 0;

}  //** _musicid_status_callback_fn()


/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/


