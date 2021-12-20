#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

AVR_ARCH_DIR	:= $(GET_PATH)

include $(AVR_ARCH_DIR)/../../common_5x_6/terravisor/build.mk

DIR		:= $(AVR_ARCH_DIR)
include mk/obj.mk
