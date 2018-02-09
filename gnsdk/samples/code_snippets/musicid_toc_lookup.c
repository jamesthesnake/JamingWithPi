/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/

/*
 *	Name: MusicID TOC Lookup
 *	Description:
 *	This example shows how to look up a CD’s metadata using its TOC. A CD’s TOC 
 *	is its table of contents. While this example focuses on looking up a CD 
 *	by its TOC, the basic query steps are similar for most GNSDK lookups. 
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
    gnsdk_error_t                 error = GNSDK_SUCCESS;
    gnsdk_musicid_query_handle_t  query_handle = GNSDK_NULL;
    gnsdk_gdo_handle_t            response_gdo = GNSDK_NULL;
    gnsdk_gdo_handle_t            resolved_response_gdo = GNSDK_NULL;
    gnsdk_uint32_t                choice_ordinal = 0;

    /*Initialize GNSDK*/
    ...

    /*Get the TOC as a string*/
    ...

    /*Create the query handle*/
    error = gnsdk_musicid_query_create(
            user_handle,     /*User handle from the initialization*/
            GNSDK_NULL,     /*No status callback*/
            GNSDK_NULL    /*No status userdata*/
            &query_handle    /*gnsdk_musicid_query_handle_t pointer*/
                );

    /*Set the input TOC*/
    error = gnsdk_musicid_query_set_toc_string(
            query_handle,
            toc    /*TOC string - like "150 14650 24167 35542 48615 60617 77010 92060 107187 123745 135162 150397"*/
            );

    /*Perform the query*/
    error = gnsdk_musicid_query_find_albums(
            query_handle,
            &response_gdo    /*gnsdk_gdo_handle_t pointer for the result GDO*/
            );

    /*Examine the match type*/
    if (gnsdk_musicid_match_type_single_exact == match_type)
    {
        /*Single exact match; so we have the full  result*/
        printf("Single exact match for TOC\r\n");

        /*Display the album's metadata*/
        ...
    }
    else if (gnsdk_musicid_match_type_none == match_type)
    {
        /*No matches for the given TOC*/
        printf("No matches for TOC\r\n");
    }
    else /*You must run the partial results by the user*/
    {
        if (gnsdk_musicid_match_type_multi_exact == match_type)
        {
            printf("Multiple exact matches for the TOC.  Have the user choose.\r\n");
        }
        else if (gnsdk_musicid_match_type_fuzzy == match_type)
        {
            printf("One or more fuzzy matches for the TOC.  Have the user choose.\n");
        }

        /*Show the user the returned partial results by iterating over the albums
        in the GDO and allow them to select the best match (if there is one).*/
        ...

        if (choice_ordinal > 0)
        {
            /*Resolve the match(es) to one single full  match. Note that
            the match ordinal is a 1-based ordinal, not a 0-based index.*/
            error = gnsdk_musicid_query_resolve(
                    query_handle,
                    response_gdo,             /*The previously retrieved partial result(s)*/
                    choice_ordinal,           /*Resolve takes a 1-based ordinal (not a 0-based index)*/
                    &resolved_response_gdo    /*A GDO to hold the single full result*/
                        );

            /*Resolved match for the given TOC*/
            printf("User selected match for TOC\r\n");

            /*Display the album's metadata*/
            ...
        }
    }

    /*Clean up*/

    /*Release the query handle*/
    error = gnsdk_musicid_query_release(query_handle);

    /*Release the results*/
    error = gnsdk_manager_gdo_release(response_gdo);
    error = gnsdk_manager_gdo_release(resolved_response_gdo);

    /*Shutdown GNSDK*/
    ...

    return 0;
}
