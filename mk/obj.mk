#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Object Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

C_OBJS		:= $(wildcard $(DIR)/*.c)
S_OBJS		:= $(wildcard $(DIR)/*.S)

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS:.c=.o)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS:.S=.o))

DEP_OBJS	+= $(C_OBJS) $(S_OBJS)

$(C_OBJS): $(OUT)/%.o: %.c | $(OUT)/$(DIR)/
	@echo "Compiling $(notdir $(@:.o=.c)) ..."
	$(CC) $(CFLAGS) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: %.S | $(OUT)/$(DIR)/
	@echo "Assembling $(notdir $(@:.o=.S)) ..."
	$(CC) -E $(CFLAGS) -c $< -o $(@:.o=.pS)
	$(AS) $(ASFLAGS) $(@:.o=.pS) -o $@
	rm $(@:.o=.pS)
