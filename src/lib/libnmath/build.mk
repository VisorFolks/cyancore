NMATH_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libnmath.a
LIB_INCLUDE	+= -I $(NMATH_PATH)/include/
DEP_LIBS	+= -lnmath

DIR		:= $(NMATH_PATH)
include mk/lib.mk
