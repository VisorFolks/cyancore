#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: config.mk
# Description		: This file defines configuration for atmega328p
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

$(eval $(call add_define,BIT))

BOOT_CORE_ID:= 0
$(eval $(call add_define,BOOT_CORE_ID))

# Call this FLAG from Project config file if needed
FCLK		?= 16000000
$(eval $(call add_define,FCLK))

N_INT		:= 26
$(eval $(call add_define,N_INT))

N_IRQ		:= 25
$(eval $(call add_define,N_IRQ))

MAX_INTERRUPTS_PER_DEVICE	:= 2
$(eval $(call add_define,MAX_INTERRUPTS_PER_DEVICE))

USE_SPINLOCK	?= 1
$(eval $(call add_define,USE_SPINLOCK))

#======================================================================
# MEMBUF Configuration
#======================================================================
MEMBUF_SIZE	?= 128
$(eval $(call add_define,MEMBUF_SIZE))
#======================================================================

#======================================================================
# GPIO Configuration
#======================================================================
GPIO		?= 1
N_PORT		:= 3
$(eval $(call add_define,GPIO))
$(eval $(call add_define,N_PORT))
#======================================================================

#======================================================================
# UART Configuration
#======================================================================
UART		?= 1
N_UART		:= 1
$(eval $(call add_define,UART))
$(eval $(call add_define,N_UART))
#======================================================================

#======================================================================
# WDT Configuration
#======================================================================
WDT		?= 1
N_WDT		:= 1
$(eval $(call add_define,WDT))
$(eval $(call add_define,N_WDT))
#======================================================================
