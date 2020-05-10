CONSOLE_PATH	:= $(GET_PATH)

CFLAGS		+= $(call add_define,EARLYCON_MEMBUF)		\
		   $(call add_define,CONSOLE_MEMBUF)		\
		   $(call add_define,EARLYCON_SERIAL)		\
		   $(call add_define,CONSOLE_SERIAL)

DIR		:= $(CONSOLE_PATH)
include mk/obj.mk
