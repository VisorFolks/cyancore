DRIVER_PATH	:= $(GET_PATH)

include $(DRIVER_PATH)/console/build.mk
include $(DRIVER_PATH)/chipset/$(FAMILY)/build.mk


DIR		:=$(DRIVER_PATH)
include mk/obj.mk
