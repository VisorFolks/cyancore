ATMEGA328P_DIR	:= $(GET_PATH)

PLAT_INCLUDE	+= -I $(ATMEGA328P_DIR)/

include $(ATMEGA328P_DIR)/arch/build.mk
include $(ATMEGA328P_DIR)/peripherals/build.mk
