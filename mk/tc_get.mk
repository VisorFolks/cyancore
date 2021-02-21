include mk/path.mk

T_ALLOWLIST	+= get_all_tc get_avr_tc get_arm_tc get_riscv_tc

AVR_TC_REPO	:=
RISC_V_TC_REPO	:=
ARM_TC_REPO	:=

get_all_tc: --tc_clear get_avr_tc get_arm_tc get_riscv_tc

--tc_clear:
	rm -rf $(TOOLS_ROOT)

get_arm_tc: $(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi-gcc
$(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi-gcc:
	$(info < ! > Fetching ARM Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(ARM_TC_REPO) arm-toolchain; chmod +x -R $(@D)/..
	echo "< / > Done !"

get_avr_tc: $(TOOLS_ROOT)/avr-toolchain/bin/avr-gcc
$(TOOLS_ROOT)/avr-toolchain/bin/avr-gcc:
	$(info < ! > Fetching AVR Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(AVR_TC_REPO) avr-toolchain; chmod +x -R $(@D)/..
	echo "< / > Done !"

get_riscv_tc: $(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf-gcc
$(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf-gcc:
	$(info < ! > Fetching RISC-V Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(RISC_V_TC_REPO) risc-v-toolchain; chmod +x -R $(@D)/..
	echo "< / > Done !"

