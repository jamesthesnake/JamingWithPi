/* Copyright (c) 2012 Gracenote.

   This software may not be used in any way or distributed
   without permission. All rights reserved.

   Some code herein may be covered by US and international
   patents.                                                */

#ifndef _GNSDK_MANAGER_GDO_INTERNAL_H_
#define _GNSDK_MANAGER_GDO_INTERNAL_H_

#include "gnsdk_manager_privileged.h" /* for gnsdk_gdo_provider_interface_t */

#ifdef __cplusplus
extern "C"{
#endif

/* enable this to assert our GDO count functions are all working.  if you find something broken and are unsure
how to fix, send jmc enough info to reproduce. */
#ifdef SDKMGR_DEBUG
#define SDKMGR_GDO_ASSERT_COUNTS	0
#endif

/*
** Lookup response code retrieval (jmctodo these macros are not just internal to the SDKManager and should be moved)
*/
#define _SDKMGR_GDO_VALUE_RESPONSE_CODE					"_sdkmgr_val_response_code"

/*
** TUI Value Keys
** For internal TUI retrieval
*/
#define _SDKMGR_GDO_VALUE_TUI_TYPE						"_sdkmgr_val_tui_type"
#define _SDKMGR_GDO_VALUE_TUI_REV						"_sdkmgr_val_tui_rev"
#define _SDKMGR_GDO_VALUE_TUI_REV_TAG					"_sdkmgr_val_tui_rev_tag"

#define _SDKMGR_GDO_VALUE_MUI							"_sdkmgr_val_mui"
#define _SDKMGR_GDO_VALUE_MUI_TAG						"_sdkmgr_val_muitag"

/*
** Result data helpers
*/
#define _SDKMGR_GDO_VALUE_LOCATOR						"_sdkmgr_val_video_locator"

#define _SDKMGR_GDO_VALUE_CERTIFIER						"_sdkmgr_val_certifier"
#define _SDKMGR_GDO_VALUE_CERTIFIER_LEVEL				"_sdkmgr_val_certifierlvl"

#define _SDKMGR_GDO_VALUE_LOOKUP_COUNT					"_sdkmgr_val_lookup_cnt"

#define _SDKMGR_GDO_VALUE_PHONETIC						"gnsdk_val_phonetic"
#define _SDKMGR_GDO_VALUE_PHONETIC_SOURCE				"gnsdk_val_phonetic_src"

/*
 * GDO TUI Types
 * For identifying TUIs found in GDO contexts.
 */
#define _SDKMGR_GDO_TUI_TYPE_ALBUM						"ALBUM"
#define _SDKMGR_GDO_TUI_TYPE_TRACK						"TRACK"
#define _SDKMGR_GDO_TUI_TYPE_LYRIC						"LYRIC"
#define _SDKMGR_GDO_TUI_TYPE_DVD_SET					"DVD_SET"
#define _SDKMGR_GDO_TUI_TYPE_DVD_DISC					"DVD_DISC"
#define _SDKMGR_GDO_TUI_TYPE_VIDEOCLIP					"VIDEO_CLIP"
#define _SDKMGR_GDO_TUI_TYPE_MUI						"MUI"
#define _SDKMGR_GDO_TUI_TYPE_AUDIO_WORK					"AUDIO_WORK"
#define _SDKMGR_GDO_TUI_TYPE_VIDEO_WORK					"VIDEO_WORK"
#define _SDKMGR_GDO_TUI_TYPE_VIDEO_SEASON				"VIDEO_SEASON"
#define _SDKMGR_GDO_TUI_TYPE_VIDEO_SERIES				"VIDEO_SERIES"
#define _SDKMGR_GDO_TUI_TYPE_TVPROGRAM					"TVPROGRAM"
#define _SDKMGR_GDO_TUI_TYPE_TVPROVIDER					"TVPROVIDER"
#define _SDKMGR_GDO_TUI_TYPE_TVCHANNEL					"TVCHANNEL"
#define _SDKMGR_GDO_TUI_TYPE_CONTRIBUTOR				"CONTRIBUTOR"
#define _SDKMGR_GDO_TUI_TYPE_MATCH_INFO					"MATCH_INFO"

#define _SDKMGR_GDO_TUI_TYPE_ALBUM_legacy				"gnsdk_tui_type_album"			/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_TRACK_legacy				"gnsdk_tui_type_track"			/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_LYRIC_legacy				"gnsdk_tui_type_lyric"			/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_DVD_SET_legacy				"gnsdk_tui_type_dvd_set"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_DVD_DISC_legacy			"gnsdk_tui_type_dvd_disc"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_VIDEOCLIP_legacy			"gnsdk_tui_type_videoclip"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_ALBUM_deprecated			"_sdkmgr_tui_type_album"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_TRACK_deprecated			"_sdkmgr_tui_type_track"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_LYRIC_deprecated			"_sdkmgr_tui_type_lyric"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_DVD_SET_deprecated			"_sdkmgr_tui_type_dvd_set"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_DVD_DISC_deprecated		"_sdkmgr_tui_type_dvd_disc"		/* deprecated */
#define _SDKMGR_GDO_TUI_TYPE_VIDEO_WORK_deprecated		"AV_WORK"						/* deprecated */


/*
 * GDO Descriptor Keys
 */
#define _SDKMGR_GDO_DESCRIPTOR_TYPE_ID					"_sdkmgr_descriptor_typeid"
#define _SDKMGR_GDO_DESCRIPTOR_ITEM_ID					"_sdkmgr_descriptor_itemid"

/*****************************************************************************
** GDO Keys specific to ALBUM OAR Descriptor
*/
#define _SDKMGR_GDO_VALUE_ALBUM_OAR						"_sdkmgr_album_oar"

#define GNSDK_ALBUMTYPE_MAINCANNON						"gnsdk_albumtype_maincannon"
#define GNSDK_ALBUMTYPE_MAINCANNON_COLLECTION			"gnsdk_albumtype_maincannon_collection"
#define GNSDK_ALBUMTYPE_COMMERCIAL_SINGLEARTIST			"gnsdk_albumtype_compilation_single"
#define GNSDK_ALBUMTYPE_COMMERCIAL_MULTIARTIST			"gnsdk_albumtype_compilation_multi"
#define GNSDK_ALBUMTYPE_MUSICSERVICE					"gnsdk_albumtype_music_service"
#define GNSDK_ALBUMTYPE_BOOTLEG_SINGLEARTIST			"gnsdk_albumtype_bootleg_single"
#define GNSDK_ALBUMTYPE_BOOTLEG_MULTIARTIST				"gnsdk_albumtype_bootleg_multi"
#define GNSDK_ALBUMTYPE_PERSONAL_BURN					"gnsdk_albumtype_personal_burn"
#define GNSDK_ALBUMTYPE_SINGLE							"gnsdk_albumtype_single"
#define GNSDK_ALBUMTYPE_OTHER							"gnsdk_albumtype_other"
#define GNSDK_ALBUMTYPE_UNKNOWN							"gnsdk_albumtype_unknown"

/*****************************************************************************
** GDO Keys specific to XIDs
*/
#define _SDKMGR_GDO_VALUE_EXTERNALID_TOKEN				"_sdkmgr_val_xid_token"

/*****************************************************************************
** GDO Keys specific to LIST responses
*/

#define _SDKMGR_GDO_TYPE_RESPONSE_LIST				"_sdkmgr_ctx_responselist"	/** GDO is of list response context (GDO contains 1 or more list contexts) */
#define _SDKMGR_GDO_TYPE_LIST						"gnsdk_ctx_list"			/** GDO is of list context */

#define _SDKMGR_GDO_CHILD_LIST							_SDKMGR_GDO_TYPE_LIST"!"	/** Retrieve list context (generally from list response GDO) */

#define _SDKMGR_GDO_VALUE_LIST_DATA						"_sdkmgr_val_list_data"
#define _SDKMGR_GDO_VALUE_LIST_PACKAGE_LANG_ID			"_sdkmgr_val_list_language_id" /* jmctodo drop PACKAGE as this (written) lang can be used in a few different ways */
#define _SDKMGR_GDO_VALUE_LIST_GENRE_ID					"_sdkmgr_val_list_genre_id"
#define _SDKMGR_GDO_VALUE_LIST_ARTIST_TYPE_ID			"_sdkmgr_val_list_artist_type_id"
#define _SDKMGR_GDO_VALUE_LIST_ORIGIN_ID				"_sdkmgr_val_list_origin_id"
#define _SDKMGR_GDO_VALUE_LIST_ERA_ID					"_sdkmgr_val_list_era_id"
#define _SDKMGR_GDO_VALUE_LIST_VIDEO_GENRE_ID			"_sdkmgr_val_list_video_genre_id"
#define _SDKMGR_GDO_VALUE_LIST_VIDEO_REGION_ID			"_sdkmgr_val_list_video_region_id"
#define _SDKMGR_GDO_VALUE_LIST_RATING_ID				"_sdkmgr_val_list_rating_id"
#define _SDKMGR_GDO_VALUE_LIST_FEATURE_TYPE				"_sdkmgr_val_list_feature_type"
#define _SDKMGR_GDO_VALUE_LIST_MEDIA_TYPE_ID			"_sdkmgr_val_list_media_type_id"
#define _SDKMGR_GDO_VALUE_LIST_VIDEO_SERIAL_TYPE_ID		"_sdkmgr_val_list_serial_type_id"
#define _SDKMGR_GDO_VALUE_LIST_VIDEO_COLORATION_TYPE_ID	"_sdkmgr_val_list_coloration_type_id"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOAUDIENCE			"_sdkmgr_val_list_videoaudience"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOMOOD				"_sdkmgr_val_list_videomood"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOSTORYTYPE			"_sdkmgr_val_list_videostorytype"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOREPUTATION			"_sdkmgr_val_list_videosreputation"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOSCENARIO			"_sdkmgr_val_list_videoscenario"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOSETTINGENV			"_sdkmgr_val_list_videosettingenv"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOSETTINGPERIOD		"_sdkmgr_val_list_videosettingperiod"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOSOURCE				"_sdkmgr_val_list_videosource"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOSTYLE				"_sdkmgr_val_list_videostyle"
#define _SDKMGR_GDO_VALUE_LIST_VIDEOTOPIC				"_sdkmgr_val_list_videotopic"
#define _SDKMGR_GDO_VALUE_LIST_WORK_TYPE_ID				"_sdkmgr_val_list_work_type_id"
#define _SDKMGR_GDO_VALUE_LIST_MEDIA_SPACE_ID			"_sdkmgr_val_list_media_space_id"
#define _SDKMGR_GDO_VALUE_LIST_MOOD_ID					"_sdkmgr_val_list_mood_id"
#define _SDKMGR_GDO_VALUE_LIST_MOOD_DATA				"_sdkmgr_val_list_mood_data"	/* like "34414:39,34412:17,34406:14,34208:8,34400:5,34217:4,34194:2,34190:2,34388:1,34387:1" */
#define _SDKMGR_GDO_VALUE_LIST_TEMPO_VALUE				"_sdkmgr_val_list_tempo_value"	/* bpm value */
#define _SDKMGR_GDO_VALUE_LIST_TEMPO_DATA				"_sdkmgr_val_list_tempo_data"	/* like "169:0,93:0,83:0" */
#define _SDKMGR_GDO_VALUE_DESC_ERA_ID					"_sdkmgr_val_desc_era_id"
#define _SDKMGR_GDO_VALUE_DESC_ORIGIN_ID				"_sdkmgr_val_desc_origin_id"
#define _SDKMGR_GDO_VALUE_DESC_COMPFORM_ID				"_sdkmgr_val_desc_compform_id"
#define _SDKMGR_GDO_VALUE_LIST_EPGVIEWINGTYPE_ID		"_sdkmgr_val_list_epgviewingtype"
#define _SDKMGR_GDO_VALUE_LIST_EPGAUDIOTYPE_ID			"_sdkmgr_val_list_epgaudiotype"
#define _SDKMGR_GDO_VALUE_LIST_EPGVIDEOTYPE_ID			"_sdkmgr_val_list_epgvideotype"
#define _SDKMGR_GDO_VALUE_LIST_EPGCAPTIONTYPE_ID		"_sdkmgr_val_list_epgcaptiontype"
#define _SDKMGR_GDO_VALUE_LIST_EPGCATEGORY_L1_ID		"_sdkmgr_val_list_epgcatl1"
#define _SDKMGR_GDO_VALUE_LIST_EPGCATEGORY_L2_ID		"_sdkmgr_val_list_epgcatl2"
#define _SDKMGR_GDO_VALUE_LIST_EPGPRODUCTIONTYPE_ID		"_sdkmgr_val_list_epgproductiontype"
#define _SDKMGR_GDO_VALUE_LIST_EPGDEVICETYPE_ID			"_sdkmgr_val_list_epgdevicetype"


/*****************************************************************************
** GDO Keys specific to LINK responses
*/
#define _SDKMGR_GDO_TYPE_RESPONSE_LINK					"_sdkmgr_ctx_responselink"
#define _SDKMGR_GDO_TYPE_RESPONSE_LINK_GENRE			"_sdkmgr_ctx_responselinkgenre"

/*****************************************************************************
** GDO Keys specific to video 'object' responses
*/
#define _SDKMGR_GDO_VALUE_OBJECT_TYPE					"_sdkmgr_val_object_type"

/*****************************************************************************
** GDO Keys for Submission responses
*/
#define _SDKMGR_GDO_VALUE_ALBUM_WORKORDERS				"_sdkmgr_val_alb_workorders" /* supported by ALBUM context */

#define _SDKMGR_GDO_TYPE_RESPONSE_SUBMIT				"_sdkmgr_ctx_responsesubmit"

#define _SDKMGR_GDO_TYPE_RESPONSE_WORKORDER				"_sdkmgr_ctx_responseworkorder"
#define _SDKMGR_GDO_TYPE_WORKORDER						"_sdkmgr_ctx_workorder"

#define _SDKMGR_GDO_CHILD_WORKORDER						_SDKMGR_GDO_TYPE_WORKORDER"!"
/*#define _SDKMGR_GDO_CHILD_WORKORDER_BY_TRACK_NUMBER	_SDKMGR_GDO_TYPE_WORKORDER"!number"*/

#define _SDKMGR_GDO_VALUE_ID							"_sdkmgr_val_id"
#define _SDKMGR_GDO_VALUE_FEATURE_TYPE					"_sdkmgr_val_feature_type"
#define _SDKMGR_GDO_VALUE_FEATURE_VERSION				"_sdkmgr_val_feature_version"
#define _SDKMGR_GDO_VALUE_FEATURE_PARAMS				"_sdkmgr_val_feature_params"
#define _SDKMGR_GDO_VALUE_FEATURE_PRIORITY				"_sdkmgr_val_feature_priority"

/*****************************************************************************
** GDO Keys specific to MEDIA responses
*/
#define _SDKMGR_GDO_VALUE_MATCH_STATE					"_sdkmgr_val_match_state"

#define _SDKMGR_GDO_VALUE_MEDIA_MATCH_BLOCK				"_sdkmgr_val_media_matchblock"
#define _SDKMGR_GDO_VALUE_MEDIA_MATCH_POSITION			"_sdkmgr_val_media_matchpos"
#define _SDKMGR_GDO_VALUE_MEDIA_MATCH_POSITION_UNITS	"_sdkmgr_val_media_matchposu"

/*****************************************************************************
** GDO Keys specific to TEXT_SEARCH/TEXT_MATCH logic
*/
#define _SDKMGR_GDO_TYPE_TEXT_MATCH						"_sdkmgr_ctx_text_match"
#define _SDKMGR_GDO_VALUE_TEXT_MATCH_ALBUM_SCORE		"_sdkmgr_val_text_match_album_score"
#define _SDKMGR_GDO_VALUE_TEXT_MATCH_CONTRIB_SCORE		"_sdkmgr_val_text_match_contrib_score"
#define _SDKMGR_GDO_VALUE_TEXT_MATCH_GENRE_SCORE		"_sdkmgr_val_text_match_genre_score"
#define _SDKMGR_GDO_VALUE_TEXT_MATCH_TRACK_SCORE		"_sdkmgr_val_text_match_track_score"

/******************************************************************************
** AIM Yomi/Betsumei accessors
*/

/*_SDKMGR_GDO_VALUE_AIM_YOMI and _SDKMGR_GDO_VALUE_AIM_BETSUMEI are the RAW data and for AIM use only, these keys SHOULD NOT be provided to anyone else under any circumstances*/

/* _SDKMGR_GDO_VALUE_AIM_YOMI is the internal Key to retrieve Raw Yomi Data.*/
#define _SDKMGR_GDO_VALUE_AIM_YOMI						"_sdkmgr_val_aimyomi"

/* _SDKMGR_GDO_VALUE_AIM_BETSUMEI is the internal Key to Raw Betsumei Data.  Data is a delimited string containing alternate names, nick names, group members, collaborations.*/
#define _SDKMGR_GDO_VALUE_AIM_BETSUMEI					"_sdkmgr_val_aimbetsumei"

/*_SDKMGR_GDO_VALUE_YOMI, _SDKMGR_GDO_VALUE_BETSUMEI_PRIMARY and _SDKMGR_GDO_VALUE_BETSUMEI_ALL are the keys to retrieve the processed string from the above 2 keys.
Previously the above 2 keys were processed in AIM Wrapper but that processing is now available in GNSDK (implemented by AIM)
E.g., some sort of normalization is done, convert Åe1Åf to ÅeoneÅf equivalent in Japanese*/

/*_SDKMGR_GDO_VALUE_YOMI is the internal key to retrieved processed Yomi data.  This key is only used for sorting use cases and by non-AIM custoemrs*/
#define _SDKMGR_GDO_VALUE_YOMI							"_sdkmgr_val_yomi"

/*_SDKMGR_GDO_VALUE_BETSUMEI_PRIMARY is the internal key to retrieved processed Betsumei data, in particular the primary betsumei data.
This key could be exposed by Gracenote to non-AIM customers for potentially ASR use case */
#define _SDKMGR_GDO_VALUE_BETSUMEI_PRIMARY				"_sdkmgr_val_betsumei-primary"

/*_SDKMGR_GDO_VALUE_BETSUMEI_ALL is the internal key to retrieved processed Betsumei data.
This key could be exposed by Gracenote to non-AIM customers for processing data retrieved by _SDKMGR_GDO_VALUE_AIM_BETSUMEI*/
#define _SDKMGR_GDO_VALUE_BETSUMEI_ALL					"_sdkmgr_val_betsumei-all"

/* _SDKMGR_VALUE_AIM_BETSUMEI this value can come back from online queries for sortable data */
#define	_SDKMGR_VALUE_AIM_BETSUMEI						"aim-betsumei"


/*****************************************************************************
** GDO Contexts and Keys specific to EBD Installer GDOs
*/
#define _SDKMGR_GDO_TYPE_CORRELATES                     "gnsdk_ctx_correlates"

#define _SDKMGR_GDO_VALUE_NAME_ID                       "_sdkmgr_val_name_id"
#define _SDKMGR_GDO_VALUE_TITLE_ID                      "_sdkmgr_val_title_id"
#define _SDKMGR_GDO_VALUE_NAME_TYPE                     "_sdkmgr_val_name_type"
#define _SDKMGR_GDO_VALUE_TITLE_TYPE                    "_sdkmgr_val_title_type"
#define _SDKMGR_GDO_VALUE_CONTRIBUTOR_ID                "_sdkmgr_val_contrib_id"
#define _SDKMGR_GDO_VALUE_IS_ARTIST                     "_sdkmgr_val_is_art"
#define _SDKMGR_GDO_VALUE_WORK_ID                       "_sdkmgr_val_work_id"
#define _SDKMGR_GDO_CHILD_NAME                          GNSDK_GDO_TYPE_NAME"!"
#define _SDKMGR_GDO_CHILD_TITLE                         GNSDK_GDO_TYPE_TITLE"!"
#define _SDKMGR_GDO_VALUE_LANG_ID                       _SDKMGR_GDO_VALUE_LIST_PACKAGE_LANG_ID
#define _SDKMGR_GDO_VALUE_IS_OFFICIAL                   "_sdkmgr_val_isofficial"
#define _SDKMGR_GDO_VALUE_IS_LANG_DEFAULT               "_sdkmgr_val_islangdefault"
#define _SDKMGR_GDO_VALUE_IS_DEFAULT                    "_sdkmgr_val_isdefault"	/* the 'default default' the 'native' the 'right one' */
#define _SDKMGR_GDO_VALUE_VARIANT_TYPE                  "_sdkmgr_val_variant_type"
#define _SDKMGR_GDO_VALUE_SORTABLE_RAW                  "_sdkmgr_val_sort_raw"	/* iterates the unprocessed sort strings */
#define _SDKMGR_GDO_VALUE_SORTABLE_SCHEME_ID            "_sdkmgr_val_sort_scheme_id"
#define _SDKMGR_GDO_TYPE_CONFIGURATION                  "gnsdk_ctx_config"

#define _SDKMGR_GDO_VALUE_EXTERNALID_CATALOG_ID         "_sdkmgr_val_xid_catid"
#define _SDKMGR_GDO_VALUE_COLLABORATOR_ID               "_sdkmgr_val_collab_id"
#define _SDKMGR_GDO_VALUE_COLLABORATOR_IS_PRIMARY       "_sdkmgr_val_collab_prim"
#define _SDKMGR_GDO_VALUE_ALBUM_OAR_ID                  "_sdkmgr_val_oar_id"

#define _SDKMGR_GDO_VALUE_NAME                          "_sdkmgr_val_name"



/* SORTABLE ALPHEBET IDS
Chu Han	7
Chu Nom	6
Hangul	16
Hanja	17
Jamo	15
Kanji	2
Latin (Quoc ngu)	5
Roman	8
Roman	4
Roman	14
Roman	11
aim-yomi	18
gn-pinyin	19
gn-pinyin	20
*/
#define _SDKMGR_SORTABLE_ALPHABET_ID_AIM_YOMI						"18"
#define _SDKMGR_SORTABLE_ALPHABET_ID_GN_PINYIN_19					"19" /* i don't know how 19 and 20 differ, hence the lame macro name */
#define _SDKMGR_SORTABLE_ALPHABET_ID_GN_PINYIN						"20"

/* VARIANT_TYPE values
2            Misspelling
3            Yomi AIM
4            Yomi Gracenote
5            Betsumei Gracenote
6            Betsumei AIM
7            Romaji Gracenote
8            Romaji AIM
9            Nickname
10           Birthname
11           Hanja
12           Korean Spelling
13           Romako
14           Russian Roman
15           Russian Roman (State)
16           Russian Roman (BGN)
17           Russian Roman (LoC)
18           Chinese Self Englished
19           Chinese Simplified
20           Chinese Traditional
21           Chinese Roman (Pinyin)
22           Chinese Roman (Non-Pinyin)
23           Shortname
24           TLS
25           Japanese
31           AIM Japanese The
32           AIM Nickname
33           AIM Misspelling
34           AIM Shortname
*/
#define	_SDKMGR_VARIANT_TYPE_NICKNAME						9
#define _SDKMGR_VARIANT_TYPE_AIM_YOMI						3  /* this is used for text indeces as well as metadata */
#define _SDKMGR_VARIANT_TYPE_AIM_BETSUMEI					6  /* this is used for text indeces only. the separate 'composite' betsumei string is used for metadata */
#define _SDKMGR_VARIANT_TYPE_SHORTNAME						23
#define _SDKMGR_VARIANT_TYPE_TLS							24

/*****************************************************************************
** GDO Helper Keys
*/
#define _SDKMGR_GDO_CHILD_VIDEO_FEATURE_BY_ORD			GNSDK_GDO_TYPE_VIDEO_FEATURE"!ord"
#define _SDKMGR_GDO_CHILD_VIDEO_DISC_BY_ORD				GNSDK_GDO_TYPE_VIDEO_DISC"!ord"
#define _SDKMGR_GDO_CHILD_VIDEO_SIDE_BY_ORD				GNSDK_GDO_TYPE_VIDEO_SIDE"!ord"
#define _SDKMGR_GDO_CHILD_VIDEO_LAYER_BY_ORD			GNSDK_GDO_TYPE_VIDEO_LAYER"!ord"

/*
 * Genre keys
 * For retrieving genre artwork.
 */
#define _SDKMGR_GDO_VALUE_GENRE_META_ID					"_sdkmgr_val_genremeta_id"

/*
 * CDS ID keys
 * For retrieving CDS content. (for now in gnsdk_link, these are used for local fetches only - where no token is needed)
 */

#define _SDKMGR_GDO_VALUE_GENRE_ART_ID					"_sdkmgr_val_genre_art_id"
#define _SDKMGR_GDO_VALUE_GENRE_ART_TOKEN				"_sdkmgr_val_genre_art_tok"

/*
 * Submit Types
 * For identifying TOCs and other submit-required info found in GDO contexts.
 */
#define _SDKMGR_GDO_VALUE_TOC_ALBUM						"gnsdk_val_toc_album"		/* same as submit's GNSDK_GDO_VALUE_TOC_ALBUM */
#define _SDKMGR_GDO_VALUE_MATCH_TYPE					"_sdkmgr_val_match_type"
#define _SDKMGR_GDO_VALUE_LOOKUP_TYPE					"_sdkmgr_val_lookup_type"
#define _SDKMGR_GDO_VALUE_LOOKUP_LANG					"_sdkmgr_val_lookup_lang"	/* the preferred lang (if set) of the query */

#define _SDKMGR_GDO_VALUE_MATCH_TYPE_SINGLE				"SINGLE"
#define _SDKMGR_GDO_VALUE_MATCH_TYPE_FUZZY				"FUZZY"
#define _SDKMGR_GDO_VALUE_MATCH_TYPE_MULTI				"MULTI"
#define _SDKMGR_GDO_VALUE_MATCH_TYPE_NONE				"NONE"
#define _SDKMGR_GDO_VALUE_MATCH_TYPE_MIDF				"MIDF" /* jmc note - this is a temporary cop out for MID-File */

#define _SDKMGR_GDO_VALUE_LOOKUP_TYPE_TOC				"TOC"
#define _SDKMGR_GDO_VALUE_LOOKUP_TYPE_TUI				"TUI"
#define _SDKMGR_GDO_VALUE_LOOKUP_TYPE_TEXT				"TEXT"
#define _SDKMGR_GDO_VALUE_LOOKUP_TYPE_XID				"XID"
#define _SDKMGR_GDO_VALUE_LOOKUP_TYPE_FP				"FP"
#define _SDKMGR_GDO_VALUE_LOOKUP_TYPE_MIDF				"MIDF" /* jmc note - this is a temporary cop out for MID-File */

/** GNSDK_GDO_TYPE_RESPONSE_LFS
  * Summary:
  *   GDO is of LFS response context.
*/
#define GNSDK_GDO_TYPE_RESPONSE_LFS					"gnsdk_ctx_response_lfs"

/* AUDIO_WORK RESPONSES are not exposed (they are part of ALBUMs/TRACKs) */
#define _SDKMGR_GDO_TYPE_RESPONSE_AUDIO_WORK			"gnsdk_ctx_response_audio_work"

#define _SDKMGR_GDO_RENDER_XML_PUBLIC_MASK				0x000FFFFF

/* Automatic render flags (set by SDK if relevant lookups were performed) */
#define _SDKMGR_GDO_RENDER_XML_CONTENT					0x00400000
#define _SDKMGR_GDO_RENDER_XML_GLOBALIDS				0x00800000
#define _SDKMGR_GDO_RENDER_XML_CLASSICAL				0x04000000
#define _SDKMGR_GDO_RENDER_XML_SONIC					0x01000000
#define _SDKMGR_GDO_RENDER_XML_AIM						0x08000000
#define _SDKMGR_GDO_RENDER_XML_SKIP_PROVIDER_RENDER		0x10000000 /* skip any data added by the GDO provider - currently this data is not render flag driven so it will always be there */

#define _SDKMGR_GDO_RENDER_EXTRA_CONTENT_MASK			(_SDKMGR_GDO_RENDER_XML_CLASSICAL|_SDKMGR_GDO_RENDER_XML_SONIC)
#define _SDKMGR_GDO_RENDER_LINK_CONTENT_MASK			(_SDKMGR_GDO_RENDER_XML_GLOBALIDS|_SDKMGR_GDO_RENDER_XML_CONTENT|_SDKMGR_GDO_RENDER_XML_AIM)

/* private rendering flag */
#define _SDKMGR_GDO_RENDER_XML_INTERNAL					0x10000000
/* render for serialization */
#define _SDKMGR_GDO_RENDER_XML_SERIALIZATION			0x20000000


/* Shortcut keys to find Works, Products, Contributors, Season or Series partial embededed within another GDO (see gcsp map)
   Some of these embedded GDOs may be embedded deep (such a Works inside of Products.)  This makes it easy for the SDK to
   find all the Work partial objects in a Product, Contributor, Series or Season by using the same child key, and not caring
   what the source context is.  For example, Work from a Contributor is 'CREDIT/AV_WORK', Work from a Series is 'AV_WORK' and
   Work from a Product is 'VIDEO_DISC/VIDEO_SIDE/VIDEO_LAYER/VIDEO_FEATURE/MEDIA_OBJECT[@TYPE=AV_WORK]', but from any of these
   contexts the SDK simply has to look for _SDKMGR_GDO_CHILD_SHORTCUT_VIDEO_WORK.
*/
#define _SDKMGR_GDO_CHILD_SHORTCUT_VIDEO_WORK			GNSDK_GDO_TYPE_VIDEO_WORK"!shortcut"
#define _SDKMGR_GDO_CHILD_SHORTCUT_VIDEO_PRODUCT		GNSDK_GDO_TYPE_VIDEO_PRODUCT"!shortcut"
#define _SDKMGR_GDO_CHILD_SHORTCUT_CONTRIBUTOR			GNSDK_GDO_TYPE_CONTRIBUTOR"!shortcut"
#define _SDKMGR_GDO_CHILD_SHORTCUT_VIDEO_SERIES			GNSDK_GDO_TYPE_VIDEO_SERIES"!shortcut"
#define _SDKMGR_GDO_CHILD_SHORTCUT_VIDEO_SEASON			GNSDK_GDO_TYPE_VIDEO_SEASON"!shortcut"



/* Special internal context for an intermediate ACR lookup step*/
#define _SDKMGR_GDO_TYPE_RESPONSE_TUIDS_ALBUM			"sdkmgr_ctx_response_tuids_album"
#define _SDKMGR_GDO_VALUE_TUID							"sdkmgr_val_tuid"

/* GA ACR */
#define _SDKMGR_GDO_VALUE_ACR_MATCH_TYPE				"sdkmgr_acr_match_type"
#define _SDKMGR_GDO_VALUE_ACR_MATCH_DATE				"sdkmgr_acr_match_date"
#define _SDKMGR_GDO_TYPE_RESPONSE_ACR_SERVICE_MATCH		"_sdkmgr_ctx_response_acr_service_match"
#define _SDKMGR_GDO_TYPE_ACR_SERVICE_MATCH 				"_sdkmgr_ctx_acr_service_match"
#define _SDKMGR_GDO_CHILD_ACR_SERVICE_MATCH				_SDKMGR_GDO_TYPE_ACR_SERVICE_MATCH"!"


/* This are private keys only added when building some internal testing apps */
#ifdef _SDKMGR_PRIVATE_TESTING_KEYS
#define _SDKMGR_VALUE_TITLE_DISPLAY_ALL					"sdkmgr_val_title_display_all"
#define _SDKMGR_VALUE_TITLE_DISPLAY_LANGUAGE_ALL		"sdkmgr_val_title_display_language_all"

#define _SDKMGR_VALUE_TITLE_SORTABLE_ALL				"sdkmgr_val_title_sortable_all"
#define _SDKMGR_VALUE_TITLE_SORTABLE_LANGUAGE_ALL		"sdkmgr_val_title_sortable_language_all"

#define _SDKMGR_VALUE_FRANCHISE_TITLE_ALL				"sdkmgr_val_franchise_title_all"
#define _SDKMGR_VALUE_FRANCHISE_TITLE_LANGUAGE_ALL		"sdkmgr_val_franchise_title_language_all"

#define _SDKMGR_VALUE_SERIES_TITLE_ALL					"sdkmgr_val_series_title_all"
#define _SDKMGR_VALUE_SERIES_TITLE_LANGUAGE_ALL			"sdkmgr_val_series_title_language_all"

#define _SDKMGR_VALUE_TITLE_PREFIX_ALL					"sdkmgr_val_title_prefix_all"
#define _SDKMGR_VALUE_TITLE_PREFIX_LANGUAGE_ALL			"sdkmgr_val_title_prefix_language_all"

#define _SDKMGR_VALUE_PLOT_SYNOPSIS_ALL					"sdkmgr_val_plot_synopsis_all"
#define _SDKMGR_VALUE_PLOT_SYNOPSIS_LANGUAGE_ALL		"sdkmgr_val_plot_synopsis_language_all"

#define _SDKMGR_VALUE_NAME_REGIONAL_ALL					"sdkmgr_val_name_reg_all"
#define _SDKMGR_VALUE_NAME_REGIONAL_LANGUAGE_ALL		"sdkmgr_val_name_lang_all"

#define _SDKMGR_VALUE_BIOGRAPHY_ALL						"sdkmgr_val_biography_all"
#define _SDKMGR_VALUE_BIOGRAPHY_LANGUAGE_ALL			"sdkmgr_val_biography_language_all"

#define _SDKMGR_CHILD_CREDIT_WORK_ONLY					GNSDK_GDO_TYPE_CREDIT"!workonly"

#endif


/* FP Local/FP Cache */
#define FPLOCAL_GDO_VALUE_FPLOCAL_MATCH_POSITION          "match_position"
#define FPLOCAL_GDO_VALUE_FPLOCAL_MATCH_POSITION_ADJUSTED "adjusted_position"

#define FPLOCAL_GDO_CHILD_ALBUM             "fplocal_child_album"
#define FPLOCAL_GDO_CHILD_VIDEO_WORK        "fplocal_child_work"
#define FPLOCAL_GDO_CHILD_TVPROGRAM         "fplocal_child_tvprogram"
#define FPLOCAL_GDO_CHILD_USER              "fplocal_child_user"

#define FPLOCAL_GDO_TYPE_RESPONSE_MATCH              "_fplocal_ctx_response_match"

#define FPLOCAL_GDO_TYPE_RESPONSE_FPLOCAL_VIDEO_WORK "_fplocal_ctx_response_fplocal_video_work"
#define FPLOCAL_GDO_TYPE_RESPONSE_FPLOCAL_ALBUM      "_fplocal_ctx_response_fplocal_album"
#define FPLOCAL_GDO_TYPE_RESPONSE_FPLOCAL_TVPROGRAM  "_fplocal_ctx_response_fplocal_tvprogram"
#define FPLOCAL_GDO_TYPE_RESPONSE_FPLOCAL_USER       "_fplocal_ctx_response_fplocal_user"


/*Hiding some previously public data keys */

/** GNSDK_LIST_TYPE_VIDEOCOLORTYPES
  * Summary:
  *   The list of supported color types for video data, such as <i>Black and
  *   White</i>, or <i>Color</i>.
*/
#define			GNSDK_LIST_TYPE_VIDEOCOLORTYPES		"list_type_videocolortypes"

/** GNSDK_GDO_VALUE_COLOR_TYPE
  * Summary:
  *   Retrieve a color type value from a GDO.
*/
#define GNSDK_GDO_VALUE_COLOR_TYPE						"gnsdk_val_list_vidcolor_type"

/** GNSDK_GDO_VALUE_PLOT_TRIVIA
  * Summary:
  *   Retrieve a plot trivia value from a GDO.
*/
#define GNSDK_GDO_VALUE_PLOT_TRIVIA						"gnsdk_val_plot_trivia"

/** GNSDK_GDO_VALUE_PLOT_TRIVIA_LANGUAGE
  * Summary:
  *   Retrieve the available language value for a returned
  *   GNSDK_GDO_VALUE_PLOT_TRIVIA object.
*/
#define GNSDK_GDO_VALUE_PLOT_TRIVIA_LANGUAGE			"gnsdk_val_plot_trivia_language"

/** GNSDK_GDO_VALUE_PLOT_QUOTE
  * Summary:
  *   Retrieve a plot quote value from a GDO.
*/
#define GNSDK_GDO_VALUE_PLOT_QUOTE						"gnsdk_val_plot_quote"

/** GNSDK_GDO_VALUE_PLOT_QUOTE_LANGUAGE
  * Summary:
  *   Retrieve the available language value for a returned GNSDK_GDO_VALUE_PLOT_QUOTE
  *   \object.
*/
#define GNSDK_GDO_VALUE_PLOT_QUOTE_LANGUAGE				"gnsdk_val_plot_quote_language"

/** GNSDK_GDO_VALUE_PLOT_TAGLINE_LANGUAGE
  * Summary:
  *   Retrieve the available language value for a returned
  *   GNSDK_GDO_VALUE_PLOT_TAGLINE object.
*/
#define GNSDK_GDO_VALUE_PLOT_TAGLINE_LANGUAGE			"gnsdk_val_plot_tagline_language"

/** GNSDK_GDO_VALUE_PRODUCTION_START_DATE
  * Summary:
  *   Retrieves a production start date value from a GDO.
*/
#define GNSDK_GDO_VALUE_PRODUCTION_START_DATE			"gnsdk_val_production_start_date"
/** GNSDK_GDO_VALUE_PRODUCTION_END_DATE
  * Summary:
  *   Retrieves a production end date value from a GDO.
*/
#define GNSDK_GDO_VALUE_PRODUCTION_END_DATE				"gnsdk_val_production_end_date"


#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_MANAGER_GDO_INTERNAL_H_ */

