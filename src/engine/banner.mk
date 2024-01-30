#
# CYANCORE LICENSE
# Copyrights (C) 2019-2022, Cyancore Team
#
# File Name		: banner.mk
# Description		: This script prints banner while starting build
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

NAME		= Boron
VERSION		= 0x01000400

$(eval $(call add_define,VERSION))

version:
	$(info Building Project $(PROJECT))
	$(info ------------------------------------)
	$(info Platform          : $(PLATFORM))
	$(info Architecture      : $(ARCH)$(BIT)-$(ARCH_VARIANT))
	$(info Cyancore Version  : $(VERSION))
	$(info Cyancore Codename : $(NAME))
	$(info )
