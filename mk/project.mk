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

include mk/mk_helper.mk
include mk/qemu.mk
include mk/picotool.mk

P_TARGETS	+= default cyancore check version copy_to_remote clean_remote
T_ALLOWLIST	+= list clean all_projects
PROJECT_LIST	:= $(shell ls projects/ -I *.template -I *.src)

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

copy_to_remote: --cpremote
clean_remote: --rmremote


ifeq ($(findstring $(MAKECMDGOALS),$(T_ALLOWLIST)),)
ifeq ($(findstring $(firstword $(MAKECMDGOALS)),$(P_TARGETS)),)
PROJECT		?= $(firstword $(MAKECMDGOALS))
CMD		:= $(word 2,$(MAKECMDGOALS))
ifeq ($(CMD),)
CMD		:= default
endif

$(PROJECT): $(CMD)

endif

ifeq ($(PROJECT),)
$(info < x > Project name was not specified...)
$(info < ! > Please try running `make help` for more details)
$(error < x > Build Failed!)
else ifeq ($(filter $(PROJECT), $(shell ls projects)),)
$(info < x > Invalid project name...)
$(info < ! > Run `make list` to get list of projects)
$(error < x > Build Failed!)
endif

include $(SRC)/sources.mk
include mk/tc.mk
include mk/copy_to_remote.mk
endif

ifeq ($(findstring $(CMD),$(T_ALLOWLIST) $(P_TARGETS)),)
$(CMD): $(filter %/$(CMD),$(DEP_LIBS) $(DEP_OBJS))
	if [ "$<" = "" ]; then			\
		echo "No such target: $@";	\
		exit 2;				\
	fi
endif
