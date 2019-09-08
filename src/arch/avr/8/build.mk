DIR		:= $(GET_PATH)

DEPS_SRCS	:= arch_vectors.S	\
		   init.c		\
		   arch.c

include mk/obj.mk
