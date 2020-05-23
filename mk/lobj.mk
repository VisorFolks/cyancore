#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#--------< Library Object Builder >---------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

C_OBJS		:= $(wildcard $(DIR)/*.c)
S_OBJS		:= $(wildcard $(DIR)/*.S)

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS:.c=.o)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS:.S=.o))

LIB_OBJS	+= $(C_OBJS) $(S_OBJS)

$(C_OBJS): $(OUT)/%.o: %.c $(LIB_INCLUDE_PATH)/ | $(OUT)/$(DIR)/
	@echo "Compiling $(notdir $(@:.o=.c)) ..."
	$(CC) $(CFLAGS) $(addprefix -I,$(+D)) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: %.S $(LIB_INCLUDE_PATH)/ | $(OUT)/$(DIR)/
	@echo "Assembling $(notdir $(@:.o=.S)) ..."
	$(CC) -E $(CFLAGS) $(addprefix -I,$(+D)) -c $< -o $(@:.o=.pS)
	$(AS) $(ASFLAGS) $(@:.o=.pS) -o $@
	rm $(@:.o=.pS)
