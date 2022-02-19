#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of console driver
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

CONSOLE_PATH	:= $(GET_PATH)

include $(CONSOLE_PATH)/stdlog_membuf/build.mk
include $(CONSOLE_PATH)/console_serial/build.mk

DIR		:= $(CONSOLE_PATH)
include mk/obj.mk
