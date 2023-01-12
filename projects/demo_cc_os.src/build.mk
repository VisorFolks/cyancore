#
# CYANCORE LICENSE
# Copyrights (C) 2019-2023, Cyancore Team
#
# File Name		: build.mk
# Description		: This file build project sources and specifies
#			  project properties
# Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
# Organisation		: Cyancore Core-Team
#

DEMO_DIR	:= $(GET_PATH)

OPTIMIZATION	:= s

EXE_MODE	:= terravisor

DIR		:= $(DEMO_DIR)
include mk/obj.mk
