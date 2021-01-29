T_SERVICES	:= $(GET_PATH)

include $(T_SERVICES)/bootloader/build.mk

ifeq ($(TERRAKERN),1)
include $(T_SERVICES)/kernel/build.mk
endif

DIR		:= $(T_SERVICES)
include mk/obj.mk
