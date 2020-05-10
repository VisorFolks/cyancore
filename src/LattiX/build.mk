DIR		:= $(GET_PATH)

LD_TEMPLATE	:= $(DIR)/LattiX.ld.sx

include $(DIR)/buildbanner.mk
include mk/elf.mk
