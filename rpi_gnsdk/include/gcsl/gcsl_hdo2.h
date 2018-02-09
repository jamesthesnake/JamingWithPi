/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_hdo2.h - Hierarchical Data Object interface
 */

#ifndef _GCSL_HDO2_H_
#define _GCSL_HDO2_H_

#ifdef	__cplusplus
extern "C" {
#endif


/* gcsl_hdo2 opaque handle
*/
GCSL_DECLARE_HANDLE( gcsl_hdo2_handle_t );


/* The data structure can maintain these enumerated data format types
*/
typedef enum
{
	gcsl_hdo2_valuetype_unknown	= 0,

	gcsl_hdo2_valuetype_string	= 1,
	gcsl_hdo2_valuetype_number	= 2,
	gcsl_hdo2_valuetype_binary	= 3,
	gcsl_hdo2_valuetype_pointer	= 4

} gcsl_hdo2_valuetype_t;

/*
 * HDO node and value flags
 */
#define GCSL_HDO2_FLAG_DEFAULT			0x00
#define GCSL_HDO2_FLAG_PRIVATE			0x10
#define GCSL_HDO2_FLAG_UNIQUE			0x20
#define GCSL_HDO2_FLAG_READ_ONLY		0x40

/*
 * Initialization
 */

gcsl_error_t	gcsl_hdo2_initialize		(void);
gcsl_error_t	gcsl_hdo2_shutdown			(void);

gcsl_cstr_t		gcsl_hdo2_get_version		(void);
gcsl_cstr_t		gcsl_hdo2_get_build_date	(void);

/*
** HDO pointer value delete callback
** (for gcsl_hdo2_new_value_pointer and gcsl_hdo2_value_setdata_pointer)
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_hdo2_deletepointer_fn)(gcsl_void_t* ptr, gcsl_size_t ptr_data_size);


/* The hierarchical data object, or any children, are created and destroyed with these APIs:
*/
gcsl_error_t	gcsl_hdo2_create				(gcsl_cstr_t name, gcsl_hdo2_handle_t* ph_hdo);
gcsl_error_t	gcsl_hdo2_addref				(gcsl_hdo2_handle_t h_hdo);
gcsl_error_t	gcsl_hdo2_release				(gcsl_hdo2_handle_t h_hdo);

/* The following APIs provide parent/child manipulation and discovery:
*/
gcsl_error_t	gcsl_hdo2_child_set				(gcsl_hdo2_handle_t h_hdo_parent, gcsl_hdo2_handle_t h_hdo_child);
gcsl_error_t	gcsl_hdo2_child_get				(gcsl_hdo2_handle_t h_hdo_parent, gcsl_cstr_t child_name, gcsl_uint32_t index, gcsl_hdo2_handle_t *ph_hdo_child);
gcsl_error_t	gcsl_hdo2_child_remove			(gcsl_hdo2_handle_t h_hdo_parent, gcsl_cstr_t child_name, gcsl_uint32_t index, gcsl_hdo2_handle_t *ph_hdo_child);
gcsl_error_t	gcsl_hdo2_child_count			(gcsl_hdo2_handle_t h_hdo_parent, gcsl_cstr_t child_name, gcsl_uint32_t* p_count); /* set child_name to GCSL_NULL to count all children */
gcsl_error_t	gcsl_hdo2_child_enum			(gcsl_hdo2_handle_t h_hdo_parent, gcsl_uint32_t index, gcsl_cstr_t* p_child_name, gcsl_hdo2_handle_t *ph_hdo_child);

gcsl_error_t	gcsl_hdo2_parent_get			(gcsl_hdo2_handle_t h_hdo_child, gcsl_hdo2_handle_t *h_hdo_parent);

/* The following APIs provide value access:
*/
gcsl_error_t	gcsl_hdo2_value_set_string		(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t value);
gcsl_error_t	gcsl_hdo2_value_set_int			(gcsl_hdo2_handle_t h_hdo, gcsl_int32_t value);
gcsl_error_t	gcsl_hdo2_value_set_uint		(gcsl_hdo2_handle_t h_hdo, gcsl_uint32_t value);
gcsl_error_t	gcsl_hdo2_value_set_binary		(gcsl_hdo2_handle_t h_hdo, const gcsl_void_t* value, gcsl_size_t value_size);
gcsl_error_t	gcsl_hdo2_value_set_pointer		(gcsl_hdo2_handle_t h_hdo, const gcsl_void_t* ptr, gcsl_size_t ptr_data_size, gcsl_hdo2_deletepointer_fn delete_callback);

gcsl_error_t	gcsl_hdo2_value_get_string		(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t* p_value);
gcsl_error_t	gcsl_hdo2_value_get_int			(gcsl_hdo2_handle_t h_hdo, gcsl_int32_t* p_value);
gcsl_error_t	gcsl_hdo2_value_get_uint		(gcsl_hdo2_handle_t h_hdo, gcsl_uint32_t* p_value);
gcsl_error_t	gcsl_hdo2_value_get_binary		(gcsl_hdo2_handle_t h_hdo, gcsl_void_t** p_value, gcsl_size_t* p_value_size);
gcsl_error_t	gcsl_hdo2_value_get_pointer		(gcsl_hdo2_handle_t h_hdo, gcsl_void_t** p_ptr, gcsl_size_t* p_ptr_data_size);

gcsl_error_t	gcsl_hdo2_value_type			(gcsl_hdo2_handle_t h_hdo, gcsl_hdo2_valuetype_t* p_valuetype);
gcsl_error_t	gcsl_hdo2_value_delete			(gcsl_hdo2_handle_t h_hdo);

/* The following APIs provide hdo attribute manipulation:
*/
gcsl_error_t	gcsl_hdo2_attribute_set			(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t attr_name, gcsl_cstr_t attr_value);
gcsl_error_t	gcsl_hdo2_attribute_get			(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t attr_name, gcsl_cstr_t* p_attr_value);
gcsl_error_t	gcsl_hdo2_attribute_delete		(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t attr_name);
gcsl_error_t	gcsl_hdo2_attribute_count		(gcsl_hdo2_handle_t h_hdo, gcsl_uint32_t *p_count);
gcsl_error_t	gcsl_hdo2_attribute_enum		(gcsl_hdo2_handle_t h_hdo, gcsl_uint32_t index, gcsl_cstr_t* p_attr_name, gcsl_cstr_t* p_attr_value);
gcsl_error_t	gcsl_hdo2_attribute_clearall	(gcsl_hdo2_handle_t h_hdo);

/* The following APIs provide xml coversion of HDOs:
*/
gcsl_error_t	gcsl_hdo2_from_xml				(const gcsl_byte_t* xml_buf, gcsl_size_t buf_size, gcsl_hdo2_handle_t* ph_hdo);
gcsl_error_t	gcsl_hdo2_from_xml_stream		(gcsl_iostream_handle_t xml_stream, gcsl_hdo2_handle_t* ph_hdo);
gcsl_error_t	gcsl_hdo2_to_xml				(gcsl_hdo2_handle_t h_hdo, gcsl_byte_t** p_xml_buf, gcsl_size_t* p_buf_size, gcsl_bool_t bHeader, gcsl_bool_t bNewLines);
gcsl_error_t	gcsl_hdo2_free_xml				(gcsl_byte_t* xml_buf);

/* The following APIs provide gpath navigation of HDOs:
*/
gcsl_error_t	gcsl_hdo2_get_count_by_xpath	(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t sz_path, gcsl_stringmap_handle_t h_vars, gcsl_uint32_t* p_count);
gcsl_error_t	gcsl_hdo2_get_string_by_xpath	(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t sz_path, gcsl_stringmap_handle_t h_vars, gcsl_uint32_t index, gcsl_cstr_t* psz_value);
gcsl_error_t	gcsl_hdo2_get_child_by_xpath	(gcsl_hdo2_handle_t h_hdo, gcsl_cstr_t sz_path, gcsl_stringmap_handle_t h_vars, gcsl_uint32_t index, gcsl_hdo2_handle_t* ph_hdo);



#ifdef	__cplusplus
}
#endif

#endif /* _GCSL_HDO2_H_ */
