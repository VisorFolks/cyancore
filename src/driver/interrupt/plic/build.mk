#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of interrupt controller
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

PLIC_PATH	:= $(GET_PATH)

ifeq ($(ARCH), riscv)
ifneq ($(N_PLAT_IRQS),0)

DIR		:= $(PLIC_PATH)
include mk/obj.mk

endif
endif
