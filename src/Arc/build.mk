DIR		:= $(GET_PATH)

ELF		:= arc.elf

DEPS_SRCS	:= arc.c

LD_TEMPLATE	:= $(DIR)/arc.ld.S

include $(DIR)/angle.mk
include mk/obj.mk
include mk/elf.mk
