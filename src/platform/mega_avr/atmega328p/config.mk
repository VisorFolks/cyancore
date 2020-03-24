# Configuration file for platform

FCLK		:= 16000000
CFLAGS		+= $(call add_define,FCLK)

N_CORES		:= 1
CFLAGS          += $(call add_define,N_CORES)

N_INT		:= 26
CFLAGS		+= $(call add_define,N_INT)

MAX_INTERRUPTS_PER_DEVICE		:= 2
CFLAGS		+= $(call add_define,MAX_INTERRUPTS_PER_DEVICE)

N_IRQ		:= 25
CFLAGS		+= $(call add_define,N_IRQ)

N_PORT		:= 3
CFLAGS          += $(call add_define,N_PORT)

MEMBUF_SIZE	:= 512
CFLAGS          += $(call add_define,MEMBUF_SIZE)

UART0		:= 1
CFLAGS		+= $(call add_define,UART0)
