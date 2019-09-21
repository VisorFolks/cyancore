#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< ELF Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/obj.mk

OBJ_EXE	:= $(addprefix $(OUT)/,$(ELF:.elf=.o))
ELF	:= $(addprefix $(OUT)/,$(ELF))

.PHONY: elf

elf: lib slib $(ELF)

$(ELF): $(DEPS_OBJS) $(OBJ_EXE)
	echo "Generating $(notdir $@) ..."
	$(CC) $(CFLAGS) -E -P -o $(LD_SCRIPT) $(LD_TEMPLATE)
	$(LD) -T $(LD_SCRIPT) $(LD_FLAGS) -o $@ $^ $(DEP_LIB_PATH) $(DEP_LIBS) -Map=$(subst .elf,.map,$@)
	$(OC) -O binary $@ $(subst .elf,.bin,$@)
	echo "Disassembling $(notdir $@) ..."
	$(OD) -Dx $@ > $(subst .elf,.dis,$@)
	echo "----------------------------------------------------------------------"
	echo "Size of Binaries:"
	cd $(OUT); $(SIZE) *.o *.elf
