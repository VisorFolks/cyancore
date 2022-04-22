#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: elf.mk
# Description		: This file accumulates all the object file
#			  and generates binaries
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< ELF Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/obj.mk
include mk/lint.mk

ELF		:= $(addprefix $(OUT)/,$(PROJECT).elf)
LD_SCRIPT	:= $(addprefix $(OUT)/,$(LD_SCRIPT:.ld.sx=.ld))
LD_SUPPLEMENT	:= $(addprefix $(OUT)/,$(LD_SUPPLEMENT:.ld.sx=.ld))

elf: $(ELF)

$(ELF): $(DEP_LIBS) $(DEP_OBJS) $(LD_SCRIPT) $(LD_SUPPLEMENT)
	@echo "Elf: Generating $(@F) ..."
	$(LD) -dT $(LD_SCRIPT) $(addprefix -T , $(LD_SUPPLEMENT)) $(LD_FLAGS) -Map=$(@:.elf=.map) -o $@ $(filter %.o, $^) $(DEP_LIB_PATH) $(DEP_LIBS_ARG) -L $(TL) -lgcc
	$(OD) -Dx -h --wide $@ > $(@:.elf=.lst)
	$(OC) -O binary $@ $(@:.elf=.bin)
	$(OC) -O ihex $@ $(@:.elf=.hex)
	@echo "=================================================="
	@echo "Size of Executable:"
	@cd $(@D); $(SIZE) $(@F)
	@echo ""

.SECONDEXPANSION:
$(OUT)/%.ld: %.ld.sx
	mkdir -p $(@D)
	@echo "Elf: Preprocessing $(@F) ..."
	$(CC) $(CFLAGS) -E -P -o $@ $<

