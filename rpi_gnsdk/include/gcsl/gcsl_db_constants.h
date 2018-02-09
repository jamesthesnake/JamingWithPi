/*
 * Copyright (c) 2000 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	db_constants.h
 *
 *	Public interface definitions for embedded database module.
 */

#ifndef	_gcsl_db_constants_h_
#define _gcsl_db_constants_h_


/*
 * Dependencies
 */

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Constants
 */

/* Allocation sizes for file I/O */
#define		DB_BLOCK_SIZE				512		/* read in chunks this size */
#define		DB_DEFAULT_INDEX_SIZE		256		/* size of index nodes */
#define		DB_DEFAULT_DATA_QUANTUM		128		/* allocation unit for data records */
#define		DB_DEFAULT_HASH_QUANTUM		128		/* allocation unit for hash collision blocks */
#define		DB_MINIMUM_QUANTUM			32		/* minimum file allocation unit */
#define		DB_MAXIMUM_QUANTUM			1024	/* maximum file allocation unit */
#define		DB_DEFAULT_INDEX_FREEALLOC	32		/* number of index nodes to "pre allocate" in file */
#define		DB_DEFAULT_DATA_FREEALLOC	128		/* number of data quanta to "pre allocate" in file */

/*
 *	Only this many keys allowed.  This was 16 for 4.2 but is now 22 for 4.3 Device 2.5.
 *	May 2008 - added two new indexed fields: gnpl_crit_field_primary_mood_id and gnpl_crit_field_primary_tempo_id.
 */
#define		DB_MAXIMUM_NUM_KEYS			30	/* ALH TEST: was 24 */

/* Error return values */

typedef gcsl_uint16_t	DBPkgError;
typedef gcsl_error_t	DBError;
typedef gcsl_uint32_t	DBKeyCompare;
typedef gcsl_uint32_t	DBHashGen;
typedef gcsl_uint32_t	DBOpenMode;
typedef gcsl_int32_t	DBCallBackAction;
typedef gcsl_uint32_t	DBXformFlags;
typedef	gcsl_uint32_t	DBDataState;


/* Key comparison methods (DBKeyCompare) */
#define	DBKEYCMP_Default			0
#define	DBKEYCMP_Binary				DBKEYCMP_Default
#define	DBKEYCMP_String				1
#define	DBKEYCMP_StringNoCase		2
#define	DBKEYCMP_LongValue			3
#define	DBKEYCMP_TocTable			4
#define	DBKEYCMP_FuzzyValS			5
#define	DBKEYCMP_UString			6
#define	DBKEYCMP_UStringNoCase		7
#define	DBKEYCMP_UStringCaseFold	8
#define	DBKEYCMP_UserDefined	0x100000
#define	DBKEYCMP_Unknown		0xffffffff

/* Methods for generating hash values from keys (DBHashGen) */
#define	DBKEYHASH_Default			0
#define	DBKEYHASH_HashString		1
#define	DBKEYHASH_SumBytes			2
#define	DBKEYHASH_SumUpper			3
#define	DBKEYHASH_KeyLength			4
#define	DBKEYHASH_KeyValue			5
#define	DBKEYHASH_Xor				6
#define	DBKEYHASH_TocTable			7
#define	DBKEYHASH_FuzzyVal			8
#define	DBKEYHASH_FuzzyValS			9
#define	DBKEYHASH_HashUString		10
#define	DBKEYHASH_HashStringUC		11
#define	DBKEYHASH_HashUStringUC		12
#define	DBKEYHASH_XORKeyValue		13
#define	DBKEYHASH_FullString		14
#define	DBKEYHASH_FullUString		15
#define	DBKEYHASH_FullStringUC		16
#define	DBKEYHASH_FullUStringUC		17
#define DBKEYHASH_FNV32String		18
#define DBKEYHASH_FNV32StringUC		19
#define DBKEYHASH_FNV32UString		20
#define DBKEYHASH_FNV32UStringCF	21
#define DBKEYHASH_Chars_1_3_5_7		22
#define	DBKEYHASH_UserDefined		0x100000
#define	DBKEYHASH_UserManaged		0x200000
#define	DBKEYHASH_Unknown			0xffffffff

