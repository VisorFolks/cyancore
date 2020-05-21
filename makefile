#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#--------< Arc Top Level Makefile >--------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

SHELL		:= /bin/bash
N_HOSTS		:= $(shell grep -c ^processor /proc/cpuinfo)
HOST_ARCH	:= $(shell lscpu | grep -Po '(?<='Architecture:'        )[^"]*')


include mk/help.mk
include mk/path.mk
include mk/tc_get.mk
include mk/project.mk
ifneq ($(MAKECMDGOALS),help)
ifneq ($(MAKECMDGOALS),list)
ifneq ($(MAKECMDGOALS),get_all_tc)
ifneq ($(MAKECMDGOALS),get_arm_tc)
ifneq ($(MAKECMDGOALS),get_avr_tc)
ifneq ($(MAKECMDGOALS),get_riscv_tc)
include $(SRC)/sources.mk
include mk/tc.mk
endif
endif
endif
endif
endif
endif

ifneq ($(V),1)
.SILENT:
endif
