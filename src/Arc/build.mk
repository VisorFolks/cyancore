DIR		:= $(GET_PATH)

LD_TEMPLATE	:= $(DIR)/arc.ld.sx

include $(DIR)/angle.mk
include mk/elf.mk
