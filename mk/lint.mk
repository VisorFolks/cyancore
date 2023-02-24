#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: lint.mk
# Description		: This file accumulates all the source files
#			  and runs linting tool
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Linting Tool >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

LT		:= $(shell which cppcheck)

LINT_FLAGS	+= --error-exitcode=25 --std=c11 	\
		   --max-ctu-depth=12 --max-configs=12	\
		   --enable=all -q -v			\
		   --suppress=unusedFunction

--lint: $(DEP_SRCS)
ifeq ($(LT),)
$(info < ! > cppcheck is not installed... Please install 'cppcheck' !)
$(error < x > Checking failed !)
endif
	@echo "Running Lint ..."
	$(LT) $^ $(LINT_FLAGS)
	@echo "< / > Done!"
