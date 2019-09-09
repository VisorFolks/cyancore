DIR		:= $(GET_PATH)

ELF		:= arc.elf

LD_TEMPLATE	:= $(DIR)/arc.ld.sx

include $(DIR)/angle.mk
include mk/obj.mk
include mk/elf.mk
