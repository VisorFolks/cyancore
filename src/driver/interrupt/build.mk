#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of interrupt controller
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

IC_PATH		:= $(GET_PATH)

$(eval $(call add_define,LOCAL_INTERRUPT_DEVICE))
$(eval $(call add_define,PLAT_INTERRUPT_DEVICE))

ifeq ($(PLAT_INTERRUPT_DEVICE),1)
include $(IC_PATH)/plic/build.mk
endif

DIR		:= $(IC_PATH)
include mk/obj.mk
