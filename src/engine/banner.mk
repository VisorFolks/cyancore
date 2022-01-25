#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: banner.mk
# Description		: This script prints banner while starting build
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

.PHONY:	version
NAME		= Helium
VERSION		= 0x01000200

$(eval $(call add_define,VERSION))

version:
	$(info Building Project $(PROJECT))
	$(info ------------------------------------)
	$(info Platform          : $(PLATFORM))
	$(info Architecture      : $(ARCH)$(BIT)-$(ARCH_VARIANT))
	$(info Cyancore Version  : $(VERSION))
	$(info Cyancore Codename : $(NAME))
	$(info )
