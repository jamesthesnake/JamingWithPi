/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
* gcsl_log.h - General logging functionality.
*/

#ifndef	_GCSL_LOG_H_
#define _GCSL_LOG_H_

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Constants
 */

#define		GCSLLOG_PKG_ALL				(0xFF)					/* Indicates all package ids. */
#define		GCSLLOG_PKG_GCSL			(GCSLERR_MAX_PKG_ID+1)	/* Indicates all GCSL package ids. */
#define		GCSLLOG_PKG_GNSDK			(GNSDKERR_MAX_PKG_ID+1)	/* Indicates all GNSDK package ids. */

/* NB: ensure this list matches corresponds with the logid_strings map */
#define		GCSLLOG_ERROR				0x00000001	/* log error messages */
#define		GCSLLOG_WARNING				0x00000002	/* log warning messages */
#define		GCSLLOG_INFO				0x00000004	/* log informational messages */
#define		GCSLLOG_DEBUG				0x00000008	/* log debug messages */

#define		GCSLLOG_ANY					0x0000000F	/* indicates all log filters */
#define		GCSLLOG_IDS_ALL_PUBLIC		GCSLLOG_ANY


/****************************************************************/
/*			LOGGING OPTION CONSTANTS							*/
/****************************************************************/

#define		GCSLLOG_OPTION_TIMESTAMP	0x01000000 /* Wed Jan 30 18:56:37 2008 */
#define		GCSLLOG_OPTION_CATEGORY		0x02000000 /* ERROR, INFO, etc */
#define		GCSLLOG_OPTION_PACKAGE		0x04000000 /* Package Name (or ID if name unavailable)*/
#define		GCSLLOG_OPTION_THREAD		0x08000000 /* Thread ID */
#define		GCSLLOG_OPTION_SOURCEINFO	0x10000000 /* __GCSL_FILE__(__LINE__) */
#define		GCSLLOG_OPTION_NEWLINE		0x20000000 /* trailing newline - \r\n */

#define		GCSLLOG_OPTION_NONE			0x00000000 /* no extra bits in the log */
#define		GCSLLOG_OPTION_ALL			0xFF000000 /* include all extra bits in the.  verbose! */

/*
 * Structures and typedefs.
 */

/* log handle */
GCSL_DECLARE_HANDLE( gcsl_log_handle_t );

/*
 * global logging callbacks
 */
typedef gcsl_error_t (GCSL_CALLBACK_API *gcsl_log_error_fn)	(gcsl_int32_t line, gcsl_cstr_t filename, gcsl_error_t code, gcsl_cstr_t context_error_info, ...);
typedef gcsl_void_t  (GCSL_CALLBACK_API *gcsl_log_fn)		(gcsl_int32_t line, gcsl_cstr_t filename, gcsl_uint16_t pkg_id, gcsl_uint32_t filter_mask, gcsl_cstr_t fmt, ...);

#if (defined GCSL_CREATE_IMPORTS)
	#define CENTRALIZED_LOG_API		GCSL_IMPORTED_API
#elif (defined GCSL_CREATE_EXPORTS)
	#define CENTRALIZED_LOG_API		GCSL_EXPORTED_API
#else
	#define CENTRALIZED_LOG_API
#endif

/* all SDKs import these globals from SDK Manager */
extern CENTRALIZED_LOG_API gcsl_log_error_fn	g_gcsl_log_error_callback;
extern CENTRALIZED_LOG_API gcsl_log_fn			g_gcsl_log_callback;
/* global enable mask array of size GCSLLOG_PKG_ALL - one mask per package id */
extern CENTRALIZED_LOG_API gcsl_uint32_t		g_gcsl_log_enabled_pkgs[GCSLLOG_PKG_ALL];

/*
 * Global Logging Macros
 */

/* TODO - these names could really be improved. */

#ifndef __GCSL_FILE__
#define __GCSL_FILE__	__FILE__
#endif

#define	GCSLERR_LOG_ERR(code)						( (g_gcsl_log_error_callback && \
														(GCSLERR_SEVERE(code)) && \
														(g_gcsl_log_enabled_pkgs[GCSLERR_PKG_ID(code)] & GCSLLOG_ERROR)) ? \
														(g_gcsl_log_error_callback(__LINE__, __GCSL_FILE__, (code), (gcsl_cstr_t)GCSL_NULL)) : \
														(code) \
													)
