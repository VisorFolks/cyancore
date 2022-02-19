#
# CYANCORE LICENSE
# Copyrights (C) 2022, Cyancore Team
#
# File Name		: build.mk
# Descrption		: This script accumulates sources and builds
#			  library
# Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
# Organisation		: Cyancore Core-Team
#

POSIX_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libposix.a
LIB_INCLUDE	+= $(POSIX_PATH)/include/
DEP_LIBS_ARG	+= -lposix

include $(POSIX_PATH)/src/build.mk

DIR		:= $(POSIX_PATH)
include mk/lib.mk
