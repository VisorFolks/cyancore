#
# CYANCORE LICENSE
# Copyrights (C) 2022, Cyancore Team
#
# File Name		: build.mk
# Descrption		: This script accumulates all the sources of libccfs
#			  and build the library
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

LIBCCFS_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libccfs.a
LIB_INCLUDE	+= $(LIBCCFS_PATH)/include/
DEP_LIBS_ARG	+= -lccfs

DIR		:= $(LIBCCFS_PATH)
include mk/lib.mk