#define	GCSLERR_LOG_ERRX(code, line, file)			( (g_gcsl_log_error_callback && \
														(GCSLERR_SEVERE(code)) && \
														(g_gcsl_log_enabled_pkgs[GCSLERR_PKG_ID(code)] & GCSLLOG_ERROR)) ? \
														(g_gcsl_log_error_callback((line), (file), (code), (gcsl_cstr_t)GCSL_NULL)) : \
														(code) \
													)

#define	GCSLERR_LOG_ERR_API(code, api_fn)			( (g_gcsl_log_error_callback && \
														(GCSLERR_SEVERE(code)) && \
														(g_gcsl_log_enabled_pkgs[GCSLERR_PKG_ID(code)] & GCSLLOG_ERROR)) ? \
														(g_gcsl_log_error_callback(0, #api_fn, code, (gcsl_cstr_t)GCSL_NULL)) : \
														(code) \
													)

#define	GCSLERR_LOG_ERR_API_CTX(code, api_fn, ctx_msg) ( (g_gcsl_log_error_callback && \
														(GCSLERR_SEVERE(code)) && \
														(g_gcsl_log_enabled_pkgs[GCSLERR_PKG_ID(code)] & GCSLLOG_ERROR)) ? \
														(g_gcsl_log_error_callback(0, #api_fn, code, ctx_msg)) : \
														(code) \
													)

#define	GCSLERR_LOG_ERR_CTX(code, ctx_msg)			( (g_gcsl_log_error_callback && \
														(GCSLERR_SEVERE(code)) && \
														(g_gcsl_log_enabled_pkgs[GCSLERR_PKG_ID(code)] & GCSLLOG_ERROR)) ? \
														(g_gcsl_log_error_callback(__LINE__, __GCSL_FILE__, code, ctx_msg)) : \
														(code) \
													)

#define	GCSLERR_LOG_ERR_CTX1(code, ctx_fmt, p1)		( (g_gcsl_log_error_callback && \
														(GCSLERR_SEVERE(code)) && \
														(g_gcsl_log_enabled_pkgs[GCSLERR_PKG_ID(code)] & GCSLLOG_ERROR)) ? \
														(g_gcsl_log_error_callback(__LINE__, __GCSL_FILE__, code, ctx_fmt, p1)) : \
														(code) \
													)

#define _GCSL_LOG_TEST(package_id, mask)			(g_gcsl_log_callback && (g_gcsl_log_enabled_pkgs[package_id] & (mask)))
#define _GCSL_LOG_CALL(package_id, mask, msg)		g_gcsl_log_callback(__LINE__, __GCSL_FILE__, package_id, mask, msg
#define _GCSL_LOG_CALLV(package_id, mask, fmt, ...)	g_gcsl_log_callback(__LINE__, __GCSL_FILE__, package_id, mask, fmt, __VA_ARGS__)
#define _GCSL_LOG_CALL_X(package_id, mask, msg)		g_gcsl_log_callback(0, GCSL_NULL, package_id, mask, msg
#define _GCSL_LOG_CALL_XV(package_id, mask, fmt, ...)	g_gcsl_log_callback(0, GCSL_NULL, package_id, mask, fmt, __VA_ARGS__)

/* for testing if call would even be logged */
#define GCSL_LOG_ENABLED(package_id, mask)			_GCSL_LOG_TEST(package_id, mask)

/* direct logging calls with source file parameters */
#define	GCSLLOG(package_id, mask, msg)									GCSLLOG0(package_id, mask, msg)
#define	GCSLLOG0(package_id, mask, msg)									{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, msg) ); }
#define	GCSLLOG1(package_id, mask, fmt, p1)								{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, fmt), p1 ); }
#define	GCSLLOG2(package_id, mask, fmt, p1, p2)							{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, fmt), p1, p2 ); }
#define	GCSLLOG3(package_id, mask, fmt, p1, p2, p3)						{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, fmt), p1, p2, p3 ); }
#define	GCSLLOG4(package_id, mask, fmt, p1, p2, p3, p4)					{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, fmt), p1, p2, p3, p4 ); }
#define	GCSLLOG5(package_id, mask, fmt, p1, p2, p3, p4, p5)				{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, fmt), p1, p2, p3, p4, p5 ); }
#define	GCSLLOG6(package_id, mask, fmt, p1, p2, p3, p4, p5, p6)			{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, fmt), p1, p2, p3, p4, p5, p6 ); }
#define	GCSLLOG7(package_id, mask, fmt, p1, p2, p3, p4, p5, p6, p7)		{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL(package_id, mask, fmt), p1, p2, p3, p4, p5, p6, p7 ); }
#define	GCSLLOGV(package_id, mask, fmt, ...)							{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALLV(package_id, mask, fmt, __VA_ARGS__ ); }

