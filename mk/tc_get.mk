include mk/path.mk

T_ALLOWLIST	+= get_all_tc get_avr_tc get_arm_tc get_riscv_tc

AVR_TC_REPO	:= git@192.168.3.100:Toolchains/avr-toolchain.git -b linux_x64_v5.4.0
RISC_V_TC_REPO	:= git@192.168.3.100:Toolchains/risc-v-toolchain.git -b linux_x64_v8.2.0
ARM_TC_REPO	:= git@192.168.3.100:Toolchains/arm-toolchain.git -b linux_x64_v7.3.1

get_all_tc: --tc_clear get_avr_tc get_arm_tc get_riscv_tc

--tc_clear:
	rm -rf $(TOOLS_ROOT)

get_arm_tc: $(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi-gcc
$(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi-gcc:
	$(info < ! > Fetching ARM Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(ARM_TC_REPO); chmod +x -R $(@D)/..
	echo "< / > Done !"

get_avr_tc: $(TOOLS_ROOT)/avr-toolchain/bin/avr-gcc
$(TOOLS_ROOT)/avr-toolchain/bin/avr-gcc:
	$(info < ! > Fetching AVR Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(AVR_TC_REPO); chmod +x -R $(@D)/..
	echo "< / > Done !"

get_riscv_tc: $(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf-gcc
$(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf-gcc:
	$(info < ! > Fetching RISC-V Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(RISC_V_TC_REPO); chmod +x -R $(@D)/..
	echo "< / > Done !"

