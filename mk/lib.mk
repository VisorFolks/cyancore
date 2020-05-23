#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Library Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/lobj.mk

LIB		:= $(addprefix $(OUT)/$(DIR)/,$(LIB))
DEP_LIB_PATH	+= -L $(OUT)/$(DIR)
DEP_LIBS	+= $(LIB)

$(LIB): $(HEADER) $(LIB_OBJS)
	@echo "Generating $(notdir $@) ..."
	$(AR) rc $@ $^

LIB_INCLUDE_PATH:=
LIB_HEADER	:=
LIB_OBJS	:=
LIB		:=