/* direct logging calls without source file parameters */
#define	GCSLLOGX(package_id, mask, msg)									GCSLLOGX0(package_id, mask, msg)
#define	GCSLLOGX0(package_id, mask, msg)								{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, msg) ); }
#define	GCSLLOGX1(package_id, mask, fmt, p1)							{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, fmt), p1 ); }
#define	GCSLLOGX2(package_id, mask, fmt, p1, p2)						{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, fmt), p1, p2 ); }
#define	GCSLLOGX3(package_id, mask, fmt, p1, p2, p3)					{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, fmt), p1, p2, p3 ); }
#define	GCSLLOGX4(package_id, mask, fmt, p1, p2, p3, p4)				{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, fmt), p1, p2, p3, p4 ); }
#define	GCSLLOGX5(package_id, mask, fmt, p1, p2, p3, p4, p5)			{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, fmt), p1, p2, p3, p4, p5 ); }
#define	GCSLLOGX6(package_id, mask, fmt, p1, p2, p3, p4, p5, p6)		{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, fmt), p1, p2, p3, p4, p5, p6 ); }
#define	GCSLLOGX7(package_id, mask, fmt, p1, p2, p3, p4, p5, p6, p7)	{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_X(package_id, mask, fmt), p1, p2, p3, p4, p5, p6, p7 ); }
#define	GCSLLOGXV(package_id, mask, fmt, ...)							{ if(_GCSL_LOG_TEST(package_id, mask)) _GCSL_LOG_CALL_XV(package_id, mask, fmt, __VA_ARGS__ ); }
/* for TIMING logs */
#define	GCSLLOG_TIMING_TYPE_SYSTEM										"SYS" /* system info that may be relevant in analyzing metrics */
#define	GCSLLOG_TIMING_TYPE_INFO										"INF" /* info about the particular metric run*/
#define	GCSLLOG_TIMING_TYPE_COLUMNS										"COL" /* */
#define	GCSLLOG_TIMING_TYPE_COUNTER										"CNT" /* */
#define	GCSLLOG_TIMING_TYPE_TASK_BEGIN									"BEG" /* */
#define	GCSLLOG_TIMING_TYPE_TASK_END									"END" /* */

#define GCSLLOG_TIMING_LOG_HEADER()										{ if(_GCSL_LOG_TEST(GCSLPKG_Timings, GCSLLOG_DEBUG)) GCSLLOG1(GCSLPKG_Timings, GCSLLOG_DEBUG, "%s|microseconds|desc|count(typically bytes)|return code|notes", GCSLLOG_TIMING_TYPE_COLUMNS); }

#define GCSLLOG_TIMING_DECLARE_COUNTER()								gcsl_time_us_t timing = 0
#define GCSLLOG_TIMING_START_COUNTER()									{ if(_GCSL_LOG_TEST(GCSLPKG_Timings, GCSLLOG_DEBUG)) { timing = gcsl_time_get_microseconds(); } }
#define GCSLLOG_TIMING_LOG_COUNTER(desc, count, error, notes)			{ if(_GCSL_LOG_TEST(GCSLPKG_Timings, GCSLLOG_DEBUG)) { timing = gcsl_time_get_microseconds() - timing; GCSLLOG6(GCSLPKG_Timings, GCSLLOG_DEBUG, "%s|%10llu|%s|%u|0x%08X|%s", GCSLLOG_TIMING_TYPE_COUNTER, timing, desc, count, error, notes); } }
/* jmctodo
#define GCSLLOG_TIMING_LOG_SYS_CPU(pkg)									{ if(_GCSL_LOG_TEST(GCSLPKG_Timings, GCSLLOG_DEBUG)) GCSLLOG2(GCSLPKG_Timings, GCSLLOG_DEBUG, "%s|%s", GCSLLOG_TIMING_TYPE_SYSTEM, cpu); } }
*/

/*
 * Prototypes
 */

/* Initialization */

gcsl_error_t	gcsl_log_initialize		(void);
gcsl_error_t	gcsl_log_shutdown		(void);

gcsl_cstr_t		gcsl_log_get_version	(void);
gcsl_cstr_t		gcsl_log_get_build_date	(void);


gcsl_error_t	gcsl_log_register_package(
					gcsl_uint16_t		package_id,
					gcsl_cstr_t			package_name
					);

