AVR_ARCH_DIR	:= $(GET_PATH)

INCLUDE		+= $(AVR_ARCH_DIR)/include/

DIR		:= $(AVR_ARCH_DIR)
include mk/obj.mk
