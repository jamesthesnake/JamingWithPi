/* Gracenote SDK: Submit GDOs
  * Author:
  *   Copyright (c) 2012 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_SUBMIT_GDO_H_
/** @internal gnsdk_submit_gdo.h @endinternal
 * Primary interface for editable GDOs.
* @ingroup Submit_HeaderFile
*/
#define _GNSDK_SUBMIT_GDO_H_

#ifdef __cplusplus
extern "C"{
#endif

/** @internal gnsdk_submit_edit_gdo_create_album_from_toc @endinternal
*  Creates an editable Album GDO to submit data for a specific GDO context. The album comes
pre-populated with the correct number of track children, but no metadata.
*  @param toc [in] CD TOC string
*  @param p_edit_gdo [out] Pointer to receive an editable GDO handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given context parameter is empty, or given p_edit_gdo parameter is
null
*  @return SUBMITERR_NoError Editable GDO was successfully created
*  <p><b>Remarks:</b></p>
*  Use this function to create an editable album GDO with the correct number of track children, as
derived from the
*  TOC.
*  The children are empty, and do not have metadata. You must enter all the children's metadata.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_create_album_from_toc(
	gnsdk_cstr_t				toc,
	gnsdk_gdo_handle_t*			p_edit_gdo
	);

/** @internal gnsdk_submit_edit_gdo_create_empty @endinternal
*  Creates an editable GDO to submit data for a specific GDO context.
*  @param context [in] GDO context from which the editable GDO is created
*  @param p_edit_gdo [out] Pointer to receive an editable GDO handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given context parameter is empty, or given p_edit_gdo parameter is
null
*  @return SUBMITERR_NoError Editable GDO was successfully created
*  <p><b>Remarks:</b></p>
*  Use this function to create an editable GDO from a GDO context
*  (GNSDK_GDO_TYPE_ALBUM).
*  This editable GDO is considered an empty GDO, as it has no child or value GDOs. Use the
gnsdk_submit_edit_gdo_child_add_* and gnsdk_submit_edit_gdo_value_add functions to add this data.
* <p><b>Note:</b></p>
*  After the function has completed processing, the child's GDO handle must be released using
gnsdk_manager_gdo_release.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_create_empty(
	gnsdk_cstr_t				context,
	gnsdk_gdo_handle_t*			p_edit_gdo
	);

/** @internal gnsdk_submit_edit_gdo_create_from_gdo @endinternal
*  Creates an editable GDO with data derived from a source GDO.
*  @param source_gdo [in] Source GDO for data used to create a new editable GDO
*  @param p_edit_gdo [out] Pointer to receive an editable GDO handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given p_edit_gdo parameter is null
*  @return SUBMITERR_NoError New editable GDO was successfully created
*  <p><b>Remarks:</b></p>
*  Use this function to create an editable GDO from a source GDO (GNSDK_GDO_TYPE_ALBUM). The
editable GDO is essentially a close copy (but not a clone) of the source GDO, containing the
metadata that is editable.
*  Add child and value GDOs using the gnsdk_submit_edit_gdo_child_add_* and
gnsdk_submit_edit_gdo_value_add functions.
* <p><b>Note:</b></p>
*  After the function has completed processing, the child's GDO handle must be released using
gnsdk_manager_gdo_release.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_create_from_gdo(
	gnsdk_gdo_handle_t			source_gdo,
	gnsdk_gdo_handle_t*			p_edit_gdo
	);

/** @internal gnsdk_submit_edit_gdo_create_from_xml @endinternal
*  Creates an editable GDO with data parsed from pre-populated, GDO-formatted XML.
*  @param xml [in] Source XML for data used to create a new editable GDO
*  @param p_edit_gdo [out] Pointer to receive an editable GDO handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given src_xml parameter is empty, or given p_edit_gdo parameter is
null
*  @return SUBMITERR_NoError New editable GDO was successfully created
*  <p><b>Remarks:</b></p>
*  Use this function to create an editable GDO from a specified source of pre-populated and GDO
-formatted XML data (GNSDK_GDO_TYPE_ALBUM). The editable GDO is essentially a close copy (but not
a clone) of the source XML, containing only editable metadata.
*  Add child and value GDOs using the gnsdk_submit_edit_gdo_child_add_* and
gnsdk_submit_edit_gdo_value_add functions.
* <p><b>Note:</b></p>
*  After the function has completed processing, the child's GDO handle must be released using
gnsdk_manager_gdo_release.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_create_from_xml(
	gnsdk_cstr_t				xml,
	gnsdk_gdo_handle_t*			p_edit_gdo
	);

/** @internal gnsdk_submit_edit_gdo_value_set @endinternal
*  Changes a GDO value for a supported key of an editable GDO. If the value does not exist, it will
be added. If the value does exist, it will be changed. If NULL or an empty string is passed in, the
value will be deleted.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param key [in] An available GDO Value Key
*  @param ordinal [in] Updates the n'th instance of the key (1-based)
*  @param value [in] Value corresponding to the specified GDO value key
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given value or value_key parameter is empty, or given ordinal
parameter is zero (0)
*  @return SUBMITERR_NotEditable Given edit_gdo_handle parameter is a handle to a non-editable GDO,
instead of an editable GDO
*  @return SUBMITWARN_NotEditable Given child_key parameter is read-only; the key is supported for
the parent GDO context, but cannot be changed in an editable GDO
*  @return SUBMITERR_NoError GDO value was successfully set
*  <p><b>Remarks:</b></p>
*  Use this function to edit an existing value of an editable GDO. Note that the value must already
exist on the editable GDO.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_value_set(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_cstr_t				key,
	gnsdk_uint32_t				ordinal,
	gnsdk_cstr_t				value
	);

/** @internal gnsdk_submit_edit_gdo_value_has_changed @endinternal
*  Returns a boolean value indicating whether the specified GDO value has changed. Changes include
adding, deleting, and changing data.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param key [in] An available GDO Value Key
*  @param ordinal [in] Updates the n'th instance of the key (1-based)
*  @param p_has_changed [out] GNSDK_TRUE if changed, GNSDK_FALSE otherwise
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given ordinal parameter is zero (0), given p_has_changed parameter
is null, or returned key parameter value contains an empty string
*  @return SUBMITERR_NoError Boolean value was successfully retrieved
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_value_has_changed(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_cstr_t				key,
	gnsdk_uint32_t				ordinal,
	gnsdk_bool_t*				p_has_changed
	);

/** @internal gnsdk_submit_edit_gdo_child_add_empty @endinternal
*  Adds an empty child GDO to a editable parent GDO.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param child_key [in] An available GDO child key that corresponds with the parent editable GDO
handle's context; for example, a Track or Credit child key for a parent Album context GDO
*  @param p_edit_gdo [out] Pointer to receive an editable child GDO
*  handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given child_key parameter is empty, or given p_edit_gdo parameter is
null
*  @return SUBMITERR_Unsupported Given child_key parameter is not supported for the parent GDO
context
*  @return SUBMITERR_NotEditable Given edit_gdo_handle parameter is a handle to a non-editable GDO,
instead of an editable GDO
*  @return SUBMITWARN_NotEditable Given child_key parameter is read-only; the key is supported for
the parent GDO context, but cannot be changed in an editable GDO
*  @return SUBMITERR_NoError Editable GDO child was successfully added
*  <p><b>Remarks:</b></p>
*  Use this function to add an empty child GDO to an editable parent GDO. The child must correspond
to the parent, meaning, if the parent is of an Album context, you can add only Track or Credit child
keys. Children are appended to the parent in the order added.
* <p><b>Note:</b></p>
*  After the function has completed processing, the child's GDO handle must be released using
gnsdk_manager_gdo_release.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_child_add_empty(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_cstr_t				child_key,
	gnsdk_gdo_handle_t*			p_edit_gdo
	);

/** @internal gnsdk_submit_edit_gdo_child_add_from_gdo @endinternal
*  Adds a derived editable child GDO to an editable parent GDO.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param child_key [in] An available GDO child key that corresponds with the parent editable GDO
handle's context; for example, a Track or Credit child key for a parent Album context GDO
*  @param child_gdo_handle [in] Handle to a derived editable child GDO Handle to a derived editable
child GDO
*  @param p_edit_gdo [out] Pointer to receive an editable child GDO handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given child_key parameter is empty, or given p_edit_gdo parameter is
null
*  @return SUBMITERR_Unsupported Given child_gdo_handle parameter is not supported for the parent
GDO context
*  @return SUBMITERR_NotEditable Given edit_gdo_handle parameter is a handle to a non-editable GDO,
instead of an editable GDO
*  @return SUBMITWARN_NotEditable Given child_key parameter is read-only; the key is supported for
the parent GDO context, but cannot be changed in an editable GDO
*  @return SUBMITERR_NoError Copied GDO child was successfully added
*  <p><b>Remarks:</b></p>
*  Use this function to add a derived editable child GDO to an editable parent GDO.
*  The input child GDO can be an editable or non-editable GDO; however, the output child GDO will be
an editable GDO that is a close copy (not a clone) of the input child GDO.
* <p><b>Note:</b></p>
*  After the function has completed processing, the child's GDO handle must be released using
gnsdk_manager_gdo_release.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_child_add_from_gdo(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_cstr_t				child_key,
	gnsdk_gdo_handle_t			child_gdo_handle,
	gnsdk_gdo_handle_t*			p_edit_gdo
	);
/** @internal gnsdk_submit_edit_gdo_child_add_from_xml @endinternal
*  Adds a child GDO derived from source XML to an editable parent GDO.
*  @param edit_gdo_handle [in] Handle to an editable GDO derived from XML source data
*  @param child_key [in] An available GDO child key that corresponds with the parent editable GDO
handle's context; for example, a Track or Credit child key for a parent Album context GDO
*  @param child_xml [in] Handle to a GDO child derived from source XML
*  @param p_edit_gdo [out] Pointer to receive an editable child GDO handle
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given child_key parameter is empty, or given p_edit_gdo parameter is
null
*  @return SUBMITERR_Unsupported Given child_xml parameter is not supported for the parent GDO
context
*  @return SUBMITERR_NotEditable Given edit_gdo_handle parameter is a handle to a non-editable GDO,
instead of an editable GDO
*  @return SUBMITWARN_NotEditable Given child_key parameter is read-only; the key is supported for
the parent GDO context, but cannot be changed in an editable GDO
*  @return SUBMITERR_NoError Derived GDO child was successfully added
*  <p><b>Remarks:</b></p>
*  Use this function to add an editable child GDO derived from source XML to an editable parent GDO.
* <p><b>Note:</b></p>
*  After the function has completed processing, the child's GDO handle must be released using
gnsdk_manager_gdo_release.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_child_add_from_xml(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_cstr_t				child_key,
	gnsdk_cstr_t				child_xml,
	gnsdk_gdo_handle_t*			p_edit_gdo
	);
/** @internal gnsdk_submit_edit_gdo_child_remove @endinternal
*  Removes an editable child GDO from a parent GDO.
*  @param edit_gdo_handle [in] Handle to the parent editable GDO
*  @param edit_gdo_child_handle [in] Handle to the child GDO
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given child_key parameter is empty, or given ordinal parameter is
zero (0)
*  @return SUBMITERR_NotEditable Given edit_gdo_handle parameter is a handle to a non-editable GDO,
instead of an editable GDO
*  @return SUBMITWARN_NotEditable Given child_key parameter is read-only; the key is supported for
the parent GDO context, but cannot be changed in an editable GDO
*  @return SUBMITERR_NoError Child GDO was successfully removed
*  <p><b>Remarks:</b></p>
*  Use this function to remove an editable child GDO of an editable parent GDO.
*  <p><b>Important:</b></p>
*  This deletion is final. Once removed, the child GDO cannot be reconstituted. If an editable child
is accidentally removed, it must be completely recreated using the appropriate
gnsdk_submit_edit_gdo_child_add_* function.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_child_remove(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_gdo_handle_t			edit_gdo_child_handle
	);

/** @internal gnsdk_submit_edit_gdo_list_value_set_by_submit_id @endinternal
*  Sets a list-based value by the list item Submit ID for an editable GDO. If the value does not
exist, it is added. If the value does exist, it is changed. If the list_item_submit_id is 0, the
value is deleted.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param list_type [in] An available GNSDK Manager list type
*  @param ordinal [in] Set the n'th item of the list type (1-based)
*  @param list_item_submit_id [in] Submit ID for a list item of the specified list type
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given list_type parameter is empty, or given list_item_submit_id or
ordinal parameter is zero (0)
*  @return SUBMITERR_NotEditable Given edit_gdo_handle parameter is a handle to a non-editable GDO,
instead of an editable GDO
*  @return SUBMITWARN_NotEditable Given child_key parameter is read-only; the key is supported for
the parent GDO context, but cannot be changed in an editable GDO
*  @return SUBMITERR_NoError Submit ID list value was successfully set
*  <p><b>Remarks:</b></p>
*  Use this function to set a list-based Submit ID to an editable GDO, prior to adding the GDO to a
parcel.
*  You must first retrieve the list-based Submit ID using
gnsdk_manager_list_element_get_id_for_submit.
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_list_value_set_by_submit_id(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_cstr_t				list_type,
	gnsdk_uint32_t				ordinal,
	gnsdk_uint32_t				list_item_submit_id
	);

/** @internal gnsdk_submit_edit_gdo_list_value_get_submit_id @endinternal
*  Gets the list item Submit ID of a list-based value from an editable GDO.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param list_type [in] An available GNSDK Manager list type
*  @param ordinal [in] Set the n'th item of the list type (1-based)
*  @param p_list_item_submit_id Submit ID for a list item of the specified list type
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given list_type parameter is empty, or given p_list_item_submit_id
parameter is null
*  @return SUBMITERR_NoError Submit ID list value was successfully retrieved
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_list_value_get_submit_id(
	gnsdk_gdo_handle_t			edit_gdo_handle,
	gnsdk_cstr_t				list_type,
	gnsdk_uint32_t				ordinal,
	gnsdk_uint32_t*				p_list_item_submit_id
	);


/** @internal gnsdk_submit_gdo_validate_callback_fn @endinternal
*  Receive Submit validation status updates.
*  @param user_data [in] Pointer to data passed in to gnsdk_submit_edit_gdo_validate_set_callback
through the callback_userdata parameter. This pointer must be cast from the gnsdk_void_t type to its
original type to be accessed properly.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param p_error_info [out] Pointer to a gnsdk_extended_error_info_t structure
*  @param invalid_key [in] Key that has a validation error
*  @param invalid_ord [in] Ordinal for the invalid key
*  @param p_abort [out] Pointer to receive boolean value indicating if the callback must be aborted
*
* @ingroup Submit_MetadataEditableGDOs_Callbacks
*/
typedef gnsdk_void_t
(GNSDK_CALLBACK_API *gnsdk_submit_gdo_validate_callback_fn)(
	const gnsdk_void_t*			user_data,
	gnsdk_gdo_handle_t			edit_gdo_handle,
	const gnsdk_error_info_t*	p_error_info,
	gnsdk_cstr_t				invalid_key,
	gnsdk_uint32_t				invalid_ord,
	gnsdk_bool_t*				p_abort
	);

/** @internal gnsdk_submit_edit_gdo_validate_set_callback @endinternal
*  Retrieves a boolean value indicating if validation status is applied to the GDO's children.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param callback_fn [in_opt] Callback function for status and progress
*  @param callback_userdata [in_opt] Data that is passed back through calls to the callback
functions
*  @param use_for_children [out] Returns boolean value; if true, indicates the callback is applied
to all the GDO's children
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given callback_fn parameter is null
*  @return SUBMITERR_Busy System is busy
*  @return SUBMITERR_NoError Boolean value was successfully retrieved
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_validate_set_callback(
	gnsdk_gdo_handle_t						edit_gdo_handle,
	gnsdk_submit_gdo_validate_callback_fn	callback_fn,
	gnsdk_void_t*							callback_userdata,
	gnsdk_bool_t							use_for_children /* if true, this callback will be used for all child gdos */
	);

