#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
#

AVR_ARCH_DIR	:= $(GET_PATH)

$(eval $(call add_include,$(AVR_ARCH_DIR)/include/))

DIR		:= $(AVR_ARCH_DIR)
include mk/obj.mk
