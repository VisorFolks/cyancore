#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file builds cyancore engine core sources
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

DIR		:= $(GET_PATH)

BOOTMSGS        ?= 1
$(eval $(call add_define,BOOTMSGS))

include $(DIR)/banner.mk
include mk/elf.mk
