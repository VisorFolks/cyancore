DIR		:= $(GET_PATH)

PLAT_INCLUDE	+= -I $(DIR)/

DEPS_SRCS	:= plat_vectors.S	\
		   isr.c

include mk/obj.mk
