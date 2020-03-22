IC_PATH		:= $(GET_PATH)

CFLAGS		+= $(call add_define,LOCAL_INTERRUPT_DEVICE)		\
		   $(call add_define,PLAT_INTERRUPT_DEVICE)		\

DIR		:= $(IC_PATH)
include mk/obj.mk
