#ifndef ACR_APP_CONFIG_H
#define ACR_APP_CONFIG_H

#define ACR_APP_AUDIO_PIPE 1
#define ACR_APP_AUDIO_ALSA 2

#define ACR_APP_AUDIO_IN ACR_APP_AUDIO_PIPE

// need to define HW name:
#define ACR_APP_ALSA_NAME "hw:0"

#define ACR_APP_LOGGING 1
#define ACR_APP_LOGFILE "RPI_SDK_LOG.log"

#define ACR_APP_CBUFF_SIZE 2048
#define ACR_APP_CONFIG_FILE "acr_app.conf"

#define ACR_APP_AUDIO_BUFF_SIZE 128

#endif
