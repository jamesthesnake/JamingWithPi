/** Gracenote SDK: MusicID privileged header file
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_MUSICID_PRIVILEGED_H_
/** gnsdk_musicid_privileged.h: Privileged prototypes and macros for MusicID.
*/
#define _GNSDK_MUSICID_PRIVILEGED_H_

#ifdef __cplusplus
extern "C"{
#endif


/** GNSDK_MUSICID_FIELD_LYRIC
  * Summary:
  *   Specifies text for a lyric title search field that is used with
  *   gnsdk_musicid_query_set_text.
*/
#define GNSDK_MUSICID_FIELD_LYRIC							"gnsdk_musicid_field_lyric"

/** GNSDK_MUSICID_OPTION_SEARCH_PRESET_OVERRIDE
  * Summary:
  *   Indicates the name of a search preset. ATM, these are gensearch Service presets.
*/
#define GNSDK_MUSICID_OPTION_SEARCH_PRESET_OVERRIDE			"gnsdk_musicid_option_search_preset"

/** GNSDK_MUSICID_OPTION_ADDITIONAL_CREDITS
  * Summary:
  *   Indicates that additiona credits are enabled and will be returned from service.
  */
#define GNSDK_MUSICID_OPTION_ADDITIONAL_CREDITS				"gnsdk_musicid_option_additional_credits"

/** GNSDK_MUSICID_OPTION_OUTPUT_OVERRIDE
  * Summary:
  *   Indicates the name of an output override.  Note only preset override searches use this.  i.e. PLP queries.
*/
#define GNSDK_MUSICID_OPTION_OUTPUT_OVERRIDE				"gnsdk_musicid_option_output"

#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_MUSICID_PRIVILEGED_H_ */

