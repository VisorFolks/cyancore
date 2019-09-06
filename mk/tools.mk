include mk/path.mk

AVR_TC_LINK	:= http://ww1.microchip.com/downloads/en/DeviceDoc/avr8-gnu-toolchain-3.6.2.1759-linux.any.x86_64.tar.gz
RISC_V_TC_LINK	:= https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.2.0-2019.05.3-x86_64-linux-ubuntu14.tar.gz
ARM_TC_LINK	:= https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2



include mk/avr_tools.mk
include mk/arm_tools.mk
include mk/riscv_tools.mk

.PHONY: get_all_tools get_avr_tools get_arm_tools get_riscv_tools

get_all_tools: get_avr_tools get_arm_tools get_riscv_tools
