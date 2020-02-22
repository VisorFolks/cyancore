ATMEGA328P_DIR	:= $(GET_PATH)

ARCH		:= avr
BIT		:= 8
TARGET_FLAGS	+= -mmcu=atmega328p

DEP_LIB_PATH	+= -L toolchain/avr-toolchain/lib/gcc/avr/5.4.0/avr5/
DEP_LIBS	+= -lgcc

OUTPUT_FORMAT	:= elf32-avr

PLAT_INCLUDE	+= -I $(ATMEGA328P_DIR)/include

include $(ATMEGA328P_DIR)/arch/build.mk
include $(ATMEGA328P_DIR)/platform/build.mk
include $(ATMEGA328P_DIR)/../common/build.mk
