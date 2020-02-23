MEGA_AVR_COMMON_DIR	:= $(GET_PATH)

PLATFORM_INCLUDE	+= $(MEGA_AVR_COMMON_DIR)/include

include $(MEGA_AVR_COMMON_DIR)/arch/build.mk
include $(MEGA_AVR_COMMON_DIR)/hal/build.mk
