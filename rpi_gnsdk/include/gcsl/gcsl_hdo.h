/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

#ifndef _GCSL_HDO_H_
#define _GCSL_HDO_H_

#ifdef	__cplusplus
extern "C" {
#endif


/* gcsl_hdo opaque handle
*/
GCSL_DECLARE_HANDLE( gcsl_hdo_handle_t );

/* gcsl_hdo_value opaque handle
*/
GCSL_DECLARE_HANDLE( gcsl_hdo_value_handle_t );


/* The data structure can maintain these enumerated data format types
*/
#ifndef GCSL_HDOVALUETYPE_T
#define GCSL_HDOVALUETYPE_T

typedef enum
{
	gcsl_hdo_valuetype_unknown	= 0,
	gcsl_hdo_valuetype_string	= 1,
	gcsl_hdo_valuetype_number	= 2,
	gcsl_hdo_valuetype_binary	= 3,
	gcsl_hdo_valuetype_pointer	= 4

} gcsl_hdo_valuetype_t;

#endif /* GCSL_HDOVALUETYPE_T */

/*
 * Defines
 */

/*
 * HDO node and value flags
 */
#define GCSL_HDO_FLAG_DEFAULT			0x00
#define GCSL_HDO_FLAG_PRIVATE			0x10
#define GCSL_HDO_FLAG_UNIQUE			0x20
#define GCSL_HDO_FLAG_READ_ONLY			0x40
#define GCSL_HDO_FLAG_NEW_VALUES_ONLY	0x80

/*
 * Initialization
 */

gcsl_error_t	gcsl_hdo_initialize		(void);
gcsl_error_t	gcsl_hdo_shutdown		(void);

gcsl_cstr_t		gcsl_hdo_get_version	(void);
gcsl_cstr_t		gcsl_hdo_get_build_date	(void);

/*
** HDO pointer value delete callback
** (for gcsl_hdo_new_value_pointer and gcsl_hdo_value_setdata_pointer)
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_hdo_deletepointer_fn)(gcsl_void_t* ptr, gcsl_size_t ptrDataSize);


/* The hierarchical data object, or any children, are created and destroyed with these APIs:
*/
gcsl_error_t	gcsl_hdo_create					(gcsl_hdo_handle_t* phHDO);
gcsl_error_t	gcsl_hdo_copy					(gcsl_hdo_handle_t hHDO, gcsl_hdo_handle_t* phHDO, gcsl_bool_t bCopyChildren);
gcsl_error_t	gcsl_hdo_clear					(gcsl_hdo_handle_t hHDO);
gcsl_error_t	gcsl_hdo_addref					(gcsl_hdo_handle_t hHDO);
gcsl_error_t	gcsl_hdo_release				(gcsl_hdo_handle_t hHDO);
gcsl_error_t	gcsl_hdo_set_flags				(gcsl_hdo_handle_t hHDO, gcsl_uint32_t mask, gcsl_uint32_t flags);

/* The following APIs provide hdo attribute manipulation:
*/
gcsl_error_t	gcsl_hdo_attribute_set			(gcsl_hdo_handle_t hHDO, gcsl_cstr_t attrName, gcsl_cstr_t attrValue);
gcsl_error_t	gcsl_hdo_attribute_get			(gcsl_hdo_handle_t hHDO, gcsl_cstr_t attrName, gcsl_cstr_t* pAttrValue);
gcsl_error_t	gcsl_hdo_attribute_delete		(gcsl_hdo_handle_t hHDO, gcsl_cstr_t attrName);
gcsl_error_t	gcsl_hdo_attribute_count		(gcsl_hdo_handle_t hHDO, gcsl_uint32_t *p_count);
gcsl_error_t	gcsl_hdo_attribute_enum			(gcsl_hdo_handle_t hHDO, gcsl_uint32_t index, gcsl_cstr_t* pAttrName, gcsl_cstr_t* pAttrValue);
gcsl_error_t	gcsl_hdo_attribute_clearall		(gcsl_hdo_handle_t hHDO);

/* The following APIs provide parent/child manipulation and discovery:
*/
gcsl_error_t	gcsl_hdo_child_set				(gcsl_hdo_handle_t hHDOParent, gcsl_cstr_t childName, gcsl_hdo_handle_t hHDOchild, gcsl_uint32_t flags);
gcsl_error_t	gcsl_hdo_child_get				(gcsl_hdo_handle_t hHDOParent, gcsl_cstr_t childName, gcsl_uint32_t index, gcsl_hdo_handle_t *phHDOchild);
gcsl_error_t	gcsl_hdo_child_remove			(gcsl_hdo_handle_t hHDOParent, gcsl_cstr_t childName, gcsl_uint32_t index, gcsl_hdo_handle_t *phHDOchild);
gcsl_error_t	gcsl_hdo_child_count			(gcsl_hdo_handle_t hHDOParent, gcsl_cstr_t childName, gcsl_uint32_t *count); /* set childName to GCSL_NULL to count all children */
gcsl_error_t	gcsl_hdo_child_enum				(gcsl_hdo_handle_t hHDOParent, gcsl_uint32_t index, gcsl_cstr_t* pChildName, gcsl_hdo_handle_t *phHDOchild);
gcsl_error_t	gcsl_hdo_child_detach			(gcsl_hdo_handle_t hHDOChild);
gcsl_error_t	gcsl_hdo_parent_get				(gcsl_hdo_handle_t hHDOChild, gcsl_hdo_handle_t *hHDOParent);

/* The following APIs provide creation of data values:
*/
gcsl_error_t	gcsl_hdo_new_value				(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_uint32_t flags, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_new_value_string		(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_cstr_t value, gcsl_uint32_t flags, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_new_value_int			(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_int32_t value, gcsl_uint32_t flags, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_new_value_uint			(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_uint32_t value, gcsl_uint32_t flags, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_new_value_binary		(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, const gcsl_void_t* value, gcsl_size_t valueSize, gcsl_uint32_t flags, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_new_value_pointer		(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, const gcsl_void_t* ptr, gcsl_size_t ptrDataSize, gcsl_uint32_t flags, gcsl_hdo_deletepointer_fn delete_callback, gcsl_hdo_value_handle_t* phValue);

/* The following APIs provide value access:
*/
gcsl_error_t	gcsl_hdo_value_set				(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_hdo_value_handle_t hValue);
gcsl_error_t	gcsl_hdo_value_get				(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_uint32_t index, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_value_remove			(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_uint32_t index, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_value_count			(gcsl_hdo_handle_t hHDO, gcsl_cstr_t valueName, gcsl_uint32_t *count); /* set valueName to GCSL_NULL to count all values */
gcsl_error_t	gcsl_hdo_value_enum				(gcsl_hdo_handle_t hHDO, gcsl_uint32_t index, gcsl_cstr_t* pValueName, gcsl_hdo_value_handle_t* phValue);

/*gcsl_error_t	gcsl_hdo_value_addref			(gcsl_hdo_value_handle_t hValue); TODO? */
gcsl_error_t	gcsl_hdo_value_release			(gcsl_hdo_value_handle_t hValue);

/* The following APIs provide setting value data:
*/
gcsl_error_t	gcsl_hdo_value_setdata_string	(gcsl_hdo_value_handle_t hValue, gcsl_cstr_t value);
gcsl_error_t	gcsl_hdo_value_setdata_int		(gcsl_hdo_value_handle_t hValue, gcsl_int32_t value);
gcsl_error_t	gcsl_hdo_value_setdata_uint		(gcsl_hdo_value_handle_t hValue, gcsl_uint32_t value);
gcsl_error_t	gcsl_hdo_value_setdata_binary	(gcsl_hdo_value_handle_t hValue, const gcsl_void_t* value, gcsl_size_t valueSize);
gcsl_error_t	gcsl_hdo_value_setdata_pointer	(gcsl_hdo_value_handle_t hValue, const gcsl_void_t* ptr, gcsl_size_t ptrDataSize, gcsl_hdo_deletepointer_fn delete_callback);

/* The following APIs provide getting value data:
*/
gcsl_error_t	gcsl_hdo_value_getdata_string	(gcsl_hdo_value_handle_t hValue, gcsl_cstr_t* value);
gcsl_error_t	gcsl_hdo_value_getdata_int		(gcsl_hdo_value_handle_t hValue, gcsl_int32_t* pValue);
gcsl_error_t	gcsl_hdo_value_getdata_uint		(gcsl_hdo_value_handle_t hValue, gcsl_uint32_t* pValue);
gcsl_error_t	gcsl_hdo_value_getdata_binary	(gcsl_hdo_value_handle_t hValue, gcsl_void_t** pValue, gcsl_size_t *pValueSize);
gcsl_error_t	gcsl_hdo_value_getdata_pointer	(gcsl_hdo_value_handle_t hValue, gcsl_void_t** pPtr, gcsl_size_t *pPtrDataSize);

/* The following APIs provide value discovery:
*/
gcsl_error_t	gcsl_hdo_value_getname			(gcsl_hdo_value_handle_t hValue, gcsl_cstr_t *pValueName);
gcsl_error_t	gcsl_hdo_value_gettype			(gcsl_hdo_value_handle_t hValue, gcsl_hdo_valuetype_t *pValueType);

/* The following APIs provide value attribute manipulation:
*/
gcsl_error_t	gcsl_hdo_value_attribute_set	(gcsl_hdo_value_handle_t hValue, gcsl_cstr_t attrName, gcsl_cstr_t attrValue);
gcsl_error_t	gcsl_hdo_value_attribute_get	(gcsl_hdo_value_handle_t hValue, gcsl_cstr_t attrName, gcsl_cstr_t* pAttrValue);
gcsl_error_t	gcsl_hdo_value_attribute_delete	(gcsl_hdo_value_handle_t hValue, gcsl_cstr_t attrName);
gcsl_error_t	gcsl_hdo_value_attribute_count	(gcsl_hdo_value_handle_t hValue, gcsl_uint32_t *p_count);
gcsl_error_t	gcsl_hdo_value_attribute_enum	(gcsl_hdo_value_handle_t hValue, gcsl_uint32_t index, gcsl_cstr_t* pAttrName, gcsl_cstr_t* pAttrValue);


/* The following APIs provide xml coversion of HDOs:
*/
gcsl_error_t	gcsl_hdo_to_xml					(gcsl_hdo_handle_t hHDO, gcsl_cstr_t xmlRootElem, gcsl_bool_t bHeader, gcsl_bool_t bNewLines, gcsl_str_t* pszXML);
gcsl_error_t	gcsl_hdo_to_xml_buf				(gcsl_hdo_handle_t hHDO, gcsl_cstr_t xmlRootElem, gcsl_bool_t bHeader, gcsl_bool_t bNewLines, gcsl_byte_t** pXMLBuf, gcsl_size_t* pXMLBufSize);
gcsl_error_t	gcsl_hdo_from_xml				(gcsl_cstr_t szXML, gcsl_hdo_handle_t* phHDO, gcsl_str_t* p_xmlRootElem);
gcsl_error_t	gcsl_hdo_from_xml_stream		(gcsl_iostream_handle_t xml_stream, gcsl_hdo_handle_t* phHDO, gcsl_str_t* p_xmlRootElem);
gcsl_error_t	gcsl_hdo_free_xml				(gcsl_str_t szXML);
gcsl_error_t	gcsl_hdo_free_xml_buf			(gcsl_byte_t* XMLBuf);

/* The following APIs provide gpath navigation of HDOs:
*/
gcsl_error_t	gcsl_hdo_get_count_by_gpath		(gcsl_hdo_handle_t hHDO, gcsl_cstr_t szPath, gcsl_hdo_handle_t hHDOvars, gcsl_uint32_t *pCount);
gcsl_error_t	gcsl_hdo_get_string_by_gpath	(gcsl_hdo_handle_t hHDO, gcsl_cstr_t szPath, gcsl_hdo_handle_t hHDOvars, gcsl_uint32_t index, gcsl_cstr_t* pszValue);
gcsl_error_t	gcsl_hdo_get_value_by_gpath		(gcsl_hdo_handle_t hHDO, gcsl_cstr_t szPath, gcsl_hdo_handle_t hHDOvars, gcsl_uint32_t index, gcsl_hdo_value_handle_t* phValue);
gcsl_error_t	gcsl_hdo_get_child_by_gpath		(gcsl_hdo_handle_t hHDO, gcsl_cstr_t szPath, gcsl_hdo_handle_t hHDOvars, gcsl_uint32_t index, gcsl_hdo_handle_t* phHDOchild);



#ifdef	__cplusplus
}
#endif

#endif /* _GCSL_HDO_H_ */
