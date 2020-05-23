#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Object Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

C_OBJS		:= $(wildcard $(DIR)/*.c)
S_OBJS		:= $(wildcard $(DIR)/*.S)

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS:.c=.o)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS:.S=.o))

DEP_OBJS	+= $(C_OBJS) $(S_OBJS)

$(C_OBJS): $(OUT)/%.o: %.c | $(OUT)/$(DIR)/
	@echo "Compiling $(subst .o,.c,$(notdir $@)) ..."
	$(CC) $(CFLAGS) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: %.S | $(OUT)/$(DIR)/
	@echo "Assembling $(subst .o,.S,$(notdir $@)) ..."
	$(CC) -E $(CFLAGS) -c $< > $(subst .o,.pS,$@)
	$(AS) $(ASFLAGS) $(subst .o,.pS,$@) -o $@
	rm $(subst .o,.pS,$@)
