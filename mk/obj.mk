#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Object Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

C_SRCS		:= $(filter %.c,$(notdir $(DEPS_SRCS)))
S_SRCS		:= $(filter %.S,$(notdir $(DEPS_SRCS)))

C_OBJS		:= $(patsubst %.c,%.o,$(C_SRCS))
S_OBJS		:= $(patsubst %.S,%.o,$(S_SRCS))

C_OBJS		:= $(addprefix $(OUT)/,$(C_OBJS)) 
S_OBJS		:= $(addprefix $(OUT)/,$(S_OBJS))

DEPS_OBJS	+= $(C_OBJS)
DEPS_OBJS	+= $(S_OBJS)

.PHONY: objects

objects: $(C_OBJS) $(S_OBJS)

$(C_OBJS): $(OUT)/%.o: $(DIR)/%.c
	echo "Compiling $(subst .o,.c,$(notdir $@)) ..."
	$(CC) $(CFLAGS) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: $(DIR)/%.S
	echo "Assembling $(subst .o,.S,$(notdir $@)) ..."
	$(CC) -E $(CFLAGS) -c $< > $(subst .o,.pS,$@)
	$(AS) $(ASFLAGS) $(subst .o,.pS,$@) -o $@
	rm $(subst .o,.pS,$@)

C_SRCS		:=
S_SRCS		:=

C_OBJS		:=
S_OBJS		:=
