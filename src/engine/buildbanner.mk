.PHONY:	version
NAME		= Aurora
VERSION		= 0x00000100

$(eval $(call add_define,VERSION))

version:
	$(info Building Project $(PROJECT))
	$(info ------------------------------------)
	$(info Platform          : $(PLATFORM))
	$(info Architecture      : $(ARCH)-$(BIT))
	$(info Cyancore Version  : $(VERSION))
	$(info Cyancore Codename : $(NAME))
	$(info )
