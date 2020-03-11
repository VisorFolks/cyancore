# Configuration file for platform

FCLK		:= 16000000
CFLAGS		+= $(call add_define,FCLK)

N_CORES		:= 1
CFLAGS          += $(call add_define,N_CORES)

MEMBUF_SIZE	:= 512
CFLAGS          += $(call add_define,MEMBUF_SIZE)

UART0		:= 1
CFLAGS		+= $(call add_define,UART0)
