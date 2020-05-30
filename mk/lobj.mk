#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#--------< Library Object Builder >---------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

C_OBJS		:= $(wildcard $(DIR)/*.c)
S_OBJS		:= $(wildcard $(DIR)/*.S)

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS:.c=.o)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS:.S=.o))

LIB_OBJS	+= $(C_OBJS) $(S_OBJS)

.SECONDEXPANSION:
$(C_OBJS): $(OUT)/%.o: %.c | $$(@D)/
	@echo "Lib: Compiling $(notdir $<) ..."
	$(CC) $(CFLAGS) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: %.S | $$(@D)/
	@echo "Lib: Assembling $(notdir $<) ..."
	$(CC) -E $(CFLAGS) -c $< -o $(@:.o=.pS)
	$(AS) $(ASFLAGS) $(@:.o=.pS) -o $@
	rm $(@:.o=.pS)
