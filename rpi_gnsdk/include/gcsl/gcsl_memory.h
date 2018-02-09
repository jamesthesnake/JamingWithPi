/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_memory.h - Abstraction header file containing the declaration
 * of memory related functions for cross platform compatibility.
 */

#ifndef _GCSL_MEMORY_H_
#define _GCSL_MEMORY_H_

#ifdef __cplusplus
extern "C"{
#endif


#if (defined GCSL_CREATE_IMPORTS)
	#define CENTRALIZED_MEM_API		GCSL_IMPORTED_API
#elif (defined GCSL_CREATE_EXPORTS)
	#define CENTRALIZED_MEM_API		GCSL_EXPORTED_API
#else
	#define CENTRALIZED_MEM_API
#endif

#ifndef GCSL_MEMORY_TEST
	#ifdef _DEBUG
		#define GCSL_MEMORY_TEST    1
		extern gcsl_size_t			g_gcsl_memory_alloc_failure_call;
	#endif
#endif


/*
 * Prototypes.
 */

/* Initialize the memory manager */
CENTRALIZED_MEM_API gcsl_error_t	gcsl_memory_initialize	(void);

/* Shut down the memory manager when we're done with it */
CENTRALIZED_MEM_API gcsl_error_t	gcsl_memory_shutdown	(void);

gcsl_cstr_t		gcsl_memory_get_version						(void);
gcsl_cstr_t		gcsl_memory_get_build_date					(void);

/*
 * Core memory manager operations (allocate/reallocate/free memory)
 */

/* Free the allocated block */
CENTRALIZED_MEM_API gcsl_error_t		gcsl_memory_free(gcsl_void_t *block);


#if GCSL_MEMORY_TEST


/* Allocate memory from the heap */
CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_alloc(gcsl_size_t size, gcsl_cstr_t file, gcsl_uint32_t line);
#define gcsl_memory_alloc(size)			gcsl_memory_alloc(size, __FILE__, __LINE__)

CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_calloc(gcsl_size_t count, gcsl_size_t size, gcsl_cstr_t file, gcsl_uint32_t line);
#define gcsl_memory_calloc(count, size)	gcsl_memory_calloc(count, size, __FILE__, __LINE__)

/* Reallocate the memory for the block */
CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_realloc(gcsl_void_t *ptr, gcsl_size_t size, gcsl_cstr_t file, gcsl_uint32_t line);
#define gcsl_memory_realloc(ptr, size)	gcsl_memory_realloc(ptr, size, __FILE__, __LINE__)

CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_dup(gcsl_void_t *ptr, gcsl_size_t size, gcsl_cstr_t file, gcsl_uint32_t line);
#define gcsl_memory_dup(ptr, size)		gcsl_memory_dup(ptr, size, __FILE__, __LINE__)


#else /* !GCSL_MEMORY_TEST */


/* Allocate memory from the heap */
CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_alloc(gcsl_size_t size);

CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_calloc(gcsl_size_t count, gcsl_size_t size);

/* Reallocate the memory for the block */
CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_realloc(gcsl_void_t *ptr, gcsl_size_t size);

/* duplicate memory block (alloc and copy) */
CENTRALIZED_MEM_API gcsl_void_t*		gcsl_memory_dup(gcsl_void_t *ptr, gcsl_size_t size);


#endif /* GCSL_MEMORY_TEST */

/* return size of memory buffer pointed to by ptr */
CENTRALIZED_MEM_API gcsl_size_t			gcsl_memory_sizeof(gcsl_void_t *ptr);

/* Retrieve current heap size */
CENTRALIZED_MEM_API gcsl_size_t			gcsl_memory_heap_now	(void);
/* Retrieve maximum heap size */
CENTRALIZED_MEM_API gcsl_size_t			gcsl_memory_heap_max	(gcsl_bool_t b_reset);
/* Dump memory report to stderr */
CENTRALIZED_MEM_API gcsl_void_t			gcsl_memory_heap_dump	(void);
/* Call function to warn of heap size */
CENTRALIZED_MEM_API gcsl_void_t			gcsl_memory_heap_warn	(void (*mem_warn_fn)(gcsl_void_t* p_arg, gcsl_size_t cur_mem_size, gcsl_size_t memory_warn_size), gcsl_void_t* p_arg, gcsl_size_t memory_warn_size);
/* Retrieve current block allocation count */
CENTRALIZED_MEM_API gcsl_size_t         gcsl_memory_alloc_count	(void);
/* Retrieve maximum block allocation count */
CENTRALIZED_MEM_API gcsl_size_t         gcsl_memory_alloc_max	(gcsl_bool_t b_reset);

/* Copy memory from point A to point B, assuming NO overlap */
CENTRALIZED_MEM_API gcsl_void_t			gcsl_memory_memcpy(gcsl_void_t *dest, const gcsl_void_t *src, gcsl_size_t size);

/* Copy memory from point A to point B, allowing for overlap */
CENTRALIZED_MEM_API gcsl_void_t			gcsl_memory_memmove(gcsl_void_t *dest, const gcsl_void_t *src, gcsl_size_t size);

/* Set a range of memory to a specific value */
CENTRALIZED_MEM_API gcsl_void_t			gcsl_memory_memset(gcsl_void_t *dest, gcsl_byte_t val, gcsl_size_t count);

/* Compare two regions of memory */
CENTRALIZED_MEM_API gcsl_int16_t		gcsl_memory_memcmp(const gcsl_void_t *buff1, const gcsl_void_t *buff2, gcsl_size_t count);

/*
** Metrics
*/
typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_memory_marker_status_callback_fn)(
	const gcsl_void_t*	app_data,
	gcsl_size_t			heap_before,
	gcsl_size_t			heap_after,
	gcsl_size_t			heap_max_before,
	gcsl_size_t			heap_max_after,
	gcsl_size_t			alloc_count_before,
	gcsl_size_t			alloc_count_after,
	gcsl_size_t			free_count_before,
	gcsl_size_t			free_count_after,
	gcsl_size_t			alloc_max_before,
	gcsl_size_t			alloc_max_after
	);


