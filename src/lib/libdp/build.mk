DP_PATH		:= $(DP_PATH)
LIB_OBJS	:=

LIB		:= libdp.a
LIB_INCLUDE	+= $(DP_PATH)/include/
DEP_LIBS	+= -ldp

DIR		:= $(DP_PATH)
include mk/lib.mk
