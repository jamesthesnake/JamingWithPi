#include "gnsdk.h"  // Standard GNSDK header

//** Standard C headers - used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//** Log entries are identified by the 'package' that logs them. here we generate
//** a package ID for our application to allow us to log entries of our own in the GNSDK log
#define MYAPP_PACKAGE_ID   GNSDKPKG_ID_APP_START+0x01

//** Local function declarations
static int _get_user_handle(
	gnsdk_cstr_t				client_id,
	gnsdk_cstr_t				client_id_tag,
	gnsdk_cstr_t				app_version,
	gnsdk_user_handle_t*		p_user_handle);

//** Declare logging function
static void
_log_app_error(
	gnsdk_int32_t			line,
	gnsdk_cstr_t			file,
	const gnsdk_char_t*		info,
	gnsdk_error_t			error
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
	gnsdk_manager_handle_t			sdkmgr_handle		= GNSDK_NULL;
	gnsdk_user_handle_t				user_handle			= GNSDK_NULL;
	gnsdk_musicid_query_handle_t	query_handle		= GNSDK_NULL;
	gnsdk_gdo_handle_t				input_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				response_gdo		= GNSDK_NULL;
	gnsdk_str_t			updated_serialized_user_string	= GNSDK_NULL;
	gnsdk_int32_t					rc					= 0;           // return code

		//** Client ID and License file must be passed in
	if (argc < 4)
	{
		printf("usage:\n\n\t\tsample.exe clientid clientidtag license\n");
		return -1;
	}
	client_id = argv[1];
	client_id_tag = argv[2];
	license_path = argv[3];

	//** Display SDK Versions
	printf("\ngnsdk_manager: v%s \t(built %s)\n", gnsdk_manager_get_version(), gnsdk_manager_get_build_date());
	printf(  "gnsdk_musicid:    v%s \t(built %s)\n\n", gnsdk_musicid_get_version(), gnsdk_musicid_get_build_date());

	//** Initialize GNSDK
	error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);
	if (GNSDK_SUCCESS != error)
	{
		printf("gnsdk_manager_initialize() failed: 0x%x\n", error); // Can't log this as logging has not been enabled yet
		return -1;
	}

	//*********************************************************************************
	//** R E G I S T E R  P A C K A G E
	//**
	//** Register our package ID with the logging system - this will make our logging
	//** entries show up with the package description of "Sample App"
	//*********************************************************************************
	error = gnsdk_manager_logging_register_package(MYAPP_PACKAGE_ID, "Sample App");
	if (error)
	{
		printf("gnsdk_manager_logging_register_package() failed: 0x%x", error); // Cannot log this as logging has not been enabled yet
		gnsdk_manager_shutdown();
		return -1;
	}

	//*****************************************
	//** E N A B L E  L O G G I N G
	//*****************************************
	error = gnsdk_manager_logging_enable(
				"sample.log",				// File path
				GNSDK_LOG_PKG_GNSDK,		// Include entries for higher level GNSDKs as well as your app
				GNSDK_LOG_LEVEL_ALL,		// Include all level entries
				GNSDK_LOG_OPTION_ALL,		// All logging options
				0,							// Max log size: 0 means a new log file will be created each run
				GNSDK_FALSE					// GNSDK_TRUE = old logs will be renamed and saved
				);
	if (error)
	{
		printf("gnsdk_manager_logging_enable() failed: 0x%x", error);
		gnsdk_manager_shutdown();
		return -1;
	}


	//** Initialize the MusicID SDK
	error = gnsdk_musicid_initialize(sdkmgr_handle);
	if (error)
	{
		_log_app_error(__LINE__, __FILE__, "gnsdk_musicid_initialize() failed", error);
		gnsdk_manager_shutdown();
		return -1;
	}

	//** Get user handle
	if (0 !=  _get_user_handle(client_id, client_id_tag,"1",&user_handle))
	{
		gnsdk_musicid_shutdown();
		gnsdk_manager_shutdown();
		return -1;
	}

	//** Create musicid query handle
	printf("\nCreating musicid query\n");
	error = gnsdk_musicid_query_create(user_handle,	GNSDK_NULL,	GNSDK_NULL, &query_handle);
	if (error)
	{
		_log_app_error(__LINE__, __FILE__, "gnsdk_musicid_query_create() failed", error);
		rc = -1;
	}

	//** Get GDO  for query
	//** You can either deserialze gdo from serialized GDO string or use live GDO


	//**
	//** C R E A T E  E R R O R
	//**
	//** We are going to comment this out to generate an error
	//** with the next SDK call
	//**
	/*if(0 == rc)
	{
		error =	 gnsdk_manager_gdo_deserialize(
					"WEcxAwpU57x6ijap4RVINrN7Uui/UEzqC7RJqnLkGzfPBYPZAIQR3ZNCbN78yxFd+uKAIOeqqVYNQSg90E9jWpzS3dCNtKaLSmSQQGJFVEtwdIe6tCPYme+bCSsN9qzj1xSnrNTwwf5HUof9PPlX4d71JWGUczplR50Bh4I2b4tvmW2xpdZ1O91gMfxVZYU=",
					&input_gdo
					);
		if (error)
		{
			_log_app_error(__LINE__, __FILE__, "gnsdk_manager_gdo_deserialize() failed", error);
			rc = -1;
		}
	}	*/

	if(0 == rc)
	{

		printf("\nSetting query GDO - should generate Error\n");
		error = gnsdk_musicid_query_set_gdo(query_handle, input_gdo);
		if (error)
		{
			_log_app_error(__LINE__, __FILE__, "gnsdk_musicid_query_set_gdo() failed", error);
			rc = -1;
		}
	}

	//** Set one or more the search options [optional]
	//** refer gnsdk reference guide for more options you can set
	//** for musicid query
	if(0 == rc)
	{
		printf("\nSetting query options\n");
		error = gnsdk_musicid_query_option_set(
					query_handle,
					GNSDK_MUSICID_OPTION_ENABLE_LINK_DATA,
					GNSDK_VALUE_TRUE
			);
		if (GNSDK_SUCCESS != error)
		{
			_log_app_error(__LINE__, __FILE__, "gnsdk_musicid_query_option_set() failed", error);
			rc = -1;
		}

	}

	//** Perform query
	if(0 == rc)
	{
		printf("\nDoing MusicID find albums query...\n");

		error = gnsdk_musicid_query_find_albums(query_handle,  &response_gdo);
		if (error)
		{
			_log_app_error(__LINE__, __FILE__, "gnsdk_musicid_query_find_albums() failed", error);
			rc = -1;
		}
	}

	if(0 == rc)  printf("\nDone MusicID query...\n");


	//** Clean up and shut down
	error = gnsdk_manager_gdo_release(input_gdo);
	if (error)
	{
		_log_app_error(__LINE__, __FILE__, "gnsdk_manager_user_release() failed", error);
	}

	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
	gnsdk_musicid_query_release(query_handle);
	gnsdk_musicid_shutdown();
	gnsdk_manager_shutdown();

	return 0;

}  //** main()


