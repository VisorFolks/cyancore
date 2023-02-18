#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file builds and gathers project properties
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

PROJECT_DIR	:= $(GET_PATH)

include $(PROJECT_DIR)/../demo.src/build.mk
include $(PROJECT_DIR)/config.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk

aux_target:
	make qemu_sifive_e_bl
