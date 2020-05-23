NMATH_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libnmath.a
LIB_INCLUDE	+= $(NMATH_PATH)/include/
DEP_LIBS_ARG	+= -lnmath

DIR		:= $(NMATH_PATH)
include mk/lib.mk
