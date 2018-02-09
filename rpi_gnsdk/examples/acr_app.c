#include "gnsdk_defines.h"
#include "gnsdk_errors.h"
#include "gnsdk_error_codes.h"
#include "gnsdk_manager.h"
#include "gnsdk_manager_gdo.h"
#include "gnsdk_manager_lists.h"
#include "gnsdk_manager_list_values.h"
#include "gnsdk_musicid.h"
#include "gnsdk_video.h"
#include "gnsdk_dsp.h"
#include "gnsdk_acr.h"

#include "gnsdk_manager_privileged.h"
#include "gnsdk_lookup_fplocal.h"

#include "acr_init.h"

#include "gnsdk_storage_sqlite.h"
#include "gcsl_error_codes.h"
#include "gcsl_string.h"
#include "gnsdk_manager_logging.h"
#include "gnsdk_musicid.h"

#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

#include "acr_app_config.h"


#if ACR_APP_LOGGING

#endif

gnsdk_error_t acr_app_read_configuration(gnsdk_cstr_t *client_id,
										 gnsdk_cstr_t *client_tag,
										 gnsdk_cstr_t *user,
										 gnsdk_cstr_t *license_filename,
										 const gnsdk_cstr_t config_filename)
{
	FILE *config = fopen(config_filename, "r");
	gnsdk_char_t buffer[ACR_APP_CBUFF_SIZE];
	gnsdk_cstr_t tmp = buffer;
	gnsdk_cstr_t *curr_val = NULL;
	gnsdk_error_t ret = GNSDK_SUCCESS;
	int ch;
	size_t i;
	
	const gnsdk_cstr_t FIELDNAMES[] = {"CLIENT_ID", "CLIENT_TAG", "USER", "LICENSE"};
	const size_t NUMFIELDS = sizeof(FIELDNAMES) / sizeof(gnsdk_cstr_t);
	gnsdk_cstr_t *FIELDVALUES[] = {client_id, client_tag, user, license_filename};
	
	if (!config)
		return GNSDKERR_IOError;
	
	
	while((ch = fgetc(config)) != -1)
	{
		if (ch != '=' && ch !='\n')
		{
			*tmp = (gnsdk_char_t) c;
			tmp++;
			continue;
		}
		
		*tmp='\0';
		
		if (ch == '=')
		{
			for (i=0; i<NUMFIELDS; i++)
			{
				if (strcmp(buffer, FIELDNAMES[i]) == 0)
					break;
			}
			if (i==NUMFIELDS)
			{
				ret = 1;
				break;
			}
			curr_val = FIELDVALUES[i];
		}
		else if (c == '\n')
		{
			if (curr_val == NULL)
				ret = 1;
			*curr_val = strdup(buffer);
			curr_val = NULL;
		}
		
		tmp = buffer;
	}
	
	if (ch == -1 && curr_val != NULL)
		*curr_val = strdup(buffer);
	fclose(config);
	return ret;
}

void acr_app_save_configuration(const acr_initialization_t *init,
								const gnsdk_cstr_t config_filename)
{
	FILE *f = fopen(config_filename, "w");
	fprintf(f, "CLIENT_ID=%s\n", init->video_client_id);
	fprintf(f, "CLIENT_TAG=%s\n", init->video_client_tag);
	fprintf(f, "LICENSE=%s\n", init->license_filename);
	fprintf(f, "USER=%s\n", init->user);
}

