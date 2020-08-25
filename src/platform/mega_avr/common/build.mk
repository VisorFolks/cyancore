MEGA_AVR_COMMON_DIR	:= $(GET_PATH)

LD_TEMPLATE	:= $(MEGA_AVR_COMMON_DIR)/sections.ld.sx

PLAT_INCLUDE		+= $(MEGA_AVR_COMMON_DIR)/include

LOCAL_INTERRUPT_DEVICE	:= 0
PLAT_INTERRUPT_DEVICE	:= 0

include $(MEGA_AVR_COMMON_DIR)/arch/build.mk
include $(MEGA_AVR_COMMON_DIR)/hal/build.mk
include $(MEGA_AVR_COMMON_DIR)/platform/build.mk
