#define GNSDK_MUSICID               1
#define GNSDK_STORAGE_SQLITE        1

#include "gnsdk.h" // Standard GNSDK header

//** Standard C headers that are used by the sample application, but not required for GNSDK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//** Local function declaration
static int _init_gnsdk(
    gnsdk_cstr_t         	client_id,
    gnsdk_cstr_t        	client_id_tag,
    gnsdk_cstr_t         	client_id_app_version,
    gnsdk_cstr_t         	license_path,
    gnsdk_user_handle_t* 	p_user_handle,
	gnsdk_manager_handle_t* p_sdkmgr_handle);

static int _get_user_handle(
    gnsdk_cstr_t 			client_id,
    gnsdk_cstr_t 			client_id_tag,
    gnsdk_cstr_t 			app_version,
    gnsdk_user_handle_t*    p_user_handle );

static void _shutdown_gnsdk(gnsdk_user_handle_t user_handle);

static int _do_sample_musicid_toc_query(gnsdk_user_handle_t user_handle);

//******************************************************************
//**
//**   M A I N
//**
//******************************************************************
int main(int argc, char* argv[])
{
    gnsdk_cstr_t            client_id            = GNSDK_NULL;
    gnsdk_cstr_t            client_id_tag        = GNSDK_NULL;
    gnsdk_cstr_t            license_path         = GNSDK_NULL;
    gnsdk_user_handle_t		user_handle          = GNSDK_NULL;
	gnsdk_manager_handle_t	sdkmgr_handle        = GNSDK_NULL;
    int rc = 0;


	//** Display SDK and SQLite Versions
    printf("\ngnsdk_manager: v%s \t(built %s)\n", gnsdk_manager_get_version(), gnsdk_manager_get_build_date());
    printf("\ngnsdk_sqlite: v%s \t(built %s)\n", gnsdk_storage_sqlite_get_version(), gnsdk_storage_sqlite_get_build_date());
    printf("\nSqlite: v%s\n", gnsdk_storage_sqlite_get_sqlite_version());

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
    rc = _init_gnsdk(client_id, client_id_tag, "1", license_path, &user_handle, &sdkmgr_handle);
    if(0 != rc) return -1;

	//** Do a MusicID TOC query,
    //** If the query response is not in the cache, it will be cached, so that
    //** when you run sample again the response comes from the cache
    printf("\nPerforming GNSDK MusicID TOC Query\n");
    rc =  _do_sample_musicid_toc_query (user_handle);

	//** Release resources and shutdown
    _shutdown_gnsdk(user_handle);

    return rc;

} //** main()


//******************************************************************
//**
//**   _ D O _ S A M P L E _ M U S I C I D _ T O C _ Q U E R Y
//**
//**
//******************************************************************
static  int _do_sample_musicid_toc_query(gnsdk_user_handle_t user_handle)
{
    gnsdk_error_t                   error           =    GNSDK_SUCCESS;
    gnsdk_gdo_handle_t              response_gdo    =    GNSDK_NULL;
    gnsdk_musicid_query_handle_t    query_handle    =    GNSDK_NULL;

    //**
	//** Create query
	//**
    error = gnsdk_musicid_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);
    if(error) return -1;

    //**
	//** Set TOC to lookup
	//**
    error = gnsdk_musicid_query_set_toc_string(query_handle,
                "150 17806 36302 51775 68727 84761 101533 118691 137736 154706 170438 188386 215491 225798"
            );
    if(error)
    {
        gnsdk_musicid_query_release(query_handle);
        return -1;
    }

    //**
	//** Perform query
	//**
    error = gnsdk_musicid_query_find_albums(query_handle, &response_gdo);
    if(error)
    {
        gnsdk_musicid_query_release(query_handle);
        return -1;
    }

    //**
	//** Since we are done with the Response GDO, release it
	//**
    gnsdk_manager_gdo_release(response_gdo);
    gnsdk_musicid_query_release(query_handle);

    return 0;

}  //** _do_sample_musicid_toc_query()


