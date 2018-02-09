/*
 * Copyright (c) 2010 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	gcsl_db.h - Gracenote DB Engine functions
 */

#ifndef	_GCSL_DB_H_
#define _GCSL_DB_H_

#ifdef __cplusplus
extern "C"{
#endif 

/*
 * Initialization
 */
gcsl_error_t	gcsl_db_initialize		(void);
gcsl_error_t	gcsl_db_shutdown		(void);

gcsl_cstr_t		gcsl_db_get_version		(void);
gcsl_cstr_t		gcsl_db_get_build_date	(void);

#define gcsl_db_configure			db_configure
#define gcsl_db_get_cfg				db_get_cfg
#define gcsl_db_initialize			db_initialize
#define gcsl_db_shutdown			db_shutdown
#define gcsl_db_create				db_create
#define gcsl_db_create_ex			db_create_ex
#define gcsl_db_create2				db_create2
#define	gcsl_db_open				db_open
#define	gcsl_db_open2				db_open2
#define	gcsl_db_open_ex				db_open_ex
#define	gcsl_db_open_ex2			db_open_ex2
#define gcsl_db_check				db_check
#define	gcsl_db_check_ex			db_check_ex
#define gcsl_db_get_params			db_get_params
#define gcsl_db_get_db_num_keys		db_get_num_keys
#define gcsl_db_get_num_keys		db_get_num_keys
#define gcsl_db_get_num_tables		db_get_num_tables
#define gcsl_db_get_table_info		db_get_table_info
#define gcsl_db_add_table			db_add_table
#define gcsl_db_delete_table		db_delete_table

#define gcsl_db_get_size			db_get_size
#define gcsl_db_get_userdata		db_get_userdata
#define gcsl_db_free_userdata		db_free_userdata
#define gcsl_db_get_userdata_offset	db_get_userdata_offset
#define gcsl_db_set_userdata		db_set_userdata
#define gcsl_db_close				db_close
#define gcsl_db_allocate_free_space	db_allocate_free_space
#define gcsl_db_retrieve_free_space	db_retrieve_free_space
#define gcsl_db_clone				db_clone
#define gcsl_db_import_raw			db_import_raw
#define gcsl_db_import				db_import
#define gcsl_db_compact				db_compact
#define gcsl_db_commit				db_commit
#define gcsl_db_release				db_release
#define gcsl_db_set_buffer			db_set_buffer

#define gcsl_db_create_record		db_create_record
#define gcsl_db_create_record2		db_create_record2
#define gcsl_db_add_key				db_add_key
#define gcsl_db_add_record			db_add_record
#define gcsl_db_add_record2			db_add_record2
#define gcsl_db_delete_record		db_delete_record
#define gcsl_db_free_record			db_free_record
#define gcsl_db_update_record		db_update_record
#define gcsl_db_update_record_key	db_update_record_key
#define gcsl_db_update_n_record_keys	db_update_n_record_keys
#define gcsl_db_validate_record		db_validate_record
#define gcsl_db_find_record			db_find_record
#define gcsl_db_fetch_records		db_fetch_records
#define gcsl_db_create_iterator		db_create_iterator
#define gcsl_db_iterate_next		db_iterate_next
#define gcsl_db_free_iterator		db_free_iterator

#define gcsl_db_record_data			db_record_data
#define	gcsl_db_record_data_length	db_record_data_length
#define gcsl_db_record_set_data_state	db_record_set_data_state
#define	gcsl_db_record_key_length	db_record_key_length
#define	gcsl_db_record_key			db_record_key

#define	gcsl_db_system_endianness	db_system_endianness
#define	gcsl_db_endianness			db_endianness
#define	gcsl_db_swap32				db_swap32
#define	gcsl_db_swap16				db_swap16

/*
 * Some typedefs.
 */

/* For public interface, these types are opaque */
typedef		void*	db_database_t;
typedef		void*	db_record_t;
typedef		void*	db_iterator_t;

/*
 * Prototypes and structures used in/for callbacks.
 */

/* Signature for "callback" function supplied when accessing records sequentially */
typedef DBCallBackAction (*DBCallBackFunc)(void* database, void* record, void* userdata);

/* Helpers available in the app-supplied functions below */
typedef void* (*DBHelperAlloc)(gcsl_size_t size);
typedef void* (*DBHelperRealloc)(void* ptr, gcsl_size_t size);
typedef gcsl_error_t (*DBHelperFree)(void* ptr);
typedef gcsl_uint32_t (*DBHelperPadBlockSize)(void* database, gcsl_uint32_t size);
typedef gcsl_error_t (*DBHelperGetSpace)(void* database, gcsl_uint32_t* offset, gcsl_uint32_t size);
typedef gcsl_error_t (*DBHelperFreeSpace)(void* database, gcsl_uint32_t offset, gcsl_uint32_t size);
typedef gcsl_error_t (*DBHelperReadRaw)(void* database, gcsl_uint32_t offset, void* buffer, gcsl_uint32_t size, gcsl_uint32_t* nread);
typedef gcsl_error_t (*DBHelperReadRecord)(void* database, gcsl_uint32_t keynum, gcsl_uint32_t offset, void** record);
typedef gcsl_error_t (*DBHelperGetRecordOffset)(void* database, void* record, gcsl_uint32_t* offset);
typedef gcsl_error_t (*DBHelperFreeRecord)(void* database, void* record);

typedef struct db_helpers {
	DBHelperAlloc			db_alloc_fn;
	DBHelperRealloc			db_realloc_fn;
	DBHelperFree			db_free_fn;
	DBHelperPadBlockSize	db_padblock_fn;
	DBHelperGetSpace		db_getspace_fn;
	DBHelperFreeSpace		db_freespace_fn;
	DBHelperReadRaw			db_readraw_fn;
	DBHelperReadRecord		db_readrecord_fn;
	DBHelperGetRecordOffset	db_getrecordoffset_fn;
	DBHelperFreeRecord		db_freerecordoffset_fn;
} db_helpers_t;

#define		DB_FRUIT_HASH_USER	3

/* Hash block header */
typedef struct db_hash_hdr {
	gcsl_uint32_t				db_type;			/* DB_FRUIT_DATA for data blocks, DB_FRUIT_HASH, DB_FRUIT_HASH_STR, or DB_FRUIT_HASH_USER for hash collision blocks */
	gcsl_uint32_t				db_total;			/* total number of entries (for growing/shrinking) */
	gcsl_uint32_t				db_valid;			/* number of valid entries */
} db_hash_hdr_t;

/* File/memory format of user hash collision blocks */
typedef struct db_hash_user {
	db_hash_hdr_t		db_hash_hdr;		/* header (count) information for hash collision blocks */
	gcsl_uint32_t		db_total_size;			/* total size of block on disk (for growing/shrinking) */
	gcsl_uint32_t		db_valid_size;			/* amount of block containing valid data */
	/* ui32_t			db_entries[1]; */	/* actual format application defined */
} db_hash_user_t;

/* In-memory structure used for "streaming" in hash collision blocks */
typedef struct db_hash_stream {
	void*				db_buffer;			/* buffer used for hash block I/O */
	gcsl_uint32_t		db_buffer_size;		/* size of this buffer (jmc note: this isn't used?!) */
	gcsl_uint32_t		db_offset;			/* current file offset at/in buffer */
	gcsl_uint32_t		db_eof;				/* set when end of buffer/file hit */
	void*				db_scratch;			/* work buffer for user/application to manage streaming */
} db_hash_stream_t;

/* Signatures for "hash collision" functions called when reading/writing information in the database */
typedef gcsl_error_t (*DBHashInitializeFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t keynum);
typedef gcsl_error_t (*DBHashShutdownFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t keynum);
typedef gcsl_error_t (*DBHashKeyFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t keynum, void* key, gcsl_uint32_t keylength, gcsl_uint32_t* hash);
typedef gcsl_error_t (*DBHashGetSpaceFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t keynum, db_hash_user_t* block, gcsl_uint32_t* block_size, gcsl_uint32_t* offset);
typedef gcsl_error_t (*DBHashCreateFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t record_offset, gcsl_uint32_t hash, gcsl_uint32_t keynum, void** block, gcsl_uint32_t* block_size, gcsl_uint32_t* offset);
typedef gcsl_error_t (*DBHashInsertFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t keynum, void* record, void* block, db_hash_stream_t* stream, gcsl_uint32_t offset, void** new_block, gcsl_uint32_t* new_block_size, gcsl_uint32_t* new_offset);
typedef gcsl_error_t (*DBHashAppendFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t keynum, db_hash_user_t* block, void* record, void* old_block, db_hash_stream_t* stream, gcsl_uint32_t offset, void** new_block, gcsl_uint32_t* new_block_size, gcsl_uint32_t* new_offset);
typedef gcsl_error_t (*DBHashDeleteFn)(db_helpers_t* helpers, void* database, gcsl_uint32_t keynum, void* record, void* block, db_hash_stream_t* stream, gcsl_uint32_t offset, void** new_block, gcsl_uint32_t* new_block_size, gcsl_uint32_t* new_offset, void** last_record);
typedef gcsl_error_t (*DBHashFindFn)(db_helpers_t* helpers, void* database, void* block, db_hash_stream_t* stream, gcsl_uint32_t offset, gcsl_uint32_t* location, gcsl_int32_t* compare_value, gcsl_uint32_t keynum, void* key, gcsl_uint32_t keylength, void** record, gcsl_uint32_t* record_offset);
typedef gcsl_error_t (*DBHashFetchFn)(db_helpers_t* helpers, void* database, DBCallBackFunc callback, void* userdata, void* block, gcsl_uint32_t keynum, void* key, gcsl_uint32_t keylength); /* (jmc note: this isn't used?!) */
typedef gcsl_error_t (*DBHashGetFn)(db_helpers_t* helpers, void* database, void* block, db_hash_stream_t* stream, gcsl_uint32_t offset, gcsl_uint32_t location, void** record);

/* Signatures for "transformation" functions called when reading/writing information in the database */
typedef gcsl_error_t (*DBXformRecordFunc)(void* database, DBXformFlags flags, gcsl_uint32_t keyinfo, void* in, gcsl_uint32_t size_in, void** out, gcsl_uint32_t* size_out);
typedef gcsl_error_t (*DBXformKeyFunc)(void* database, DBXformFlags flags, gcsl_uint32_t keynum, void* in, gcsl_uint32_t size_in, void** out, gcsl_uint32_t* size_out);
typedef gcsl_error_t (*DBXformBlockFunc)(void* database, DBXformFlags flags, gcsl_uint32_t keynum, void* in, gcsl_uint32_t size_in, void** out, gcsl_uint32_t* size_out);


/*
 * Structures.
 */

/*
 * Tuning parameters for database creation:
 * These parameters can affect the structure of the database and can only be
 * established at the time of creation.  If none are specified, a single-keyed
 * database with default sizes for index and data blocks is created.
 */
typedef struct db_params {
	gcsl_uint32_t		db_version;			/* optional, caller-supplied version number */
	gcsl_int32_t		db_num_keys;		/* number of keys */
	DBKeyCompare*		db_keycomp;			/* preferred method to compare keys */
	DBHashGen*			db_hashgen;			/* preferred method to generate hash values for keys */
	gcsl_uint32_t		db_index_size;		/* recommended size of index blocks */
	gcsl_uint32_t		db_hash_quantum;	/* allocation quantum for hash blocks (for duplicate keys) */
	gcsl_uint32_t		db_data_quantum;	/* allocation quantum for of data blocks */
	gcsl_uint32_t		db_user_size;		/* size for single block of non-indexed "user data" */
} db_params_t;

/*
 * Application information for controlling endian-ness
 */
typedef struct db_xform_info {
	DBXformFlags		db_format;		/* desired format of database */
	DBXformRecordFunc	db_record_fn;	/* application function for transforming records */
	DBXformKeyFunc		db_key_fn;		/* application function for transforming keys */
	DBXformBlockFunc	db_block_fn;	/* application function for transforming user-managed hash blocks */
} db_xform_info_t;

typedef struct db_xform_info2 {
	DBXformFlags		db_format;			/* desired format of database */
	DBXformKeyFunc		db_key_fn;			/* application function for transforming keys */
	DBXformBlockFunc	db_block_fn;		/* application function for transforming user-managed hash blocks */
	gcsl_int32_t		db_table_count;		/* number of distinct tables (schemas, record layouts) */
	DBXformRecordFunc*	db_record_fns;		/* application function for transforming records */
} db_xform_info2_t;

/*
 * Application information for controlling behavior of hash collision blocks
 */
typedef struct db_hash_info {
	gcsl_uint32_t		db_keynum;			/* index number for these functions */
	gcsl_uint32_t		db_block_limit;		/* hash block size limit - blocks larger are streamed */
	DBHashInitializeFn	db_initialize_fn;	/* user-managed hash block functions */
	DBHashShutdownFn	db_shutdown_fn;
	DBHashKeyFn			db_hash_fn;
	DBHashGetSpaceFn	db_get_space_fn;
	DBHashCreateFn		db_create_fn;
	DBHashInsertFn		db_insert_fn;
	DBHashAppendFn		db_append_fn;
	DBHashDeleteFn		db_delete_fn;
	DBHashFindFn		db_find_fn;
	DBHashFetchFn		db_fetch_fn;
	DBHashGetFn			db_get_fn;
} db_hash_info_t;

/*
 * Application information for extended interfaces (create/open)
 */
typedef struct db_ex_info {
	gcsl_uint32_t		db_cache_size;	/* DEPRECATED - but leaving in to avoid multiple file changes */
	db_xform_info_t*	db_xform;		/* transformation/endian information */
	gcsl_uint32_t		db_hash_count;	/* number of entries in following array */
	db_hash_info_t*		db_hash_info;	/* user-managed hash information */
} db_ex_info_t;

typedef struct db_ex_info2 {
	db_xform_info2_t*	db_xform;		/* transformation/endian information */
	gcsl_uint32_t		db_hash_count;	/* number of entries in following array */
	db_hash_info_t*		db_hash_info;	/* user-managed hash information */
} db_ex_info2_t;

/* for creating "version 2" db files */
typedef struct db_table {
	gcsl_uint32_t		db_num_keys;		/* number of keys supported in this table */
	DBKeyCompare*		db_keycomp;			/* preferred method to compare keys */
	DBHashGen*			db_hashgen;			/* preferred method to generate hash values for keys */
	DBXformRecordFunc	db_record_fn;		/* application function for transforming records in this table */
} db_table_t;

typedef struct db_params2 {
	gcsl_uint32_t		db_version;			/* optional, caller-supplied version number */
	gcsl_int32_t		db_num_keys;		/* number of keys (total, for all tables) */
	gcsl_int32_t		db_table_count;		/* number of distinct tables (schemas, record layouts) */
	db_table_t*			db_table_info;		/* index/key information for the tables */
	gcsl_uint32_t		db_index_size;		/* recommended size of index blocks */
	gcsl_uint32_t		db_hash_quantum;	/* allocation quantum for hash blocks (for duplicate keys) */
	gcsl_uint32_t		db_data_quantum;	/* allocation quantum for of data blocks */
	db_xform_info2_t*	db_xform;			/* transformation/endian information */
	gcsl_uint32_t		db_hash_count;		/* number of entries in following array */
	db_hash_info_t*		db_hash_info;		/* user-managed hash information */
} db_params2_t;

/* run-time configuration parameters */
typedef struct db_config {
	gcsl_uint32_t		db_user_info;		/* optional, caller-supplied value */
	gcsl_uint32_t		db_cache_size;		/* total bytes to allocate for index cache buffers */
	void*				db_cache_buffer;	/* if supplied, used internally for index caching */
	gcsl_uint32_t		db_index_alloc;		/* number of index nodes to allocate when needed */
	gcsl_uint32_t		db_data_alloc;		/* number of data quantum to allocate when needed */
} db_config_t;

/* Table & Key management macros */
#define	DB_TABLE_KEY_NUM(t, k)			((t << DBKEY_TableNumShift) | (k & DBKEY_KeyNumMask))

/*
 * Public Interface Database Routines.
 */

/* configure database with buffer (or NULL) and size to use */
gcsl_error_t
db_configure(void* buffer, gcsl_uint32_t size);

/* find out what the current configuration is */
gcsl_error_t
db_get_cfg(void** buffer, gcsl_uint32_t* size);

/* initialize DB engine */
gcsl_error_t
gcsl_db_initialize();

/* shutdown DB engine  */
gcsl_error_t
gcsl_db_shutdown();


/*
 * File level operations
 */

/* Create a (version 1) database and leave open for further access */
gcsl_error_t
gcsl_db_create(db_database_t* database, gcsl_cstr_t filename, DBOpenMode mode, db_params_t* params);


/* Create a (version 1) database and leave open for further access */
gcsl_error_t
gcsl_db_create_ex(db_database_t* database, gcsl_cstr_t filename, DBOpenMode mode, db_params_t* params, db_ex_info_t* info, gcsl_uint32_t user_info);

/* Create a (version 2) database and leave open for further access */
gcsl_error_t
gcsl_db_create2(db_database_t* database, gcsl_cstr_t filename, DBOpenMode mode, db_params2_t* params, db_config_t* config);


/* Open a database */
gcsl_error_t
gcsl_db_open(db_database_t* database, gcsl_cstr_t filename, DBOpenMode mode);


/* Open a database */
gcsl_error_t
gcsl_db_open_ex(db_database_t* database, gcsl_cstr_t filename, DBOpenMode mode, db_ex_info_t* info, gcsl_uint32_t user_info);

/* Open a (version 2) database and leave open for further access */
gcsl_error_t
gcsl_db_open2(db_database_t* database, gcsl_cstr_t filename, DBOpenMode mode, db_ex_info2_t* info, db_config_t* config);


/* Check database integrity */
gcsl_error_t
gcsl_db_check(gcsl_cstr_t filename, DBOpenMode mode);

/* Check database integrity */
gcsl_error_t
gcsl_db_check_ex(gcsl_cstr_t filename, DBOpenMode mode, db_ex_info_t* info);

/* Retrieve parameters for an existing database */
gcsl_error_t
gcsl_db_get_params(db_database_t database, db_params_t* params);

/*	Get the number of keys for this database.	*/
gcsl_error_t
gcsl_db_get_num_keys(db_database_t db, gcsl_uint32_t* nkeys);

/*	Get the number of tables for this database.	*/
gcsl_error_t
gcsl_db_get_num_tables(db_database_t db, gcsl_uint32_t* ntables);

/*	Get the number of tables for this database.	*/
gcsl_error_t
gcsl_db_table_get_num_keys(db_database_t db, gcsl_uint32_t table_num, gcsl_uint32_t* nkeys);

/*	Retrieve indexing information for the specified table and key.	*/
gcsl_error_t
gcsl_db_table_get_key_info(db_database_t db, gcsl_uint32_t table_num, gcsl_uint32_t key_num, DBKeyCompare* key_comp, DBHashGen* hash_gen);

/*	Add a table to an existing database.	*/
gcsl_error_t
gcsl_db_add_table(db_database_t db, gcsl_uint32_t table_num, db_table_t* table_info);

/*	Remove any remaining indexing information for a table.	*/
gcsl_error_t
gcsl_db_delete_table(db_database_t db, gcsl_uint32_t table_num);


/*	Get the user db version for this database.	*/
gcsl_error_t
gcsl_db_get_db_version(db_database_t db, gcsl_uint32_t *version);

/* Retrieve size of an existing database */
gcsl_error_t
gcsl_db_get_size(db_database_t database, gcsl_uint32_t* size);


/* Retrieve non-indexed "user data" for the database */
gcsl_error_t
gcsl_db_get_userdata(db_database_t database, void** data, gcsl_uint32_t* datalength);

/* Free memory allocated by db_get_userdata */
gcsl_error_t
db_free_userdata(db_database_t database, void* data);

/* Get raw offset of "user data" for the database */
gcsl_error_t
gcsl_db_get_userdata_offset(db_database_t database, gcsl_uint32_t* offset);

/* Set/update non-indexed "user data" for the database */
gcsl_error_t
gcsl_db_set_userdata(db_database_t database, void* data, gcsl_uint32_t datalength);


/* Retrieve "user info" for an open database */
gcsl_error_t
gcsl_db_get_user_info(db_database_t database, gcsl_uint32_t* user_info);

/* Set/update "user info" for an open database */
gcsl_error_t
gcsl_db_set_user_info(db_database_t database, gcsl_uint32_t user_info);


/* Close an open database */
gcsl_error_t
gcsl_db_close(db_database_t database);


/* Extend file size and add space to free list */
gcsl_error_t
gcsl_db_allocate_free_space(db_database_t database, gcsl_uint32_t index_space, gcsl_uint32_t data_space);


/* Return free list information */
gcsl_error_t
gcsl_db_retrieve_free_space(db_database_t database, gcsl_uint32_t* index_space_max, gcsl_uint32_t* index_space_total, gcsl_uint32_t* data_space_max, gcsl_uint32_t* data_space_total);


/* Return free list allocation information */
gcsl_error_t
gcsl_db_get_free_allocation(db_database_t database, gcsl_uint32_t* index_count, gcsl_uint32_t* data_count);


/* Return free list allocation information */
gcsl_error_t
gcsl_db_set_free_allocation(db_database_t database, gcsl_uint32_t index_count, gcsl_uint32_t data_count);


/* Copy entries/userdata from a database into passed file */
gcsl_error_t
gcsl_db_clone(db_database_t database, gcsl_cstr_t filename, gcsl_uint16_t all_indices);


/* Import entries and user data from one database into another */
gcsl_error_t
gcsl_db_import_raw(db_database_t src_database, db_database_t dst_database, gcsl_uint16_t all_indices);


/* Import entries from one database into another */
gcsl_error_t
gcsl_db_import(db_database_t src_database, db_database_t dst_database, gcsl_uint16_t all_indices);


/* Try to reduce the size of a database by moving data/index nodes into "holes"
   in the database file */
gcsl_error_t
gcsl_db_compact(db_database_t database);


/* Commit any changes to disk, leaving the database in a consistent state */
gcsl_error_t
gcsl_db_commit(db_database_t database);


/* Release memory associated with the database */
gcsl_error_t
gcsl_db_release(db_database_t database, gcsl_uint32_t amount);


/* Set/reset dynamic buffering allocation (database can be null) for the database
   or the database engine */
gcsl_error_t
gcsl_db_set_buffer(db_database_t database, void* buffer, gcsl_uint32_t amount);

/* get endian-ness of system */
DBXformFlags
gcsl_db_system_endianness(void);

/* get endian-ness of database */
DBXformFlags
gcsl_db_endianness(db_database_t database);


/*
 * Database Record level operations
 */

/* Create a new record for insertion */
gcsl_error_t
gcsl_db_create_record(db_database_t database, db_record_t* record, void* data, gcsl_uint32_t datalength, gcsl_uint32_t keylength);

/* Create a new (version 2) record for population and insertion */
gcsl_error_t
gcsl_db_create_record2(db_database_t database, db_record_t* record, gcsl_uint32_t table, void* data, gcsl_uint32_t datalength, gcsl_uint32_t keylength);

/*  db_create_record_no_data
 * Description: creates a new record without data populated in the record
 *
 * Args:	db_database_t	- handle to the database
 *			db_record_t		- pointer to the record to be created
 *			ui32_t			- size in bytes of space to allocate for the data in the record (to be populated later)
 *			keylength		- size in bytes of the key
 *
 * Returns:	GNERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Invalid argument
 *				Not enough memory
 *
 */
gcsl_error_t
gcsl_db_create_record_no_data(db_database_t db, db_record_t* record, gcsl_uint32_t datalength, gcsl_uint32_t keylength);

/*  db_record_get_data_pointer
 * Description: gets a pointer to the data buffer in the record, along with buffer size
 *
 * Args:	db_record_t		- record from which to retrieve the data pointer
 *			pp_data			- pointer to be set to the data buffer in the record
 *			p_data_len		- pointer to be set to the size of the data buffer
 *
 * Returns:	GNERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Invalid argument
 *
 */
gcsl_error_t
gcsl_db_record_get_data_pointer(db_record_t record, void** pp_data, gcsl_uint32_t* p_data_len);

/*  db_record_set_data_state
 * Description: sets the state of the db_data member of the db_record
 *
 * Args:	db_record_t		- record to set the db_data state
 *			db_data_state	- db_data state to set in the record
 *
 * Returns:	GNERR_NoError upon success or an error.
 *			Failure conditions include:
 *				Invalid argument
 *
 */
gcsl_error_t
gcsl_db_record_set_data_state(db_record_t record, DBDataState db_data_state);

/* Associate key with a record or update the key value */
gcsl_error_t
gcsl_db_add_key(db_database_t database, db_record_t record, gcsl_uint32_t keynumber, void* key, gcsl_uint32_t keylength);


/* Insert record into database */
gcsl_error_t
gcsl_db_add_record(db_database_t database, db_record_t record);

/* Insert record into version 2 database (and into specific indices) */
gcsl_error_t
gcsl_db_add_record2(db_database_t database, db_record_t record, gcsl_uint32_t index_mask);


/* Delete record from database (NOTE: this doesn't delete the record from memory) */
gcsl_error_t
gcsl_db_delete_record(db_database_t database, db_record_t record);


/* Free memory associated with the record - use after add/update or find */
gcsl_error_t
gcsl_db_free_record(db_database_t database, db_record_t record);


/* Update record in database (NOTE: only the data portion can be updated.  If the key
   values have changed, the record must be deleted from the database and reinserted.) */
gcsl_error_t
gcsl_db_update_record(db_database_t database, db_record_t record, void* data, gcsl_uint32_t datalength);


/* Update a single key for a record in database. */
gcsl_error_t
gcsl_db_update_record_key(db_database_t database, db_record_t record, gcsl_uint32_t keynumber, void* key, gcsl_uint32_t keylength);


/* Update multiple keys for a record in database. */
gcsl_error_t
gcsl_db_update_n_record_keys(db_database_t database, db_record_t record, gcsl_uint32_t keycount, gcsl_uint32_t* keynumbers, void** keys, gcsl_uint32_t* keylengths);


/* Verify that passed record is valid */
gcsl_error_t
gcsl_db_validate_record(db_database_t database, db_record_t record);


/* Compare the records to see if they refer to the same record in the database */
gcsl_error_t
gcsl_db_compare_records(db_database_t database, db_record_t record1, db_record_t record2, gcsl_uint32_t *same);

/* Add a "block" of records (which hash to the same value) to an index.
   NOTE: this is ONLY supported for application-managed hashing. */
gcsl_error_t
gcsl_db_add_block_to_index(db_database_t database, db_hash_user_t* block, gcsl_uint32_t keynumber, gcsl_uint32_t hash);


/*
 * Database Record traversal operations
 */

/* Find record with the passed key (if multiple records exist with that key value, the
   first matching record is returned) */
gcsl_error_t
gcsl_db_find_record(db_database_t database, db_record_t* record, gcsl_uint32_t keynumber, void* key, gcsl_uint32_t keylength);


/* Find matching records in database.  The callback function is called with each matching
   record and the userdata.  If no key value is specified, all records (sorted by the index
   specified in keynumber) are returned */
gcsl_error_t
gcsl_db_fetch_records(db_database_t database, DBCallBackFunc callback, void* userdata, gcsl_uint32_t keynumber, void* key, gcsl_uint32_t keylength);


/* Create iterator to return matching records in database.  If no key value is specified, all records
   (sorted by the index specified in keynumber) will be returned */
gcsl_error_t
gcsl_db_create_iterator(db_database_t database, db_iterator_t *iterator, gcsl_uint32_t keynumber, void* key, gcsl_uint32_t keylength, gcsl_char_t key_start_only);


/* Return next matching record in database associated with the iterator. */
gcsl_error_t
gcsl_db_iterate_next(db_database_t database, db_iterator_t iterator, db_record_t* record);


/* Free iterator and release memory. */
gcsl_error_t
gcsl_db_free_iterator(db_database_t database, db_iterator_t iterator);


/*
 * Record level operations
 */

/* Get size of record (data & keys) jmc note: declared, but not implemented?
gcsl_uint32_t
gcsl_db_record_size(db_record_t record);
*/


/* Get length of record data */
gcsl_uint32_t
gcsl_db_record_data_length(db_record_t record);


/* Get pointer to record data */
void*
gcsl_db_record_data(db_record_t record);


/* Get length of specified record key */
gcsl_uint32_t
gcsl_db_record_key_length(db_record_t record, gcsl_uint32_t keynumber);


/* Get pointer to specified record key */
void*
gcsl_db_record_key(db_record_t record, gcsl_uint32_t keynumber);


/*
 *	Since db_swap32 is called so often in the db subsystem it makes sense to define
 *	it as in-line code.
 */
#define DB_DEFINE_DB_SWAP_AS_INLINE


#ifdef DB_DEFINE_DB_SWAP_AS_INLINE
#define db_swap32(x)	\
			((((gcsl_uint32_t)x & 0x000000ff)<<24)		| \
			 (((gcsl_uint32_t)x & 0x0000ff00)<<8)		| \
			 (((gcsl_uint32_t)x & 0x00ff0000)>>8)		| \
			 (((gcsl_uint32_t)x & 0xff000000)>>24))

#define db_swap16(x)	\
			((((gcsl_uint16_t)x & 0x00ff)<<8)	| \
			 (((gcsl_uint16_t)x & 0xff00)>>8))
#else
/* swap 32-bit value */
ui32_t
db_swap32(ui32_t x);

/* swap 16-bit value */
ui16_t
db_swap16(ui16_t x);
#endif	/* DB_DEFINE_DB_SWAP_AS_INLINE */

#ifdef __cplusplus
}
#endif 

#endif /* _GCSL_DB_H_ */
