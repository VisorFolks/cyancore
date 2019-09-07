#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Library Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

C_SRCS		:= $(filter %.c,$(notdir $(DEPS_SRCS)))
S_SRCS		:= $(filter %.S,$(notdir $(DEPS_SRCS)))

C_OBJS		:= $(patsubst %.c,%.o,$(C_SRCS))
S_OBJS		:= $(patsubst %.S,%.o,$(S_SRCS))

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS))

LIB		:= $(addprefix $(OUT)/,$(LIB))

LIB_OBJS	+= $(C_OBJS)
LIB_OBJS	+= $(S_OBJS)

.PHONY: libraries

libraries: copy_lib_headers $(LIB)

copy_lib_headers:
	cp $(LIB_INCLUDE_PATH)/$(LIB_HEADER) $(OUT)

$(LIB): $(LIB_OBJS)
	echo "Generating $(notdir $@) ..."
	$(AR) rc $@ $^

$(C_OBJS): $(OUT)/%.o: $(DIR)/%.c
	echo "Compiling $(subst .o,.c,$(notdir $@)) ..."
	$(CC) $(CFLAGS) -I $(LIB_INCLUDE_PATH) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: $(DIR)/%.S
	echo "Assembling $(subst .o,.S,$(notdir $@)) ..."
	$(CC) -E $(CFLAGS) -I $(LIB_INCLUDE_PATH) -c $< > $(subst .o,.pS,$@)
	$(AS) $(ASFLAGS) $(subst .o,.pS,$@) -o $@
	rm $(subst .o,.pS,$@)

LIB_OBJS	:=

LIB		:=

C_SRCS		:=
S_SRCS		:=

C_OBJS		:=
S_OBJS		:=
