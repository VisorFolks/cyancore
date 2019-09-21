ATMEGA328P_DIR	:= $(GET_PATH)

ARCH		:= avr
BIT		:= 8
TARGET_FLAGS	+= -mmcu=atmega328p

PLAT_INCLUDE	+= -I $(ATMEGA328P_DIR)/include

include $(ATMEGA328P_DIR)/arch/build.mk
include $(ATMEGA328P_DIR)/../common/build.mk
