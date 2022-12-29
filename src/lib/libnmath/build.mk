#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Descrption		: This script accumulates sources and build
#			  neo-math library
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

NMATH_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libnmath.a
LIB_INCLUDE	+= $(NMATH_PATH)/include/
DEP_LIBS_ARG	+= -lnmath

include $(NMATH_PATH)/arithmetic/build.mk
include $(NMATH_PATH)/dsp/build.mk

DIR		:= $(NMATH_PATH)
include mk/lib.mk
