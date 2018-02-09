/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_xml.h - XML tree, parsing, and rendering library
 */

#ifndef _GCSL_XML_H_
#define _GCSL_XML_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gcsl_xml_element_t* gcsl_xml_element_ref_t;

gcsl_error_t			gcsl_xml_initialize		(void);
gcsl_error_t			gcsl_xml_shutdown		(void);

gcsl_cstr_t				gcsl_xml_get_version	(void);
gcsl_cstr_t				gcsl_xml_get_build_date	(void);


gcsl_xml_element_ref_t	gcsl_xml_create_element					(gcsl_cstr_t element_name);
gcsl_xml_element_ref_t	gcsl_xml_create_element_from_str		(gcsl_cstr_t element_name, gcsl_cstr_t element_data);
gcsl_xml_element_ref_t	gcsl_xml_create_element_from_buf		(gcsl_cstr_t element_name, gcsl_byte_t* element_data, gcsl_size_t element_data_len);
gcsl_xml_element_ref_t	gcsl_xml_create_element_from_buf_cdata	(gcsl_cstr_t element_name, gcsl_byte_t* element_data, gcsl_size_t element_data_len);
gcsl_xml_element_ref_t	gcsl_xml_clone_element					(const gcsl_xml_element_ref_t xml_element, gcsl_bool_t deep);

gcsl_void_t				gcsl_xml_dispose_element				(gcsl_xml_element_ref_t xml_element);
gcsl_void_t				gcsl_xml_smart_dispose_element			(gcsl_xml_element_ref_t* xml_element);

/* XML Element _name */
gcsl_cstr_t				gcsl_xml_get_name						(const gcsl_xml_element_ref_t xml_element);

/* XML Element Data */
gcsl_cstr_t				gcsl_xml_get_data						(const gcsl_xml_element_ref_t xml_element);
gcsl_cstr_t				gcsl_xml_get_data_trimmed				(const gcsl_xml_element_ref_t xml_element);

gcsl_error_t			gcsl_xml_set_data_from_buf				(gcsl_xml_element_ref_t	xml_element, gcsl_cstr_t element_data, gcsl_size_t element_data_len);
gcsl_error_t			gcsl_xml_set_cdata_from_buf				(gcsl_xml_element_ref_t	xml_element, const gcsl_byte_t* element_data, gcsl_size_t element_data_len);

typedef gcsl_void_t		(GCSL_CALLBACK_API *gcsl_xml_assume_data_delete_fn)(gcsl_void_t* data);
gcsl_error_t			gcsl_xml_assume_data					(gcsl_xml_element_ref_t xml_element, gcsl_str_t element_data, gcsl_xml_assume_data_delete_fn delete_fn);

/* XML Element Attributes */
gcsl_size_t				gcsl_xml_get_attr_count					(const gcsl_xml_element_ref_t xml_element);
gcsl_error_t			gcsl_xml_get_attr						(const gcsl_xml_element_ref_t xml_element, gcsl_cstr_t* attr_name, gcsl_cstr_t* attr_value, gcsl_size_t index);
gcsl_cstr_t				gcsl_xml_get_attr_from_str				(const gcsl_xml_element_ref_t xml_element, gcsl_cstr_t attr_name);
gcsl_error_t			gcsl_xml_set_attr_from_str				(gcsl_xml_element_ref_t xml_element, gcsl_cstr_t attr_name, gcsl_cstr_t attr_value);
gcsl_error_t			gcsl_xml_set_attr_from_str_checked		(gcsl_xml_element_ref_t xml, gcsl_error_t last_error, gcsl_cstr_t attr_name, gcsl_cstr_t attr_value);
gcsl_error_t			gcsl_xml_set_attr_from_int				(gcsl_xml_element_ref_t xml_element, gcsl_cstr_t attr_name, gcsl_int32_t attr_value);
gcsl_error_t			gcsl_xml_set_attr_from_int_checked		(gcsl_xml_element_ref_t xml_element, gcsl_error_t last_error, gcsl_cstr_t attr_name, gcsl_int32_t attr_value);
gcsl_error_t			gcsl_xml_set_attr_from_uint				(gcsl_xml_element_ref_t xml_element, gcsl_cstr_t attr_name, gcsl_uint32_t attr_value);
gcsl_error_t			gcsl_xml_set_attr_from_uint_checked		(gcsl_xml_element_ref_t xml_element, gcsl_error_t last_error, gcsl_cstr_t attr_name, gcsl_uint32_t attr_value);

/* XML Subelements */
gcsl_size_t				gcsl_xml_get_sub_element_count			(const gcsl_xml_element_ref_t xml_element);
gcsl_size_t				gcsl_xml_get_named_sub_element_count	(const gcsl_xml_element_ref_t xml_element,gcsl_cstr_t	element_name);

