/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

#ifndef _GCSL_TIME_H_
#define _GCSL_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif


#if (defined GCSL_CREATE_IMPORTS)
	#define CENTRALIZED_TIME_API		GCSL_IMPORTED_API
#elif (defined GCSL_CREATE_EXPORTS)
	#define CENTRALIZED_TIME_API		GCSL_EXPORTED_API
#else
	#define CENTRALIZED_TIME_API
#endif

#ifndef GCSL_TIME_TEST
	#ifdef _DEBUG
		#define GCSL_TIME_TEST    1
	#endif
#endif

gcsl_error_t	gcsl_time_initialize		(void);
gcsl_error_t	gcsl_time_shutdown			(void);

gcsl_cstr_t		gcsl_time_get_version		(void);
gcsl_cstr_t		gcsl_time_get_build_date	(void);


/* Time in Microseconds (1,000,000th second) */
typedef	gcsl_uint64_t	gcsl_time_us_t;
/* Time in Milliseconds (1,000th second) */
typedef	gcsl_uint64_t	gcsl_time_ms_t;
/* Time in Seconds (1th second)*/
typedef	gcsl_uint64_t	gcsl_time_s_t;

/*
** Returns highest resolution 'ticks' (in microseconds) since system start
*/
gcsl_time_us_t	gcsl_time_get_ticks			(void);

/* 
** Time APIs return elapsed time since epoch (12:00 Jan 1, 1970)
*/
gcsl_time_s_t	gcsl_time_get_seconds		(void);
gcsl_time_ms_t	gcsl_time_get_milliseconds	(void);
gcsl_time_us_t	gcsl_time_get_microseconds	(void);

#define		GCSL_TIME_MICROSECONDS_PER_SECOND		1000000		/* 1 million microseconds per second */

/* 
 *  gcsl_time formats
*/
#if (defined GCSL_WINDOWS) || (defined GCSL_WINCE)

	#define		GCSL_TIME_FORMAT_WEEK_DATE_TIME				"ddd MMM dd HH:mm:ss yyyy"
	#define		GCSL_TIME_FORMAT_WEEK_DATE_TIME_SIZE		26

	#define		GCSL_TIME_FORMAT_DATE_TIME_BASIC			"yyyyMMddHHmmss"
	#define		GCSL_TIME_FORMAT_DATE_TIME_BASIC_SIZE		22

	#define		GCSL_TIME_FORMAT_YYYYMMDD					"yyyyMMdd"
	#define		GCSL_TIME_FORMAT_YYYYMMDD_SIZE				10

	#define		GCSL_TIME_FORMAT_YYYYMM						"yyyyMM"
	#define		GCSL_TIME_FORMAT_YYYYMM_SIZE				8

	#define		GCSL_TIME_FORMAT_DATE						"yyyy-MM-dd"
	#define		GCSL_TIME_FORMAT_DATE_SIZE					12

	#define		GCSL_TIME_FORMAT_ISO8601					"yyyy-MM-dd HH:mm:ss"
	#define		GCSL_TIME_FORMAT_ISO8601_SIZE				22

	#define		GCSL_TIME_FORMAT_TIMEVAL					"s.u"
	#define		GCSL_TIME_FORMAT_TIMEVAL_SIZE				22

#else

	#define		GCSL_TIME_FORMAT_WEEK_DATE_TIME				"%a %b %d %H:%M:%S %Y"
	#define		GCSL_TIME_FORMAT_WEEK_DATE_TIME_SIZE		26

	#define		GCSL_TIME_FORMAT_DATE_TIME_BASIC			"%Y%m%d%H%M%S"
	#define		GCSL_TIME_FORMAT_DATE_TIME_BASIC_SIZE		22

	#define		GCSL_TIME_FORMAT_YYYYMMDD					"%Y%m%d"
	#define		GCSL_TIME_FORMAT_YYYYMMDD_SIZE				10

	#define		GCSL_TIME_FORMAT_YYYYMM						"%Y%m"
	#define		GCSL_TIME_FORMAT_YYYYMM_SIZE				8

	#define		GCSL_TIME_FORMAT_DATE						"%Y-%m-%d"
	#define		GCSL_TIME_FORMAT_DATE_SIZE					12

	#define		GCSL_TIME_FORMAT_ISO8601					"%Y-%m-%d %H:%M:%S"
	#define		GCSL_TIME_FORMAT_ISO8601_SIZE				22

	#define		GCSL_TIME_FORMAT_TIMEVAL					"s.u"
	#define		GCSL_TIME_FORMAT_TIMEVAL_SIZE				22

