#
# File Name		: build.mk
# Description		: This file accumalates the build scripts from 
#			  all the driver directories
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]

DRIVER_PATH	:= $(GET_PATH)

#==========< Essentials Drivers >==========#
include $(DRIVER_PATH)/interrupt/build.mk

#==========< User Config Drivers >==========#
ifeq ($(CONSOLE),1)
include $(DRIVER_PATH)/console/build.mk
endif

DIR		:=$(DRIVER_PATH)
include mk/obj.mk
