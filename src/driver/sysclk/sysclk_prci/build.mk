#
# CYANCORE LICENSE
# Copyrights (C) 2022, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of prci sysclk driver
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

SYSCLK_PRCI_PATH	:= $(GET_PATH)

DIR			:= $(SYSCLK_PRCI_PATH)
include mk/obj.mk
