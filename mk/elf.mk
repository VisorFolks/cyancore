#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< ELF Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/obj.mk

ELF	:= $(addprefix $(OUT)/,$(PROJECT).elf)

elf: $(ELF)

$(ELF): $(DEP_LIBS) $(DEP_OBJS)
	@echo "Elf: Generating $(@F) ..."
	$(CC) $(CFLAGS) -E -P -o $(LD_SCRIPT) $(LD_TEMPLATE)
	$(LD) -T $(LD_SCRIPT) $(LD_FLAGS) -Map=$(@:.elf=.map) -o $@ $(filter %.o, $^) $(DEP_LIB_PATH) $(DEP_LIBS_ARG) -L $(TL) -lgcc
	$(OD) -Dx -h $@ > $(@:.elf=.lst)
	$(OC) -O binary $@ $(@:.elf=.bin)
	$(OC) -O ihex $@ $(@:.elf=.hex)
	@echo "=================================================="
	@echo "Size of Executable:"
	@cd $(@D); $(SIZE) $(@F)
	@echo ""
