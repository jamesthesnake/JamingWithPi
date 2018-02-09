#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Mac OS X
#


ifneq ($(GNSDK_BUILD_PLATFORM),macos)
$(error Building MacOS X target is currently only supported on MacOS clients)
endif


SHARED_LIB_EXT = dylib
STATIC_LIB_EXT = a
SHARED_LINK_EXT = dylib
STATIC_LINK_EXT = a
	
APP_EXE_PATTERN := %
SHARED_LIB_PATTERN := libgroup_library.$(GNSDK_VERSION).$(SHARED_LIB_EXT)
STATIC_LIB_PATTERN := libgroup_library.$(STATIC_LIB_EXT)
SHARED_LINK_PATTERN = $(SHARED_LIB_PATTERN)
STATIC_LINK_PATTERN = $(STATIC_LIB_PATTERN)

SHARED_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LIB_PATTERN)))
STATIC_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LIB_PATTERN)))
SHARED_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LINK_PATTERN)))
STATIC_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LINK_PATTERN)))

#
# Tool Chain variables
#

TOOLDIR=

# Compilation 
CC=$(TOOLDIR)gcc
CCPP=$(TOOLDIR)gcc
COUTFLAG=-o 
CWARNERR=-Werror
CDEFS=-D_THREAD_SAFE -D_REENTRANT -DGCSL_STRICT_HANDLES -DGNSDK_STRICT_HANDLES
CFLAGS_DEBUG=-g $(ARCHFLAGS) -fPIC -funsigned-char -Wall -pedantic -Wextra -Wno-long-long -Wno-variadic-macros -Wno-missing-field-initializers -Wpointer-arith -D_DEBUG 
CFLAGS_RELEASE=-O2 $(ARCHFLAGS) -fPIC -funsigned-char -Wall -pedantic -Wextra -Wno-long-long -Wno-variadic-macros -Wno-missing-field-initializers -Wpointer-arith -DNDEBUG

# Shared Linker
LD=$(TOOLDIR)gcc
LDOUTFLAG=-o 
LDFLAGS_DEBUG=-g $(ARCHFLAGS) -dynamiclib -single_module -compatibility_version $(GNSDK_VERSION) -current_version $(GNSDK_VERSION) -install_name @loader_path/$(SHARED_LIB_TARGET)
LDFLAGS_RELEASE=$(ARCHFLAGS) -dynamiclib -single_module -s -exported_symbols_list $(group_name)_exports.txt -compatibility_version $(GNSDK_VERSION) -current_version $(GNSDK_VERSION) -install_name @loader_path/$(SHARED_LIB_TARGET)
LDLIBS_PLATFORM=
	
# Static Linker Flags
LDS=$(TOOLDIR)ar
LDSOUTFLAG=
LDSFLAGS_DEBUG=rcs
LDSFLAGS_RELEASE=rcs
	
# Application Linker Flags
LINK=$(TOOLDIR)gcc
LINKOUTFLAG=-o 
LINKFLAGS_DEBUG=$(ARCHFLAGS) -lstdc++
LINKFLAGS_RELEASE=$(ARCHFLAGS) -lstdc++
	
# Other Tools
AR=$(TOOLDIR)ar
STRIP=$(TOOLDIR)strip
CP=cp -fp
MV=mv -f

MIN_VERSION_OSX_FLAG = -mmacosx-version-min=10.5 

# check cross-compiling setting
ifeq ($(ARCH),)
	IMPLDIR = mac
	IMPLARCH = x86-64
	ARCHFLAGS = -arch i386 -m64 $(MIN_VERSION_OSX_FLAG)

	# detect PPC
	arch := $(shell uname -m)
	ifneq ($(findstring Power, $(arch)),)
		IMPLARCH = ppc-32
		ARCHFLAGS= -arch ppc $(MIN_VERSION_OSX_FLAG)
	endif
	
else ifneq ($(filter i386 x86-32 x86,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = x86-32
	ARCHFLAGS = -arch i386 -m32 $(MIN_VERSION_OSX_FLAG)

else ifneq ($(filter x86_64 x86-64 x64,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = x86-64
	ARCHFLAGS = -arch i386 -m64 $(MIN_VERSION_OSX_FLAG)

else ifneq ($(filter ppc ppc32 ppc-32,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = ppc-32
	ARCHFLAGS= -arch ppc $(MIN_VERSION_OSX_FLAG)

else ifneq ($(filter ppc64 ppc-64,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = ppc-64
	ARCHFLAGS= -arch ppc64 $(MIN_VERSION_OSX_FLAG)

else
$(error ARCH="$(ARCH)" is unsupported.)
endif

