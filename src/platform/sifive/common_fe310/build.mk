#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources from FE310
#			  common directory
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

FE310_COMMON_DIR	:= $(GET_PATH)

LD_SCRIPT		:= $(FE310_COMMON_DIR)/sections.ld.sx

PLAT_INCLUDE		+= $(FE310_COMMON_DIR)/include

LINT_FLAGS		+= --platform=unix32

MEMSIZE_ARGS		+= -m ITIM $(ITIM_START) $(ITIM_SIZE)

USE_DEFAULT_RESOURCES	?= 1
LOCAL_INTERRUPT_DEVICE	?= 1
PLAT_INTERRUPT_DEVICE	?= 1

include $(FE310_COMMON_DIR)/arch/build.mk
include $(FE310_COMMON_DIR)/hal/build.mk
include $(FE310_COMMON_DIR)/platform/build.mk
