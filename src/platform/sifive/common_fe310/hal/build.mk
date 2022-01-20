#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates HAL sources from FE310
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#======================================================================
# Configuration file for Platforms
#======================================================================
# Do not make changes to this file or variables

HAL_DIR	:= $(GET_PATH)

include $(HAL_DIR)/uart/build.mk
include $(HAL_DIR)/clint/build.mk
