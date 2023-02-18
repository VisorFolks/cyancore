#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts from 
#			  all other directories that have HiFive 1 Rev B
#			  board support sources
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

FE310G002_DIR	:= $(GET_PATH)

ARCH		:= riscv
BIT		:= 32
ARCH_VARIANT	:= imac
ARCH_ABI	:= ilp32
TARGET_FLAGS	+= -march=rv32imac -mabi=$(ARCH_ABI)
PLAT_INCLUDE	+= $(FE310G002_DIR)/include
OUTPUT_FORMAT	:= elf32-littleriscv

include $(FE310G002_DIR)/config.mk
include $(FE310G002_DIR)/../common_fe310/build.mk
$(eval $(call check_and_include,USE_DEFAULT_RESOURCES,$(FE310G002_DIR)/resources/build.mk))

DIR		:= $(FE310G002_DIR)
include mk/obj.mk
