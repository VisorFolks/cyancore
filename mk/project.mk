#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Project Search >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

include mk/path.mk
include mk/mk_helper.mk

default: dependency_targets
	make $(PROJECT) arc -j$(N_HOSTS)

.PHONY: arc --dependency clean list lib elf slib dependency_targets

arc: version --dependency elf
	$(info < / > Done !)

--dependency:
	mkdir -p $(OUT)

clean:
	$(info < ! > Removing $(PROJECT) binaries ...)
	rm -rf $(OUT)

list:
	$(info Available projects are :)
	ls $(SRC)/projects/ -I *.template

ifneq ($(MAKECMDGOALS),help)
ifneq ($(MAKECMDGOALS),get_all_tc)
ifneq ($(MAKECMDGOALS),get_arm_tc)
ifneq ($(MAKECMDGOALS),get_avr_tc)
ifneq ($(MAKECMDGOALS),get_riscv_tc)
ifneq ($(MAKECMDGOALS),list)

ifneq ($(firstword $(MAKECMDGOALS)),clean)
ifneq ($(firstword $(MAKECMDGOALS)),default)
ifneq ($(firstword $(MAKECMDGOALS)),arc)
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
endif
endif
endif
endif
endif

