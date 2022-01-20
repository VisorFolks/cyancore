#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of interrupt controller
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

CLINT_PATH	:= $(GET_PATH)

ifeq ($(ARCH), riscv)

DIR		:= $(CLINT_PATH)
include mk/obj.mk

endif
