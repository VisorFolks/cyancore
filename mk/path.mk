#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: path.mk
# Description		: This file defines standard variables used
#			  in cyacnore build system
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Paths >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

ARC_ROOT	:= .
TOOLS_ROOT	?= $(abspath $(ARC_ROOT))/toolchain

SRC		:= $(ARC_ROOT)/src
OUT_PATH	?= $(ARC_ROOT)/out
OUT		?= $(OUT_PATH)/$(PROJECT)

GET_PATH	= $(patsubst %/,%,./$(dir $(lastword $(MAKEFILE_LIST))))

$(OUT)/%/:
	mkdir -p $@
