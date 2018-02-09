#
# Copyright (c) 2013 Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.
#


GRACENOTE SDK SAMPLE APPLICATIONS:

As an aid to understanding correct GNSDK API usage, we provide a working, command-line based sample application for each library, the “main.c” file. This file uses only ANSI C and C Standard library functions. Though you may find running the application to be helpful, it is probably more beneficial to step through its execution with a debugger to observe its internal library usage.
Note: The sample application code is designed strictly for simplicity and clarity, and not for realistic applicability to any application-specific needs—this means you should not copy the source verbatim into your application, as it probably does not meet your specific implementation requirements.

SAMPLE APPLICATION FOLDER CONTENTS:

main.c:		C source for sample application
makefile:	GNU Make makefiles for building sample applications
data/:		Folder of data for sample application; present only for certain libraries

BUILDING SAMPLE APPLICATIONS

Requirements:

• GNU Make 3.81 or above.
• A command-line environment supported by the target platform, since the target sample application is built via the included makefiles.

Windows platform developers must first install Cygwin. For installation instructions, refer to the README_windows.txt file included in the package.

Building a Sample Application:
1. Open a shell.
2. Navigate to the directory of the GNSDK sample application to be built.
3. Type “make.”

Completion of a successful build results in a sample.exe application and possibly other output files created within the same directory, and object files from the compiler created in the _output/ directory.

Running a Sample Application:

Running a sample application requires the CLIENT ID, CLIENT ID TAG, and LICENSE data Gracenote provided to you with this SDK. The Gracenote SDKs and the sample applications cannot successfully execute without these identifiers. For the LICENSE data, copy the contents to a text file, which will be read by the sample application.

Type the command in the following format:

./sample.exe <clientid> <clientid_tag> <license_file>

For example:

./sample.exe 12345678 ABCDEF0123456789ABCDEF012345679 license.txt

Each sample application output varies, but in general, you should see the application performing online querying and displaying scrolling output. Redirect the output to a file to capture it for viewing. The application also creates a “sample.log” file, which logs any errors that may have occurred. 

Send Gracenote SDK feedback to gnsdk_feedback@gracenote.com	


