#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: obj.mk
# Description		: This file build sources to generate objects
#			  used to generate executable binary
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#
#------------< Object Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*#

C_SRCS		:= $(wildcard $(DIR)/*.c)
CPP_SRCS	:= $(wildcard $(DIR)/*.cpp)
S_SRCS		:= $(wildcard $(DIR)/*.S)

C_OBJS		:= $(addprefix $(OUT)/,$(C_SRCS:.c=.o))
CPP_OBJS	:= $(addprefix $(OUT)/,$(CPP_SRCS:.cpp=.o))
S_OBJS		:= $(addprefix $(OUT)/,$(S_SRCS:.S=.o))

DEP_OBJS	+= $(C_OBJS) $(CPP_OBJS) $(S_OBJS)
DEP_SRCS	+= $(C_SRCS) $(CPP_SRCS)

.SECONDEXPANSION:
$(CPP_OBJS): $(OUT)/%.o: %.cpp | $$(@D)/
	@echo "Elf: Compiling $(@F:.o=.cpp) ..."
	$(CCP) $(CFLAGS) -c $< -o $@

$(C_OBJS): $(OUT)/%.o: %.c | $$(@D)/
	@echo "Elf: Compiling $(@F:.o=.c) ..."
	$(CC) $(CFLAGS) -c $< -o $@

$(S_OBJS): $(OUT)/%.o: %.S | $$(@D)/
	@echo "Elf: Assembling $(@F:.o=.S) ..."
	$(CC) -E $(CFLAGS) -c $< -o $(@:.o=.pS)
	$(AS) $(ASFLAGS) $(@:.o=.pS) -o $@
	rm $(@:.o=.pS)
