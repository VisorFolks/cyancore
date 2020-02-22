LIBARCC_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libarcc.a
LIB_INCLUDE	+= -I $(LIBARCC_PATH)/include/
DEP_LIBS	+= -larcc

include $(LIBARCC_PATH)/modules/build.mk
DIR		:= $(LIBARCC_PATH)
include mk/lib.mk
