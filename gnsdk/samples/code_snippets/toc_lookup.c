/*
 * This function performs a TOC lookup
 */
static void
_query_album_lookup(
	gnsdk_user_handle_t	 user_handle
	)
{
	gnsdk_error_t						error					= GNSDK_SUCCESS;
	gnsdk_musicid_query_handle_t		query_handle			= GNSDK_NULL;
	gnsdk_gdo_handle_t					response_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t					album_gdo				= GNSDK_NULL;
	gnsdk_gdo_handle_t					followup_response_gdo	= GNSDK_NULL;
	gnsdk_uint32_t						count					= 0;
	gnsdk_uint32_t						choice_ordinal			= 0;
	gnsdk_cstr_t						needs_decision			= GNSDK_NULL;
	gnsdk_cstr_t						is_full					= GNSDK_NULL;

	printf("\n*****MusicID TOC Query*****\n");

	/* Create the query handle */
	error = gnsdk_musicid_query_create(
				user_handle,
				GNSDK_NULL,	 /* User callback function */
				GNSDK_NULL,	 /* Optional data to be passed to the callback */
				&query_handle
				);
	if (GNSDK_SUCCESS != error)
	{
		_display_error( __LINE__, "gnsdk_musicid_query_create() failed", error );
	}

	/* Set the input TOC as a string. */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_musicid_query_set_toc_string(
					query_handle,
					"150 14112 25007 41402 54705 69572 87335 98945 112902 131902 144055 157985 176900 189260 203342"
					);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicid_query_set_toc_string()", error);
		}
	}

	/* Perform the query */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_musicid_query_find_albums(
					query_handle,
					&response_gdo
					);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_musicid_query_find_albums()", error);
		}
	}

	/* See how many albums were found. */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_manager_gdo_child_count( 
						response_gdo, 
						GNSDK_GDO_CHILD_ALBUM, 
						&count 
						);
		if (GNSDK_SUCCESS != error)
		{
			_display_error(__LINE__, "gnsdk_manager_gdo_child_count(GNSDK_GDO_CHILD_ALBUM)", error);
		}
	}

	/* See if we need any follow-up queries or disambiguation */
	if (GNSDK_SUCCESS == error)
	{
		if (count == 0)
		{
			printf("\nNo albums found for the input.\n");
		}
		else
		{
			/* we have at least one album, see if disambiguation (match resolution) is necessary. */
			error = gnsdk_manager_gdo_value_get( 
						response_gdo, 
						GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION, 
						1, 
						&needs_decision
						);
			if (GNSDK_SUCCESS != error)
			{
				_display_error(__LINE__, "gnsdk_manager_gdo_value_get(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION)", error);
			}
			else
			{
				/* See if selection of one of the albums needs to happen */
				if (0 == strcmp(needs_decision, GNSDK_VALUE_TRUE))
				{
					choice_ordinal = _do_match_selection(response_gdo);
				}
				else
				{
					/* no need for disambiguation, we'll take the first album */
					choice_ordinal = 1;
				}

				error = gnsdk_manager_gdo_child_get( 
							response_gdo, 
							GNSDK_GDO_CHILD_ALBUM, 
							choice_ordinal, 
							&album_gdo 
							);
				if (GNSDK_SUCCESS != error)
				{
					_display_error(__LINE__, "gnsdk_manager_gdo_child_get(GNSDK_GDO_CHILD_ALBUM)", error);
				}
				else
				{
					/* See if the album has full data or only partial data. */
					error = gnsdk_manager_gdo_value_get( 
								album_gdo, 
								GNSDK_GDO_VALUE_FULL_RESULT, 
								1, 
								&is_full
								);
					if (GNSDK_SUCCESS != error)
					{
						_display_error(__LINE__, "gnsdk_manager_gdo_value_get(GNSDK_GDO_VALUE_FULL_RESULT)", error);
					}
					else
					{
						/* if we only have a partial result, we do a follow-up query to retrieve the full album */
						if (0 == strcmp(is_full, GNSDK_VALUE_FALSE))
						{
							/* do followup query to get full object. Setting the partial album as the query input. */
							error = gnsdk_musicid_query_set_gdo(
										query_handle,
										album_gdo
										);
							if (GNSDK_SUCCESS != error)
							{
								_display_error(__LINE__, "gnsdk_musicid_query_set_gdo()", error);
							}
							else
							{
								/* we can now release the partial album */
								gnsdk_manager_gdo_release(album_gdo);
								album_gdo = GNSDK_NULL;

								error = gnsdk_musicid_query_find_albums(
											query_handle,
											&followup_response_gdo
											);
								if (GNSDK_SUCCESS != error)
								{
									_display_error(__LINE__, "gnsdk_musicid_query_find_albums()", error);
								}
								else
								{
									/* now our first album is the desired result with full data */
									error = gnsdk_manager_gdo_child_get( 
												followup_response_gdo, 
												GNSDK_GDO_CHILD_ALBUM, 
												1, 
												&album_gdo 
												);
									
									/* Release the followup query's response object */
									gnsdk_manager_gdo_release(followup_response_gdo);
								}
							}
						}
					}
					
					/* We should now have our final, full album result. */
					if (GNSDK_SUCCESS == error)
					{
						printf( "%16s\n", "Final album:");

						_display_album_gdo(album_gdo);
					}

					gnsdk_manager_gdo_release(album_gdo);
					album_gdo = GNSDK_NULL;
				 }
			}
		}
	}

	/* Clean up */
	/* Release the query handle */
	if (GNSDK_NULL != query_handle)
	{
		gnsdk_musicid_query_release(query_handle);
	}
	/* Release the results */
	if (GNSDK_NULL != response_gdo)
	{
		gnsdk_manager_gdo_release(response_gdo);
	}
}