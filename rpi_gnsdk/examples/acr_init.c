/* Use GCSL for memory */
#include "gcsl_defines.h"
#include "gcsl_errors.h"
#include "gcsl_error_codes.h"
#include "gcsl_memory.h"


/* GNSDK */

#include "gnsdk_defines.h"
#include "gnsdk_errors.h"
#include "gnsdk_error_codes.h"
#include "gnsdk_manager.h"
#include "gnsdk_manager_gdo.h"
#include "gnsdk_manager_lists.h"
#include "gnsdk_manager_list_values.h"
#include "gnsdk_video.h"
#include "gnsdk_dsp.h"
#include "gnsdk_link.h"
#include "gnsdk_epg.h"
#include "gnsdk_lookup_fplocal.h"
#include "gnsdk_musicid.h"


/* Optional caching */
#include "gnsdk_storage_sqlite.h"


/* New! ACR */
#include "gnsdk_acr.h"

#include "acr_init.h"

gnsdk_error_t acr_initialize(acr_initialization_t* p_init, acr_handle_t** p_acr_handle)
{
	gnsdk_error_t	error                 = GNSDK_SUCCESS;
	gnsdk_locale_handle_t	locale_handle = GNSDK_NULL;
	acr_handle_t*	internal_handle       = GNSDK_NULL;
	gcsl_bool_t		video_initialized     = GNSDK_FALSE;
	gcsl_bool_t		memory_initialized    = GNSDK_FALSE;
	gcsl_bool_t		acr_initialized       = GNSDK_FALSE;
	gcsl_bool_t		dsp_initialized       = GNSDK_FALSE;
	gcsl_bool_t		sqlite_initialized    = GNSDK_FALSE;
	gcsl_bool_t     link_initialized      = GNSDK_FALSE;
	gcsl_bool_t     epg_initialized       = GNSDK_FALSE;
	gcsl_bool_t     fplocal_initialized   = GNSDK_FALSE;
	gcsl_bool_t     musicid_initialized   = GNSDK_FALSE;

	if ((p_init == GNSDK_NULL) || (p_acr_handle == GNSDK_NULL))
	{
		return GNSDKERR_InvalidArg;
	}

	/*Initialize memory*/
	error = gcsl_memory_initialize();

	if (GCSL_SUCCESS == error)
	{
		memory_initialized = GCSL_TRUE;

		/*Create internal handle*/
		internal_handle = gcsl_memory_alloc( sizeof (acr_handle_t));

		if (internal_handle == GNSDK_NULL)
		{
			error = GNSDKERR_NoMemory;
		}
	}
	
	if (GCSL_SUCCESS == error)
	{
		/*Clear handle*/
		gcsl_memory_memset(internal_handle, 0, sizeof(*internal_handle));

		/*Initialize GNSDK*/
		error = gnsdk_manager_initialize(&(internal_handle->gnsdk_handle), p_init->license_filename , GNSDK_MANAGER_LICENSEDATA_FILENAME);
		//error = gnsdk_manager_initialize(& (internal_handle->gnsdk_handle), 0, 0);
	}

	if (GCSL_SUCCESS == error)
	{
		error = gnsdk_storage_sqlite_initialize( internal_handle->gnsdk_handle );
	}
	
	if (GCSL_SUCCESS == error)
	{
		sqlite_initialized = GCSL_TRUE;

		/* Initialize video SDK */

		error = gnsdk_video_initialize(internal_handle->gnsdk_handle);
	}

	if (GCSL_SUCCESS == error)
	{
		video_initialized = GCSL_TRUE;  /*successfully initalized video */

		error = gnsdk_musicid_initialize(internal_handle->gnsdk_handle);
	}

	if (GCSL_SUCCESS == error)
	{
		musicid_initialized = GCSL_TRUE;  /*successfully initalized video */

		error = gnsdk_dsp_initialize(internal_handle->gnsdk_handle);
	}

	if (GCSL_SUCCESS == error)
	{
		dsp_initialized = GCSL_TRUE;  /*successfully initalized dsp */

		error = gnsdk_acr_initialize(internal_handle->gnsdk_handle);
	}

	if (GCSL_SUCCESS == error)
	{
		acr_initialized = GCSL_TRUE;

		error = gnsdk_epg_initialize(internal_handle->gnsdk_handle);
	}

	if (GCSL_SUCCESS == error)
	{
		epg_initialized = GCSL_TRUE;

		error = gnsdk_link_initialize(internal_handle->gnsdk_handle);
	}

	if(GCSL_SUCCESS == error)
	{
		link_initialized = GCSL_TRUE;

		error = gnsdk_lookup_fplocal_initialize(internal_handle->gnsdk_handle);
	}

	if (GCSL_SUCCESS == error)
	{
		fplocal_initialized = GCSL_TRUE;

		/*Need to create user handle, lets use existing serialized user*/
		if (p_init->user != GNSDK_NULL)
		{
			error = gnsdk_manager_user_create(p_init->user, &(internal_handle->user_handle));
		}
		else 
		{
			/*or create new user*/
			error = gnsdk_manager_user_create_new( p_init->video_client_id, p_init->video_client_id_tag, "ACRTESTAPP", & (internal_handle->user_handle));
		}
	}

#if 1
	if ((error == GNSDK_SUCCESS) && (internal_handle->user_handle != GNSDK_NULL))
	{
		error = gnsdk_manager_locale_load(
					GNSDK_LOCALE_GROUP_VIDEO,
					GNSDK_LANG_ENGLISH,
					GNSDK_REGION_DEFAULT,
					GNSDK_DESCRIPTOR_DEFAULT,
					internal_handle->user_handle,
					(gnsdk_manager_query_callback_fn)GNSDK_NULL,
					GNSDK_NULL,
					&locale_handle
					);

		if (error == GNSDK_SUCCESS)
		{
			error = gnsdk_manager_locale_set_group_default(locale_handle);
			gnsdk_manager_locale_release(locale_handle);
			locale_handle = GNSDK_NULL;
		}

		error = gnsdk_manager_locale_load(
					GNSDK_LOCALE_GROUP_EPG,
					GNSDK_LANG_ENGLISH,
					GNSDK_REGION_DEFAULT,
					GNSDK_DESCRIPTOR_DEFAULT,
					internal_handle->user_handle,
					(gnsdk_manager_query_callback_fn)GNSDK_NULL,
					GNSDK_NULL,
					&locale_handle
					);

		if (error == GNSDK_SUCCESS)
		{
			error = gnsdk_manager_locale_set_group_default(locale_handle);
			gnsdk_manager_locale_release(locale_handle);
			locale_handle = GNSDK_NULL;
		}

		error = gnsdk_manager_locale_load(
					GNSDK_LOCALE_GROUP_MUSIC,
					GNSDK_LANG_ENGLISH,
					GNSDK_REGION_DEFAULT,
					GNSDK_DESCRIPTOR_DEFAULT,
					internal_handle->user_handle,
					(gnsdk_manager_query_callback_fn)GNSDK_NULL,
					GNSDK_NULL,
					&locale_handle
					);

		if (error == GNSDK_SUCCESS)
		{
			error = gnsdk_manager_locale_set_group_default(locale_handle);
			gnsdk_manager_locale_release(locale_handle);
			locale_handle = GNSDK_NULL;
		}

		error = GNSDK_SUCCESS;
	}
#endif

	if (GCSL_SUCCESS == error)
	{
		/*If we successfully created a user handle, lets return our created handle*/
		*p_acr_handle =   internal_handle;
	} 
	else if (internal_handle != GNSDK_NULL)
	{
		/*If something went wrong, lets unitialize and free everything*/
		if (internal_handle->user_handle != GNSDK_NULL)
		{
			gnsdk_str_t	user_serialized = GNSDK_NULL;

			gnsdk_manager_user_release(internal_handle->user_handle, &user_serialized);
			gnsdk_manager_string_free(user_serialized);
			internal_handle->user_handle = GNSDK_NULL;
		}

		if (fplocal_initialized)
		{
			gnsdk_lookup_fplocal_shutdown();
		}

		if (link_initialized)
		{
			gnsdk_link_shutdown();
		}

		if (epg_initialized)
		{
			gnsdk_epg_shutdown();
		}

		if (acr_initialized)
		{
			gnsdk_acr_shutdown();
		}

		if (dsp_initialized)
		{
			gnsdk_dsp_shutdown();
		}

		if (video_initialized)
		{
			gnsdk_video_shutdown();
		}

		if(musicid_initialized)
		{
			gnsdk_musicid_shutdown();
		}

		if (sqlite_initialized)
		{
			gnsdk_storage_sqlite_shutdown();
		}

		if (internal_handle->gnsdk_handle != GNSDK_NULL)
		{
			gnsdk_manager_shutdown();
			internal_handle->gnsdk_handle = GNSDK_NULL;
		}
	
		gcsl_memory_free(internal_handle);
		internal_handle = GNSDK_NULL;
	}
	
	if ((memory_initialized == GCSL_TRUE) && (internal_handle == GNSDK_NULL))
	{	
		/* If we don't have an internal handle (because we were out of memory, or something didn't initialize),
		 * but memory is initialized, lets unititialize memory */
		
		gcsl_memory_shutdown();
	}

	return error;
}


