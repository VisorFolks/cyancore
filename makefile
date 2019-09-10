#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#--------< Arc Top Level Makefile >--------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

SHELL		:= /bin/bash
N_HOSTS		:= $(shell grep -c ^processor /proc/cpuinfo)

default:
	make $(PROJECT) all -j$(N_HOSTS)

.PHONY: all --dependency clean

--dependency:
	mkdir -p $(OUT)

clean:
	$(info < ! > Removing $(PROJECT) binaries ...)
	rm -rf $(OUT)

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

all: version --dependency lib obj elf
	$(info < / > Done !)

.SILENT:
