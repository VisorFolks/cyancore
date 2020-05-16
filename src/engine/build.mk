DIR		:= $(GET_PATH)

LD_TEMPLATE	:= $(DIR)/sections.ld.sx

include $(DIR)/buildbanner.mk
include mk/elf.mk
