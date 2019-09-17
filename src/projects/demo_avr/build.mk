DIR		:= $(GET_PATH)

PLATFORM	:= atmega328p

CFLAGS		+= -O2

include mk/obj.mk