gcsl_xml_element_ref_t	gcsl_xml_get_sub_element				(const gcsl_xml_element_ref_t xml_element, gcsl_size_t index);
gcsl_cstr_t				gcsl_xml_get_sub_element_name			(const gcsl_xml_element_ref_t xml_element, gcsl_size_t index);
gcsl_xml_element_ref_t	gcsl_xml_get_sub_element_from_str		(const gcsl_xml_element_ref_t xml_element, gcsl_cstr_t sub_element_name);
gcsl_xml_element_ref_t	gcsl_xml_get_sub_element_from_buf		(const gcsl_xml_element_ref_t xml_element, gcsl_cstr_t sub_element_name, gcsl_size_t sub_element_name_len);
gcsl_error_t			gcsl_xml_add_sub_element				(gcsl_xml_element_ref_t xml_element, gcsl_xml_element_ref_t sub_element);
gcsl_void_t				gcsl_xml_remove_sub_element				(gcsl_xml_element_ref_t xml_element, gcsl_xml_element_ref_t sub_element, gcsl_bool_t dispose_sub_element);
gcsl_error_t			gcsl_xml_add_sub_element_from_str		(gcsl_xml_element_ref_t element, gcsl_cstr_t name, gcsl_cstr_t value, gcsl_xml_element_ref_t* sub_element);
gcsl_error_t			gcsl_xml_add_sub_element_from_str_checked(gcsl_xml_element_ref_t element, gcsl_error_t last_error, gcsl_cstr_t name, gcsl_cstr_t value, gcsl_xml_element_ref_t* sub_element);
gcsl_error_t			gcsl_xml_add_sub_element_from_uint		(gcsl_xml_element_ref_t xml_element, gcsl_cstr_t name, gcsl_size_t value, gcsl_xml_element_ref_t* sub_element);

/* Parse Helper */
#define		gcsl_xml_action_entering_element	1 /* p1 points to the '<', p2 points to the name */
#define		gcsl_xml_action_parsed_attribute	2 /* p1 points to the attr name, p2 points to the attr data */
#define		gcsl_xml_action_parsed_data			3 /* p1 points to the data, p2 is unused */
#define		gcsl_xml_action_leaving_element		4 /* p1 points to the name, p2 points to the '>' */

typedef gcsl_uint16_t	 gcsl_xml_parse_action;

typedef gcsl_error_t	(GCSL_CALLBACK_API *gcsl_xml_parse_helper_fn)
						(gcsl_xml_parse_action action, const gcsl_void_t* user_data, gcsl_cstr_t p1, gcsl_size_t len1, gcsl_cstr_t p2, gcsl_size_t len2);

/* Parsing */
gcsl_error_t			gcsl_xml_parse_str_to_element			(gcsl_cstr_t sz_xml, gcsl_xml_element_ref_t* xml_element);
gcsl_error_t			gcsl_xml_parse_str_to_helper			(gcsl_cstr_t sz_xml, gcsl_xml_parse_helper_fn helper, const gcsl_void_t* user_data);

gcsl_error_t			gcsl_xml_parse_buf_to_element			(const gcsl_byte_t* buf, gcsl_size_t buf_len, gcsl_xml_element_ref_t* xml_element);
gcsl_error_t			gcsl_xml_parse_buf_to_helper			(const gcsl_byte_t* buf, gcsl_size_t buf_len, gcsl_xml_parse_helper_fn helper, const gcsl_void_t* user_data);

gcsl_error_t			gcsl_xml_parse_stream_to_helper			(gcsl_iostream_handle_t in_stream, gcsl_xml_parse_helper_fn helper, const gcsl_void_t* user_data);

gcsl_error_t			gcsl_xml_unescape_str					(gcsl_cstr_t escaped_str, gcsl_size_t str_len, gcsl_str_t* unescaped_str, gcsl_size_t* p_str_len);

/* Rendering */
gcsl_char_t*			gcsl_xml_render_to_str					(const gcsl_xml_element_ref_t xml_element, gcsl_bool_t header);
gcsl_char_t*			gcsl_xml_render_to_str_ex				(const gcsl_xml_element_ref_t xml_element, gcsl_bool_t header, gcsl_bool_t indent, gcsl_bool_t newlines);
gcsl_error_t			gcsl_xml_render_to_buffer				(const gcsl_xml_element_ref_t xml_element, gcsl_bool_t header, gcsl_bool_t indent, gcsl_bool_t newlines, gcsl_byte_t** p_buf, gcsl_size_t* p_buf_size);

/* Path-Based Access */
gcsl_cstr_t				gcsl_xml_get_sub_element_data			(const gcsl_xml_element_ref_t xml_element, gcsl_cstr_t path);
gcsl_error_t			gcsl_xml_set_value_at_path				(gcsl_xml_element_ref_t xml_element, gcsl_cstr_t path, gcsl_cstr_t value);


#ifdef __cplusplus
}
#endif

#endif /* _GCSL_XML_H_ */
