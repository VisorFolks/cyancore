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

P_TARGETS	+= default cyancore check version copy_to_remote clean_remote
T_ALLOWLIST	+= help list clean all_projects
PROJECT_LIST	:= $(shell ls $(SRC)/projects/ -I *.template)

.PHONY: aux_target

default: aux_target
	make $(PROJECT) cyancore -j$(N_JOBS)

all_projects:
	for project in $(PROJECT_LIST);	\
	do				\
		make $$project check;	\
		make $$project;		\
	done

cyancore: version elf
	$(info < / > Done !)

clean:
	$(info < ! > Removing $(PROJECT) binaries ...)
	rm -rf $(OUT)

list:
	$(info Available projects are :)
	echo $(PROJECT_LIST)

check: --lint


ifeq ($(findstring $(MAKECMDGOALS),$(T_ALLOWLIST)),)
ifneq ($(firstword $(MAKECMDGOALS)),clean)
ifneq ($(firstword $(MAKECMDGOALS)),default)
ifneq ($(firstword $(MAKECMDGOALS)),cyancore)
ifneq ($(firstword $(MAKECMDGOALS)),check)
ifneq ($(firstword $(MAKECMDGOALS)),copy_to_target)
PROJECT		?= $(firstword $(MAKECMDGOALS))
CMD		:= $(word 2,$(MAKECMDGOALS))
ifeq ($(CMD),)
CMD		:= default
endif

.PHONY: $(PROJECT)
$(PROJECT): $(CMD)

endif
endif
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

ifeq ($(findstring $(MAKECMDGOALS),$(T_ALLOWLIST)),)
include $(SRC)/sources.mk
include mk/tc.mk
endif

ifeq ($(findstring $(CMD),$(T_ALLOWLIST) default clean cyancore copy_to_target),)
$(CMD): $(filter %/$(CMD),$(DEP_LIBS) $(DEP_OBJS))
	if [ "$<" = "" ]; then			\
		echo "No such target: $@";	\
		exit 2;				\
	fi
endif
include mk/copy_to_remote.mk
