#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Project Search >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

include mk/path.mk

default:
	make $(PROJECT) all -j$(N_HOSTS)

.PHONY: all --dependency clean list

all: version --dependency lib obj elf
	$(info < / > Done !)

--dependency:
	mkdir -p $(OUT)

clean:
	$(info < ! > Removing $(PROJECT) binaries ...)
	rm -rf $(OUT)

list:
	$(info Available projects are :)
	ls -1 $(SRC)/projects/

ifneq ($(MAKECMDGOALS),help)
ifneq ($(MAKECMDGOALS),get_all_tc)
ifneq ($(MAKECMDGOALS),get_arm_tc)
ifneq ($(MAKECMDGOALS),get_avr_tc)
ifneq ($(MAKECMDGOALS),get_riscv_tc)
ifneq ($(MAKECMDGOALS),list)

ifneq ($(firstword $(MAKECMDGOALS)),clean)
ifneq ($(firstword $(MAKECMDGOALS)),default)
ifneq ($(firstword $(MAKECMDGOALS)),all)
PROJECT		:= $(firstword $(MAKECMDGOALS))
CMD		:= $(word 2,$(MAKECMDGOALS))
ifeq ($(CMD),)
CMD		:= default
else
CMD		:=
endif
.PHONY: $(PROJECT)

$(PROJECT): $(CMD)
	echo > /dev/null
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

