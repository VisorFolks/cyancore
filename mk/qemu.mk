#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: qemu.mk
# Description		: This file helps fetch and build qemu
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

T_ALLOWLIST	+= get_qemu clean_qemu

QEMU_CHECKOUT	:= v7.2.0
QEMU_PATH	:= $(TOOLS_ROOT)/qemu
QEMU_BUILD_PATH	:= $(QEMU_PATH)/build
QEMU_OUT_PATH	:= $(TOOLS_ROOT)/cc_qemu
QEMU_TLIST	:= avr-softmmu,arm-softmmu,riscv32-softmmu

get_qemu: $(QEMU_OUT_PATH)

$(TOOLS_ROOT)/qemu:
	@echo "< ! > Using qemu version: $(QEMU_CHECKOUT)"
	@echo "< ! > Fetching qemu ..."
	mkdir -p $(TOOLS_ROOT)
	cd $(TOOLS_ROOT); git clone https://gitlab.com/qemu-project/qemu.git --quiet;
	cd $@; git checkout -b $(QEMU_CHECKOUT) $(QEMU_CHECKOUT) 1> /dev/null 2> /dev/null
	@echo "< / > Done !"


$(QEMU_OUT_PATH): $(QEMU_PATH)
	@echo "< ! > Building qemu ..."
	@echo "< ? > Please be patient as this might take a while ..."
	cd $<; ./configure --prefix=$(QEMU_OUT_PATH) --target-list=$(QEMU_TLIST) 2> /dev/null 1> /dev/null
	make -j $(N_JOBS) -C $< install 2> /dev/null 1> /dev/null
	@echo "< ! > Cleaning up build space ..."
	rm -rf $(QEMU_PATH)
	@echo "< ! > Adding load_qemu alias to bashrc ..."
	@echo "< ! > run 'load_qemu' before trying to launch qemu!"
	echo "alias load_qemu='export PATH=\"\$$PATH\":$@/bin/'" >> ~/.bashrc
	@echo "< / > Done !"

clean_qemu:
	@echo "< ! > Removing cc-qemu installation ..."
	rm -rf $(QEMU_OUT_PATH) $(QEMU_PATH)
	@echo "< / > Done!"
