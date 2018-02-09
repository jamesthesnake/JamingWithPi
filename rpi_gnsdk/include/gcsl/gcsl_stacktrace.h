/*
 * Copyright (c) 2011 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * gcsl_stacktrace.h - Function prototypes for doing simple stack tracing
 *    while the code is running. Implementation of these functions is
 *    up to the developer. These functions are part of the abstract layer
 *    routines.
 *
 *    Internal stacktracing will be compiled in only if GCSL_STACKTRACE is
 *    defined at compile time.
 */

#ifndef _GCSL_STACKTRACE_H_
#define _GCSL_STACKTRACE_H_

#ifdef __cplusplus
extern "C" {
#endif 


/*
 * Function prototypes
 */
gcsl_error_t    gcsl_stacktrace_initialize		(void);
gcsl_error_t    gcsl_stacktrace_shutdown		(void);
gcsl_cstr_t		gcsl_stacktrace_get_version		(void);
gcsl_cstr_t		gcsl_stacktrace_get_build_date	(void);


/* set signal handler */
gcsl_void_t		gcsl_stacktrace_set_sighandler	(void);

/* capture current stack */
gcsl_uint32_t	gcsl_stacktrace_get(gcsl_void_t** frames, gcsl_uint32_t num_frames);
/* display given stack to stderr */
gcsl_void_t		gcsl_stacktrace_display(gcsl_void_t** frames, gcsl_uint32_t num_frames);
/* display current stack to stderr */
gcsl_void_t		gcsl_stacktrace_display_current	(void);


/*
 * Stack Usage Measuring
 */
#ifndef GCSL_STACKTRACE_ENABLE_MEASURE
	#ifdef _DEBUG
		#define GCSL_STACKTRACE_ENABLE_MEASURE    0
	#endif
#endif

#if GCSL_STACKTRACE_ENABLE_MEASURE

#if (defined GCSL_CREATE_IMPORTS)
	#define CENTRALIZED_STACK_API		GCSL_IMPORTED_API
#elif (defined GCSL_CREATE_EXPORTS)
	#define CENTRALIZED_STACK_API		GCSL_EXPORTED_API
#else
	#define CENTRALIZED_STACK_API		GCSL_EXPORTED_API
#endif

gcsl_void_t CENTRALIZED_STACK_API		gcsl_stacktrace_do_measure		(gcsl_char_t* stack_bottom);
gcsl_void_t CENTRALIZED_STACK_API		gcsl_stacktrace_display_report	(void);

#define GCSL_DOSTACKTRACE_INIT()		{ gcsl_char_t _stacktrace_current; gcsl_stacktrace_do_measure(&_stacktrace_current); }
#define GCSL_DOSTACKTRACE()				{ gcsl_char_t _stacktrace_current; gcsl_stacktrace_do_measure(&_stacktrace_current); }
#define GCSL_DOSTACKTRACE_REPORT()		gcsl_stacktrace_display_report()

#else /* GCSL_STACKTRACE_ENABLE_MEASURE */

#define GCSL_DOSTACKTRACE_INIT()
#define GCSL_DOSTACKTRACE()
#define GCSL_DOSTACKTRACE_REPORT()

#endif /* GCSL_STACKTRACE_ENABLE_MEASURE */


#ifdef __cplusplus
}
#endif 


#endif  /* _GCSL_STACKTRACE_H_ */

