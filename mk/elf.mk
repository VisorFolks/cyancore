#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< ELF Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/obj.mk

OBJ_EXE	:= $(addprefix $(OUT)/,$(ELF:.elf=.o))
ELF	:= $(addprefix $(OUT)/,$(ELF))
BIN	:= $(subst .elf,.bin,$(ELF))

.PHONY: elf $(BIN)

elf: lib slib $(ELF) $(BIN)

$(ELF): $(DEPS_OBJS) $(OBJ_EXE)
	echo "Generating $(notdir $@) ..."
	$(CC) $(CFLAGS) -E -P -o $(LD_SCRIPT) $(LD_TEMPLATE)
	$(LD) -T $(LD_SCRIPT) $(LD_FLAGS) -o $@ $^ $(DEP_LIB_PATH) $(DEP_LIBS) -Map=$(subst .elf,.map,$@)
	echo "Disassembling $(notdir $@) ..."
	$(OD) -Dx $@ > $(subst .elf,.dis,$@)
	echo "=================================================="
	echo "Size of Executable:"
	cd $(OUT); $(SIZE) *.elf
	echo ""

ifeq ($(GENERATE_BIN),1)
$(BIN): $(ELF)
	echo "Generating $(notdir $(BIN)) ..."
	$(OC) -O binary $^ $@
endif
