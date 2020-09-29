#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------< Cyancore Top Level Makefile >------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

SHELL		:= /bin/bash
N_HOSTS		:= $(shell grep -c ^processor /proc/cpuinfo)
HOST_ARCH	:= $(shell lscpu | grep -Po '(?<='Architecture:'        )[^"]*')

include mk/help.mk
include mk/path.mk
include mk/tc_get.mk
include mk/project.mk
ifeq ($(findstring $(MAKECMDGOALS),$(T_ALLOWLIST)),)
include $(SRC)/sources.mk
include mk/tc.mk
endif

ifneq ($(V),1)
.SILENT:
endif
