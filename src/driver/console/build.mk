CONSOLE_PATH	:= $(GET_PATH)

$(eval $(call add_define,CONSOLE))
include $(CONSOLE_PATH)/console_membuf/build.mk
include $(CONSOLE_PATH)/console_serial/build.mk

DIR		:= $(CONSOLE_PATH)
include mk/obj.mk
