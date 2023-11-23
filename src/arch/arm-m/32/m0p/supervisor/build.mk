#
# CYANCORE LICENSE
# Copyrights (C) 2023, Cyancore Team
#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

ARM32_M0P_T_ARCH_DIR	:= $(GET_PATH)

include $(ARM32_M0P_T_ARCH_DIR)/../../common_v6_v7/supervisor/build.mk

DIR		:= $(ARM32_M0P_T_ARCH_DIR)
include mk/obj.mk