gnsdk_error_t acr_shutdown(acr_handle_t* p_acr_handle)
{

	acr_handle_t* internal_handle = GNSDK_NULL;

	if (p_acr_handle == GNSDK_NULL)
	{
		return GNSDKERR_InvalidArg;
	}
	
	internal_handle =  p_acr_handle;

	/* release user handle */
	if (internal_handle->user_handle != GNSDK_NULL)
	{
		gnsdk_str_t	user_serialized = GNSDK_NULL;

		gnsdk_manager_user_release(internal_handle->user_handle, &user_serialized);
		gnsdk_manager_string_free(user_serialized);
		internal_handle->user_handle = GNSDK_NULL;
	}

	/* Shutdown epg */
	gnsdk_epg_shutdown();

	/* shutdown acr */
	gnsdk_acr_shutdown();

	/* shutdown dsp */
	gnsdk_dsp_shutdown();

	/* shutdown video */
	gnsdk_video_shutdown();

	/* Shutdown fp local engine */
	/* TODO - sqlite error if this is shut down after sqlite */
	gnsdk_lookup_fplocal_shutdown();

	/* shutdown sqlite */
	gnsdk_storage_sqlite_shutdown();

	/* shutdown link */
	gnsdk_link_shutdown();

	/* shutdown GNSDK */
	if (internal_handle->gnsdk_handle != GNSDK_NULL)
	{
		gnsdk_manager_shutdown();
		internal_handle->gnsdk_handle = GNSDK_NULL;
	}

	/*Free internal handle */
	gcsl_memory_free(internal_handle);

	/*shutdown memory */

	gcsl_memory_shutdown();

	return GNSDK_SUCCESS;

}
