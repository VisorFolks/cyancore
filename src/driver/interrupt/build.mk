IC_PATH		:= $(GET_PATH)

$(eval $(call add_define,LOCAL_INTERRUPT_DEVICE))
$(eval $(call add_define,PLAT_INTERRUPT_DEVICE))

DIR		:= $(IC_PATH)
include mk/obj.mk
