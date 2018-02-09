/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/

/*
 *	Name:	List-Based Filters 
 *	Description:
 *	This example demonstrates Video Explore's list-based filtering functionality. 
 *	The example shows how to restrict the returned results of a query by by including a list element in the query. 
 *	In Video Explore, use the GNSDK_VIDEO_FILTER_KEY_*_INCLUDE and *_EXCLUDE macros to filter results using 
 *	list-based values. You can filter results by setting only one condition, or multiple conditions. 
 *	For example, setting genre filters that include action but exclude drama returns all products marked as action, 
 *	except any product categorized as belonging to both the action and drama genres. 
 *	Note that the exclusion functionality supersedes the inclusion functionality. This means that when corresponding 
 *	_INCLUDE and _EXCLUDE filter keys are set to the same value, the exclusion cancels out the inclusion, 
 *	essentially creating a null value. In this situation, no results are returned. 
 *	Steps:
 *	01. Retrieve and display list elements of a list.
 *	02. Prompt for user selection of a list element.
 *	03. Set the selected list element as a filter condition.
 *	04. Set query options.
 *	05. Check for No Match errors.
 *	06. Handle the results.
 *	07. Perform handle cleanup. 																			
 *	Command-line Syntax:
 *	sample.exe client_id client_id_tag license																	
*/


#include "gnsdk.h"
...

int
main(int argc, char* argv[])
{

gnsdk_video_query_handle_t    query_handle = GNSDK_NULL;
gnsdk_list_element_handle_t     genre_list =   GNSDK_NULL;
gnsdk_gdo_handle_t              result_gdo =   GNSDK_NULL;
gnsdk_gdo_handle_t              work_gdo =     GNSDK_NULL;
gnsdk_error_t                   error =        GNSDK_SUCCESS;
gnsdk_uint32_t                  count=0;
gnsdk_uint32_t                  i=0;
gnsdk_uint32_t                  sel=0;
gnsdk_list_element_handle_t     list_element = GNSDK_NULL;
gnsdk_char_t* string=0;

 /*Initialize GNSDK*/

/*...*/

 /*This example assumes the list handle variable genre_list contains a valid handle to the genre list*/

/*Create a new query handle*/

error = gnsdk_video_query_create(
user_handle,
GNSDK_NULL,    /*No callback*/
GNSDK_NULL,    /*No callback data*/
&query_handle
);

 /*Set query text*/
error = gnsdk_video_query_set_text(
query_handle,
GNSDK_VIDEO_SEARCH_FIELD_WORK_TITLE,   /*search work titles*/
"Star Wars",
gnsdk_video_search_type_default       /*NOT using an anchored search*/
);


/*
* Display available genres to filter against
*/


printf("Available Genres:\n");

 /*count of elements in genre_list at level 1*/
error = gnsdk_manager_list_get_element_count(genre_list,
1,           /*genre level one*/
&count);

if ((!error) && (count >0) )
{
for(i=0;i<count;i++)
{

/*Get list element at level one, number i*/
error = gnsdk_manager_list_get_element(genre_list, 1, i, &list_element);

if(!error)
{
/*Get display string of genre list element*/
gnsdk_manager_list_element_get_display_string(list_element,&string);
printf("\t%2d: %s\n", i, string);
}
}

/*Ask user for genre choice*/
while( ( 1 != scanf("%d", &sel)) || (sel >= count)  );/*Wait until user enters a valid value*/

}


/*
* Set the chosen genre filter
*/

error = gnsdk_manager_list_get_element(genre_list, 1, sel, &list_element);/*Get the selected list element, at level one*/

 /*Apply this list element to the GENRE INCLUDE filter*/
error = gnsdk_video_query_set_filter_by_list_element(query_handle, GNSDK_VIDEO_FILTER_KEY_GENRE_INCLUDE, list_element);



/*
* Set Query Options
*/


 /*Enable LINK data for this query*/
error = gnsdk_video_query_option_set(
query_handle,
GNSDK_VIDEO_OPTION_ENABLE_LINK_DATA,
GNSDK_VALUE_TRUE
);

 /*Find works*/
error = gnsdk_video_query_find_works(
query_handle,
&result_gdo
);


 /*Check error*/

if (match_type == gnsdk_video_match_type_none)
{
 /*No match*/
printf("No results\n");
}
else
{
 /*Handle the results here.
* Note that in the case of a single match, you will have a single work GDO
* as a child of the result. In the case of multiple matches, you will have
* multiple partial work GDOs within the results. A partial GDO contains
* less data than a full GDO.
*/


/*Count number of results*/
error =   gnsdk_manager_gdo_child_count( result_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, &count);

if (count >0)
{
for(i=1;i<=count;i++)
{
/*Get Ith work*/
error =   gnsdk_manager_gdo_child_get( result_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, i, &work_gdo);

if (work_gdo != GNSDK_NULL)
{

printf("Result %d:\n", i);


/*Get and display title*/
error = gnsdk_manager_gdo_value_get(work_gdo, GNSDK_GDO_VALUE_TITLE_DISPLAY, 1, &string);
if ( (error ==GNSDK_SUCCESS) &&( string !=GNSDK_NULL))
{
printf("\tTitle: %s\n", string);
}

/*Get and display release date*/
error = gnsdk_manager_gdo_value_get(work_gdo, GNSDK_GDO_VALUE_DATE_ORIGINAL_RELEASE, 1, &string);
if ( (error ==GNSDK_SUCCESS) &&( string !=GNSDK_NULL))
{
printf("\tOriginal Release Date: %s\n", string);
}


/*Release this work*/
gnsdk_manager_gdo_release(work_gdo);
work_gdo = GNSDK_NULL;
}
}
}
}


/*Clean up any handles*/
if (result_gdo != GNSDK_NULL)
{
error = gnsdk_manager_gdo_release(result_gdo);
}

if (query_handle != GNSDK_NULL)
{
error = gnsdk_video_query_release(query_handle);
}

 /*Shutdown GNSDK*/
...

return 0;

}
