include mk/path.mk

ifeq ($(ARCH),arm)
TC	:= $(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi
TI	:= $(TOOLS_ROOT)/arm-toolchain/arm-none-eabi/include
TL	:= $(TOOLS_ROOT)/arm-toolchain/arm-none-eabi/lib
AS	:= $(TC)-as
CC	:= $(TC)-gcc
LD	:= $(TC)-ld
OD	:= $(TC)-objdump
OC	:= $(TC)-objcopy
STRIP	:= $(TC)-strip
A2L	:= $(TC)-addr2line
endif

ifeq ($(MAKECMDGOALS),get_arm_tools)
ifneq ($(realpath $(TOOLS_ROOT)/arm-toolchain/bin/),)
$(error < ! > ARM-Toolchain is already present!)
endif
endif

.PHONY: get_arm_tools

get_arm_tools:
	$(info < ! > Fetching ARM Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd toolchain;	\
	wget -q $(ARM_TC_LINK) -O arm-toolchain.tar.bz2;		\
	tar -xjf arm-toolchain.tar.bz2;		\
	mv gcc-arm-none-eabi* arm_toolchain;	\
	rm -f *.tar.bz2
	echo "< / > Done !"
