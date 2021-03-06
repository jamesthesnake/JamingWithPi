#define GNSDK_MUSICID  1
#include "gnsdk.h"

//** Standard C headers - used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//** Local function declarations
static int
_init_gnsdk(
	gnsdk_cstr_t			client_id,
	gnsdk_cstr_t			client_id_tag,
	gnsdk_cstr_t		 	client_id_app_version,
	gnsdk_cstr_t		 	license_path,
	gnsdk_user_handle_t* 	p_user_handle
	);

static int
_get_user_handle(
	gnsdk_cstr_t 			client_id,
	gnsdk_cstr_t 			client_id_tag,
	gnsdk_cstr_t 			app_version,
	gnsdk_user_handle_t*	p_user_handle
	);

static void _shutdown_gnsdk(gnsdk_user_handle_t user_handle);
static void _do_musicid_lookup(gnsdk_user_handle_t user_handle,	gnsdk_gdo_handle_t* work_gdo);

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
	gnsdk_locale_handle_t			eng_locale_handle	= GNSDK_NULL;
	gnsdk_locale_handle_t			chinese_locale_handle	= GNSDK_NULL;
	gnsdk_gdo_handle_t				work_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				work_title_gdo		= GNSDK_NULL;
	gnsdk_cstr_t					value				= GNSDK_NULL;

	//** Client ID and License file must be passed in
	if (argc < 4)
	{
		printf("usage:\n\n\t\tsample.exe clientid clientidtag license\n");
		return -1;
	}

	client_id		= argv[1];
	client_id_tag	= argv[2];
	license_path	= argv[3];

	//** Display SDK Versions
	printf("\ngnsdk_manager: v%s \t(built %s)\n", gnsdk_manager_get_version(), gnsdk_manager_get_build_date());
	printf("\ngnsdk_musicid:    v%s \t(built %s)\n\n", gnsdk_musicid_get_version(), gnsdk_musicid_get_build_date());

    if(0 == _init_gnsdk(client_id, client_id_tag, "1", license_path, &user_handle))
	{
		//** Load an English locale as the default locale to be used when an explicit locale is not set
		printf("\nLoading locale : English\n");
		error = gnsdk_manager_locale_load(
					GNSDK_LOCALE_GROUP_MUSIC,
					GNSDK_LANG_ENGLISH,       		// English
					GNSDK_REGION_GLOBAL,     		// Default video region is US
					GNSDK_DESCRIPTOR_DETAILED, 		// Default video descriptor is 'detailed'
					user_handle,              		// User handle from the init
					GNSDK_NULL,               		// No status callback
					GNSDK_NULL,                		// No status userdata
					&eng_locale_handle
					);

		if (error) printf("Error Loading English Locale: 0x%x\n",error);

		//** Load a Chinese locale so it is available if needed
		printf("\nLoading locale : Chinese Simplified\n");
		error = gnsdk_manager_locale_load(
					GNSDK_LOCALE_GROUP_MUSIC,
					GNSDK_LANG_CHINESE_SIMP,
					GNSDK_REGION_DEFAULT,
					GNSDK_DESCRIPTOR_DETAILED,
					user_handle,
					GNSDK_NULL,
					GNSDK_NULL,
					&chinese_locale_handle
					);

		if (error) printf("Error Loading Chinese Locale: 0x%x\n",error);

		//** Music ID lookup
		_do_musicid_lookup(user_handle, &work_gdo);

	    //** Get Child title GDO
		error = gnsdk_manager_gdo_child_get(work_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &work_title_gdo);
		if (!error)
		{
		    //** Get and display title
			error = gnsdk_manager_gdo_value_get(work_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value);
			if (!error) printf("\nTitle: %s\n", value);
		}

		//** Fetch primary genre value in English
		error = gnsdk_manager_gdo_set_locale(work_gdo, eng_locale_handle);

		if (!error)
		{
		    //** Grab a locale-specific value in our default locale (English)
		    error = gnsdk_manager_gdo_value_get(work_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL1, 1, &value);
		    if (!error) printf("English primary genre: %s\r\n", value);
		}

		//** Now fetch the same value in Chinese
		error = gnsdk_manager_gdo_set_locale(work_gdo, chinese_locale_handle);

		if (!error)
		{
		    error = gnsdk_manager_gdo_value_get(work_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL1,	1,&value);
			if (!error) printf("Chinese primary genre: %s\r\n", value);
		}
		else printf("Error set GDO locale to Chinese: 0x%x\n",error);

	}  //** if init ok


	//** Cleanup and Shutdown
	gnsdk_manager_gdo_release(work_gdo);
	gnsdk_manager_locale_release(eng_locale_handle);
	gnsdk_manager_locale_release(chinese_locale_handle);
	_shutdown_gnsdk(user_handle);

	return 0;

} //** main()

