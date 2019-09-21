DRIVER_PATH	:= $(GET_PATH)

ifeq ($(ADC),1)
include $(DRIVER_PATH)/adc/build.mk
endif

ifeq ($(UART),1)
include $(DRIVER_PATH)/uart/build.mk
endif
