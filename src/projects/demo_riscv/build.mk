ARCH		:= riscv
BIT		:= 32
PLATFORM	:= freedom_e310
TARGET_FLAGS	+= -march=rv32imac	\
		   -mabi=ilp32

DIR		:= $(GET_PATH)

CFLAGS		+= -O2

include mk/obj.mk
