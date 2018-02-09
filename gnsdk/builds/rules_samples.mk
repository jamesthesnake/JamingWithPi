#
# common application makefile
#

ifeq ($(appname),)
$(error No target application name has been defined. Set 'appname=')
endif

group_name = group
library_name = library

APP_TARGET = $(patsubst %,$(APP_EXE_PATTERN),$(appname))

ifneq "$(wildcard ../../builds )" ""
sdk_version = $(build_dir)/../version
else
sdk_version = $(build_dir)/../version/csdk-version
endif
GNSDK_VERSION := $(shell cat $(sdk_version) | cut -d"." -f 1,2,3)

#
# includes
#
include $(build_dir)/platform_vars.mk

ifeq ($(filter clean distclean,$(MAKECMDGOALS)),)
	include $(build_dir)/gather_sources.mk

	ifeq ($(words $(objects)), 0)
$(error	NO SOURCES FOUND for $(APP_TARGET) on $(IMPLDIR)_$(IMPLARCH))
	endif
endif


#
# build system vars
#
BUILD_CONFIGS=debug release
OUTPUT_DIR=_output/$(IMPLDIR)_$(IMPLARCH)

ifneq "$(wildcard ../../builds )" ""
GNSDK_INSTALL_DIR=$(build_dir)/..
else
GNSDK_INSTALL_DIR=$(build_dir)/../install/common
endif

#
# set vars for target build configuration
#

# CFLAGS: externally set flags
# CDEFS: externally set defines
# CFLAGS_COMMON: common to debug and release
# CFLAGS_DEBUG: debug specific flags
# CFLAGS_RELEASE: release specific flags
# CFLAGS_LIB: any library specific flags
CFLAGS_COMMON = $(CFLAGS_LIB) $(CFLAGS_SDK) $(CDEFS)
LDFLAGS_COMMON =
LDSFLAGS_COMMON =
LINKFLAGS_COMMON =
RCFLAGS_COMMON =

#static = build against static libs
ifeq ($(filter static, $(MAKECMDGOALS)), static)
	STATIC = static
endif

CFLAGS_ALL_DEBUG = $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_COMMON)
LDFLAGS_ALL_DEBUG = $(LDFLAGS) $(LDFLAGS_DEBUG) $(LDFLAGS_COMMON)
LDSFLAGS_ALL_DEBUG = $(LDSFLAGS) $(LDSFLAGS_DEBUG) $(LDSFLAGS_COMMON)
LINKFLAGS_ALL_DEBUG = $(LINKFLAGS) $(LINKFLAGS_DEBUG) $(LINKFLAGS_COMMON)
RCFLAGS_ALL_DEBUG = $(RCFLAGS_DEBUG) $(RCFLAGS_COMMON)

CFLAGS_ALL_RELEASE = $(CFLAGS) $(CFLAGS_RELEASE) $(CFLAGS_COMMON) 
LDFLAGS_ALL_RELEASE = $(LDFLAGS) $(LDFLAGS_RELEASE) $(LDFLAGS_COMMON)
LDSFLAGS_ALL_RELEASE = $(LDSFLAGS) $(LDSFLAGS_RELEASE) $(LDSFLAGS_COMMON)
LINKFLAGS_ALL_RELEASE = $(LINKFLAGS) $(LINKFLAGS_RELEASE) $(LINKFLAGS_COMMON)
RCFLAGS_ALL_RELEASE = $(RCFLAGS_RELEASE) $(RCFLAGS_COMMON)


#
# vars based on target build configuration
#
ifneq "$(wildcard ../../builds )" ""
	GNSDK_INCLUDE = $(GNSDK_INSTALL_DIR)/include
else
	GNSDK_INCLUDE = $(GNSDK_INSTALL_DIR)/$(BUILD_CONFIG)/include
endif
BUILD_OUTPUT= $(OUTPUT_DIR)/$(BUILD_CONFIG)

ifeq ($(STATIC),static)
	ifneq "$(wildcard ../../builds )" ""
		GNSDK_LIBPATH = $(GNSDK_INSTALL_DIR)/lib_static/$(IMPLDIR)_$(IMPLARCH)
	else
		GNSDK_LIBPATH = $(GNSDK_INSTALL_DIR)/$(BUILD_CONFIG)/lib_static/$(IMPLDIR)_$(IMPLARCH)
	endif
	GNSDK_LINKPATTERN = $(subst group,gnsdk,$(subst library,%,$(STATIC_LINK_PATTERN)))
	GNSDK_LIBPATTERN = $(subst group,gnsdk,$(subst library,%,$(STATIC_LIB_PATTERN)))
