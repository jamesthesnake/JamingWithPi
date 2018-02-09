#
# Gather sources for projects
#  Recusively search for source, header and dependent library files
#  Search occurs within makefile folder and certain children
#
#  <make dir>/*.c|cpp|h
#  |_<IMPLDIR>/*.c|cpp|h
#  |_<IMPLDIR>/<IMPLARCH>/*.c|cpp|h
#  |_<extra_srcs>/*.c|cpp|h
#  |_<extra_srcs><IMPLDIR>/*.c|cpp|h
#  |_<extra_srcs><IMPLDIR>/<IMPLARCH>/*.c|cpp|h
#  |_<extra_libs><IMPLDIR>/<IMPLARCH>/<static libs>
#  |_<extra_libs><IMPLDIR>/<IMPLARCH>/debug/<static libs>   
#  |_<extra_libs><IMPLDIR>/<IMPLARCH>/release/<COMPILER_VER>/<static libs>   
#
# Output variables set:
#	sources
#	headers
#	objects
#	objects_libs
#

ifeq ($(IMPLDIR),)
$(error Incorrect Makefile setup: IMPLDIR is not set)
endif
ifeq ($(IMPLARCH),)
$(error Incorrect Makefile setup: IMPLARCH is not set)
endif


all_sources := \
	$(info Gathering sources for '$(IMPLDIR)_$(IMPLARCH)' build...) \
	$(wildcard _include/*.*) \
	$(wildcard *.*) \
	$(wildcard $(IMPLDIR)/*.*) \
	$(wildcard $(IMPLDIR)/$(IMPLARCH)/*.*) \
	$(foreach dir,$(extra_srcs),$(wildcard $(dir)/*.*)) \
	$(foreach dir,$(extra_srcs),$(wildcard $(dir)/$(IMPLDIR)/*.*)) \
	$(foreach dir,$(extra_srcs),$(wildcard $(dir)/$(IMPLDIR)/$(IMPLARCH)/*.*))

all_libraries := \
	$(info Gathering libraries for '$(IMPLDIR)_$(IMPLARCH)' build...) \
	$(wildcard $(IMPLDIR)/$(IMPLARCH)/*.*) \
	$(foreach dir,$(extra_libs),$(wildcard $(dir)/$(IMPLDIR)/$(IMPLARCH)/*.*))

debug_libraries := \
	$(wildcard $(IMPLDIR)/$(IMPLARCH)/debug/*.*) \
	$(wildcard $(IMPLDIR)/$(IMPLARCH)/debug/$(COMPILER_VER)/*.*) \
	$(foreach dir,$(extra_libs),$(wildcard $(dir)/$(IMPLDIR)/$(IMPLARCH)/debug/*.*)) \
	$(foreach dir,$(extra_libs),$(wildcard $(dir)/$(IMPLDIR)/$(IMPLARCH)/debug/$(COMPILER_VER)/*.*)) 
	
release_libraries := \
	$(wildcard $(IMPLDIR)/$(IMPLARCH)/release/*.*) \
	$(wildcard $(IMPLDIR)/$(IMPLARCH)/release/$(COMPILER_VER)/*.*) \
	$(foreach dir,$(extra_libs),$(wildcard $(dir)/$(IMPLDIR)/$(IMPLARCH)/release/*.*)) \
	$(foreach dir,$(extra_libs),$(wildcard $(dir)/$(IMPLDIR)/$(IMPLARCH)/release/$(COMPILER_VER)/*.*)) 

#
# C sources (*.c)
#
sources_c = $(filter %.c,$(all_sources) $(extra_src_files))

#
# C++ sources (*.cpp)
#
sources_cpp = $(filter %.cpp,$(all_sources) $(extra_src_files)) 

#
# ObjC sources (*.m *.mm)
#
sources_m = $(filter %.m,$(extra_src_files)) 
sources_mm = $(filter %.mm,$(extra_src_files)) 
sources_objc = $(sources_m) $(sources_mm)

#
# All sources
#
sources = $(sources_c) $(sources_cpp) $(sources_objc)

#
# Source headers
#
headers = $(filter %.h,$(all_sources))


#
# Object Libraries
#

# objects from sources
objects_c = $(sources_c:%.c=%.o)
objects_cpp = $(sources_cpp:%.cpp=%.opp)
objects_objc = $(sources_mm:%.mm=%.omm) $(sources_m:%.m=%.om)
objects = $(objects_c) $(objects_cpp) $(objects_objc)

# objects directly included in project
ifeq ($(STATIC),static)
	objects_lib_tmp = $(filter %.$(STATIC_LIB_EXT),$(all_libraries))
	objects_lib_tmp_debug = $(filter %.$(STATIC_LIB_EXT),$(debug_libraries))
	objects_lib_tmp_release = $(filter %.$(STATIC_LIB_EXT),$(release_libraries))
else
	ifeq ($(SHARED_LINK_EXT),$(STATIC_LIB_EXT))
		objects_lib_tmp = $(filter %.$(SHARED_LINK_EXT),$(all_libraries))
		objects_lib_tmp_debug = $(filter %.$(SHARED_LINK_EXT),$(debug_libraries))
		objects_lib_tmp_release = $(filter %.$(SHARED_LINK_EXT),$(release_libraries))
	else
		objects_lib_tmp = $(filter %.$(SHARED_LINK_EXT),$(all_libraries)) $(filter %.$(STATIC_LIB_EXT),$(all_libraries))
		objects_lib_tmp_debug = $(filter %.$(SHARED_LINK_EXT),$(debug_libraries)) $(filter %.$(STATIC_LIB_EXT),$(debug_libraries))
		objects_lib_tmp_release = $(filter %.$(SHARED_LINK_EXT),$(release_libraries)) $(filter %.$(STATIC_LIB_EXT),$(release_libraries))
	endif
endif

objects_lib_debug = $(sort $(objects_lib_tmp) $(objects_lib_tmp_debug))
objects_lib_release = $(sort $(objects_lib_tmp) $(objects_lib_tmp_release))


