#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Library Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/lobj.mk

LIB		:= $(addprefix $(OUT)/,$(LIB))
HEADER		:= $(addprefix $(LIB_INCLUDE_PATH)/,$(LIB_HEADER))

.PHONY: lib

lib: $(LIB)

$(LIB): $(HEADER) $(LIB_OBJS)
	echo "Generating $(notdir $@) ..."
	$(AR) rc $@ $^

$(HEADER): --dependency
	cp $@ $(OUT)

LIB_INCLUDE_PATH:=
LIB_HEADER	:=
LIB_OBJS	:=
LIB		:=
