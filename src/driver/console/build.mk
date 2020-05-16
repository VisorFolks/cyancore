CONSOLE_PATH	:= $(GET_PATH)

$(eval $(call add_define,EARLYCON_MEMBUF))
$(eval $(call add_define,CONSOLE_MEMBUF))
$(eval $(call add_define,EARLYCON_SERIAL))
$(eval $(call add_define,CONSOLE_SERIAL))

DIR		:= $(CONSOLE_PATH)
include mk/obj.mk