//******************************************************************
//**
//**   _ I N I T _ G N S D K
//**
//******************************************************************
static int _init_gnsdk(
    gnsdk_cstr_t            client_id,
    gnsdk_cstr_t            client_id_tag,
    gnsdk_cstr_t            client_id_app_version,
    gnsdk_cstr_t            license_path,
    gnsdk_user_handle_t*    p_user_handle,
	gnsdk_manager_handle_t* p_sdkmgr_handle
    )
{

    gnsdk_error_t                error                = GNSDK_SUCCESS;
    gnsdk_manager_handle_t       sdkmgr_handle        = GNSDK_NULL;
    gnsdk_user_handle_t           user_handle         = GNSDK_NULL;

    printf("\nInitializing GNSDK\n");
    error = gnsdk_manager_initialize(&sdkmgr_handle, license_path, GNSDK_MANAGER_LICENSEDATA_FILENAME);
    if(GNSDK_SUCCESS != error)
    {
        return -1;
    }

    //**
	//** Initialize SQLite Cache
	//** to ensure that all queries are properly cached by this library, it should be initialized immediately
	//** after the GNSDK Manager and before any other libraries.
	//**
    printf("\nInitializing GNSDK Cache\n");
    error = gnsdk_storage_sqlite_initialize(sdkmgr_handle);
    if( GNSDK_SUCCESS != error)
    {
        printf("gnsdk_storage_sqlite_initialize() failed, Error : 0x%x",error);
        return -1;
    }

    //**
	//** For this library to successfully operate, you must first establish a valid storage folder path using the
    //** GNSDK_SQLITE_OPTION_STORAGE_FOLDER option.
    //**
    error = gnsdk_storage_sqlite_option_set(
                    GNSDK_STORAGE_SQLITE_OPTION_STORAGE_FOLDER,   // option name : storage folder [required]
                    "."                                           // option value : "." set it to current directory for this sample
             );

    if( GNSDK_SUCCESS != error)
    {
        printf("gnsdk_storage_sqlite_option_set() failed, Error : 0x%x",error);
        return -1;
    }

    error = gnsdk_manager_storage_location_set(GNSDK_MANAGER_STORAGE_QUERYCACHE, "./querycache");
	if (GNSDK_SUCCESS != error)
    {
	   printf("gnsdk_manager_storage_location_set() failed, Error : 0x%x",error);
	}

    error = gnsdk_musicid_initialize(sdkmgr_handle);
    if(GNSDK_SUCCESS != error)
    {
		printf("gnsdk_musicid_initialize() failed, Error : 0x%x",error);
		gnsdk_storage_sqlite_shutdown();
        gnsdk_manager_shutdown();
        return -1;
    }

    //**
    //** Get user handle - Refer to the general_initialization sample
    //** (Example: Basic Initializaton and Shutdown in Implementation documentation) to learn more
	//**
    error = _get_user_handle(client_id, client_id_tag, client_id_app_version, &user_handle);
    if(GNSDK_SUCCESS != error)
    {
		gnsdk_musicid_shutdown();
		gnsdk_storage_sqlite_shutdown();
        gnsdk_manager_shutdown();
        return -1;
    }

    *p_user_handle = user_handle;
    *p_sdkmgr_handle = sdkmgr_handle;
    return error;

}  //** _init_gnsdk()


//******************************************************************
//**
//**   _ S H U T D O W N _ G N S D K
//**
//******************************************************************
static void _shutdown_gnsdk(gnsdk_user_handle_t user_handle)
{
	gnsdk_str_t		updated_serialized_user_string	= GNSDK_NULL;

	//printf("\nShutting down GNSDK Sqlite Cache\n");
    gnsdk_storage_sqlite_shutdown();

    printf("\nShutting down GNSDK\n");
    gnsdk_musicid_shutdown();
    gnsdk_manager_user_release(user_handle, &updated_serialized_user_string);
    gnsdk_manager_shutdown();

}  //** _shutdown gnsdk()


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







