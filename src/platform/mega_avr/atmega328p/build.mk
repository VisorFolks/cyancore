ATMEGA328P_DIR	:= $(GET_PATH)

ARCH		:= avr
BIT		:= 8
ARCH_VARIANT	:= 5
TARGET_FLAGS	+= -mmcu=atmega328p
LIBGCC_PATH	+= -L toolchain/avr-toolchain/lib/gcc/avr/5.4.0
PLAT_INCLUDE	+= $(ATMEGA328P_DIR)/include
OUTPUT_FORMAT	:= elf32-avr

include $(ATMEGA328P_DIR)/config.mk
include $(ATMEGA328P_DIR)/arch/build.mk
include $(ATMEGA328P_DIR)/platform/build.mk
include $(ATMEGA328P_DIR)/../common/build.mk
