#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Library Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/lobj.mk

LIB		:= $(addprefix $(OUT)/$(DIR)/,$(LIB))
HEADER		:= $(addprefix $(LIB_INCLUDE_PATH)/,$(LIB_HEADER))
INCLUDE		+= -I $(dir $(OUT)/$(HEADER))

.PHONY: lib

lib: $(LIB)

$(LIB): $(HEADER) $(LIB_OBJS)
	echo "Generating $(notdir $@) ..."
	$(AR) rc $@ $^

$(HEADER): --dependency
	mkdir -p $(OUT)/$(dir $@)
	cp $@ $(OUT)/$(dir $@)

LIB_INCLUDE_PATH:=
LIB_HEADER	:=
LIB_OBJS	:=
LIB		:=
