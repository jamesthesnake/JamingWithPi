/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gcsl_datatypes.h
 *
 * APIs for complex datatypes for data management
 *
 */
#ifndef _GCSL_DATATYPES_H_
#define _GCSL_DATATYPES_H_

#ifdef __cplusplus
extern "C"{
#endif

/*
 * gcsl_datatypes are:
 *
 *		gcsl_hashtable		- hash table implementation
 *		gcsl_stringmap		- string map implementation (uses gcsl_hashtable)
 *		gcsl_stringtable	- string compaction and expansion
 *		gcsl_vector			- vector (resizeable array) of pointers implementation
 *		gcsl_vector2		- vector (resizeable array) of structs implementation
 *		gcsl_queue			- fifo queue implementation
 *		gcsl_stack			- stack implementation
 *		gcsl_bloomfilter	- bloom filter implementation
 *		gcsl_huffman		- huffman encoding implementation
 *		gcsl_outbuffer		- streaming buffer size normalization
 *
 */

/*
 * Initialization
 */

gcsl_error_t    gcsl_datatypes_initialize		(void);
gcsl_error_t    gcsl_datatypes_shutdown			(void);

gcsl_cstr_t		gcsl_datatypes_get_version		(void);
gcsl_cstr_t		gcsl_datatypes_get_build_date	(void);

/******************************************************************************
* gcsl_hashtable
* configurably sized hash table for storing key/value pairs
******************************************************************************/

/*
** hash table opaque handle
*/

GCSL_DECLARE_HANDLE( gcsl_hashtable_handle_t );


/*
** hash table value delete callback
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_hashtable_deletevalue_fn)(gcsl_void_t* value, gcsl_size_t valueSize);

/*
** hash table creation flags
*/
#define	GCSL_HASHTABLE_DEFAULT          	(0x0)
#define	GCSL_HASHTABLE_THREADSAFE			(0x1)
#define	GCSL_HASHTABLE_CASESENSITIVE    	(0x10)
#define	GCSL_HASHTABLE_ERRORDUPLICATES		(0x20)
#define	GCSL_HASHTABLE_ALLOWDUPLICATES		(0x40)
#define GCSL_HASHTABLE_NODEADZONE			(0x80)
#define GCSL_HASHTABLE_CONSTANTKEYS			(0x100) /* does not copy key values */

/*
** hash table creation functions
*/

gcsl_error_t  gcsl_hashtable_create			(gcsl_hashtable_handle_t* phHashTable, gcsl_uint32_t flags, gcsl_hashtable_deletevalue_fn delete_callback);
gcsl_error_t  gcsl_hashtable_delete			(gcsl_hashtable_handle_t hHashTable);

/*
** hash table accessor functions
*/

gcsl_error_t  gcsl_hashtable_value_add		(gcsl_hashtable_handle_t hHashTable, gcsl_cstr_t sz_key, const gcsl_void_t* value, gcsl_size_t valueSize, gcsl_bool_t bCopy);

gcsl_error_t  gcsl_hashtable_value_get		(gcsl_hashtable_handle_t hHashTable, gcsl_uint32_t index, gcsl_cstr_t* psz_key, gcsl_void_t** p_value, gcsl_size_t* p_valuesize);

#define       gcsl_hashtable_value_find(hHashTable, sz_key, p_value, p_valuesize) \
							gcsl_hashtable_value_find_ex(hHashTable, sz_key, 0, p_value, p_valuesize)
gcsl_error_t  gcsl_hashtable_value_find_ex	(gcsl_hashtable_handle_t hHashTable, gcsl_cstr_t sz_key, gcsl_uint32_t index, gcsl_void_t** p_value, gcsl_size_t* p_valuesize);

#define       gcsl_hashtable_value_update(hHashTable, sz_key, value, valueSize, bCopy) \
							gcsl_hashtable_value_update_ex(hHashTable, sz_key, 0, value, valueSize, bCopy)
gcsl_error_t  gcsl_hashtable_value_update_ex(gcsl_hashtable_handle_t hHashTable, gcsl_cstr_t sz_key, gcsl_uint32_t index, const gcsl_void_t* value, gcsl_size_t valueSize, gcsl_bool_t bCopy);

#define       gcsl_hashtable_value_remove(hHashTable, sz_key, p_value, p_valuesize) \
							gcsl_hashtable_value_remove_ex(hHashTable, sz_key, 0, p_value, p_valuesize)
gcsl_error_t  gcsl_hashtable_value_remove_ex(gcsl_hashtable_handle_t hHashTable, gcsl_cstr_t sz_key, gcsl_uint32_t index, gcsl_void_t** p_value, gcsl_size_t* p_valuesize);

gcsl_error_t  gcsl_hashtable_value_delete	(gcsl_hashtable_handle_t hHashTable, gcsl_cstr_t sz_key);


gcsl_error_t  gcsl_hashtable_count			(gcsl_hashtable_handle_t hHashTable, gcsl_uint32_t* pCount);
gcsl_error_t  gcsl_hashtable_value_count	(gcsl_hashtable_handle_t hHashTable, gcsl_cstr_t sz_key, gcsl_uint32_t* pCount);

gcsl_error_t  gcsl_hashtable_copy			(gcsl_hashtable_handle_t hHashTable, gcsl_hashtable_handle_t* phHashTable);

gcsl_error_t  gcsl_hashtable_clear			(gcsl_hashtable_handle_t hHashTable);



/******************************************************************************
* gcsl_stringmap
* configurably sized string map for storing key/string value pairs
* based on gcsl_hashtable
******************************************************************************/

/*
** string map creation flags
*/
#define GCSL_STRINGMAP_DEFAULT				(0x0)
#define	GCSL_STRINGMAP_THREADSAFE			(0x1)
#define	GCSL_STRINGMAP_CASESENSITIVE		(0x10)
#define GCSL_STRINGMAP_CONSTANTKEYS			(0x100) /* does not copy key strings */
#define GCSL_STRINGMAP_CONSTANTVALUES		(0x1000) /* does not copy value strings */

/*
** string map opaque handle
*/

GCSL_DECLARE_HANDLE( gcsl_stringmap_handle_t );

/*
** string map creation functions
*/

gcsl_error_t  gcsl_stringmap_create			(gcsl_stringmap_handle_t* ph_map, gcsl_uint32_t flags);
gcsl_error_t  gcsl_stringmap_delete			(gcsl_stringmap_handle_t h_map);

/*
** string map accessor functions
*/

gcsl_error_t  gcsl_stringmap_value_add		(gcsl_stringmap_handle_t h_map, gcsl_cstr_t sz_key, gcsl_cstr_t sz_value);
gcsl_error_t  gcsl_stringmap_value_find		(gcsl_stringmap_handle_t h_map, gcsl_cstr_t sz_key, gcsl_cstr_t* psz_value);
gcsl_error_t  gcsl_stringmap_value_get		(gcsl_stringmap_handle_t h_map, gcsl_uint32_t index, gcsl_cstr_t* psz_key, gcsl_cstr_t* psz_value);
gcsl_error_t  gcsl_stringmap_value_delete	(gcsl_stringmap_handle_t h_map, gcsl_cstr_t sz_key);

gcsl_error_t  gcsl_stringmap_count			(gcsl_stringmap_handle_t h_map, gcsl_uint32_t* p_count);
gcsl_error_t  gcsl_stringmap_clear			(gcsl_stringmap_handle_t h_map);
gcsl_error_t  gcsl_stringmap_copy			(gcsl_stringmap_handle_t h_map, gcsl_stringmap_handle_t* ph_map);



/******************************************************************************
* gcsl_stringtable
* compact and contiguous storage of sets of strings
******************************************************************************/

GCSL_DECLARE_HANDLE( gcsl_stringtable_handle_t );

#define     GCSL_STRINGTABLE_DEFAULT		(0x0)

/*
** string table creation functions
*/
gcsl_error_t  gcsl_stringtable_create		(gcsl_stringtable_handle_t* ph_strtable, gcsl_uint32_t flags);
gcsl_error_t  gcsl_stringtable_clear		(gcsl_stringtable_handle_t h_strtable);
gcsl_error_t  gcsl_stringtable_delete		(gcsl_stringtable_handle_t h_strtable);

/*
** string table accessor functions
*/
gcsl_error_t  gcsl_stringtable_count		(gcsl_stringtable_handle_t h_strtable, gcsl_uint32_t* p_count);
gcsl_error_t  gcsl_stringtable_enum			(gcsl_stringtable_handle_t h_strtable, gcsl_uint32_t index, gcsl_uint32_t* p_value_ref, gcsl_cstr_t* psz_value);

gcsl_error_t  gcsl_stringtable_add_value	(gcsl_stringtable_handle_t h_strtable, gcsl_cstr_t sz_value, gcsl_uint32_t* p_value_ref);
gcsl_error_t  gcsl_stringtable_get_value	(gcsl_stringtable_handle_t h_strtable, gcsl_uint32_t value_ref, gcsl_cstr_t* psz_value);
gcsl_error_t  gcsl_stringtable_get_value_ref(gcsl_stringtable_handle_t h_strtable, gcsl_cstr_t sz_value, gcsl_uint32_t* p_value_ref);
gcsl_error_t  gcsl_stringtable_remove_value	(gcsl_stringtable_handle_t h_strtable, gcsl_uint32_t value_ref);

gcsl_error_t  gcsl_stringtable_get_buffer	(gcsl_stringtable_handle_t h_strtable, const gcsl_void_t** p_buffer, gcsl_size_t* p_buffer_size);
gcsl_error_t  gcsl_stringtable_attach_buffer(gcsl_stringtable_handle_t h_strtable, const gcsl_void_t* buffer, gcsl_size_t buffer_size);



/******************************************************************************
* gcsl_vector
* dynamicly sized pointer array with indexed access and sorting
******************************************************************************/

/*
** vector opaque handle
*/

GCSL_DECLARE_HANDLE( gcsl_vector_handle_t );

/*
** vector value delete callback
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_vector_deletevalue_fn)(gcsl_void_t* value);

/*
** vector value compare callback
*/
typedef gcsl_int32_t (GCSL_CALLBACK_API *gcsl_vector_comparevalues_fn)(const gcsl_void_t* value1, const gcsl_void_t* value2);

/*
** vector value process callback
*/
typedef gcsl_bool_t (GCSL_CALLBACK_API *gcsl_vector_processvalue_fn)(const gcsl_void_t* callback_data, const gcsl_void_t* value);


/*
** vector creation flags
*/
#define     GCSL_VECTOR_DEFAULT			(0x0)	/* unsorted, no thread protection */
#define		GCSL_VECTOR_THREADSAFE		(0x1)	/* create vector safe for multiple thread access */
#define     GCSL_VECTOR_SORTED			(0x10)	/* create vector sorted so all adds will insert in sorted order */

/*
** vector creation functions
*/
gcsl_error_t  gcsl_vector_create		(gcsl_vector_handle_t* ph_vector, gcsl_uint32_t flags, gcsl_vector_comparevalues_fn compare_callback, gcsl_vector_deletevalue_fn delete_callback);
gcsl_error_t  gcsl_vector_delete		(gcsl_vector_handle_t h_vector);

gcsl_error_t  gcsl_vector_set_min_size	(gcsl_vector_handle_t h_vector, gcsl_uint32_t min_value_count);

/*
** vector accessor functions
*/

/* add value to vector either in sorted position if vector is sorted, or to end
** otherwise */
gcsl_error_t  gcsl_vector_add			(gcsl_vector_handle_t h_vector, const gcsl_void_t* value);
/* insert value into vector at given index. the sorted status of the vector
** will be removed if this insert is not in sorted order */
gcsl_error_t  gcsl_vector_insert		(gcsl_vector_handle_t h_vector, gcsl_uint32_t index, const gcsl_void_t* value);

/* find first index of value that matches according to compare function */
gcsl_error_t  gcsl_vector_find			(gcsl_vector_handle_t h_vector, const gcsl_void_t* value, gcsl_uint32_t* p_index);
/* find first index of value that matches the value iteself */
gcsl_error_t  gcsl_vector_find_literal	(gcsl_vector_handle_t h_vector, const gcsl_void_t* value, gcsl_uint32_t* p_index);

/* get value at index */
gcsl_error_t  gcsl_vector_getindex		(gcsl_vector_handle_t h_vector, gcsl_uint32_t index, gcsl_void_t** p_value);

/* get count of values in vector */
gcsl_error_t  gcsl_vector_count			(gcsl_vector_handle_t h_vector, gcsl_uint32_t* p_count);

/* remove and return value at index. delete callback will only be called for
** value if p_value parameter is not given (is NULL) */
gcsl_error_t  gcsl_vector_removeindex	(gcsl_vector_handle_t h_vector, gcsl_uint32_t index, gcsl_void_t** p_value);
/* remove value at index. delete callback will only be called for value if
** exists */
gcsl_error_t  gcsl_vector_deleteindex	(gcsl_vector_handle_t h_vector, gcsl_uint32_t index);
/* clear all values from vector. delete callback will be called for all values
** if exists */
gcsl_error_t  gcsl_vector_clear			(gcsl_vector_handle_t h_vector);

/* sort vector according to given compare function. if vector is already
** sorted by the given compare function this will not cause a resort. if you
** must force a resort, set the force parameter to true. Force should be rarely
** used if ever */
gcsl_error_t  gcsl_vector_sort			(gcsl_vector_handle_t h_vector, gcsl_vector_comparevalues_fn compare_callback, gcsl_bool_t bForce);

gcsl_error_t  gcsl_vector_foreach		(gcsl_vector_handle_t h_vector, gcsl_vector_processvalue_fn process_callback, const gcsl_void_t* callback_data);


/******************************************************************************
* gcsl_vector2
* dynamicly sized array with indexed access and sorting
******************************************************************************/

/*
** vector2 opaque handle
*/

GCSL_DECLARE_HANDLE( gcsl_vector2_handle_t );

/*
** vector value delete callback
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_vector2_deletevalue_fn)(const gcsl_void_t* value);

/*
** vector2 value compare callback
*/
typedef gcsl_int32_t (GCSL_CALLBACK_API *gcsl_vector2_comparevalues_fn)(const gcsl_void_t* value1, const gcsl_void_t* value2);

/*
** vector2 value process callback
*/
typedef gcsl_bool_t (GCSL_CALLBACK_API *gcsl_vector2_processvalue_fn)(const gcsl_void_t* callback_data, const gcsl_void_t* value);

/*
** vector2 creation flags
*/
#define     GCSL_VECTOR2_DEFAULT		(0x0)	/* unsorted, no thread protection */
#define		GCSL_VECTOR2_THREADSAFE		(0x1)	/* create vector safe for multiple thread access */
#define     GCSL_VECTOR2_SORTED			(0x10)	/* create vector sorted so all adds will insert in sorted order */
#define     GCSL_VECTOR2_UNIQUE			(0x20)	/* vector only keeps unique entries */

/*
** vector creation functions
*/
gcsl_error_t  gcsl_vector2_create		(gcsl_vector2_handle_t* ph_vector, gcsl_size_t value_size, gcsl_uint32_t flags, gcsl_vector2_comparevalues_fn compare_callback, gcsl_vector2_deletevalue_fn delete_callback);
gcsl_error_t  gcsl_vector2_delete		(gcsl_vector2_handle_t h_vector);

gcsl_error_t  gcsl_vector2_set_min_size	(gcsl_vector2_handle_t h_vector, gcsl_uint32_t min_value_count);
gcsl_error_t  gcsl_vector2_attach		(gcsl_vector2_handle_t h_vector, gcsl_void_t* value_array, gcsl_size_t array_size, gcsl_size_t value_size, gcsl_bool_t b_own);
gcsl_error_t  gcsl_vector2_detach		(gcsl_vector2_handle_t h_vector, gcsl_void_t** p_value_array, gcsl_size_t* p_array_size, gcsl_size_t* p_value_size);

gcsl_error_t  gcsl_vector2_get_buffer	(gcsl_vector2_handle_t h_vector, const gcsl_void_t** p_buffer, gcsl_size_t* p_buffer_size, gcsl_size_t* p_value_size);

/*
** vector accessor functions
*/
gcsl_error_t  gcsl_vector2_add			(gcsl_vector2_handle_t h_vector, const gcsl_void_t* value, gcsl_size_t value_size, gcsl_uint32_t* p_dest_index);
gcsl_error_t  gcsl_vector2_insert		(gcsl_vector2_handle_t h_vector, gcsl_uint32_t index, const gcsl_void_t* value, gcsl_size_t value_size);
gcsl_error_t  gcsl_vector2_find			(gcsl_vector2_handle_t h_vector, const gcsl_void_t* value, gcsl_uint32_t* p_index);
gcsl_error_t  gcsl_vector2_count		(gcsl_vector2_handle_t h_vector, gcsl_uint32_t* p_count);
gcsl_error_t  gcsl_vector2_getindex		(gcsl_vector2_handle_t h_vector, gcsl_uint32_t index, gcsl_void_t** p_value);
gcsl_error_t  gcsl_vector2_deleteindex	(gcsl_vector2_handle_t h_vector, gcsl_uint32_t index);
gcsl_error_t  gcsl_vector2_deleterange	(gcsl_vector2_handle_t h_vector, gcsl_uint32_t start_index, gcsl_uint32_t end_index);
gcsl_error_t  gcsl_vector2_trim			(gcsl_vector2_handle_t h_vector);
gcsl_error_t  gcsl_vector2_clear		(gcsl_vector2_handle_t h_vector);
gcsl_error_t  gcsl_vector2_sort			(gcsl_vector2_handle_t h_vector, gcsl_vector2_comparevalues_fn compare_callback, gcsl_bool_t b_force);
gcsl_error_t  gcsl_vector2_foreach		(gcsl_vector2_handle_t h_vector, gcsl_vector2_processvalue_fn process_callback, const gcsl_void_t* callback_data);


/******************************************************************************
* gcsl_queue
* first-in first-out list
******************************************************************************/

/*
** queue opaque handle
*/

GCSL_DECLARE_HANDLE( gcsl_queue_handle_t );

/*
** queue value delete callback
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_queue_deletevalue_fn)(gcsl_void_t* value);

/*
** queue creation flags
*/
#define     GCSL_QUEUE_DEFAULT		(0x0)	/* no thread protection */
#define		GCSL_QUEUE_THREADSAFE	(0x1)	/* create queue safe for multiple thread access */

/*
** queue creation functions
*/
gcsl_error_t  gcsl_queue_create		(gcsl_queue_handle_t* ph_queue, gcsl_uint32_t flags, gcsl_queue_deletevalue_fn delete_callback);
gcsl_error_t  gcsl_queue_delete		(gcsl_queue_handle_t h_queue);

/* return size of queue */
gcsl_error_t  gcsl_queue_count		(gcsl_queue_handle_t h_queue, gcsl_uint32_t* p_count);
/* access next queue item */
gcsl_error_t  gcsl_queue_front		(gcsl_queue_handle_t h_queue, gcsl_void_t** p_value);
/* access last queue item */
gcsl_error_t  gcsl_queue_back		(gcsl_queue_handle_t h_queue, gcsl_void_t** p_value);
/* insert queue item */
gcsl_error_t  gcsl_queue_push		(gcsl_queue_handle_t h_queue, const gcsl_void_t* value);
/* delete next queue item */
gcsl_error_t  gcsl_queue_pop		(gcsl_queue_handle_t h_queue, gcsl_void_t** p_value);


/******************************************************************************
* gcsl_stack
* implemented via linked-list
******************************************************************************/

/*
** stack opaque handle
*/

GCSL_DECLARE_HANDLE( gcsl_stack_handle_t );

/*
** stack value delete callback
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_stack_deletevalue_fn)(gcsl_void_t* value);

/*
** stack creation flags
*/
#define     GCSL_STACK_DEFAULT		(0x0)	/* no thread protection */
#define		GCSL_STACK_THREADSAFE	(0x1)	/* create stack safe for multiple thread access */

/*
** stack creation functions
*/
gcsl_error_t  gcsl_stack_create		(gcsl_stack_handle_t* ph_stack, gcsl_uint32_t flags, gcsl_stack_deletevalue_fn delete_callback);
gcsl_error_t  gcsl_stack_delete		(gcsl_stack_handle_t h_stack);

gcsl_error_t  gcsl_stack_top		(gcsl_stack_handle_t h_stack, gcsl_void_t** p_value);
gcsl_error_t  gcsl_stack_push		(gcsl_stack_handle_t h_stack, const gcsl_void_t* value);
gcsl_error_t  gcsl_stack_pop		(gcsl_stack_handle_t h_stack, gcsl_void_t** p_value);

gcsl_error_t  gcsl_stack_count		(gcsl_stack_handle_t h_stack, gcsl_uint32_t* p_count);


/******************************************************************************
* gcsl_bloomfilter
* bloom filter implementation (set inclusion/exclusion testing)
******************************************************************************/

GCSL_DECLARE_HANDLE( gcsl_bloomfilter_handle_t );

typedef gcsl_size_t (GCSL_CALLBACK_API *gcsl_bloomfilter_hash_fn)(gcsl_void_t* value);
	

gcsl_error_t	gcsl_bloomfilter_create				(gcsl_bloomfilter_handle_t* ph_bloom, gcsl_size_t size, gcsl_bloomfilter_hash_fn* hash_functions, gcsl_uint32_t hash_fn_count, gcsl_uint32_t flags);
gcsl_error_t	gcsl_bloomfilter_delete				(gcsl_bloomfilter_handle_t h_bloom);

gcsl_error_t	gcsl_bloomfilter_add				(gcsl_bloomfilter_handle_t h_bloom, gcsl_void_t* value);
gcsl_error_t	gcsl_bloomfilter_test				(gcsl_bloomfilter_handle_t h_bloom, gcsl_void_t* value, gcsl_bool_t* b_in);

gcsl_error_t	gcsl_bloomfilter_print				(gcsl_bloomfilter_handle_t h_bloom, gcsl_char_t* buffer, gcsl_size_t buffer_size);
gcsl_error_t	gcsl_bloomfilter_false_probability	(gcsl_bloomfilter_handle_t h_bloom, gcsl_flt32_t* p_probability);



/******************************************************************************
* gcsl_huffman
* huffman tree creation, data encoding and decoding
******************************************************************************/

GCSL_DECLARE_HANDLE( gcsl_huffman_handle_t );


typedef gcsl_uint32_t	(GCSL_CALLBACK_API *gcsl_huffman_value_freq_fn)(gcsl_uint32_t index, gcsl_void_t* values);

gcsl_error_t	gcsl_huffman_create			(gcsl_huffman_handle_t* ph_huff);
gcsl_error_t	gcsl_huffman_delete			(gcsl_huffman_handle_t h_huff);

gcsl_error_t	gcsl_huffman_calc_codes		(gcsl_huffman_handle_t h_huff, gcsl_void_t* values, gcsl_uint32_t value_count, gcsl_huffman_value_freq_fn freq_fn);
gcsl_error_t	gcsl_huffman_max_code_size	(gcsl_huffman_handle_t h_huff, gcsl_size_t* p_code_bytes, gcsl_size_t* p_code_bits);
gcsl_error_t	gcsl_huffman_code_for_index	(gcsl_huffman_handle_t h_huff, gcsl_uint32_t value_index, gcsl_byte_t* p_code, gcsl_size_t* p_code_bytes, gcsl_size_t* p_code_bits);
gcsl_error_t	gcsl_huffman_index_from_code(gcsl_huffman_handle_t h_huff, gcsl_byte_t* p_code, gcsl_size_t* p_code_byte, gcsl_size_t* p_code_bit, gcsl_uint32_t* p_value_index);

gcsl_error_t	gcsl_huffman_code_to_string (gcsl_byte_t* p_code, gcsl_size_t code_bits, gcsl_char_t* buf, gcsl_size_t buf_size);



/******************************************************************************
* gcsl_outbuffer
* dole out consistent sized buffers of data from inconsistently size input data
******************************************************************************/

GCSL_DECLARE_HANDLE( gcsl_outbuffer_handle_t );

/*
** outbuffer creation flags
*/
#define     GCSL_OUTBUFFER_DEFAULT		(0x0)	/* no thread protection */
#define		GCSL_OUTBUFFER_THREADSAFE	(0x1)	/* create for multiple thread access */


typedef gcsl_void_t	(GCSL_CALLBACK_API *gcsl_outbuffer_output_fn)(const gcsl_void_t* data, gcsl_size_t data_size, const gcsl_void_t* callback_data);


gcsl_error_t	gcsl_outbuffer_create		(gcsl_outbuffer_handle_t* ph_outbuffer, gcsl_uint32_t flags, gcsl_size_t min_output_size, gcsl_size_t max_output_size, gcsl_size_t modulo_output_size);
gcsl_error_t	gcsl_outbuffer_delete		(gcsl_outbuffer_handle_t h_outbuffer);

gcsl_error_t	gcsl_outbuffer_size_set		(gcsl_outbuffer_handle_t h_outbuffer, gcsl_size_t min_output_size, gcsl_size_t max_output_size, gcsl_size_t modulo_output_size, gcsl_outbuffer_output_fn output_fn, const gcsl_void_t* callback_data);
gcsl_error_t	gcsl_outbuffer_size_get		(gcsl_outbuffer_handle_t h_outbuffer, gcsl_size_t* p_min_output_size, gcsl_size_t* p_max_output_size, gcsl_size_t* p_modulo_output_size);

gcsl_error_t	gcsl_outbuffer_write		(gcsl_outbuffer_handle_t h_outbuffer, const gcsl_void_t* data_in, gcsl_size_t byte_size, gcsl_outbuffer_output_fn output_fn, const gcsl_void_t* callback_data);
gcsl_error_t	gcsl_outbuffer_flush		(gcsl_outbuffer_handle_t h_outbuffer, gcsl_outbuffer_output_fn output_fn, const gcsl_void_t* callback_data);


#ifdef __cplusplus
}
#endif

#endif /* _GCSL_DATATYPES_H_ */

