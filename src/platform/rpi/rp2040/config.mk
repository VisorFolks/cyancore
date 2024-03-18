#
# CYANCORE LICENSE
# Copyrights (C) 2023, Cyancore Team
#
# File Name		: config.mk
# Description		: This file defines configuration for RP2040
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#======================================================================
# Configuration file for Platforms
#======================================================================

#======================================================================
# Platform Configuration
# Do not alter below FLAGS unless explicitly mentioned
#======================================================================
N_CORES		:= 2
$(eval $(call add_define,N_CORES))

CCSMP		?= 1
$(eval $(call add_define,CCSMP))

$(eval $(call add_define,BIT))

BOOT_CORE_ID:= 0
$(eval $(call add_define,BOOT_CORE_ID))

FLASH_START	:= 0x10000000
FLASH_SIZE	:= 0x1000000	# 16M
RAM_START	:= 0x20000000
RAM_SIZE	:= 0x42000	# 264K
HEAP_SIZE	?= 16K
STACK_SIZE	?= 8K
STACK_SIZE_PCPU	?= 4K

$(eval $(call add_define,HEAP_SIZE))
$(eval $(call add_define,STACK_SIZE))
$(eval $(call add_define,STACK_SIZE_PCPU))

# Call this FLAG from Project config file if needed
XCLK		?= 12000000
ICLK		?= 12000000
$(eval $(call add_define,XCLK))
$(eval $(call add_define,ICLK))

N_EXCEP		:= 15
$(eval $(call add_define,N_EXCEP))

N_IRQ		:= 26
$(eval $(call add_define,N_IRQ))

MAX_INTERRUPTS_PER_DEVICE	:= 1
$(eval $(call add_define,MAX_INTERRUPTS_PER_DEVICE))

USE_SPINLOCK	?= 1
$(eval $(call add_define,USE_SPINLOCK))

#======================================================================
# MEMBUF Configuration
#======================================================================
MEMBUF_SIZE	?= 1024
$(eval $(call add_define,MEMBUF_SIZE))
#======================================================================

#======================================================================
# GPIO Configuration
#======================================================================
N_PORT		:= 1
$(eval $(call add_define,N_PORT))
#======================================================================

#======================================================================
# Timer: Sched timer/wall clock
#======================================================================
USE_TIMER	?= 1
$(eval $(call add_define,USE_TIMER))
#======================================================================
