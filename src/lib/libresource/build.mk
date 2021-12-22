#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Descrption		: This script accumulates sources and builds
#			  library
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

DP_PATH		:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libresource.a
LIB_INCLUDE	+= $(DP_PATH)/include/
DEP_LIBS_ARG	+= -lresource

include $(DP_PATH)/dp/build.mk
include $(DP_PATH)/sp/build.mk

DIR		:= $(DP_PATH)
include mk/lib.mk
