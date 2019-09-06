include mk/path.mk

ifeq ($(ARCH),riscv)
TC	:= $(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf
TI	:= $(TOOLS_ROOT)/risc-v-toolchain/riscv64-unknown-elf/include
TL	:= $(TOOLS_ROOT)/risc-v-toolchain/riscv64-unknown-elf/lib
AS	:= $(TC)-as
CC	:= $(TC)-gcc
LD	:= $(TC)-ld
OD	:= $(TC)-objdump
OC	:= $(TC)-objcopy
STRIP	:= $(TC)-strip
A2L	:= $(TC)-addr2line
endif

ifeq ($(MAKECMDGOALS),get_riscv_tools)
TEMP	:= $(TC)
TC	:= $(TOOLS_ROOT)/risc-v-toolchain/bin/
ifneq ($(realpath $(TC)),)
$(error < ! > RISC-V Toolchain is alredy present!)
endif
TC	:= $(TEMP)
endif

.PHONY: get_riscv_tools

get_riscv_tools:
	$(info < ! > Fetching RISC-V Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd toolchain;		\
	wget -q $(RISC_V_TC_LINK) -O risc-v-toolchain.tar.gz;	\
	tar -xzf risc-v-toolchain.tar.gz;	\
	mv riscv64-unknown-elf-gcc* risc-v-toolchain;	\
	rm *.tar.gz
	echo "< / > Done !"

