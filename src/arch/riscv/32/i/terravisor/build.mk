#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

RV32I_T_ARCH_DIR	:= $(GET_PATH)

$(eval $(call add_include,$(RV32I_T_ARCH_DIR)/include/))

DIR		:= $(RV32I_T_ARCH_DIR)
include mk/obj.mk
