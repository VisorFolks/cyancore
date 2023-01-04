#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file build project sources and specifies
#			  project properties
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

PROJECT_DIR	:= $(GET_PATH)

OPTIMIZATION	:= s

EXE_MODE	:= terravisor

include $(PROJECT_DIR)/config/config.mk

# You can add another folder with necessary files to build the project
# The below path should be valid
# include $(PROJECT_DIR)/<folder>/build.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