//******************************************************************
//**
//**   _ L O G _ A P P _ E R R O R
//**
//**  Log and echo the error info
//******************************************************************
static void
_log_app_error(
	gnsdk_int32_t			line,
	gnsdk_cstr_t			file,
	const gnsdk_char_t*		info,
	gnsdk_error_t			error
	)
{
	gnsdk_error_t				logging_error = GNSDK_SUCCESS;
	const gnsdk_error_info_t*  	err_info	 = GNSDK_NULL;

	printf("\n_log_app_error() called\n");

	//********************************************
	//** G E T  S Y S T E M  E R R  I N F O
	//********************************************
	printf("\nCalling gnsdk_manager_error_info() to get system error information\n");
	err_info = gnsdk_manager_error_info();


	//*****************************************************
	//** W R I T E  E R R  T O  L O G  F I L E
	//*****************************************************
	if (GNSDK_NULL != err_info)
	{
		//**
		//** Write the error to the GNSDK log(s) with our package ID
		//**
		logging_error =
			gnsdk_manager_logging_write(
				line,
				file,
				MYAPP_PACKAGE_ID,
				GNSDK_LOG_LEVEL_ERROR,
				"API:%s, SDK error code: 0x%x, Description: %s, Internal error code: 0x%x",
				err_info->error_api ? err_info->error_api : "[no info]",
				err_info->error_code,
				err_info->error_description,
				err_info->source_error_code
			);
	}
	else
	{
		//**
		//** Write the error to the GNSDK log(s) with our package ID
		//**
		printf("\nerr_info is null\n");
		logging_error = gnsdk_manager_logging_write(
											line, file,
											MYAPP_PACKAGE_ID,
											GNSDK_LOG_LEVEL_ALL,
											"%s: 0x%x - %s", info, error
											);
		printf("Error:\n\t%s\n\t0x%x - %s\n", info, error);
	}
	GNSDK_ASSERT(GNSDK_SUCCESS == logging_error);

	return;

}  //** _log_app_error()



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
 * Some code herein may be covered by US and international patents.
*/