#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: tc_get.mk
# Description		: This file helps developer get toolchains
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

include mk/path.mk

T_ALLOWLIST	+= get_all_tc get_avr_tc get_arm_tc get_riscv_tc

# GIT REPO RECOMMENDED
# Provide git repo path for toolchains for better experience
AVR_TC_REPO	?=
RISC_V_TC_REPO	?=
ARM_TC_REPO	?=

get_all_tc: --tc_clear get_avr_tc get_arm_tc get_riscv_tc

--tc_clear:
	rm -rf $(TOOLS_ROOT)

get_arm_tc: $(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi-gcc
$(TOOLS_ROOT)/arm-toolchain/bin/arm-none-eabi-gcc:
ifeq ($(ARM_TC_REPO),)
	$(error < x > Please provide valid ARM Toolchain git link)
endif
	$(info < ! > Fetching ARM Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(ARM_TC_REPO) arm-toolchain; chmod +x -R $(@D)/..
	echo "< / > Done !"

get_avr_tc: $(TOOLS_ROOT)/avr-toolchain/bin/avr-gcc
$(TOOLS_ROOT)/avr-toolchain/bin/avr-gcc:
ifeq ($(AVR_TC_REPO),)
	$(error < x > Please provide valid AVR Toolchain git link)
endif
	$(info < ! > Fetching AVR Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(AVR_TC_REPO) avr-toolchain; chmod +x -R $(@D)/..
	echo "< / > Done !"

get_riscv_tc: $(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf-gcc
$(TOOLS_ROOT)/risc-v-toolchain/bin/riscv64-unknown-elf-gcc:
ifeq ($(RISC_V_TC_REPO),)
	$(error < x > Please provide valid RISC-V Toolchain git link)
endif
	$(info < ! > Fetching RISC-V Toolchain ...)
	$(info < ? > Please be patient as this might take a while ...)
	mkdir -p toolchain
	cd $(TOOLS_ROOT); git clone $(RISC_V_TC_REPO) risc-v-toolchain; chmod +x -R $(@D)/..
	echo "< / > Done !"

