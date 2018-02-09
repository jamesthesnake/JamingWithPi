#
# GNSDK Common Build: Platform Detection and Variable Setup
#

# Variable Defined:
# GNSDK_BUILD_PLATFORM       - value for platform build is occuring on
# GNSDK_TARGET_PLATFORM      - value for platform target is built for
#


UNAME := $(shell uname)

#
# PLATFORM: MS Windows
#
ifneq ($(findstring CYGWIN, $(UNAME)),)
	GNSDK_BUILD_PLATFORM = windows
endif

#
# PLATFORM: Mac OSX and iOS
#
ifeq ($(UNAME), Darwin)
	GNSDK_BUILD_PLATFORM = macos
endif

#
# PLATFORM: Linux
#
ifeq ($(UNAME), Linux)
	GNSDK_BUILD_PLATFORM = linux
endif

#
# PLATFORM: QNX
#
ifeq ($(UNAME), QNX)
	GNSDK_BUILD_PLATFORM = qnx
endif

#
# PLATFORM: Solaris
#
ifeq ($(UNAME), SunOS)
	GNSDK_BUILD_PLATFORM = solaris
endif

#
# Unsupported Platform
#
ifeq ($(GNSDK_BUILD_PLATFORM),)
$(error Build platform "$(UNAME)" is unsupported)
endif


#
# Set GNSDK_TARGET_PLATFORM for default or cross-compile
#
GNSDK_TARGET_PLATFORM = $(GNSDK_BUILD_PLATFORM)

ifneq ($(filter android,$(ARCH)),)
	GNSDK_TARGET_PLATFORM = android
endif
ifneq ($(filter ios ios_armv6 ios_armv7 ios_armv7s ios_simulator,$(ARCH)),)
	GNSDK_TARGET_PLATFORM = ios
endif
ifneq ($(filter wince wince_sh wince_cp7sh wince_arm wince_cp7arm,$(ARCH)),)
	GNSDK_TARGET_PLATFORM = wince
endif
ifneq ($(filter winrt,$(ARCH)),)
	GNSDK_TARGET_PLATFORM = winrt
endif
ifneq ($(filter qnx qnx_mips-32 qnx_armv7-32 qnx_arm-32 qnx_x86-32,$(ARCH)),)
	GNSDK_TARGET_PLATFORM = qnx
endif
ifneq ($(filter mtk,$(ARCH)),)
	GNSDK_TARGET_PLATFORM = mtk
endif
ifneq ($(filter mgtv,$(ARCH)),)
	GNSDK_TARGET_PLATFORM = mgtv
endif

