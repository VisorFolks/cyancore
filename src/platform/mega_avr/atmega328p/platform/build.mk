DIR	:= $(GET_PATH)

CFLAGS	+= -DADC=$(ADC)			\
	   -DUART=$(UART)

include mk/obj.mk
