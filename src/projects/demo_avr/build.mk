DIR		:= $(GET_PATH)

FAMILY		:= mega_avr
PLATFORM	:= atmega328p
AUTOINIT	:= 1

OPTIMIZATION	:= s

include mk/obj.mk
