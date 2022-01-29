#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: Build script for this directory.
# Primary Authod	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

RV32IA_ARCH_DIR	:= $(GET_PATH)

DIR		:= $(RV32IA_ARCH_DIR)
include mk/obj.mk
