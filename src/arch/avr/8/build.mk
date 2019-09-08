DIR		:= $(GET_PATH)

DEPS_SRCS	:= arch_vectors.S	\
		   asm.S		\
		   init.c		\
		   arch.c

include mk/obj.mk
