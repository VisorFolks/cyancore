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
ARCH_VARIANT	:= v6
TARGET_FLAGS	+=
PLAT_INCLUDE	+= $(RP2040_DIR)/include
OUTPUT_FORMAT	:=

#include $(RP2040_DIR)/config.mk
#include $(RP2040_DIR)/arch/build.mk
#include $(RP2040_DIR)/platform/build.mk
#include $(RP2040_DIR)/resources/build.mk
#include $(RP2040_DIR)/../common_fe310/build.mk