void GNSDK_CALLBACK_API acr_callback_result(const gnsdk_void_t        *callback_userdata,
											gnsdk_acr_query_handle_t  acr_query_handle,   /* stream instance */
											gnsdk_gdo_handle_t        result_gdo,         /* match result */
											gnsdk_acr_match_source_t  match_source,       /* match source*/
											gnsdk_uint32_t            match_count,        /* total of match results */
											gnsdk_flt32_t             no_match_duration   /* duration of no match (only for gnsdk_acr_match_type_none) */
											)
{
	if (match_count == 0)
	{
		fprintf(stderr, "NO MATCHES\n");
		return;
	}
	else
	{
		size_t i;
		gnsdk_gdo_handle_t acr_gdo, airing_gdo, program_gdo;
		gnsdk_cstr_t tui;
		gnsdk_cstr_t tag;
		gnsdk_error_t error = GNSDK_SUCCESS;
		for (i=0; i<match_count; i++)
		{
			error = gnsdk_manager_gdo_child_get(result_gdo, GNSDK_GDO_CHILD_MATCH_ACR, i + 1, &acr_gdo);
			error = gnsdk_manager_gdo_child_get(acr_gdo, GNSDK_GDO_CHILD_TVAIRING, 1, &airing_gdo);
			error = gnsdk_manager_gdo_child_get(airing_gdo, GNSDK_GDO_CHILD_TVPROGRAM, 1, &program_gdo);
			error = gnsdk_manager_gdo_value_get(program_gdo, GNSDK_GDO_VALUE_TUI, 1, &tui);
			error = gnsdk_manager_gdo_value_get(program_gdo, GNSDK_GDO_VALUE_TUI_TAG, 1, &tag);
			fprintf(stderr, "MATCHED: %s-%s\n", tui, tag);
		}
	}
	
}

void GNSDK_CALLBACK_API acr_callback_status(
											const gnsdk_void_t       *callback_userdata,
											gnsdk_acr_query_handle_t acr_query_handle,
											gnsdk_acr_status_t       acr_status,
											gnsdk_size_t             bytes_done,
											gnsdk_size_t             bytes_total,
											gnsdk_flt32_t            value3,
											gnsdk_error_t			 error,
											gnsdk_cstr_t             message
											)
{
	return;
}


static gnsdk_acr_callbacks_t acr_callbacks = { acr_callback_status, acr_callback_result};

