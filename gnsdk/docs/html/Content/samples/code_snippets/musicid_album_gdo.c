/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/

/*
 *	Name: MusicID: Retrieving an Album GDO Response
 *	Description:
 *	This example demonstrates retrieving basic metadata from an album response GDO. 
 *	When successfully completed, the gnsdk_musicid_query_find_albums API returns a response GDO of a 
 *	GNSDK_GDO_TYPE_RESPONSE_ALBUM context. If the match type is not a single exact match, you must 
 *	resolve the GDO to a single match using the gnsdk_musicid_query_resolve API.  
 *	Whether derived from a single exact match or a resolved response, the response GDO contains a single album. 
 *	This example shows you how to retrieve that album and display its basic metadata.
 *	Notes:
 *	For clarity and simplicity error handling in not shown here. 
 *	Refer "logging" sample to learn about GNSDK error handling.																					
 *	Command-line Syntax:
 *	sample.exe client_id client_id_tag license																
*/


#include "gnsdk.h"
...

int
main(int argc, char* argv[])
{
    gnsdk_error_t          error = GNSDK_SUCCESS;
    gnsdk_gdo_handle_t     response_gdo = GNSDK_NULL;
    gnsdk_gdo_handle_t     album_gdo = GNSDK_NULL;
    gnsdk_gdo_handle_t     track_gdo = GNSDK_NULL;
    gnsdk_cstr_t           value = GNSDK_NULL;
    gnsdk_cstr_t           track_num = GNSDK_NULL;
    gnsdk_uint32_t         count = 0;
    gnsdk_uint32_t         i = 0;

    /*Initialize GNSDK*/
    ...

    /*Perform the TOC lookup and (when necessary) resolve the result*/
    ...

    /*Response_gdo should now have a response GDO containing one album*/

    /*Get the album child*/
    error = gnsdk_manager_gdo_child_get(
                response_gdo,
                GNSDK_GDO_CHILD_ALBUM,
                1, /*This confirms there is only one album in this response*/
                &album_gdo
                );

    /*Get the album title*/
    error = gnsdk_manager_gdo_value_get(
                album_gdo,
                GNSDK_GDO_VALUE_TITLE_DISPLAY,
                1,
                &value
                );
    if (GNSDK_SUCCESS == error)
    {
        printf("title: %s\r\n", value);
    }

    /*Get the album artist*/
    error = gnsdk_manager_gdo_value_get(
                album_gdo,
                GNSDK_GDO_VALUE_ARTIST_DISPLAY,
                1,
                &value
                );
    if (GNSDK_SUCCESS == error)
    {
        printf("artist: %s\r\n", value);
    }

    /*Get the genre(s); note that is a locale-dependent value */
    error = gnsdk_manager_gdo_value_count(album_gdo, GNSDK_GDO_VALUE_GENRE, &count);

    for (i = 1; i <= count; i++)
    {
        error = gnsdk_manager_gdo_value_get(
                    album_gdo,
                    GNSDK_GDO_VALUE_GENRE,
                    i,
                    &value
                    );
        if (GNSDK_SUCCESS == error)
        {
            printf("genre %d: %s\r\n", i, value);
        }
    }

    /*Iterate over the tracks*/
    error = gnsdk_manager_gdo_child_count(
                album_gdo,
                GNSDK_GDO_CHILD_TRACK,
                &count
                );
    if (GNSDK_SUCCESS == error)
    {
        printf("tracks: %d\r\n", count);
    }

    /*Note that GDO ordinals are 1-based, not 0-based*/
    for (i = 1; i <= count; i++)
    {
        /*Get the feature GDO*/
        error = gnsdk_manager_gdo_child_get(
                    album_gdo,
                    GNSDK_GDO_CHILD_TRACK,
                    i,
                    &track_gdo
                    );

        /*Get track number and title*/
        error = gnsdk_manager_gdo_value_get(
                    track_gdo,
                    GNSDK_GDO_VALUE_TRACK_NUMBER,
                    1,
                    &track_num
                    );

        error = gnsdk_manager_gdo_value_get(
                    track_gdo,
                    GNSDK_GDO_VALUE_TITLE_DISPLAY,
                    1,
                    &value
                    );

        if (GNSDK_SUCCESS == error)
        {
            printf("\ttrack %d: %s\n", track_num, value);
        }

        error = gnsdk_manager_gdo_release(track_gdo);
    }

    /*Clean up*/

    /*Release the GDOs*/
    error = gnsdk_manager_gdo_release(response_gdo);
    error = gnsdk_manager_gdo_release(album_gdo);

    /*Shutdown GNSDK*/
    ...

    return 0;
}
