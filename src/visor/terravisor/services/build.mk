#
# CYANCORE LICENSE
# Copyrights (C) 2022, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts
#			  from terravisor services
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

T_SERVICES	:= $(GET_PATH)

include $(T_SERVICES)/bootstrap/build.mk
include $(T_SERVICES)/driver/build.mk

ifeq ($(TERRAKERN),1)
include $(T_SERVICES)/kernel/build.mk
endif

DIR		:= $(T_SERVICES)
include mk/obj.mk