#if(ACR_APP_AUDIO_IN==ACR_APP_AUDIO_PIPE)
void send_samples(gnsdk_acr_query_handle_t *acr_query_handle)
{
	int err;
	int fd;
	short buf[ACR_APP_AUDIO_BUFF_SIZE];
	mkfifo("AUDIO", 0777);
	fd = open("AUDIO", O_RDONLY);
	while (1)
	{
		size_t bytes;
		bytes = read(fd, buf, ACR_APP_AUDIO_BUFF_SIZE*sizeof(short));
		gnsdk_acr_query_write_audio_data(acr_query_handle, buf, bytes, 0);
	}
}
#else
#include <alsa/asoundlib.h>
void send_samples(gnsdk_acr_query_handle_t *acr_query_handle)
{
	int err;
	int fd;
	short buf[ACR_APP_AUDIO_BUFF_SIZE];
	snd_pcm_t *capture_handle;
	snd_pcm_hw_params_t *hw_params;
	
	if ((err = snd_pcm_open (&capture_handle, ACR_APP_ALSA_NAME, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		fprintf (stderr, "cannot open audio device %s (%s)\n", 
				 argv[1],
				 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf (stderr, "cannot set access type (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		fprintf (stderr, "cannot set sample format (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, 44100, 0)) < 0) {
		fprintf (stderr, "cannot set sample rate (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0) {
		fprintf (stderr, "cannot set channel count (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	
	if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot set parameters (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	
	snd_pcm_hw_params_free(hw_params);
	
	if ((err = snd_pcm_prepare (capture_handle)) < 0) {
		fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
				 snd_strerror (err));
		exit (1);
	}
	
	while(1)
	{
		if ((err = snd_pcm_readi (capture_handle, buf, ACR_APP_AUDIO_BUFF_SIZE)) != ACR_APP_AUDIO_BUFF_SIZE) {
			fprintf (stderr, "read from audio interface failed (%s)\n",
					 snd_strerror (err));
			exit (1);
		}
		gnsdk_acr_query_write_audio_data(acr_query_handle, buf, ACR_APP_AUDIO_BUFF_SIZE*2, 0);
	}
}
#endif

void acr_init_shutdown(acr_handle_t **handle, 
					   acr_initialization_t *init,
					   gnsdk_acr_query_handle_t *acr_query_handle)
{

	gnsdk_error_t error = GNSDK_SUCCESS;
	pthread_t pid;
	error = acr_initialize(init, handle);
	assert(error == GNSDK_SUCCESS);
#if ACR_APP_LOGGING
	error = gnsdk_manager_logging_enable(ACR_APP_LOGFILE,									/* file path */
										 GNSDK_LOG_PKG_ALL,
										 GNSDK_LOG_LEVEL_DEBUG,
										 GNSDK_LOG_OPTION_ALL,							/* all logging options: timestamps, thread IDs, etc */
										 1000000,												/* max size of log: 0 means a new log file will be created each run */
										 GNSDK_FALSE										/* GNSDK_TRUE = old logs will be renamed and saved */
										 );
#endif
	
	//gnsdk_acr_query_option_set( acr_query_handle, _GNSDK_ACR_OPTION_FP_SERVER_URL, "https://c14336256.acr-audio.gcsp.cddbp.net/gcsp/2.0/");
	//gnsdk_acr_query_option_set( acr_query_handle, _GNSDK_ACR_OPTION_METADATA_SERVER_URL, "https://c14336256.ipg.web.cddbp.net/webapi/xml/1.0/");
	
	if (init->user == NULL)
	{
		gnsdk_str_t user_string = NULL;
		error =  gnsdk_manager_user_serialize( (*handle)->user_handle, &user_string);
		if (error == GNSDK_SUCCESS)
		{
			/* Copy the user string into the init structure so we have it at next init */
			init->user = strdup((const char *) user_string);  
			gnsdk_manager_string_free(user_string);
		}
	}
	
	error = gnsdk_acr_query_create((*handle)->user_handle, &acr_callbacks, NULL, &acr_query_handle);
	/*error = gnsdk_acr_query_option_set(acr_query_handle,
									   _GNSDK_ACR_OPTION_ENABLE_NEW_CLASSIFIER,
									   GNSDK_VALUE_TRUE); */
	error = gnsdk_acr_query_init_audio_stream(acr_query_handle,
											  gnsdk_acr_audio_alg_1_3svlq,
											  44100,
											  gnsdk_acr_audio_sample_format_pcm16,
											  1);
	
	//pthread_create(&pid, NULL, run_samples_thread, NULL);
	//pthread_join(pid, NULL);
	send_samples(acr_query_handle);
}


int main(int argc, char *argv[])
{
	acr_handle_t *handle;
	acr_initialization_t acr_init_s;
	gnsdk_acr_query_handle_t acr_query_handle;
	
	acr_init_s.video_client_id = NULL;
	acr_init_s.video_client_id_tag = NULL; 
	acr_init_s.user = NULL;
	acr_init_s.license_filename = NULL;
	
	if (acr_app_config(&acr_init_s.video_client_id, 
					   &acr_init_s.video_client_id_tag,
					   &acr_init_s.user,
					   &acr_init_s.license_filename,
					   ACR_APP_CONFIG_FILE))
	{
		fprintf(stderr, "INVALID CONFIGURAITON FILE\n");
	}
	else if (!acr_init_s.client_id)
	{
		fprintf(stderr, "MISSING CLIENT ID\n");
	}
	else if (!acr_init_s.client_tag)
	{
		fprintf(stderr, "MISSING CLIENT TAG\n");
	}
	else if (!acr_init_s.license_filename)
	{
		fprintf(stderr, "MISSING LICENSE FILE\n");
	}
	else
	{
		acr_init_shutdown(&handle, &acr_init_s, &acr_query_handle);		
		return 0;
	}
	return 1;

}
