#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#--------< Arc Top Level Makefile >--------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

SHELL		:= /bin/bash
N_HOSTS		:= $(shell grep -c ^processor /proc/cpuinfo)

default:
	make all -j$(N_HOSTS)

.PHONY: all --dependency clean

--dependency:
	mkdir -p $(OUT)

clean:
	$(info < ! > Removing binaries ...)
	rm -rf $(OUT)

include mk/help.mk
include mk/path.mk
include mk/tc_get.mk
include mk/project_search.mk

ifneq ($(MAKECMDGOALS),help)
ifneq ($(MAKECMDGOALS),list)
ifneq ($(MAKECMDGOALS),get_all_tc)
ifneq ($(MAKECMDGOALS),get_arm_tc)
ifneq ($(MAKECMDGOALS),get_avr_tc)
ifneq ($(MAKECMDGOALS),get_riscv_tc)
include $(SRC)/sources.mk
endif
endif
endif
endif
endif
endif

include mk/tc.mk

all: --dependency libraries objects #executable
	$(info < / > Done !)

.SILENT:
