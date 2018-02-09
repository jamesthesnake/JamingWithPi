//**
//**  GNSDK headers
//**
//** Define the modules your application needs.
//** These constants enable inclusion of headers and symbols in gnsdk.h.
//**
#define GNSDK_MUSICID               1
#include "gnsdk.h"

//** Standard C headers - used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//** Local function declarations
static void _display_error(
	int				line_num,
	const char*		info,
	gnsdk_error_t	error_code
	);

static int _get_user_handle(
    gnsdk_cstr_t 			client_id,
    gnsdk_cstr_t 			client_id_tag,
    gnsdk_cstr_t 			app_version,
    gnsdk_user_handle_t*    p_user_handle );


//******************************************************************
//**
//**   M A I N
//**
//******************************************************************
int main(int argc, char* argv[])
{
	gnsdk_error_t				error				= 0;
	gnsdk_cstr_t				client_id			= GNSDK_NULL;
	gnsdk_cstr_t				client_id_tag		= GNSDK_NULL;
	gnsdk_cstr_t				license_path		= GNSDK_NULL;
	gnsdk_manager_handle_t		sdkmgr_handle		= GNSDK_NULL;
	gnsdk_user_handle_t			user_handle			= GNSDK_NULL;
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

	//** Initialize the GNSDK SDK Manager
	//** You must initialize gnsdk manager in order to use any other sdk functionality
	printf("\nInitializing gnsdk manager\n");
	error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);

	//** Initialize any other sdk to use its functionality.
	//** For e.g, Initialize the GNSDK MusicID
	printf("\nInitializing gnsdk musicid\n");
	error = gnsdk_musicid_initialize(sdkmgr_handle);

	//** Get a user handle for our client ID.  This will be passed in for all queries
	if (!error)
	{
		error = _get_user_handle(client_id,	client_id_tag, "1",&user_handle);
	}

	//**
	//** Perform queries - Refer "musicid" or "musicid_file" samples
    //** ...
	//**


	//**
	//** Done using SDK;  Clean up and shutdown
	//**
	printf("\nReleasing user\n");
	error =	gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);

	//**
	//** Save user handle to serialized storage here
	//** ...
	//**

	printf("\nShutting down gnsdk musicid\n");
	error = gnsdk_musicid_shutdown();

	printf("\nShutting down gnsdk manager\n");
	error = gnsdk_manager_shutdown();

	return 0;

}  //** main()

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

