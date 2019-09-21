DIR		:= $(GET_PATH)

FAMILY		:= mega_avr
PLATFORM	:= atmega328p

CFLAGS		+= -O2

include mk/obj.mk