/** @internal gnsdk_submit_edit_gdo_validate @endinternal
*  Returns a boolean value indicating whether an edited GDO is valid.
*  @param edit_gdo_handle [in] Handle to an editable GDO
*  @param p_has_errors [out] GNSDK_TRUE if GDO has errors, GNSDK_FALSE otherwise.
*  @return SUBMITERR_NotInited gnsdk_submit_initialize was not successfully initiated
*  @return SUBMITERR_InvalidArg Given p_has_errors parameter is null
*  @return SUBMITERR_Busy System is busy
*  @return SUBMITERR_NoError Boolean value was successfully retrieved
* @ingroup Submit_MetadataEditableGDOs_Functions
*/
gnsdk_error_t GNSDK_API
gnsdk_submit_edit_gdo_validate(
	gnsdk_gdo_handle_t						edit_gdo_handle,
	gnsdk_bool_t*							p_has_errors
	);


/** @internal GNSDK_GDO_VALUE_TOC_ALBUM @endinternal
*  Sets an album TOC value from a GDO.
*  <p><b>Remarks:</b></p>
*  This value is declared in header file gnsdk_submit_gdo.h.
* @ingroup GDO_ValueKeys_Music
*/
#define GNSDK_GDO_VALUE_TOC_ALBUM				"gnsdk_val_toc_album"

#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_SUBMIT_GDO_H_ */

