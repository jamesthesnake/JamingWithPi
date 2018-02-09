#
# Makefile:
# gnsdk_musicid_file sample app
#

sdkdepends = musicid_file dsp lookup_local storage_sqlite manager

ifeq ($(filter static, $(MAKECMDGOALS)), static)
	extra_libs = ../../xtralibs/ipp ../../xtralibs/s12t ../../xtralibs/afx3
endif

include ../sample_vars.mk
include $(build_dir)/rules_samples.mk
