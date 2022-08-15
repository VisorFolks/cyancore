#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file builds cyancore engine core sources
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

DIR		:= $(GET_PATH)

BOOTMSGS        ?= 1
$(eval $(call add_define,BOOTMSGS))

ifneq ($(filter $(BOOTMSGS) $(STDLOG_MEMBUF)\
	$(EARLYCON_SERIAL) $(CONSOLE_SERIAL),1),1)
NOLOGS		:= 1
else
NOLOGS		:= 0
endif

$(eval $(call add_define,NOLOGS))

include $(DIR)/banner.mk
include mk/elf.mk
