include mk/path.mk

include mk/avr_tools.mk
include mk/arm_tools.mk
include mk/riscv_tools.mk

.PHONY: get_all_tools get_avr_tools get_arm_tools get_riscv_tools

get_all_tools: get_avr_tools get_arm_tools get_riscv_tools
