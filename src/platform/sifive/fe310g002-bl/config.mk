#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: config.mk
# Description		: This file defines configuration for HiFive 1B
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
N_CORES		:= 1
$(eval $(call add_define,N_CORES))

CCSMP		:= 0
$(eval $(call add_define,CCSMP))

$(eval $(call add_define,BIT))

BOOT_CORE_ID:= 0
$(eval $(call add_define,BOOT_CORE_ID))

FLASH_START	:= 0x20000000
FLASH_SIZE	:= 0x10000	# 64K
RAM_START	:= 0x80000000
RAM_SIZE	:= 0x4000	# 16K
ITIM_START	:= 0x08000000
ITIM_SIZE	:= 0x2000	# 8K
HEAP_SIZE	?= 512
STACK_SIZE	?= 0xc00
STACK_SIZE_PCPU	?= 0xc00

$(eval $(call add_define,HEAP_SIZE))
$(eval $(call add_define,STACK_SIZE))
$(eval $(call add_define,STACK_SIZE_PCPU))

# Call this FLAG from Project config file if needed
XCLK		?= 16000000
ICLK		?= 72000000
$(eval $(call add_define,XCLK))
$(eval $(call add_define,ICLK))

N_EXCEP		:= 12
$(eval $(call add_define,N_EXCEP))

N_IRQ		:= 12
$(eval $(call add_define,N_IRQ))

N_PLAT_IRQS	:= 52
$(eval $(call add_define,N_PLAT_IRQS))

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
# Errata CIP-578
#======================================================================
ERRATA_CIP578	:= 1
$(eval $(call add_define,ERRATA_CIP578))
#======================================================================

#======================================================================
# PRCI Sysclk Configuration
#======================================================================
SYSCLK_ENABLE	:= 1
PRCI_CLK	:= 1
#======================================================================

#======================================================================
# Bootload Configuration
#======================================================================
$(eval $(call add_define,BOOTLOADER))
#======================================================================
