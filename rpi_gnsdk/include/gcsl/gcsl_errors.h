/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_errors.h - Definitions for error handling with GCSL.
 */

#ifndef	_GCSL_ERRORS_H_
#define _GCSL_ERRORS_H_

/*
 * Background.
 */

/*
 * ERROR CODE FORMAT VERSION 1
 */
/*
 *  Gracenote GCSL error codes (gcsl_error_t) [version 1]
 *  are 32-bit values layed out as follows:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *  +-+-----+-------+---------------+---------------+---------------+
 *  |s| ver | rsvd  |  package/lib  |          error code           |
 *  +-+-----+-----------------------+---------------+---------------+
 *
 *  where
 *
 *      s - severity
 *          0 - warning
 *          1 - failure
 *
 *      ver - version bits (value = 001).
 *
 *      rsvd - reserved portion of the error code.
 *
 *      package/lib - which library or package is the source of the error.
 *
 *      errror code - as defined in gcsl_error_codes.h.
 */


/*
 * Dependencies.
 */

#ifdef __cplusplus
extern "C"{
#endif 

/*
 * Constants.
 */
#define GCSL_ERROR_VERSION             1

/* Generic value for success */
#define	GCSL_SUCCESS                   0

/* Severity values */
#define GCSL_SEVERITY_WARNING          0
#define GCSL_SEVERITY_FAILURE          1

/* Offsets into error code */
#define	GCSLERR_CODE_OFFSET            0
#define	GCSLERR_PKG_OFFSET             16
#define	GCSLERR_VER_OFFSET             28
#define	GCSLERR_SEV_OFFSET             31

/* Masks for fields within error code */
#define	GCSLERR_CODE_MASK              0x0000FFFF
#define	GCSLERR_PKG_MASK               0x00FF0000
#define	GCSLERR_VER_MASK               0x70000000
#define	GCSLERR_SEV_MASK               0x80000000

/* Sizes (in bits) of fields within error code */
#define	GCSLERR_CODE_SIZE              16
#define	GCSLERR_PKG_SIZE               8
#define	GCSLERR_VER_SIZE               3
#define	GCSLERR_SEV_SIZE               1

#define GCSLERR_CODE_RANGE             ((gcsl_uint32_t)((1 << (GCSLERR_CODE_SIZE + 1)) - 1))
#define GCSLERR_PKG_RANGE              ((gcsl_uint32_t)((1 << (GCSLERR_PKG_SIZE + 1)) - 1))
#define GCSLERR_VER_RANGE              ((gcsl_uint32_t)((1 << (GCSLERR_VER_SIZE + 1)) - 1))
#define GCSLERR_SEV_RANGE              ((gcsl_uint32_t)((1 << (GCSLERR_SEV_SIZE + 1)) - 1))

/* Error descriptions */
#define	GCSLERR_MAX_PACKAGE_STRING     32
#define	GCSLERR_MAX_CODE_STRING        64
#define	GCSLERR_MAX_MESSAGE_STRING     (GCSLERR_MAX_PACKAGE_STRING + GCSLERR_MAX_CODE_STRING + 64)


/*
 * Error assembly/disassembly
 */

/* Form error value from package id and error code */
#define	GCSLERR_MAKE_ERROR(package_id,error_code)	\
\
	((gcsl_error_t)(((gcsl_uint32_t)(GCSL_SEVERITY_FAILURE)               << (GCSLERR_SEV_OFFSET)) | \
	                ((gcsl_uint32_t)(GCSL_ERROR_VERSION)                  << (GCSLERR_VER_OFFSET)) | \
	                ((gcsl_uint32_t)((package_id) & (GCSLERR_PKG_RANGE))  << (GCSLERR_PKG_OFFSET)) | \
	                ((gcsl_uint32_t)((error_code) & (GCSLERR_CODE_RANGE)) << (GCSLERR_CODE_OFFSET))))


	/* Form warning value from package id and error code */
#define	GCSLERR_MAKE_WARNING(package_id,error_code)	\
\
	((gcsl_error_t)(((gcsl_uint32_t)(GCSL_SEVERITY_WARNING)               << (GCSLERR_SEV_OFFSET)) | \
	                ((gcsl_uint32_t)(GCSL_ERROR_VERSION)                  << (GCSLERR_VER_OFFSET)) | \
	                ((gcsl_uint32_t)((package_id) & (GCSLERR_PKG_RANGE))  << (GCSLERR_PKG_OFFSET)) | \
	                ((gcsl_uint32_t)((error_code) & (GCSLERR_CODE_RANGE)) << (GCSLERR_CODE_OFFSET))))


/* Extract error code */
#define	GCSLERR_ERROR_CODE(error_code) \
\
	((gcsl_uint16_t)((gcsl_uint32_t)((error_code) & GCSLERR_CODE_MASK) >> GCSLERR_CODE_OFFSET))


/* Extract package id */
#define	GCSLERR_PKG_ID(error_code) \
\
	((gcsl_uint16_t)((gcsl_uint32_t)((error_code) & GCSLERR_PKG_MASK) >> GCSLERR_PKG_OFFSET))


/* Extract severity code */
#define	GCSLERR_SEVERE(error_code) \
\
	((gcsl_uint16_t)((gcsl_uint32_t)((error_code) & GCSLERR_SEV_MASK) >> GCSLERR_SEV_OFFSET))



#ifdef __cplusplus
}
#endif 


#endif /* #ifndef _GCSL_ERRORS_H_ */

