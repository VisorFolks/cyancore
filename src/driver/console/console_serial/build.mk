DIR		:= $(GET_PATH)

$(eval $(call add_define,EARLYCON_SERIAL))
$(eval $(call add_define,CONSOLE_SERIAL))

ifeq ($(filter $(CONSOLE_SERIAL) $(EARLYCON_SERIAL),1),1)
include mk/obj.mk
endif