else
	ifneq "$(wildcard ../../builds )" ""
		GNSDK_LIBPATH = $(GNSDK_INSTALL_DIR)/lib/$(IMPLDIR)_$(IMPLARCH)
	else
		GNSDK_LIBPATH = $(GNSDK_INSTALL_DIR)/$(BUILD_CONFIG)/lib/$(IMPLDIR)_$(IMPLARCH)
	endif
	GNSDK_LINKPATTERN = $(subst group,gnsdk,$(subst library,%,$(SHARED_LINK_PATTERN)))
	GNSDK_LIBPATTERN = $(subst group,gnsdk,$(subst library,%,$(SHARED_LIB_PATTERN)))
endif

GNSDK_LINKDEPS = $(patsubst %,$(GNSDK_LINKPATTERN),$(sdkdepends))
GNSDK_LIBDEPS = $(patsubst %,$(GNSDK_LIBPATTERN),$(sdkdepends))

#
# include vars
#
LOCAL_INCLUDE=_include
CINCLUDES = -I$(LOCAL_INCLUDE) -I$(IMPLDIR) -I$(GNSDK_INCLUDE) -I$(GNSDK_INCLUDE)/$(IMPLDIR)_$(IMPLARCH)
CINCLUDES += $(addprefix -I,$(extra_srcs) $(extra_srcs)/$(IMPLDIR))


#
# gather source files for project
#
ifeq ($(GNSDK_TARGET_PLATFORM),windows)
	ver_resource := $(IMPLDIR)/gnsdk_$(sdkname)_version.rc
endif


ifeq ($(filter $(ver_header), $(headers)),)
	headers +=$(ver_header)
endif

src_headers = $(filter-out $(ver_header), $(headers))

