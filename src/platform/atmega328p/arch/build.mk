DIR		:= $(GET_PATH)

CFLAGS		+=

DEPS_SRCS	:= plat_vectors.S	\
		   isr.S

include mk/obj.mk
