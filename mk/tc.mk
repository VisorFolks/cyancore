include mk/path.mk

ifeq ($(ARCH),arm-v7)
TC	:= $(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi
TI	:= $(TOOLS_ROOT)/arm-toolchain/arm-none-eabi/include
TL	:= $(TOOLS_ROOT)/arm-toolchain/arm-none-eabi/lib
endif

ifeq ($(ARCH),riscv)
TC	:= $(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf
TI	:= $(TOOLS_ROOT)/risc-v-toolchain/riscv64-unknown-elf/include
TL	:= $(TOOLS_ROOT)/risc-v-toolchain/riscv64-unknown-elf/lib
endif

ifeq ($(ARCH),avr5)
TC	:= $(TOOLS_ROOT)/avr-toolchain/bin/avr
TI	:= $(TOOLS_ROOT)/avr-toolchain/lib/gcc/avr/5.4.0/include-fixed
TL	:= $(TOOLS_ROOT)/avr-toolchain/avr/lib
endif

ifneq ($(ARCH),)
AS	:= $(TC)-as
CC	:= $(TC)-gcc
LD	:= $(TC)-ld
OD	:= $(TC)-objdump
OC	:= $(TC)-objcopy
STRIP	:= $(TC)-strip
A2L	:= $(TC)-addr2line
SIZE	:= $(TC)-size
endif

ifeq ($(realpath $(TI)),)
$(info < ! > Toolchain is not available !)
$(info < ! > Try running 'make help' ...)
$(error < x > Build Failed !)
endif
