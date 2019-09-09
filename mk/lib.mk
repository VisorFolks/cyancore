#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Library Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

C_OBJS		:= $(notdir $(wildcard $(DIR)/*.c))
S_OBJS		:= $(notdir $(wildcard $(DIR)/*.S))

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS:.c=.o)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS:.S=.o))

LIB		:= $(addprefix $(OUT)/,$(LIB))

LIB_OBJS	+= $(C_OBJS) $(S_OBJS)

.PHONY: lib --copy_lib_headers 

lib: --copy_lib_headers $(LIB)

--copy_lib_headers: --dependency
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

C_OBJS		:=
S_OBJS		:=
