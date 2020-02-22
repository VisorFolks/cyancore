#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< ELF Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/obj.mk

ELF	:= $(addprefix $(OUT)/,$(PROJECT).elf)

elf: lib slib $(ELF)

$(ELF): $(DEPS_OBJS)
	echo "Generating $(notdir $@) ..."
	$(CC) $(CFLAGS) -E -P -o $(LD_SCRIPT) $(LD_TEMPLATE) -nostdlib
	$(LD) -T $(LD_SCRIPT) $(LD_FLAGS) -o $@ $^ $(DEP_LIB_PATH) $(DEP_LIBS) -Map=$(subst .elf,.map,$@) -nostdlib
	$(OD) -Dx $@ > $(subst .elf,.dis,$@)
	$(OC) -O binary $@ $(subst .elf,.bin,$@)
	$(OC) -O ihex $@ $(subst .elf,.hex,$@)
	echo "=================================================="
	echo "Size of Executable:"
	cd $(OUT); $(SIZE) *.elf
	echo ""