CENTRALIZED_MEM_API gcsl_void_t				gcsl_memory_marker_initialize	(gcsl_memory_marker_status_callback_fn callback_fn);
CENTRALIZED_MEM_API gcsl_void_t				gcsl_memory_marker_start		(const gcsl_void_t* app_data, gcsl_void_t** p_marker_data);
CENTRALIZED_MEM_API gcsl_void_t				gcsl_memory_marker_end			(gcsl_void_t* marker_data);


#define GCSL_MEMORY_MARKSTART(app_data)		{ gcsl_void_t* __p_memory_marker; gcsl_memory_marker_start(app_data, &__p_memory_marker);
#define GCSL_MEMORY_MARKEND					gcsl_memory_marker_end(__p_memory_marker); }


/* Memory provider interface */
typedef struct gcsl_memory_provider_interface_s
{
	gcsl_error_t	(GCSL_CALLBACK_API *memory_initialize)	(void);
	gcsl_void_t		(GCSL_CALLBACK_API *memory_shutdown)	(void);

	gcsl_void_t*	(GCSL_CALLBACK_API *memory_alloc)		(gcsl_size_t size);
	gcsl_void_t*	(GCSL_CALLBACK_API *memory_calloc)		(gcsl_size_t count, gcsl_size_t size);
	gcsl_void_t*	(GCSL_CALLBACK_API *memory_realloc)		(gcsl_void_t* p_ptr, gcsl_size_t size);
	gcsl_void_t		(GCSL_CALLBACK_API *memory_free)		(gcsl_void_t* p_ptr);

	gcsl_void_t		(GCSL_CALLBACK_API *memory_memcpy)		(gcsl_void_t *dest, const gcsl_void_t *src, gcsl_size_t size);
	gcsl_void_t		(GCSL_CALLBACK_API *memory_memmove)		(gcsl_void_t *dest, const gcsl_void_t *src, gcsl_size_t size);
	gcsl_void_t		(GCSL_CALLBACK_API *memory_memset)		(gcsl_void_t *dest, gcsl_byte_t val, gcsl_size_t count);
	gcsl_int32_t	(GCSL_CALLBACK_API *memory_memcmp)		(const gcsl_void_t *buff1, const gcsl_void_t *buff2, gcsl_size_t count);

} gcsl_memory_provider_interface_t;

/* set Memory provider override */
CENTRALIZED_MEM_API gcsl_error_t	gcsl_memory_register_provider_interface(
										gcsl_memory_provider_interface_t*	p_memory_interface
										);

#ifdef __cplusplus
}
#endif

#endif

