LIBARCC_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libarcc.a
LIB_INCLUDE	+= -I $(LIBARCC_PATH)/include/
DEP_LIBS	+= -larcc

include $(LIBARCC_PATH)/modules/build.mk
include $(LIBARCC_PATH)/stdlib/build.mk
include $(LIBARCC_PATH)/stdio/build.mk
include $(LIBARCC_PATH)/string/build.mk
DIR		:= $(LIBARCC_PATH)
include mk/lib.mk
