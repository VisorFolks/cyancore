#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts from 
#			  all other directories that have atmega328p
#			  board support sources
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

ATMEGA328P_DIR	:= $(GET_PATH)

ARCH		:= avr
BIT		:= 8
ARCH_VARIANT	:= 5
TARGET_FLAGS	+= -mmcu=atmega328p
PLAT_INCLUDE	+= $(ATMEGA328P_DIR)/include
OUTPUT_FORMAT	:= elf32-avr

include $(ATMEGA328P_DIR)/config.mk
include $(ATMEGA328P_DIR)/arch/build.mk
include $(ATMEGA328P_DIR)/platform/build.mk
include $(ATMEGA328P_DIR)/resources/build.mk
include $(ATMEGA328P_DIR)/../common/build.mk
