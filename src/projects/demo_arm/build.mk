ARCH		:= arm-v7
BIT		:= 32
PLATFORM	:= tm4c123gh6pm
TARGET_FLAGS	+= -march=armv7-m	\
		   -mtune=cortex-m4	\
		   -mabi=aapcs-linux

DIR		:= $(GET_PATH)

CFLAGS		+= -O2

include mk/obj.mk
