#include "gnsdk.h"

//** Standard C headers - used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//** Local function declarations
static int _init_gnsdk(
	gnsdk_cstr_t		 client_id,
	gnsdk_cstr_t		 client_id_tag,
	gnsdk_cstr_t		 client_id_app_version,
	gnsdk_cstr_t		 license_path,
	gnsdk_user_handle_t* p_user_handle);

static int _get_user_handle(
	gnsdk_cstr_t client_id,
	gnsdk_cstr_t client_id_tag,
	gnsdk_cstr_t app_version,
	gnsdk_user_handle_t*	p_user_handle);

static void _shutdown_gnsdk(gnsdk_user_handle_t user_handle	);

static gnsdk_error_t _display_list(gnsdk_list_handle_t list_handle);

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
	int								rc					= 0;
	gnsdk_list_handle_t 			list_handle			= GNSDK_NULL;

	//** Display SDK Versions
	printf("\ngnsdk_manager: v%s \t(built %s)\n", gnsdk_manager_get_version(), gnsdk_manager_get_build_date());


	//** Client ID and License file must be passed in
	if (argc < 4)
	{
		printf("usage:\n\n\t\tsample.exe clientid clientidtag license\n");
		return -1;
	}
	client_id = argv[1];
	client_id_tag = argv[2];
	license_path = argv[3];

	//** Initialize GNSDK
	rc = _init_gnsdk(client_id, client_id_tag, "1", license_path, &user_handle);
	if(0 != rc) return -1;

	//************************************************
	//** Retrieve music genre list
	//************************************************
	printf("\nRetrieving music genre list ...\n");
	error =  gnsdk_manager_list_retrieve(
				GNSDK_LIST_TYPE_GENRES,			 // list_type
				GNSDK_LANG_ENGLISH ,			 // list_language
				GNSDK_REGION_DEFAULT,			 // list_region
				GNSDK_DESCRIPTOR_DETAILED,		 // list_descriptor
				user_handle,					 // user handle
				GNSDK_NULL,						 // callback [otional], Refer "callbacks" sample application*
				GNSDK_NULL,						 // [optional] callback user data
				 &list_handle
				);

	if(GNSDK_SUCCESS != error)
	{
		printf("\ngnsdk_manager_list_retrieve failed : 0x%x\n", error);
		rc = -1;
	}
	else
	{
        //*************************
		//** Display list
		//**************************
		_display_list(list_handle);
	}

	//** Release list
	error = gnsdk_manager_list_release(list_handle);

	//** Clean up and Shutdown
	_shutdown_gnsdk(user_handle);

	return rc;

}  //** main()


//******************************************************************
//**
//**   _ D I S P L A Y _ L I S T
//**
//******************************************************************
static gnsdk_error_t _display_list(gnsdk_list_handle_t list_handle)
{
	gnsdk_error_t				error			= GNSDK_SUCCESS;
	gnsdk_list_element_handle_t	element			= GNSDK_NULL;
	gnsdk_cstr_t				display			= GNSDK_NULL;
	gnsdk_uint32_t				id				= 0;
	gnsdk_uint32_t				level_count		= 0;
	gnsdk_uint32_t				element_count	= 0;
	gnsdk_uint32_t				i				= 0;
	gnsdk_uint32_t				j				= 0;
	gnsdk_cstr_t				list_type		= GNSDK_NULL;
	gnsdk_cstr_t				list_language	= GNSDK_NULL;
	gnsdk_cstr_t				list_region		= GNSDK_NULL;
	gnsdk_cstr_t				list_descriptor	= GNSDK_NULL;

	if (GNSDK_NULL == list_handle) return GNSDKERR_InvalidArg;

 	error = gnsdk_manager_list_get_type(list_handle, &list_type);
	if (error) return error;

	error = gnsdk_manager_list_get_language(list_handle, &list_language);
	if (error) return error;

	error = gnsdk_manager_list_get_region(list_handle, &list_region);
	if (error) return error;

	error = gnsdk_manager_list_get_descriptor(list_handle, &list_descriptor);
	if (error) return error;

	error = gnsdk_manager_list_get_level_count(list_handle, &level_count);
	if (error) return error;

	printf("\n\n________________________________________________________________\n");
	printf("List:\n\t%s\n\t%s\n\t%s\n\t%s\n\t%d levels\n",list_type, list_region ,list_descriptor,  list_language, level_count);
	printf("________________________________________________________________\n\n" );
	printf("\t\t [list id] - [display string]\n");

	for(i = 1; i <= level_count; i++)
	{
		printf("Level -  %d\n", i);

		error = gnsdk_manager_list_get_element_count(list_handle, 1, &element_count);
		if (error) return error;

		for (j = 0; j < element_count; j++)
		{
			error = gnsdk_manager_list_get_element(list_handle, i, j, &element);
			if (error) break;

			printf("\t\t ");

			error = gnsdk_manager_list_element_get_id(element, &id);
			if (error) break;

			error = gnsdk_manager_list_element_get_display_string(element, &display);
			if (error) break;

			if (display) printf("[ %d ] - [ %s ]\n",id, display);

		} //** for each element in this level

	} //** for each level

	return error;

}  //** _display_list()


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
	gnsdk_user_handle_t*	p_user_handle
	)
{
	gnsdk_manager_handle_t		sdkmgr_handle		= GNSDK_NULL;
	gnsdk_error_t				error				= GNSDK_SUCCESS;
	gnsdk_user_handle_t			user_handle			= GNSDK_NULL;
	gnsdk_str_t		updated_serialized_user_string	= GNSDK_NULL;

	printf("\nInitializing GNSDK\n");
	error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);
	if(GNSDK_SUCCESS != error)
	{
		printf("gnsdk_manager_initialize() failed , Error : 0x%x",error);
		return -1;
	}

	//** Get user handle - Refer sample "initialization" to learn more
	error = _get_user_handle(client_id, client_id_tag, client_id_app_version, &user_handle);
	if(GNSDK_SUCCESS != error)
	{
		printf("get_user_handle() failed , Error : 0x%x",error);
		gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
		gnsdk_manager_shutdown();
		return -1;
	}

	*p_user_handle = user_handle;
	return error;

}  //** _init_gnsdk()


//******************************************************************
//**
//**   _ S H U T D O W N _ G N S D K
//**
//******************************************************************
static void
_shutdown_gnsdk(gnsdk_user_handle_t user_handle)
{
	gnsdk_str_t		updated_serialized_user_string	= GNSDK_NULL;

	printf("\nShutting down GNSDK\n");
	gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
	gnsdk_manager_shutdown();
}


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

		}  //** if (NULL != file)
		else
		{
			printf("\nInfo: No stored user - this must be the app's first run.\n");
		}

		//**
		//** If not, create new one
		//**
		if (GNSDK_NULL == user_handle)
		{
			error = gnsdk_manager_user_create_new(client_id, client_id_tag, client_app_version, &user_handle);
			if (GNSDK_SUCCESS != error)
			{
				printf("gnsdk_manager_user_create_new() failed, Error : 0x%x",error);
				rc = -1;
			}
		}

		free(user_filename);

	} //** //** if (NULL != user_filename)

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
 * Some code herein may be covered by US and international patents.
*/