#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources from mega-avr
#			  common directory
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

MEGA_AVR_COMMON_DIR	:= $(GET_PATH)

LD_SCRIPT		:= $(MEGA_AVR_COMMON_DIR)/sections.ld.sx

PLAT_INCLUDE		+= $(MEGA_AVR_COMMON_DIR)/include

LD_FLAGS		+= -m$(ARCH)$(ARCH_VARIANT)

LINT_FLAGS		+= --platform=avr8

EXLIB_ARGS		+= -L $(TOOLS_ROOT)/avr-toolchain/avr/lib/$(ARCH)$(ARCH_VARIANT)/
EXLIB_ARGS		+= -lm


USE_DEFAULT_RESOURCES	?= 1
LOCAL_INTERRUPT_DEVICE	:= 0
PLAT_INTERRUPT_DEVICE	:= 0

include $(MEGA_AVR_COMMON_DIR)/arch/build.mk
include $(MEGA_AVR_COMMON_DIR)/hal/build.mk
include $(MEGA_AVR_COMMON_DIR)/platform/build.mk
