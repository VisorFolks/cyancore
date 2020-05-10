#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#---------< Shared Library Builder >----------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

include mk/lobj.mk

SLIB		:= $(addprefix $(OUT)/,$(SLIB))
HEADER		:= $(addprefix $(LIB_INCLUDE_PATH)/,$(LIB_HEADER))

.PHONY: slib

slib: $(SLIB)

$(SLIB): $(HEADER) $(LIB_OBJS)
	echo "Generating $(notdir $@) ..."
	$(LD) --shared -Wl,-soname,$(notdir $@) -o $@ $<

$(HEADER): --dependency
	cp $@ $(OUT)

LIB_INCLUDE_PATH:=
LIB_HEADER	:=
LIB_OBJS	:=
SLIB		:=
