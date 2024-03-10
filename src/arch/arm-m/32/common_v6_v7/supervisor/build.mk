#
# CYANCORE LICENSE
# Copyrights (C) 2024, Cyancore Team
#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

ARM32_M_S_ARCH_DIR	:= $(GET_PATH)

$(eval $(call add_include,$(ARM32_M_S_ARCH_DIR)/include/))

DIR		:= $(ARM32_M_S_ARCH_DIR)
include mk/obj.mk
