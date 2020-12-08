AVR_ARCH_DIR	:= $(GET_PATH)

$(eval $(call add_include,$(AVR_ARCH_DIR)/include/))

DIR		:= $(AVR_ARCH_DIR)
include mk/obj.mk
