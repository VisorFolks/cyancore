#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< ELF Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

OBJ_EXE	:= $(patsubst %.elf,%.o,$(EXE))
OBJ_EXE	:= $(addprefix $(OUT)/,$(OBJ_EXE))

.PHONY: executable

executable: $(OUT)/$(ELF)

$(OUT)/$(ELF): $(DEPS_OBJS) $(OBJ_EXE)
	echo "Generating $(notdir $@) ..."
	$(CC) $(CFLAGS) -E -P -o $(LD_SCRIPT) $(LD_TEMPLATE)
	$(LD) -T $(LD_SCRIPT) $(LDFLAGS) -o $@ $^ $(LIB_PATH) $(LIBS) -Map=$(subst .elf,.map,$@)
	$(OC) -O binary $@ $(subst .elf,.bin,$@)
	echo "Disassembling $(notdir $@) ..."
	$(OD) -Dx $@ > $(subst .elf,.dis,$@)
	echo "----------------------------------------------------------------------"
	echo "Size of Binaries:"
	cd $(OUT); size *.o *.elf
