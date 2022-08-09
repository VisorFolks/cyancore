#
# CYANCORE LICENSE
# Copyrights (C) 2022, Cyancore Team
#
# File Name		: build.mk
# Description		: This file builds all the drivers associated
#			  with terravisor
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

T_DRIVER_DIR	:= $(GET_PATH)

DIR		:= $(T_DRIVER_DIR)
include mk/obj.mk
