DRIVER_PATH	:= $(GET_PATH)
#LD_SCRIPT	+= -T $(DRIVER_PATH)/driver.ld

include $(DRIVER_PATH)/console/build.mk

DIR		:=$(DRIVER_PATH)
include mk/obj.mk
