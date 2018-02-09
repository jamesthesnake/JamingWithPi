#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Android
#

ifeq ($(GNSDK_BUILD_PLATFORM),windows)
	NDK_ROOT := $(strip $$NDK_ROOT)
else
	NDK_ROOT := $(strip $(NDK_ROOT))
endif

ifeq ($(NDK_ROOT),)
$(error Need to set NDK_ROOT environment variable to location of Android NDK)
else
	ifneq ($(words $(NDK_ROOT)),1)
$(info The Android NDK installation path contains spaces: '$(NDK_ROOT)')
$(error Please fix the problem by reinstalling to a different location.)
	endif
	ifneq ($(findstring CYGWIN, $(UNAME)),)
		NDK_ROOT:=$(shell cygpath -u $(NDK_ROOT))
	endif
	# get rid of trailing slash
	NDK_ROOT := $(NDK_ROOT:%/=%)
endif

SYSROOT:=$(NDK_ROOT)/platforms/android-5/arch-arm
ifneq ($(findstring CYGWIN, $(UNAME)),)
	SYSROOT:=$(shell cygpath -m $(SYSROOT))
endif

ifeq ($(GNSDK_BUILD_PLATFORM),macos)
	TOOLDIR=$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.4.3/prebuilt/darwin-x86/bin
else ifeq ($(GNSDK_BUILD_PLATFORM),linux)
	TOOLDIR=$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin
else ifeq ($(GNSDK_BUILD_PLATFORM),windows)
	TOOLDIR=$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.4.3/prebuilt/windows/bin
else
$(error Build system not setup to build on '$(GNSDK_BUILD_PLATFORM)')
endif

SHARED_LIB_EXT = so
STATIC_LIB_EXT = a
SHARED_LINK_EXT = $(STATIC_LIB_EXT)
STATIC_LINK_EXT = $(STATIC_LIB_EXT)

APP_EXE_PATTERN := %
SHARED_LIB_PATTERN := libgroup_library.$(GNSDK_VERSION).$(SHARED_LIB_EXT)
STATIC_LIB_PATTERN := libgroup_library.$(STATIC_LIB_EXT)
SHARED_LINK_PATTERN = $(SHARED_LIB_PATTERN)
STATIC_LINK_PATTERN = $(STATIC_LIB_PATTERN)

STATIC_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LIB_PATTERN)))
SHARED_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LIB_PATTERN)))
STATIC_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LINK_PATTERN)))
SHARED_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LINK_PATTERN)))


IMPLDIR = android
IMPLARCH = arm-32

ARCHFLAGS = -mfpu=vfp -mfloat-abi=softfp -ffunction-sections -funwind-tables -fstack-protector -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wa,--noexecstack -Wno-psabi
LD_ARCHFLAGS = -shared -lc -ldl -lm -lstdc++ 

CC=$(TOOLDIR)/arm-linux-androideabi-gcc --sysroot=$(SYSROOT)
CCPP=$(TOOLDIR)/arm-linux-androideabi-g++ --sysroot=$(SYSROOT) -lsupc++
CFLAGS_DEBUG = -g $(ARCHFLAGS) -DANDROID -D_DEBUG -D_REENTRANT -D_THREAD_SAFE
CFLAGS_RELEASE = -Os -O2 $(ARCHFLAGS) -DANDROID -DNDEBUG -D_REENTRANT -D_THREAD_SAFE
COUTFLAG=-o

LD=$(TOOLDIR)/arm-linux-androideabi-gcc --sysroot=$(SYSROOT)
LDOUTFLAG=-o
LDFLAGS_DEBUG=$(LD_ARCHFLAGS)
LDFLAGS_RELEASE=$(LD_ARCHFLAGS)

LDS=$(TOOLDIR)/arm-linux-androideabi-ar
LDSOUTFLAG=
LDSFLAGS_DEBUG=rcs
LDSFLAGS_RELEASE=rcs

LINK=$(TOOLDIR)/arm-linux-androideabi-gcc --sysroot=$(SYSROOT)
LINKOUTFLAG=-o 
LINKFLAGS_DEBUG=$(LD_ARCHFLAGS)
LINKFLAGS_RELEASE=$(LD_ARCHFLAGS)

AR=$(TOOLDIR)/arm-linux-androideabi-ar

CP=cp -fp
MV=mv -f