gcsl_error_t	gcsl_log_open(
					gcsl_log_handle_t*	p_handle,
					gcsl_cstr_t			path,
					gcsl_uint64_t		max_size,	/* bytes. set to 0 to create a new file each time */
					gcsl_bool_t			b_archive,	/* true=back up existing logfile before creating new one, false=overwrite existing */
					gcsl_bool_t			b_async,	/* true=entries are written to log in background, false=entries written immediately */
					gcsl_cstr_t			header_msg
					);

gcsl_error_t	gcsl_log_close(
					gcsl_log_handle_t	handle
					);

/* Basic logging API */
gcsl_error_t	gcsl_log_entry(
					gcsl_log_handle_t	handle,
					gcsl_uint16_t		package_id,
					gcsl_uint32_t		filter_mask,
					gcsl_int32_t		line,
					gcsl_cstr_t			filename,
					gcsl_cstr_t			format,
					...
					);

gcsl_error_t	gcsl_log_ventry(
					gcsl_log_handle_t	handle,
					gcsl_uint16_t		package_id,
					gcsl_uint32_t		filter_mask,
					gcsl_int32_t		line,
					gcsl_cstr_t			filename,
					gcsl_cstr_t			format,
					va_list				argptr
					);

/* API to log or display the error information */
gcsl_error_t	gcsl_log_error(
					gcsl_log_handle_t	handle,
					gcsl_int32_t		line,
					gcsl_cstr_t			filename,
					gcsl_error_t		code,
					gcsl_cstr_t			context_format,
					...
					);

gcsl_error_t	gcsl_log_verror(
					gcsl_log_handle_t	handle,
					gcsl_int32_t		line,
					gcsl_cstr_t			filename,
					gcsl_error_t		code,
					gcsl_cstr_t			context_format,
					va_list				argptr
					);


/* Control functions called during initialization (or at other opportune times). */
/* Control settings are stored on a package-by-package basis. */

gcsl_error_t	gcsl_log_enable(
					gcsl_log_handle_t	handle,
					gcsl_uint16_t		package_id,
					gcsl_uint32_t		category_mask
					);

gcsl_error_t	gcsl_log_enable_global(
					gcsl_log_fn			log_callback,
					gcsl_log_error_fn	log_error_callback,
					gcsl_uint16_t		package_id,
					gcsl_uint32_t		category_mask
					);

gcsl_error_t	gcsl_log_disable(
					gcsl_log_handle_t	handle,
					gcsl_uint16_t		package_id
					);

gcsl_error_t	gcsl_log_disable_global(
					gcsl_uint16_t		package_id
					);

gcsl_error_t	gcsl_log_is_enabled(
					gcsl_log_handle_t	handle,
					gcsl_bool_t*		pb_enabled
					);

gcsl_bool_t		gcsl_log_get_pkg_mask(
					gcsl_log_handle_t	handle,
					gcsl_uint32_t		package_index,
					gcsl_uint32_t*		p_mask
					);

gcsl_error_t	gcsl_log_set_rolling(
					gcsl_log_handle_t	handle,
					gcsl_uint64_t		max_size,	/* bytes. set to 0 to create a new file each time */
					gcsl_bool_t			b_archive	/* true=back up existing logfile before creating new one, false=overwrite existing */
					);

/****** formerly gcsl_error_code_strings.h ****/

/* Return descriptive string associated with package code.
Free the returned string with gcsl_log_free_desc() */
gcsl_cstr_t		gcsl_log_get_package_desc(
					gcsl_uint16_t		package_id
					);

/* Return descriptive string associated with error code */
gcsl_cstr_t		gcsl_log_get_code_desc(
					gcsl_error_t		error_code
					);

/*
wishlist - change name arrays to be direct access, not iterater/comparisons
DONE - max_size checked per write
DONE - in GCSLERR_LOG_ERR check severity bit and ensure GCLS_ERROR is enabled for the packageID
DONE - add header column names on new file creation
DONE - add header entry on log file open (***********)
DONE - ERROR, WARNING, INFO, DEBUG, INTERNAL
DONE - time\tlevel\tpkg\tthread\t__FILE__(__LINE__)\tentry\r\n
DONE - if no pkg name, then pkg id as hex
DONE - ensure hex entries are right number of bytes
DONE - each header value has its' own mask.  GCSL_HEADER_ALL shows them all, GCSL_HEADER_NONE shows none.  GCSL_HEADER_THREAD|GCSL_HEADER_TIME
DONE - if archive option is TRUE, rename old file logfile.1, logfile.2 etc.
DONE - max_size checked per open
DONE - log entry trailing newline is optional
DONE - add get error desc to sdkmgr
*/

#ifdef __cplusplus
}
#endif

#endif /* _GCSL_LOG_H_ */

