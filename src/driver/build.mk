DRIVER_PATH	:= $(GET_PATH)

include $(DRIVER_PATH)/console/build.mk

ifeq ($(ADC),1)
include $(DRIVER_PATH)/adc/build.mk
endif

ifeq ($(UART),1)
include $(DRIVER_PATH)/uart/build.mk
endif

DIR		:=$(DRIVER_PATH)
include mk/obj.mk
