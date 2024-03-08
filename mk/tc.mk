#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: tc.mk
# Description		: This file defines toolchain specific variables
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

include mk/path.mk

ifeq ($(findstring arm,$(ARCH)),arm)
TC	?= $(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi
$(eval $(call get_tc_version,$(TC)))	# Sets TC_VER
TI	:= $(TOOLS_ROOT)/arm-toolchain/lib/gcc/arm-none-eabi/$(TC_VER)/include-fixed/
TI	+= $(TOOLS_ROOT)/arm-toolchain/arm-none-eabi/include/
TL	:= $(TOOLS_ROOT)/arm-toolchain/lib/gcc/arm-none-eabi/$(TC_VER)/$(TL_TYPE)/
endif

ifeq ($(findstring riscv,$(ARCH)),riscv)
TC	?= $(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf
$(eval $(call get_tc_version,$(TC)))	# Sets TC_VER
TI	:= $(TOOLS_ROOT)/risc-v-toolchain/lib/gcc/riscv64-unknown-elf/$(TC_VER)/include-fixed/
TI	+= $(TOOLS_ROOT)/risc-v-toolchain/riscv64-unknown-elf/include/
TL	:= $(TOOLS_ROOT)/risc-v-toolchain/lib/gcc/riscv64-unknown-elf/$(TC_VER)/rv$(BIT)$(ARCH_VARIANT)/$(ARCH_ABI)/
endif

ifeq ($(findstring avr,$(ARCH)),avr)
TC	?= $(TOOLS_ROOT)/avr-toolchain/bin/avr
$(eval $(call get_tc_version,$(TC)))	# Sets TC_VER
TI	:= $(TOOLS_ROOT)/avr-toolchain/lib/gcc/avr/$(TC_VER)/include-fixed
TL	:= $(TOOLS_ROOT)/avr-toolchain/lib/gcc/avr/$(TC_VER)/$(ARCH)$(ARCH_VARIANT)/
endif

ifneq ($(ARCH),)
AS	:= $(TC)-as
AR	:= $(TC)-ar
CC	:= $(TC)-gcc
CCP	:= $(TC)-g++
LD	:= $(TC)-ld
OD	:= $(TC)-objdump
OC	:= $(TC)-objcopy
STRIP	:= $(TC)-strip
A2L	:= $(TC)-addr2line
endif

ifeq ($(realpath $(TI)),)
$(info < ! > Toolchain is not available !)
$(info < ! > Try running 'make help' ...)
$(error < x > Build Failed !)
endif


