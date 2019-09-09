ARCH		:= avr
BIT		:= 8
PLATFORM	:= atmega328p
TARGET_FLAGS	+= -mmcu=atmega328p

DIR		:= $(GET_PATH)

CFLAGS		+= -O2

include mk/obj.mk
