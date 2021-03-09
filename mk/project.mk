#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: project.mk
# Description		: This scipt helps the build system in searching
#			  project name from command arguments
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Project Search >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

include mk/path.mk
include mk/mk_helper.mk

T_ALLOWLIST	+= help list

.PHONY: aux_target

default: aux_target
	make $(PROJECT) cyancore -j$(N_HOSTS)

cyancore: version elf
	$(info < / > Done !)

clean:
	$(info < ! > Removing $(PROJECT) binaries ...)
	rm -rf $(OUT)

list:
	$(info Available projects are :)
	ls $(SRC)/projects/ -I *.template

ifeq ($(findstring $(MAKECMDGOALS),$(T_ALLOWLIST)),)
ifneq ($(firstword $(MAKECMDGOALS)),clean)
ifneq ($(firstword $(MAKECMDGOALS)),default)
ifneq ($(firstword $(MAKECMDGOALS)),cyancore)
PROJECT		:= $(firstword $(MAKECMDGOALS))
CMD		:= $(word 2,$(MAKECMDGOALS))
ifeq ($(CMD),)
CMD		:= default
else
CMD		:=
endif

.PHONY: $(PROJECT)
$(PROJECT): $(CMD)

endif
endif
endif

ifeq ($(PROJECT),)
$(info < x > Project name was not specified...)
$(info < ! > Please try running `make help` for more details)
$(error < x > Build Failed!)
else ifeq ($(filter $(PROJECT), $(shell ls $(SRC)/projects)),)
$(info < x > Invalid project name...)
$(info < ! > Run `make list` to get list of projects)
$(error < x > Build Failed!)
endif
endif
