DIR		:= $(GET_PATH)

$(eval $(call add_define,EARLYCON_MEMBUF))
$(eval $(call add_define,CONSOLE_MEMBUF))

ifeq ($(filter $(EARLYCON_MEMBUF) $(CONSOLE_MEMBUF),1),1)
include mk/obj.mk
endif
