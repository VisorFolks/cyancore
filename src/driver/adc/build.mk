DIR		:= $(GET_PATH)
LIB_OBJS	:=

LIB		:= libadc.a
LIB_INCLUDE_PATH:=
LIB_HEADER	:=

DEP_LIBS	+= -ladc

include mk/lib.mk
