include mk/path.mk

ifeq ($(ARCH),avr)
TC	:= $(TOOLS_ROOT)/avr-toolchain/bin/avr
TI	:= $(TOOLS_ROOT)/avr-toolchain/avr/include/
TL	:= $(TOOLS_ROOT)/avr-toolchain/avr/lib/
AS	:= $(TC)-as
CC	:= $(TC)-gcc
LD	:= $(TC)-ld
OD	:= $(TC)-objdump
OC	:= $(TC)-objcopy
STRIP	:= $(TC)-strip
A2L	:= $(TC)-addr2line
endif

ifeq ($(MAKECMDGOALS),get_avr_tools)
ifneq ($(realpath $(TOOLS_ROOT)/avr-toolchain/bin/),)
$(error < ! > AVR-Toolchain is already present!)
endif
endif

.PHONY: get_avr_tools

get_avr_tools:
	$(info < ! > Fetching AVR Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd toolchain;		\
	wget -q $(AVR_TC_LINK) -O avr-toolchain.tar.gz;	\
	tar -xzf avr-toolchain.tar.gz;		\
	mv avr8-gnu-toolchain* avr-toolchain;		\
	rm -f *.tar.gz
	echo "< / > Done !"
