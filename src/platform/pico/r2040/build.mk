#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts from 
#			  all other directories that have RPi-pico R2040
#			  board support sources
# Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
# Organisation		: Cyancore Core-Team
#

R2040_DIR	:= $(GET_PATH)

ARCH		:= arm-m
BIT		:= 32
ARCH_VARIANT	:= v6
TARGET_FLAGS	+=
PLAT_INCLUDE	+= $(R2040_DIR)/include
OUTPUT_FORMAT	:=

#include $(R2040_DIR)/config.mk
#include $(R2040_DIR)/arch/build.mk
#include $(R2040_DIR)/platform/build.mk
#include $(R2040_DIR)/resources/build.mk
#include $(R2040_DIR)/../common_fe310/build.mk
