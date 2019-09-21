
.PHONY:	version
NAME	= point
VERSION	= 0x00000100

CFLAGS	+= -DVERSION=$(VERSION)

version:
	$(info Building Project $(PROJECT))
	$(info ------------------------------------)
	$(info Platform          : $(PLATFORM))
	$(info Architecture      : $(ARCH)-$(BIT))
	$(info Arc Version       : $(VERSION))
	$(info Arc Codename      : $(NAME))
	$(info )