LIBC_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libc.a
LIB_INCLUDE	+= $(LIBC_PATH)/include/
DEP_LIBS	+= -lc

DIR		:= $(LIBC_PATH)
include mk/lib.mk