#endif

gcsl_error_t	gcsl_time_get_current		(gcsl_cstr_t format, gcsl_char_t* time_buf, gcsl_size_t buf_size);
gcsl_error_t	gcsl_time_format_us			(gcsl_time_us_t us_time, gcsl_bool_t b_local, gcsl_cstr_t format, gcsl_char_t* time_buf, gcsl_size_t buf_size);
gcsl_error_t	gcsl_time_format_ms			(gcsl_time_ms_t ms_time, gcsl_bool_t b_local, gcsl_cstr_t format, gcsl_char_t* time_buf, gcsl_size_t buf_size);
gcsl_error_t	gcsl_time_format_s			(gcsl_time_s_t s_time,   gcsl_bool_t b_local, gcsl_cstr_t format, gcsl_char_t* time_buf, gcsl_size_t buf_size);

gcsl_error_t	gcsl_time_iso8601_to_epoch	(gcsl_cstr_t time, gcsl_time_s_t *epochdatetime);

/*
gcsl_time GNTimestamp
	32-bit time value represented:

Year:  12 bits [0,4096]		- years since 0
Month:  4 bits [0,11]		- months since start of year
Day:    5 bits [0,30]		- days since start of the month
Hour:   5 bits [0,23]		- hours since start of the day (midnight)
Min:    6 bits [0,59]		- minutes since start of the hour
--------------------------
	   32 bits

(note: only has minute resolution)
*/
gcsl_error_t	gcsl_time_gntime_create				(gcsl_uint32_t year, gcsl_uint32_t month, gcsl_uint32_t day, gcsl_uint32_t hour, gcsl_uint32_t min, gcsl_uint32_t* p_gntimestamp);
gcsl_error_t	gcsl_time_gntime_create_from_seconds(gcsl_uint64_t seconds, gcsl_uint32_t* p_gntimestamp);
gcsl_error_t	gcsl_time_gntime_current			(gcsl_uint32_t* p_gntimestamp);
gcsl_error_t	gcsl_time_gntime_delta				(gcsl_uint32_t gntimestamp1, gcsl_uint32_t gntimestamp2, gcsl_int64_t* p_delta_seconds);
gcsl_error_t	gcsl_time_gntime_add				(gcsl_uint32_t gntimestamp1, gcsl_int64_t delta_seconds, gcsl_uint32_t* p_gntimestamp2);

#define	GCSL_GNTIME_YEAR(gntime)	((gntime >> 20) & 0xFFF)
#define	GCSL_GNTIME_MONTH(gntime)	((gntime >> 16) & 0x00F)
#define	GCSL_GNTIME_DAY(gntime)		((gntime >> 11) & 0x01F)
#define	GCSL_GNTIME_HOUR(gntime)	((gntime >> 6)  & 0x01F)
#define	GCSL_GNTIME_MIN(gntime)		((gntime >> 0)  & 0x03F)

#define GCSL_TIME_SECONDS_PER_MIN	(gcsl_uint64_t)(60)
#define GCSL_TIME_SECONDS_PER_HOUR	(gcsl_uint64_t)(60*GCSL_TIME_SECONDS_PER_MIN)
#define GCSL_TIME_SECONDS_PER_DAY	(gcsl_uint64_t)(24*GCSL_TIME_SECONDS_PER_HOUR)
#define GCSL_TIME_SECONDS_PER_YEAR	(gcsl_uint64_t)(365*GCSL_TIME_SECONDS_PER_DAY)
	


typedef gcsl_void_t (GCSL_CALLBACK_API *gcsl_time_marker_status_callback_fn)(const gcsl_void_t* app_data, gcsl_time_us_t time);

CENTRALIZED_TIME_API gcsl_void_t		gcsl_time_marker_initialize	(gcsl_time_marker_status_callback_fn callback_fn);
CENTRALIZED_TIME_API gcsl_void_t		gcsl_time_marker_start		(const gcsl_void_t* app_data, gcsl_void_t** p_marker_data);
CENTRALIZED_TIME_API gcsl_void_t		gcsl_time_marker_end		(gcsl_void_t* marker_data);


#define GCSL_TIME_MARKSTART(app_data)	{ gcsl_void_t* __p_time_marker; gcsl_time_marker_start(app_data, &__p_time_marker);
#define GCSL_TIME_MARKEND				gcsl_time_marker_end(__p_time_marker); }


#ifdef __cplusplus
}
#endif

#endif /* _GCSL_TIME_H_ */
