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

BLP_DIR		:= $(GET_PATH)

OPTIMIZATION	:= s

EXE_MODE	:= terravisor

DIR		:= $(BLP_DIR)
include mk/obj.mk
