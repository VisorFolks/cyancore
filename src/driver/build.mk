DRIVER_PATH	:= $(GET_PATH)

include $(DRIVER_PATH)/console/build.mk
include $(DRIVER_PATH)/interrupt/build.mk

DIR		:=$(DRIVER_PATH)
include mk/obj.mk
