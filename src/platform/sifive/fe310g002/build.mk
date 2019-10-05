FE310G002_DIR	:= $(GET_PATH)

ARCH		:= riscv
BIT		:= 32
TARGET_FLAGS	:= -march=rv32imac	\
		   -mabi=ilp32

OUTPUT_FORMAT	:= elf32-littleriscv

PLAT_INCLUDE	+= -I $(FE310G002_DIR)/include

include $(FE310G002_DIR)/platform/build.mk

