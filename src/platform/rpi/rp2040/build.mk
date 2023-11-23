#
# CYANCORE LICENSE
# Copyrights (C) 2023, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts from 
#			  all other directories that have RPi-pico RP2040
#			  board support sources
# Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
# Organisation		: Cyancore Core-Team
#

RP2040_DIR	:= $(GET_PATH)

ARCH		:= arm-m
BIT		:= 32
ARCH_VARIANT	:= m0p
TL_TYPE		:= thumb/v6-m
TARGET_FLAGS	+= -mcpu=cortex-m0plus -mfloat-abi=softfp
PLAT_INCLUDE	+= $(RP2040_DIR)/include
OUTPUT_FORMAT	:= elf32-littlearm

include $(RP2040_DIR)/config.mk
#include $(RP2040_DIR)/resources/build.mk
include $(RP2040_DIR)/../common_rp2/build.mk
