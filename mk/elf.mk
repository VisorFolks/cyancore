#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< ELF Builder >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

include mk/obj.mk

ELF	:= $(addprefix $(OUT)/,$(PROJECT).elf)

elf: lib slib $(ELF)

$(ELF): $(DEPS_OBJS)
	echo "Generating $(notdir $@) ..."
	$(CC) $(CFLAGS) -E -P -o $(LD_SCRIPT) $(LD_TEMPLATE)
	$(CC) -Wl,-T $(LD_SCRIPT) $(foreach i,$(LD_FLAGS),-Wl,$(i)) -o $@ $^ $(foreach i,$(DEP_LIB_PATH),-Wl,$(i)) $(foreach i,$(DEP_LIBS),-Wl,$(i)) -Wl,-Map=$(subst .elf,.map,$@)
	$(OD) -Dx $@ > $(subst .elf,.dis,$@)
	$(OC) -O binary $@ $(subst .elf,.bin,$@)
	$(OC) -O ihex $@ $(subst .elf,.hex,$@)
	echo "=================================================="
	echo "Size of Executable:"
	cd $(OUT); $(SIZE) *.elf
	echo ""
