#
# CYANCORE LICENSE
# Copyrights (C) 2023, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts
#			  from supervisor services
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

S_SERVICES	:= $(GET_PATH)

include $(S_SERVICES)/bootstrap/build.mk

DIR		:= $(S_SERVICES)
include mk/obj.mk
