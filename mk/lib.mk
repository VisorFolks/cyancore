#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: lib.mk
# Description		: This file accumulates all the object files
#			  and generates the library
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Library Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/lobj.mk

LIB		:= $(addprefix $(OUT)/$(DIR)/,$(LIB))
DEP_LIB_PATH	+= -L $(OUT)/$(DIR)
DEP_LIBS	+= $(LIB)

$(LIB): $(LIB_OBJS)
	@echo "Lib: Generating $(@F) ..."
	$(AR) rc $@ $^

LIB_INCLUDE_PATH:=
LIB_OBJS	:=
LIB		:=
