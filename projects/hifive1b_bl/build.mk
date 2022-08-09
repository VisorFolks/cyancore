#
# CYANCORE LICENSE
# Copyrights (C) 2022, Cyancore Team
#
# File Name		: build.mk
# Description		: This file build project sources and specifies
#			  project properties
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

PROJECT_DIR	:= $(GET_PATH)

include $(PROJECT_DIR)/config.mk
include $(PROJECT_DIR)/../bl.src/build.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
