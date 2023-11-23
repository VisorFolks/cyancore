#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts
#			  from visor directories
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

VISOR_DIR	:= $(GET_PATH)

INCLUDE		+= $(SRC)/include/visor/

include $(VISOR_DIR)/common/build.mk
ifneq ($(EXE_MODE),)
include $(VISOR_DIR)/$(EXE_MODE)/build.mk
endif
