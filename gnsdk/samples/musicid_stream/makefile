#
# Makefile:
# gnsdk_musicid sample app
#

sdkdepends = musicid dsp storage_sqlite manager

ifeq ($(filter static, $(MAKECMDGOALS)), static)
	extra_libs = ../../xtralibs/ipp ../../xtralibs/s12t ../../xtralibs/afx3
endif

include ../sample_vars.mk
include $(build_dir)/rules_samples.mk
