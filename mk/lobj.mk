#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#--------< Library Object Builder >---------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

C_OBJS		:= $(wildcard $(DIR)/*.c)
S_OBJS		:= $(wildcard $(DIR)/*.S)

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS:.c=.o)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS:.S=.o))

LIB_OBJS	+= $(C_OBJS) $(S_OBJS)

$(C_OBJS): $(OUT)/%.o: %.c $(LIB_INCLUDE_PATH)/
	mkdir -p $(dir $@)
	echo "Compiling $(subst .o,.c,$(notdir $@)) ..."
	$(CC) $(CFLAGS) $(addprefix -I,$(+D)) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: %.S $(LIB_INCLUDE_PATH)/
	mkdir -p $(dir $@)
	echo "Assembling $(subst .o,.S,$(notdir $@)) ..."
	$(CC) -E $(CFLAGS) $(addprefix -I,$(+D)) -c $< > $(subst .o,.pS,$@)
	$(AS) $(ASFLAGS) $(subst .o,.pS,$@) -o $@
	rm $(subst .o,.pS,$@)

C_OBJS		:=
S_OBJS		:=
