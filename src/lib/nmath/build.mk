DIR		:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libnmath.a
LIB_INCLUDE_PATH:= $(DIR)/include
LIB_HEADER	:= nmath.h
DEP_LIBS	+= -lnmath

include mk/lib.mk
