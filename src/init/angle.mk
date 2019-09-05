
.PHONY:	version
NAME	= point
DEGREES	= 1
MINUTES	= 0
SECONDS	= 0

version:
	$(info Arc Version  : $(DEGREES)°$(MINUTES)'$(SECONDS)")
	$(info Arc Codename : $(NAME))
.SILENT:
