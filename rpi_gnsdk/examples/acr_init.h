#ifndef ACR_INIT_H
#define ACR_INIT_H

typedef struct 
{
	//GNSDK
	gnsdk_manager_handle_t	gnsdk_handle;
	gnsdk_user_handle_t		user_handle;
	gnsdk_user_handle_t		music_user_handle;
}
acr_handle_t;

typedef struct 
{
	gnsdk_char_t* user;				/*serialized user handle*/
	gnsdk_char_t* license_filename;	/*path to GNSDK license file*/

	gnsdk_char_t* video_client_id;		/*To initialize, must pass in serialized user handle OR client_id awith client_id_tag */
	gnsdk_char_t* video_client_id_tag;

	gnsdk_char_t* music_client_id;		/*To initialize, must pass in serialized user handle OR client_id awith client_id_tag */
	gnsdk_char_t* music_client_id_tag;
} acr_initialization_t;


#ifdef __cplusplus
extern "C"{
#endif




gnsdk_error_t acr_initialize(acr_initialization_t* p_init, acr_handle_t** p_acr_handle);

gnsdk_error_t acr_shutdown(acr_handle_t* p_acr_handle);

#ifdef __cplusplus
}
#endif

#endif