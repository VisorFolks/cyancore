#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

RV32IMAC_T_ARCH_DIR	:= $(GET_PATH)

include $(RV32IMAC_T_ARCH_DIR)/../../i/terravisor/build.mk

DIR		:= $(RV32IMAC_T_ARCH_DIR)
include mk/obj.mk