/*	See unit_tests/common/db/test/db_hash_test for a unit test application that runs selected hash
	methods against a large number of strings.  Only the methods that are logical for strings were
	used.   Below are the results from the app for a list of 10,275 unique "artist_name|album_name"
	strings.

	"StringUC" indicates that lowercase characters in the string are converted to upper case during
	the hash process.  This will guarantee that "Hello World" and "hello world" will generate the
	same hash code.  "UString" indicates that the string is treated as a unicode string.
	
	"UStringCF" is the latest addition in an attempt to handle unicode characters more effectively
	in that "case folding" is preferable over "upper caseing" since upper case is not well defined
	for a lot of languages that use unicode.

		DBKEYHASH_FNV32String		15268 microseconds		No collisions
		DBKEYHASH_FNV32UString		19418 microseconds		No collisions
		DBKEYHASH_FNV32StringUC		21301 microseconds		No collisions
		DBKEYHASH_HashStringUC		23161 microseconds		No collisions
		DBKEYHASH_HashUStringUC		25226 microseconds		No collisions
		DBKEYHASH_FNV32UStringCF	33401 microseconds		No collisions

		DBKEYHASH_Xor				15003 microseconds		1 collision
		DBKEYHASH_HashString		16969 microseconds		1 collision
		DBKEYHASH_HashUString		19344 microseconds		1 collision

		DBKEYHASH_FullUString		14727 microseconds		7068 collisions
		DBKEYHASH_FullString		14797 microseconds		4478 collisions
		DBKEYHASH_FuzzyVal			14999 microseconds		4081 collisions
		DBKEYHASH_FuzzyValS			15084 microseconds		4467 collisions
		DBKEYHASH_SumBytes			15277 microseconds		3357 collisions
		DBKEYHASH_FullUStringUC		15646 microseconds		7115 collisions
		DBKEYHASH_FullStringUC		16250 microseconds		4497 collisions
		DBKEYHASH_SumUpper			20416 microseconds		3893 collisions
 */

/* Open access modes for database files (DBOpenMode) */
#define	DBOPEN_ReadAccess				0x1
#define	DBOPEN_WriteAccess				0x2
#define	DBOPEN_DenyReadAccess			0x4
#define	DBOPEN_DenyWriteAcces			0x8
#define	DBOPEN_AutoCommit				0x10
#define	DBOPEN_OverWrite				0x20
#define	DBOPEN_AppendOnly				0x40
		/* Thread synchronization flags */
#define	DBOPEN_UserThreadSingle			0x100	/* db only allows a single thread access to the database at one time */
#define	DBOPEN_UserThreadMulti			0x200	/* db allows multiple threads to read the database simultaneously, but only one writer at a time */
#define DBOPEN_UserThreadMask			0x300
		/* Check flags */
#define	DBOPEN_Check			0x1000
#define	DBOPEN_CheckDeep		0x2000
#define	DBOPEN_CheckMask		0xF000

/* Values to return from callback to affect processing of records during fetch operation (DBCallBackAction) */
#define	DBCB_Nothing			0
#define	DBCB_Abort				-1		/* free current record and stop */
#define	DBCB_UpdateRecord		0x1		/* update record - data only, not reindexed */
#define	DBCB_DeleteRecord		0x2		/* delete this record from this and other indices */
#define	DBCB_FreeRecord			0x4		/* release this record's memory */

/* Default access mode */
#define	DBOPEN_Default		((DBOpenMode)(DBOPEN_ReadAccess | DBOPEN_WriteAccess))

/* Data transformation flags (DBXformFlags) */
#define	DBXFORM_None			0x0
#define	DBXFORM_BigEndian		0x1		/* database is in "big-endian" (Network byte order) format */
#define	DBXFORM_LittleEndian	0x2		/* database is in "little-endian" (Intel) format */
#define	DBXFORM_Reading			0x10	/* data is being read into memory and transformed */
#define	DBXFORM_Writing			0x20	/* data is being transformed and written onto disk */
#define DBXFORM_InPlaceOkay		0x100	/* in-place transformation allowed (not required) */
#define DBXFORM_UseOutBuff		0x200	/* output buffer preallocated - do not allocate memory */
#define DBXFORM_ForceXform		0x400	/* call transformation functions always (despite byte-order) */

/* Data state flags (DBDataState) */
#define	DBDATASTATE_Empty		0x0		/* db_record_t->db_data_t is not populated */
#define	DBDATASTATE_Populated	0x1		/* db_record_t->db_data_t is populated populated */

/* V2: Table & Key management */
#define	DBKEY_TableNumShift		0x10
#define	DBKEY_KeyNumMask		0xFFFF
#define	DBKEY_MaxTables			10
#define	DBKEY_MaxIndicesPer		32

#ifdef __cplusplus
}
#endif

#endif

