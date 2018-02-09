#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Mac iOS
#


ifneq ($(GNSDK_BUILD_PLATFORM),macos)
$(error Building iOS target is currently only supported on MacOS clients)
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
CFLAGS_DEBUG=-g $(ARCHFLAGS) -fPIC -funsigned-char -Wall -Wformat -Wpointer-arith -D_DEBUG 
CFLAGS_RELEASE=-O2 $(ARCHFLAGS) -fPIC -funsigned-char -Wall -Wformat -Wpointer-arith -DNDEBUG

# Shared Linker
LD=$(TOOLDIR)gcc
LDOUTFLAG=-o 
LDFLAGS_DEBUG=$(ARCHFLAGS) -dynamiclib -single_module -compatibility_version $(GNSDK_VERSION) -current_version $(GNSDK_VERSION) -install_name @loader_path/$(SHARED_LIB_TARGET)
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
LINKFLAGS_DEBUG=$(ARCHFLAGS)
LINKFLAGS_RELEASE=$(ARCHFLAGS)
	
# Other Tools
AR=$(TOOLDIR)ar
STRIP=$(TOOLDIR)strip
CP=cp -fp
MV=mv -f

# IOS DevRoot
DEVROOT_IOS = $(shell xcode-select -print-path)/Platforms/$(PLATFORM_IOS).platform/Developer

# check cross-compiling setting
ifeq ($(ARCH),ios_armv6)
	PLATFORM_IOS = iPhoneOS
	IMPLDIR = ios
	IMPLARCH = armv6-32
	TOOLDIR = $(DEVROOT_IOS)/usr/bin/
	ARCHFLAGS = -arch armv6 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static
	
else ifeq ($(ARCH),ios_armv7)
	PLATFORM_IOS = iPhoneOS
	IMPLDIR = ios
	IMPLARCH = armv7-32
	TOOLDIR = $(DEVROOT_IOS)/usr/bin/
	ARCHFLAGS = -arch armv7 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static
	
else ifeq ($(ARCH),ios_armv7s)
	PLATFORM_IOS = iPhoneOS
	IMPLDIR = ios
	IMPLARCH = armv7s-32
	TOOLDIR = $(DEVROOT_IOS)/usr/bin/
	ARCHFLAGS = -arch armv7s -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static
	
else ifeq ($(ARCH),ios_simulator)
	PLATFORM_IOS = iPhoneSimulator
	IMPLDIR = ios
	IMPLARCH = x86-32
	TOOLDIR = $(DEVROOT_IOS)/usr/bin/
	ARCHFLAGS = -arch i386 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static
	
else
$(error ARCH="$(ARCH)" is unsupported. Try ios_armv6, ios_armv7, ios_armv7s, ios_simulator.)
endif

# check IOS SDK is available
MIN_VERSION_IOS = 3.2
MAX_VERSION_IOS = 6.0
SDKROOT_IOS = $(DEVROOT_IOS)/SDKs/$(PLATFORM_IOS)$(MAX_VERSION_IOS).sdk

# check 6.0 SDK is available
ifeq ($(wildcard $(SDKROOT_IOS)),)
	# then check 5.0 SDK is available
	MAX_VERSION_IOS = 5.0
	ifeq ($(wildcard $(SDKROOT_IOS)),)
		# fall back to 4.2 SDK
		MAX_VERSION_IOS = 4.2
		ifeq ($(wildcard $(SDKROOT_IOS)),)
# if still not available, error
$(error Could not locale suitable iPhone development SDK)
		endif
	endif
endif
	