ifeq ($(filter clean distclean, $(MAKECMDGOALS)),)
	gnsdk_headers := $(info GNSDK Headers...) $(wildcard $(GNSDK_INCLUDE)/*.h) $(wildcard $(GNSDK_INCLUDE)/$(IMPLDIR)_$(IMPLARCH)/*.h)
	local_headers := $(info Local Headers...) $(notdir $(wildcard $(LOCAL_INCLUDE)/*.h))
endif

#
# set known dependencies
#
ifeq ($(platformlibs),)
	ifeq ($(IMPLDIR), win)
		platformlibs += advapi32.lib ws2_32.lib
	else ifeq ($(IMPLDIR), linux)
		platformlibs += -lstdc++ -lpthread -ldl
	else ifeq ($(IMPLDIR), mac)
		platformlibs += -lstdc++ -lpthread -ldl
	else ifeq ($(IMPLDIR), wince)
		platformlibs += coredll.lib corelibc.lib 
		ifneq ($(filter socket,$(gcsl_libdeps)),)
			platformlibs += ws2.lib
		endif
		LINKFLAGS_ALL_DEBUG += -SUBSYSTEM:CONSOLE
		LINKFLAGS_ALL_RELEASE += -SUBSYSTEM:CONSOLE
	endif
endif

#
# targets and commands
#
.PHONY: clean distclean all showinfo $(BUILD_CONFIGS)

real_goals=$(filter-out static,$(MAKECMDGOALS))
ifeq ($(real_goals),)
	real_goals=debug
endif

debug: BUILD_CONFIG=debug
debug: CFLAGS_ALL=$(CFLAGS_ALL_DEBUG)
debug: LDFLAGS_ALL=$(LDFLAGS_ALL_DEBUG)
debug: LINKFLAGS_ALL=$(LINKFLAGS_ALL_DEBUG)
debug: RCFLAGS_ALL=$(RCFLAGS_ALL_DEBUG)
debug: PDB_NAME=./$(appname).pdb
debug: clean-debug ./$(APP_TARGET)-debug $(addprefix ./,$(GNSDK_LIBDEPS))
	$(info )
	$(info **** ./$(APP_TARGET) up to date.)
	$(info )

release: BUILD_CONFIG=release
release: CFLAGS_ALL=$(CFLAGS_ALL_RELEASE)
release: LDFLAGS_ALL=$(LDFLAGS_ALL_RELEASE)
release: LINKFLAGS_ALL=$(LINKFLAGS_ALL_RELEASE)
release: RCFLAGS_ALL=$(RCFLAGS_ALL_RELEASE)
release: PDB_NAME=./$(appname).pdb
release: clean-release ./$(APP_TARGET)-release $(addprefix ./,$(GNSDK_LIBDEPS))
	$(info )
	$(info **** ./$(APP_TARGET) up to date.)
	$(info )


all: debug release

static: $(real_goals)
	$(info )
	$(info Static build complete)
	$(info )

#
# link target library with created output and dependant libs
#

mkdir_target = $(sort $(dir $(addprefix $(OUTPUT_DIR)/$1/,$(objects))))

$(call mkdir_target,debug) $(call mkdir_target,release):
	mkdir -p $@


#$(call make_target_requisites,outdir)
make_target_requisites =  $(objects_a) $(call mkdir_target,$1) $(addprefix $(OUTPUT_DIR)/$1/,$(objects)) $(GNSDK_LINKDEPS) | showinfo


./$(APP_TARGET)-debug: $(call make_target_requisites,debug)
	$(info )
	$(LINK) $(LINKFLAGS_ALL) $(LINKOUTFLAG)$(APP_TARGET) $(addprefix $(OUTPUT_DIR)/debug/,$(objects)) $(GNSDK_LINKDEPS) $(objects_lib_debug) $(platformlibs)

./$(APP_TARGET)-release: $(call make_target_requisites,release)
	$(info )
	$(LINK) $(LINKFLAGS_ALL) $(LINKOUTFLAG)$(APP_TARGET) $(addprefix $(OUTPUT_DIR)/release/,$(objects)) $(GNSDK_LINKDEPS) $(objects_lib_release) $(platformlibs)

ifneq ($(GNSDK_LINKDEPS),$(GNSDK_LIBDEPS))
$(GNSDK_LINKDEPS):
	$(CP) $(GNSDK_LIBPATH)/$@ .
endif

$(addprefix ./,$(GNSDK_LIBDEPS)):
	$(CP) $(GNSDK_LIBPATH)/$(@F) $@


#
# compile various sources for target library
#
#$(call make_compile_requisites,outdir)
make_compile_requisites = $(headers) $(gnsdk_headers) $(gcsl_headers) | showinfo

$(OUTPUT_DIR)/debug/%.o: %.c $(call make_compile_requisites,debug)
	$(CC) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/debug/%.opp: %.cpp $(call make_compile_requisites,debug)
	$(CCPP) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/debug/%.om: %.m $(call make_compile_requisites,debug)
	$(CCPP) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/debug/%.omm: %.mm $(call make_compile_requisites,debug)
	$(CCPP) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/release/%.o: %.c $(call make_compile_requisites,release)
	$(CC) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/release/%.opp: %.cpp $(call make_compile_requisites,release)
	$(CCPP) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/release/%.om: %.m $(call make_compile_requisites,release)
	$(CCPP) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/release/%.omm: %.mm $(call make_compile_requisites,release)
	$(CCPP) $(CFLAGS_ALL) $(CINCLUDES) -c $< $(COUTFLAG)$@

$(OUTPUT_DIR)/debug/%.res: %.rc $(headers)
	@mkdir -p $(@D)
	$(RC) $(RCFLAGS_ALL) $(RCOUTFLAG)$@ $<

$(OUTPUT_DIR)/release/%.res: %.rc $(headers)
	@mkdir -p $(@D)
	$(RC) $(RCFLAGS_ALL) $(RCOUTFLAG)$@ $<
	
run: debug
	./$(APP_TARGET)

#
# Cleanup
#
distclean clean:
	$(RM) $(APP_TARGET)
	$(RM) $(GNSDK_LINKDEPS)
	if [ -d _output ]; then $(RM) -r _output; fi

clean-%:
	if [ -d _output/$(IMPLDIR)_$(IMPLARCH)/$* ]; then $(RM) -r _output/$(IMPLDIR)_$(IMPLARCH)/$*; fi

#
# Show info
#

showinfo:
	@echo
	@echo "***********************************************"
	@echo PLATFORM\ : $(IMPLDIR)_$(IMPLARCH)
	@echo TARGET\ \ \ : ./$(APP_TARGET) 
	@echo SOURCES\ \ : $(sources) $(headers)
ifneq ($(objects_lib),)
	@echo OBJECTS\ \ : $(objects_lib)
endif
	@echo DEPENDS\ \ : $(gcsl_libdeps) $(GNSDK_SDKDEPS) $(PLAT_LIBDEPS) $(PLAT_SDKDEPS)
	@echo
