//** Standard Gracenote SDK header
#include "gnsdk.h"

//** Standard C headers - used by the sample app, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//** Local declarations
gnsdk_error_t init_musicid();
gnsdk_error_t init_musicid_file();
gnsdk_error_t shutdown_all();


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

	//** Initialize SDK Manager - get handle
    error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);
    error = init_musicid();
    error = init_musicid_file();

    shutdown_all();

    return 0;

} //** main()


//******************************************************************
//**
//**   I N I T _ M U S I C I D
//**
//** Initialization of MusicID
//**
//******************************************************************
gnsdk_error_t init_musicid()
{
    gnsdk_manager_handle_t    sdkmgr_handle = GNSDK_NULL;
    gnsdk_error_t             error;

	//** Retrieve a GNSDK Manager handle to initialize a GNSDK.
	//** No license data required after first time.
    error = gnsdk_manager_initialize(&sdkmgr_handle, GNSDK_NULL, 0);
    if (!error)
    {
		//** Use retrieved sdkmgr_handle to initialize other GNSDKs
        error = gnsdk_musicid_initialize(sdkmgr_handle);

		//** Pair the initialize above with a shutdown.
		//** Note that this is the 2nd initialize of GNSDK Manager
		//** so this shutdown will not cause an actual shutdown
        gnsdk_manager_shutdown();
    }
    return error;

} //** init_musicid()

//******************************************************************
//**
//**   I N I T _ M U S I C I D _ F I L E
//**
//** Initialization of MusicID File
//**
//******************************************************************
gnsdk_error_t init_musicid_file()
{
    gnsdk_manager_handle_t    sdkmgr_handle = GNSDK_NULL;
    gnsdk_error_t             error;

	//** Retrieve a GNSDK Manager handle to initialize another GNSDK
	//** No license data required after first time
    error = gnsdk_manager_initialize(&sdkmgr_handle, GNSDK_NULL, 0);
    if (!error)
    {
		//** Use the retrieved sdkmgr_handle to initialize another GNSDK
		error = gnsdk_musicidfile_initialize(sdkmgr_handle);

		//** Pair the initialize above with a shutdown.
		//** Note that this is the second initialization of GNSDK Manager
		//** so this shutdown will not cause an actual shutdown
        gnsdk_manager_shutdown();
    }

	return error;

} //** init_musicid_file()

//******************************************************************
//**
//**   S H U T D O W N _ A L L
//**
//** Shutdown all initialized GNSDKs
//**
//******************************************************************
gnsdk_error_t shutdown_all()
{
    gnsdk_error_t    error;

	//** Shutdown GNSDKs; note that the order is not important
    error = gnsdk_musicid_shutdown();
    error = gnsdk_musicidfile_shutdown();
    error = gnsdk_manager_shutdown(); // Pair the first initialize at top with a shutdown

	return error;

} //** shutdown_all()

/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/


//**
//** E N D
//**