//******************************************************************
//**
//**   _ I N I T _ G N S D K
//**
//******************************************************************
static int
_init_gnsdk(
	gnsdk_cstr_t			client_id,
	gnsdk_cstr_t			client_id_tag,
	gnsdk_cstr_t			client_id_app_version,
	gnsdk_cstr_t			license_path,
	gnsdk_user_handle_t* 	p_user_handle
	)
{
	gnsdk_manager_handle_t		sdkmgr_handle		= GNSDK_NULL;
	gnsdk_error_t				error				= GNSDK_SUCCESS;
	gnsdk_user_handle_t			user_handle			= GNSDK_NULL;

	printf("\nInitializing gnsdk\n");
	error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);
	if (!error)
	{
		//** Initialize musicid
		error = gnsdk_musicid_initialize(sdkmgr_handle);
		if (!error)
		{
		    //** Get user handle - Refer sample "initialization" to learn more
		    error = _get_user_handle(client_id, client_id_tag, client_id_app_version, &user_handle);
			if (!error) *p_user_handle = user_handle;
		}
	}

	return error;

}	//** _init_gnsdk()


//******************************************************************
//**
//**   _ S H U T D O W N _ G N S D K
//**
//******************************************************************
static void _shutdown_gnsdk(gnsdk_user_handle_t user_handle)
{
	gnsdk_str_t		updated_serialized_user_string	= GNSDK_NULL;

	printf("\nShutting down GNSDK\n");
	gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
	gnsdk_musicid_shutdown();
	gnsdk_manager_shutdown();

} //** _shutdown_gnsdk()


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

		//** Do we have a user saved locally?
		file = fopen(user_filename, "r");
		if (NULL != file)
		{
			gnsdk_char_t serialized_user_string[1024] = {0};

			if (NULL != (fgets(serialized_user_string, 1024, file)))
			{
				//** Create the user handle from the saved user
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
			error = gnsdk_manager_user_create_new(client_id, client_id_tag,	client_app_version,	&user_handle);
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



//******************************************************************
//**
//**   _ D O _ M U S I C I D _ L O O K U P
//**
//******************************************************************
static void
_do_musicid_lookup(
	gnsdk_user_handle_t user_handle,
	gnsdk_gdo_handle_t* p_album_gdo
	)
{
	gnsdk_error_t					error				= GNSDK_SUCCESS;
	gnsdk_musicid_query_handle_t	query_handle		= GNSDK_NULL;
	gnsdk_gdo_handle_t				input_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				response_gdo		= GNSDK_NULL;

	error = gnsdk_musicid_query_create(user_handle,GNSDK_NULL,	GNSDK_NULL, &query_handle);
	error =	             			gnsdk_manager_gdo_deserialize("WEcxAwpU57x6ijap4RVINrN7Uui/UEzqC7RJqnLkGzfPBYPZAIQR3ZNCbN78yxFd+uKAIOeqqVYNQSg90E9jWpzS3dCNtKaLSmSQQGJFVEtwdIe6tCPYme+bCSsN9qzj1xSnrNTwwf5HUof9PPlX4d71JWGUczplR50Bh4I2b4tvmW2xpdZ1O91gMfxVZYU=", &input_gdo);

	error = gnsdk_musicid_query_set_gdo(query_handle, input_gdo);
	error = gnsdk_musicid_query_find_albums(query_handle,&response_gdo);
	error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_ALBUM, 1, p_album_gdo);

	gnsdk_manager_gdo_release(input_gdo);
	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_musicid_query_release(query_handle);

	return;

} //** _do_musicid_lookup()

/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/









