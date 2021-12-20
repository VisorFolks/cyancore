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
ifeq ($(CONSOLE),1)
# Call this FLAG from Project config file
EARLYCON_MEMBUF	?= 0
ifeq ($(EARLYCON_MEMBUF),1)
MEMBUF_SIZE	?= 128
$(eval $(call add_define,MEMBUF_SIZE))
endif
# Call this FLAG from Project config file
CONSOLE_MEMBUF	?= 0
ifeq ($(CONSOLE_MEMBUF),1)
MEMBUF_SIZE	?= 128
$(eval $(call add_define,MEMBUF_SIZE))
endif
endif
#======================================================================

#======================================================================
# GPIO Configuration
#======================================================================
# Call this FLAG from Project config file
GPIO		?= 0
ifeq ($(GPIO),1)
N_PORT		:= 3
$(eval $(call add_define,N_PORT))
endif
#======================================================================

#======================================================================
# UART Configuration
#======================================================================
# UART can directly be used by Adding UART0 to Project config file
UART0		?= 0
ifeq ($(CONSOLE),1)
# Call this FLAG from Project config file
EARLYCON_SERIAL	?= 0
ifeq ($(EARLYCON_SERIAL),1)
UART0		:= 1
endif
# Call this FLAG from Project config file
CONSOLE_SERIAL	?= 0
ifeq ($(CONSOLE_SERIAL),1)
UART0		:= 1
endif
endif
#======================================================================
