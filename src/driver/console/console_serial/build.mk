#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of console serial
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

DIR		:= $(GET_PATH)

$(eval $(call add_define,EARLYCON_SERIAL))
$(eval $(call add_define,CONSOLE_SERIAL))

ifeq ($(filter $(CONSOLE_SERIAL) $(EARLYCON_SERIAL),1),1)
include mk/obj.mk
endif
