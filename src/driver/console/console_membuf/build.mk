#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of console_membuf
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

DIR		:= $(GET_PATH)

$(eval $(call add_define,EARLYCON_MEMBUF))
$(eval $(call add_define,CONSOLE_MEMBUF))

ifeq ($(filter $(EARLYCON_MEMBUF) $(CONSOLE_MEMBUF),1),1)
include mk/obj.mk
endif
