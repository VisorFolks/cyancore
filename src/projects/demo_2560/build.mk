#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file build project sources and specifies
#			  project properties
# Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
# Organisation		: Cyancore Contributor
#

PROJECT_DIR	:= $(GET_PATH)

OPTIMIZATION	:= s

EXE_MODE	:= terravisor

include $(PROJECT_DIR)/config.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
