#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts from
#			  all other directories that have atmega328p
#			  board support sources
# Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
# Organisation		: Cyancore Contributor
#

ATMEGA2560_DIR	:= $(GET_PATH)

ARCH		:= avr
BIT		:= 8
ARCH_VARIANT	:= 6
TARGET_FLAGS	+= -mmcu=atmega2560
PLAT_INCLUDE	+= $(ATMEGA2560_DIR)/include
OUTPUT_FORMAT	:= elf32-avr

include $(ATMEGA2560_DIR)/config.mk
include $(ATMEGA2560_DIR)/arch/build.mk
include $(ATMEGA2560_DIR)/platform/build.mk
include $(ATMEGA2560_DIR)/../common/build.mk
$(eval $(call check_and_include,USE_DEFAULT_RESOURCES,$(ATMEGA2560_DIR)/resources/build.mk))
