DIR		:= $(GET_PATH)

DEPS_SRCS	:= vectors.S		\
		   isr.c

include mk/obj.mk
