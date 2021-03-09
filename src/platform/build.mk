#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates the build scripts from 
#			  all the platform directories
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

PLAT_DIR	:= $(GET_PATH)

ifeq ($(FAMILY),)
$(info < ! > Family of chip used in  project is not defined !)
$(error < x > Build Failed !)
endif
ifeq ($(PLATFORM),)
$(info < ! > Platform for project is not defined !)
$(error < x > Build Failed !)
endif

include $(PLAT_DIR)/$(FAMILY)/$(PLATFORM)/build.mk
