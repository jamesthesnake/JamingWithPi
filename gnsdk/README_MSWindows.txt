#
# Copyright (c) 2013 Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.
#

GRACENOTE SDK SAMPLE APPLICATIONS ON WINDOWS:

The GNSDK consist of multi-platform shared libraries that provide the services that Gracenote offers to applications. As the libraries are cross-platform, we've strived to make the Gracenote SDK package cross-platform as well—and this is the reason the SDK utilizes GNU Makefiles to build the sample applications.
To get GNU Makefile support on Windows, you need to install and use a publicly available, free, and no licensing-required tool called Cygwin. Cygwin is a Linux-like command-line environment for Windows. Cygwin provides the tools to run makefiles and other scripts used by the Gracenote SDK, however, it does not provide a compiler. For building the sample applications, we require that you use Microsoft Visual Studio, specifically Visual Studio 2005 or Visual Studio 2008.



*******************************************************************************
** 
** Building with Microsoft Visual Studio
**
"Nope, sorry. Not going to do Cygwin. Can't live without my Microsoft Visual Studio!"
We understand it takes a lot to move to a new environment. However, we don't deliver the project files within this package. Here’s how to create projects to build the sample application in Microsoft Visual Studio; note that all paths in the following procedure are relative to the project folder.
To create new solution and project for a console application: 
1. Add main.c and any other sample source files
2. Add the following include paths:
   ../include
   ../include/win_x86-32 (only for 32-bit systems)
   ../include/win_x86-64 (only for 64-bit systems)
3. Add the following library paths:
  ../lib/win_x86-32 (only for 32-bit systems)
  ../lib/win_x86-64 (only for 64-bit systems)
4. Set the sample application to link to the Gracenote SDK library files found in the lib directory set in step 3.
5. Set your client ID and client ID tag values in the command line argument setting for the debugger.
This procedure should be applicable to most cases; any other requirements are specific to your environment.

*******************************************************************************
**
** Building With Cygwin
**

INSTALLING CYGWIN

Installing Cygwin involves specifying configuration options from the Cygwin setup.exe and adding a Cygwin directory to the PATH variable.

To install Cygwin:

1. Navigate your browser to: http://cygwin.com/
2. Download the setup.exe to your desktop (keep it handy, for future updates).
3. Run the setup.exe, and configure the following options:
   a. Page 1: Cygwin Setup introduction. Click Next.
   b. Page 2: Choose Installation Type. Choose Install from Internet and click Next.
   c. Page 3: Choose Installation Directory. Specify a Root Directory of c:\cygwin and Install For All users. Click Next.
   d. Page 4: Select Local Package Directory. Specify a Local Package Directory of c:\cygwin\archive.
   e. Page 5: Select Connection Type. Choose the appropriate option for your configuration.
   f. Page 6: Choose Download Site(s). If you have correctly set page 5, a list of servers displays. Choose http://mirrors.kernel.org or one closer to your region, and click Next. The download progress displays. 
   g. Page 7: Select Packages. The available downloaded packages are displayed. Note: The package list is sorted by the Package column; use the Search field in the upper left to locate specific packages.
   i. Maximize the installation window and click the View button in the upper right to expand the package tree. Required packages are selected by default. 
   ii. To select a package to install, click the word Skip in the New column.  As you continue clicking, it cycles treturning back to Skip. Select these additional packages:
   - Devel/binutils
   - Devel/make
4. Click Next to begin the install.
5. When all packages have been installed, select Create an Icon on Desktop and Add Icon to Start Menu, and click Finish. This completes installing Cygwin from the setup.exe. 
6. Finally, add c:\cygwin\bin to the system PATH environment variable. 

BUILDING SAMPLES

NOTE: The provided makefiles require Visual Studio 2012 or Visual Studio 2010/2008 (older Visual Studio versions probably won’t work). Each sample application's makefile includes the GNSDK Build (makefile_platforms.inc) and the Common GCSL Library Sample (makefile_sample.inc) makefiles, which configure the sample application with the library files and variables needed to run on the target platform.

Before running make from the Cygwin command shell, the location of the Visual Studio compiler must be set. To do this, edit the cygwin.bat file as shown below to run the appropriate Visual Studio configuration file.

*******************************************************************************
@echo off

:: Change this call based on the version of Visual Studio being used
:: If using Visual Studio 2008, call "%VS90COMNTOOLS%\.."
:: If using Visual Studio 2010, call "%VS100COMNTOOLS%\.."
:: If using Visual Studio 2012, call "%VS110COMNTOOLS%\.."
call "%VS100COMNTOOLS%\..\..\VC\vcvarsall.bat" x86


C:
chdir C:\cygwin\bin

bash --login
*******************************************************************************

To make the sample applications:

1. Launch a Cygwin shell by running the desktop shortcut or by directly executing cygwin.bat. 
2. Use the shell command line to navigate to the specific GNSDK library sample application location to be built. Generally, this path is: .../gndsk_<version>_<date>/_sample/<library>
3. Run make to build the sample applications via the Cygwin shell.

This creates a sample.exe file (and generally other output files) in the same directory. Object files from the compiler are stored in an output directory.

Send Gracenote SDK feedback to gnsdk_feedback@gracenote.com
