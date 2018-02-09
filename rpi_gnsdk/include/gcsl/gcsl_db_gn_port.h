/*
 * Copyright (c) 2010 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* 
 *	gcsl_db_gn_port.h - Helper mapping from eMMS db interface to GCSL interface - for apps written for eMMS but wanting to use GCSL.
 */

#ifndef	_GCSL_DB_GN_PORT_H_
#define _GCSL_DB_GN_PORT_H_

typedef gcsl_char_t			gn_uchar_t;
typedef gcsl_uint16_t		gn_uint16_t;
typedef gcsl_uint32_t		gn_uint32_t;
typedef gcsl_int32_t		gn_int32_t;
typedef gcsl_size_t			gn_size_t;
typedef gcsl_error_t		gn_error_t;

typedef gcsl_char_t			ui8_t;		/* Unsigned 8-bit integer. (jmc note that in GCSL, char is always unsigned by way of compiler switches) */
typedef gcsl_int16_t		i16_t;		/* Signed 16-bit integer. */
typedef gcsl_uint16_t		ui16_t;		/* Unsigned 16-bit integer. */
typedef gcsl_int32_t		i32_t;		/* Signed 32-bit integer. */
typedef gcsl_uint32_t		ui32_t;		/* Unsigned 32-bit integer. */
typedef gcsl_size_t			sz_t;	/* Generic size type */

typedef gcsl_handle_t		fhandle_t;
typedef gcsl_uint32_t		foffset_t; /* jmc note: we use 32 bits here to produce eMMS-style DBs */

#define	gnmem_initialize_v2	gcsl_memory_initialize
#define	gnmem_shutdown		gcsl_memory_shutdown
#define	gnfs_initialize		gcsl_fs_initialize
#define	gnfs_shutdown		gcsl_fs_shutdown

#define	gnmem_memcpy		gcsl_memory_memcpy
#define	gnmem_malloc		gcsl_memory_alloc

#define	GN_SUCCESS			GCSL_SUCCESS
#define	GNERR_NoError			GCSL_SUCCESS
#define	GN_NULL				GCSL_NULL
#define	GN_TRUE					GCSL_TRUE
#define	GN_FALSE				GCSL_FALSE

#define	DBERR_MemoryErr	DBERR_NoMemory

#endif	/* #ifndef _GCSL_DB_GN_PORT_H_ */
