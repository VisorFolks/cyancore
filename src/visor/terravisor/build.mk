#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts
#			  from terravisor directories
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

TERRA_PATH	:= $(GET_PATH)

TERRAVISOR	:= 1
$(eval $(call add_define,TERRAVISOR))

include $(TERRA_PATH)/services/build.mk
