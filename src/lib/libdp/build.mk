DP_PATH		:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libdp.a
LIB_INCLUDE	+= $(DP_PATH)/include/
DEP_LIBS_ARG	+= -ldp

DIR		:= $(DP_PATH)
include mk/lib.mk
