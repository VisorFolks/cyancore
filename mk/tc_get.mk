include mk/path.mk

AVR_TC_LINK	:= http://ww1.microchip.com/downloads/en/DeviceDoc/avr8-gnu-toolchain-3.6.2.1759-linux.any.x86_64.tar.gz
RISC_V_TC_LINK	:= https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.2.0-2019.05.3-x86_64-linux-ubuntu14.tar.gz
ARM_TC_LINK	:= https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2

.PHONY: get_all_tc get_avr_tc get_arm_tc get_riscv_tc

ifeq ($(MAKECMDGOALS),get_arm_tools)
ifneq ($(realpath $(TOOLS_ROOT)/arm-toolchain/bin/),)
$(error < ! > ARM-Toolchain is already present!)
endif
endif

ifeq ($(MAKECMDGOALS),get_avr_tools)
ifneq ($(realpath $(TOOLS_ROOT)/avr-toolchain/bin/),)
$(error < ! > AVR-Toolchain is already present!)
endif
endif

ifeq ($(MAKECMDGOALS),get_riscv_tools)
ifneq ($(realpath $(TOOLS_ROOT)/riscv-toolchain/bin/),)
$(error < ! > RISC-V Toolchain is alredy present!)
endif
endif


get_all_tc: get_avr_tc get_arm_tc get_riscv_tc

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

