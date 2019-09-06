ARCH		:= avr
BIT		:= 8
TARGET_FLAGS	+= -mmcu=atmega328p


DIR		:= $(GET_PATH)

DEPS_SRCS	:= project.c

include mk/obj.mk
