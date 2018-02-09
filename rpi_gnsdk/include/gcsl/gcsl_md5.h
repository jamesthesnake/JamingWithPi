/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
#ifndef _GCSL_MD5_H_
#define _GCSL_MD5_H_

#ifdef __cplusplus
extern "C" {
#endif

gcsl_error_t	gcsl_md5_initialize		(void);
gcsl_error_t	gcsl_md5_shutdown		(void);

gcsl_cstr_t		gcsl_md5_get_version	(void);
gcsl_cstr_t		gcsl_md5_get_build_date	(void);

/********* MD5 ********/

/* Don't change these for any reason. */
#define MD5_BITS		2
#define MD5_SCRATCHSZ	4
#define MD5_INPUTSZ		64
#define MD5_DIGESTSZ	16
#define MD5_SEEDSZ		32
#define MD5_HASHSZ		(MD5_DIGESTSZ*2)

/* typedef for seeds */
typedef gcsl_byte_t md5_seed_t[MD5_SEEDSZ];


/* Data structure for MD5 (Message-Digest) computation. */
typedef struct md5_ctxt
{
	gcsl_uint32_t	i[MD5_BITS];			/* number of _bits_ handled mod 2^64 */
	gcsl_uint32_t	buf[MD5_SCRATCHSZ];		/* scratch buffer */
	gcsl_byte_t		in[MD5_INPUTSZ];		/* input buffer */
	gcsl_byte_t		digest[MD5_DIGESTSZ];	/* actual digest */
	gcsl_char_t		hash[MD5_HASHSZ+1];		/* hex string form of digest */

} md5_ctxt_t;

gcsl_error_t	gcsl_md5_start(md5_ctxt_t* mdc);
gcsl_error_t	gcsl_md5_compute(md5_ctxt_t* mdc, const gcsl_void_t* v, gcsl_size_t len);
gcsl_error_t	gcsl_md5_end(md5_ctxt_t* mdc);

gcsl_bool_t		gcsl_md5_isvalidhash(gcsl_cstr_t hash);

gcsl_error_t	gcsl_md5_hash_stream(gcsl_iostream_handle_t in_stream, gcsl_iostream_handle_t* p_out_stream, md5_ctxt_t* p_mdc);


#ifdef __cplusplus
}
#endif

#endif /* _GCSL_MD5_H_ */
