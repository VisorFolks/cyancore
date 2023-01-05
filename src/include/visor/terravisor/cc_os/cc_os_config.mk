#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: kern_config.mk
# Description		: This file consists of CC_OS kernal configuration
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

CC_OS_USE_DYNAMIC 		?= 0
CC_OS_HEAP_SIZE 		?= 1024
CC_OS_MAX_THREAD 		?= 2
CC_OS_IDLE_TASK_STACK_LEN 	?= 255
CC_OS_POWER_SAVE_EN 		?= 0

$(eval $(call add_define,CC_OS_USE_DYNAMIC))
$(eval $(call add_define,CC_OS_HEAP_SIZE))
$(eval $(call add_define,CC_OS_MAX_THREAD))
$(eval $(call add_define,CC_OS_IDLE_TASK_STACK_LEN))
$(eval $(call add_define,CC_OS_POWER_SAVE_EN))
