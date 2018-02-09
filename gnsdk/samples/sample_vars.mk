group_name = sample
appname = sample

build_dir = ../../../../../builds
install_dir = ../../../../../install/common
ifneq "$(wildcard ../../builds )" ""
build_dir = ../../builds
install_dir = ../../..
endif

ifeq ($(IMPLDIR),linux)
platformlibs = -lstdc++
endif

ifeq ($(IMPLDIR),qnx)
platformlibs = -lstdc++
endif

