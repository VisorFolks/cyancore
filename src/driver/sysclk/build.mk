#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of sysclk driver
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

SYSCLK_PATH	:= $(GET_PATH)

$(eval $(call check_and_include,PRCI_CLK,$(SYSCLK_PATH)/sysclk_prci/build.mk))

DIR		:= $(SYSCLK_PATH)
include mk/obj.mk
