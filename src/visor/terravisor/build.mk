TERRA_PATH	:= $(GET_PATH)

include $(TERRA_PATH)/bootloader/build.mk
include $(TERRA_PATH)/worker/build.mk
