DIR		:= $(GET_PATH)

PLATFORM	:= atmega328p

CFLAGS		+= -std=gnu99 -O1

include mk/obj.mk
