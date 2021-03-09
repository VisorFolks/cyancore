#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Descrption		: Build script for arch directory.
#			  Here various checkes are performed based on which
#			  correct target-arch directory is picked up.
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

ARCH_DIR	:= $(GET_PATH)

ifeq ($(ARCH),)
$(info < ! > CPU - Architecture is not defined !)
$(error < x > Build Failed !)
endif

ifeq ($(BIT),)
$(info < ! > CPU - Data Width is not defined !)
$(error < x > Build Failed !)
endif

ifeq ($(ARCH_VARIANT),)
$(info < ! > CPU - Architecture Variant is not defined !)
$(error < x > Build Failed !)
endif

ifeq ($(EXE_MODE),)
$(info < ! > CPU - Execution mode is not defined !)
$(error < x > Build Failed !)
endif

$(eval $(call add_define,ARCH))
$(eval $(call add_define,BIT))
$(eval $(call add_define,ARCH_VARIANT))

include $(ARCH_DIR)/$(ARCH)/$(BIT)/$(ARCH_VARIANT)/$(EXE_MODE)/build.mk
