#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Linux
#


ifneq ($(GNSDK_BUILD_PLATFORM),linux)
$(error Building Linux target is currently only supported on Linux clients)
endif


SHARED_LIB_EXT = so
STATIC_LIB_EXT = a
SHARED_LINK_EXT = $(STATIC_LIB_EXT)
STATIC_LINK_EXT = $(STATIC_LIB_EXT)

APP_EXE_PATTERN := %
SHARED_LIB_PATTERN := libgroup_library.$(SHARED_LIB_EXT).$(GNSDK_VERSION)
STATIC_LIB_PATTERN := libgroup_library.$(STATIC_LIB_EXT)
SHARED_LINK_PATTERN = $(SHARED_LIB_PATTERN)
STATIC_LINK_PATTERN = $(STATIC_LIB_PATTERN)

STATIC_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LIB_PATTERN)))
SHARED_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LIB_PATTERN)))
STATIC_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LINK_PATTERN)))
SHARED_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LINK_PATTERN)))

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
LDFLAGS_DEBUG=$(LD_ARCHFLAGS)
LDFLAGS_RELEASE=$(LD_ARCHFLAGS)
LDLIBS_PLATFORM = -lpthread -lm -ldl -Wl,-soname,$(SHARED_LIB_TARGET)

# Static Linker Flags
LDS=$(TOOLDIR)ar
LDSOUTFLAG=
LDSFLAGS_DEBUG=rcs
LDSFLAGS_RELEASE=rcs

# Application Linker Flags
LINK=$(TOOLDIR)gcc
LINKOUTFLAG=-o 
LINKFLAGS_DEBUG=$(ARCHFLAGS) -Wl,-rpath,'$$ORIGIN'
LINKFLAGS_RELEASE=$(ARCHFLAGS) -Wl,-rpath,'$$ORIGIN'

# Other Tools
AR=$(TOOLDIR)ar
STRIP=$(TOOLDIR)strip
CP=cp -fp
MV=mv -f


# check cross-compiling setting
ifeq ($(ARCH),)
	# detect 64/32-bit linux
	arch := $(shell uname -m)
	ifeq ($(arch), x86_64)
		ARCH=x86_64
	else
		ARCH=x86
	endif
endif
	
ifneq ($(filter i386 x86_32 x86-32 x86,$(ARCH)),)
	IMPLDIR = linux
	IMPLARCH = x86-32
	ARCHFLAGS = -m32
	LD_ARCHFLAGS = -m32 -shared -Wl,-rpath,'$$ORIGIN'

else ifneq ($(filter x86_64 x86-64 x64,$(ARCH)),)
	IMPLDIR = linux
	IMPLARCH = x86-64
	ARCHFLAGS = -m64
	LD_ARCHFLAGS = -m64 -shared -Wl,-rpath,'$$ORIGIN'

# check AISIN-AW SDK is available
else ifneq ($(filter arm-32aw,$(ARCH)),)
	CC=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-gcc-4.4.1
	LD=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-gcc-4.4.1
	LINK=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-gcc-4.4.1
	LDS=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-ar
	STRIP=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-strip
	IMPLDIR = linux
	IMPLARCH = arm-32aw
	ARCHFLAGS = -tarmv6 -fexpensive-optimizations -fomit-frame-pointer -frename-registers -O0 -g -D_GNU_SOURCE -Wcast-align -I/opt/default-rootfs-image/usr/include
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN',-O0 -L$(WORK_ROOT)/runtime/lib/$(TARGET_CPU) -L$(WORK_ROOT)/runtime/bin/$(TARGET_CPU) --sysroot=/opt/default-rootfs-image -L/opt/default-rootfs-image/lib  -Wl,-rpath-link,/opt/default-rootfs-image/lib -L/opt/default-rootfs-image/usr/lib -Wl,-rpath-link,/opt/default-rootfs-image/usr/lib -L/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/lib -Wl,-rpath-link,/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/lib -L/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/usr/lib -Wl,-rpath-link,/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/usr/lib
	LDLIBS_PLATFORM = -lpthread -lm -ldl
	LINKLIBS_PLATFORM =
	#STATIC = static

else ifneq ($(filter arm arm-32,$(ARCH)),)
	CC=arm-none-linux-gnueabi-gcc
	CCPP=arm-none-linux-gnueabi-gcc
	LD=arm-none-linux-gnueabi-gcc
	LINK=arm-none-linux-gnueabi-gcc
	LDS=arm-none-linux-gnueabi-ar
	STRIP=arm-none-linux-gnueabi-strip
	IMPLDIR = linux
	IMPLARCH = arm-32
	ARCHFLAGS =
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN'
	LDLIBS_PLATFORM = -lpthread -lm -ldl
	LINKLIBS_PLATFORM =
	#STATIC = static

else ifneq ($(filter mips32 mips32-el mips-32el,$(ARCH)),)
	IMPLDIR=linux
	IMPLARCH=mips-32EL
	TOOLDIR=/usr/local/CodeSourcery/bin
	#STATIC = static
	
	CC=$(TOOLDIR)/mips-linux-gnu-gcc
	CCPP=$(TOOLDIR)/mips-linux-gnu-gcc
	LD=$(TOOLDIR)/mips-linux-gnu-gcc
	LDS=$(TOOLDIR)/mips-linux-gnu-ar
	AR=$(TOOLDIR)/mips-linux-gnu-ar
	STRIP=$(TOOLDIR)/mips-linux-gnu-strip
	
	ARCHFLAGS = -march=mips32 -EL -mhard-float 

else ifneq ($(filter sh sh-32,$(ARCH)),)
	CC=sh-linux-gnu-gcc
	LD=sh-linux-gnu-gcc
	LINK=sh-linux-gnu-gcc
	LDS=sh-linux-gnu-ar
	STRIP=sh-linux-gnu-strip
	IMPLDIR = linux
	IMPLARCH = sh-32
	ARCHFLAGS =
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN'
	LDLIBS_PLATFORM = -lpthread -lm -ldl
	LINKLIBS_PLATFORM =
	#STATIC = static	
else
$(error ARCH="$(ARCH)" is unsupported.)
endif


