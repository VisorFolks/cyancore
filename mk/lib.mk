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
