#
# CYANCORE LICENSE
# Copyrights (C) 2019-2023, Cyancore Team
#
# File Name		: build.mk
# Description		: This file build project sources and specifies
#			  project properties
# Primary Author	: Pranjal Chdanda [pranjalchanda08@gmail.com]
# Organisation		: Cyancore Core-Team
#

PROJECT_DIR	:= $(GET_PATH)

include $(PROJECT_DIR)/../demo_cc_os.src/build.mk
include $(PROJECT_DIR)/config.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
