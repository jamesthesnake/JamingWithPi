/*
 * Copyright (c) 2012 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/

 /*
 *	Name: Direct Logging to a Callback
 *
 *	Description:
 *		The following pseudo-code demonstrates how to configure the GNSDK logging functionality with a custom callback that
 *		enables the application complete control over how logging messages are captured.
 *		The example shows setting up a logging callback that echoes the messages to the system log (Syslog). When using
 *		the GNSDK to log application-level messages and errors, the GNSDK Manager controls all of GNSDK's logging,
 *		from the core Gracenote Client Standard Library (GCSL) level, through the higher level SDKs (GNSDK) and up
 *		through any application logging.
 *		The most typical use case for GNSDK logging is to configure a single log file to capture all logged messages
 *		and errors. You can control the detail level of the run time logs to include specific information (such as
 *		logging only errors or full debug information). However, you can also direct the GNSDK to allow a logging
 *		callback, enabling you to determine how best to capture the specific logged message(s). In this callback,
 *		the application can write to its own log files or pass the messages to an external logging framework, such
 *		as the Unix Syslog or the Windows Event Log. Note that you can configure the GNSDK to have any number of
 *		logging destinations (0-n log files and 0-n log callbacks). You may decide to send important error messages
 *		to the Syslog while specifying a run-time-enabled file to capture more detailed information during development
 *		or bug tracking.
 *
 *	Steps:
 *		01. Open the Syslog.
 *		02. Initialize GNSDK.
 *		03. Register callback with the GNSDK Manager.
 *		04. Perform the application function.
 *		05. Shut down GNSDK.
 *		06. Close the Syslog.
 *
 *	Command-line Syntax:
 *		sample.exe client_id client_id_tag license
*/


#include "gnsdk.h"

//**
//** Standard C headers that are used by the sample application, but not required for GNSDK
//**
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <syslog.h>


//******************************************************************
//**
//**   _ L O G G I N G _ C A L L B A C K _ F N
//**
//**   Define the logging callback
//**
//******************************************************************

static gnsdk_void_t GNSDK_CALLBACK_API
_logging_callback_fn(
					 const gnsdk_void_t*     user_data,
					 gnsdk_uint16_t    package_id,
					 gnsdk_uint32_t    mask,
					 gnsdk_cstr_t      format,
					 va_list           argptr
					 )
{
	 //**
	 //** Map the GNSDK level to the Syslog level and pass along the message
	 //**
	if (mask & GNSDK_LOG_LEVEL_ERROR)
	{
		vsyslog(LOG_ERR, format, argptr);
	}
	else if (mask & GNSDK_LOG_LEVEL_WARNING)
	{
		vsyslog(LOG_WARNING, format, argptr);
	}
	else if (mask & GNSDK_LOG_LEVEL_INFO)
	{
		vsyslog(LOG_INFO, format, argptr);
	}
	else if (mask & GNSDK_LOG_LEVEL_DEBUG)
	{
		vsyslog(LOG_DEBUG, format, argptr);
	}
} //** _logging_callback_fn()


//******************************************************************
//**
//**   M A I N
//**
//******************************************************************
int main(int argc, char* argv[])
{
	gnsdk_error_t		error				= GNSDK_SUCCESS;

	//**
	//** Open the Syslog
	//**
	// openlog ("GNSDK App", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	//** Initialize GNSDK
	//** ...

	//**
	//** Register our callback with the GNSDK Manager
	//**
	error = gnsdk_manager_logging_enable_callback(
				_logging_callback_fn,
				GNSDK_NULL,           // Optional data passed to the callback
				GNSDK_LOG_PKG_ALL,    // Messages from all libraries
				GNSDK_LOG_LEVEL_ALL   // Message of all levels
			);
	//...

	//**
	//** Perform the app function
	//**
	//** do_stuff();

	// ...

	//**
	//** Shut down GNSDK
	//**
	// ...

	//**
	//** Close the Syslog
	//**
	// closelog();

	return 0;
}