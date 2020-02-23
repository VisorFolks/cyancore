SHI_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libdp.a
LIB_INCLUDE	+= -I $(SHI_PATH)/include/
DEP_LIBS	+= -ldp

DIR		:= $(SHI_PATH)
include mk/lib.mk
