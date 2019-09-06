#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#--------< Arc Top Level Makefile >--------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

SHELL		:= /bin/bash

N_HOSTS		:= $(shell grep -c ^processor /proc/cpuinfo)

default:
	make all -j $(N_HOSTS)

.PHONY: --dependency clean
--dependency:
	mkdir -p $(OUT)

clean:
	$(info < ! > Removing binaries ...)
	rm -rf $(OUT)

include mk/help.mk
include mk/path.mk
include mk/tools.mk
include mk/project_search.mk

ifneq ($(MAKECMDGOALS),help)
ifneq ($(MAKECMDGOALS),list)
ifneq ($(MAKECMDGOALS),get_all_tools)
ifneq ($(MAKECMDGOALS),get_arm_tools)
ifneq ($(MAKECMDGOALS),get_avr_tools)
ifneq ($(MAKECMDGOALS),get_riscv_tools)
include $(SRC)/sources.mk
endif
endif
endif
endif
endif
endif

.PHONY: all
all: --dependency libraries objects executable
	$(info < / > Done !)


.SILENT:
