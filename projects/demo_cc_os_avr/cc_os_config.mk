#
# CYANCORE LICENSE
# Copyrights (C) 2019-2023, Cyancore Team
#
# File Name		: kern_config.mk
# Description		: This file consists of CC_OS kernal configuration
# Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
# Organisation		: Cyancore Core-Team
#

ccosconfig_CC_OS_USE_DYNAMIC 		:= 1
ccosconfig_CC_OS_HEAP_SIZE 		:= 1024
ccosconfig_CC_OS_MAX_THREAD 		:= 3
ccosconfig_CC_OS_TASK_STACK_LEN 	:= 255
ccosconfig_CC_OS_POWER_SAVE_EN 		:= 0

include $(CC_OS_ROOT)/cc_os_config.mk
