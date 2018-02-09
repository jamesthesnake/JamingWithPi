#
# GNSDK Common Build: Platform Detection and Variable Setup
#

#
# required predefined vars
#
ifeq ($(group_name),)
$(error Must set 'group_name' to name this library is a part of (eg: 'gcsl'))
endif
#ifeq ($(library_name),)
#$(error Must set 'library_name' to name of library being built (eg: 'memory'))
#endif
 

#
# Load Platform Variables
#
ifeq ($(GNSDK_TARGET_PLATFORM),)
	include $(build_dir)/platform_detect.mk
endif

include $(build_dir)/platform_vars_$(GNSDK_TARGET_PLATFORM).mk


#
# Platform Variables 
#   These must be defined for all build platforms
#
ifeq (0,1)


#
# File and Target naming
#

#SHARED_LIB_EXT					# file extension for shared library (eg: dll, so, dylib)
#STATIC_LIB_EXT					# file extension for static library (eg: lib, a)
#SHARED_LINK_EXT				# file extension to link against when linking to shared library (eg: lib, so)
#STATIC_LINK_EXT				# file extension to link against when linking to static library (eg: lib, a)
	
#APP_EXE_PATTERN				# pattern of naming for executables (eg: %, %.exe)
#SHARED_LIB_PATTERN				# pattern of naming for shared libraries (eg: libname.so)
#STATIC_LIB_PATTERN				# pattern of naming for static libraries (eg: libname.a)
#SHARED_LINK_PATTERN			# pattern of naming of shared library to link to
#STATIC_LINK_PATTERN			# pattern of naming of static library to link to

#SHARED_LIB_TARGET				# name of build target when building as shared library
#STATIC_LIB_TARGET				# name of build target when building as static library
#SHARED_LINK_TARGET				# name of build target to link against when linking to shared library
#STATIC_LINK_TARGET				# name of build target to link against when linking to static library
	
#IMPLDIR						# name of os platform
#IMPLARCH						# name of cpu architecture

#
# Tool Chain variables
#

#TOOLDIR						# path for toolchain (can be empty, which implies tools are in path)

CC								# C compiler
CCPP							# C++ compiler
LD								# shared library linker
LDS								# static library linker
LINK							# application linker
RC								# resource compiler (Windows only)
AR								# library archiver 
STRIP							# symbol stripper
CP								# file copy command
MV								# file move command

# Compilation Flags 
COUTFLAG						# compiler: output flag
CWARNERR						# compiler: halt on warnings flag (for strict build)
CDEFS							# compiler: additional defines to add to compile command
CFLAGS_DEBUG					# compiler: flags for debug build
CFLAGS_RELEASE					# compiler: flags for release build

# Shared Linker Flags
LDOUTFLAG						# shared linker: output flag
LDFLAGS_DEBUG					# shared linker: flags for debug build
LDFLAGS_RELEASE					# shared linker: flags for release build
LDLIBS_PLATFORM					# shared linker: platform specific libraries to link against
	
# Static Linker Flags
LDSOUTFLAG						# static linker: output flag
LDSFLAGS_DEBUG					# static linker: flags for debug build
LDSFLAGS_RELEASE				# static linker: flags for release build
	
# Application Linker Flags
LINKOUTFLAG						# app linker: output flag 
LINKFLAGS_DEBUG					# app linker: flags for debug build
LINKFLAGS_RELEASE				# app linker: flags for release build
	
# Resource Compiler (Windows Only)
RCOUTFLAG						# output flag
RCFLAGS_DEBUG					# flags for debug build
RCFLAGS_RELEASE					# flags for release build


endif