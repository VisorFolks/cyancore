TERRA_PATH	:= $(GET_PATH)

TERRAVISOR	:= 1
$(eval $(call add_define,TERRAVISOR))

include $(TERRA_PATH)/services/build.mk
include $(TERRA_PATH)/workers/build.mk
