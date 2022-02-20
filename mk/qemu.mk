#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: qemu.mk
# Description		: This file helps fetch and build qemu
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

get_qemu: $(TOOLS_ROOT)/qemu

$(TOOLS_ROOT)/qemu:
	@echo "< ! > Fetching qemu ..."
	mkdir -p $(TOOLS_ROOT)
	cd $(TOOLS_ROOT); git clone https://gitlab.com/qemu-project/qemu.git;
	@echo "< ! > Building qemu ..."
	@echo "< ? > Please be patient as this might take a while ..."
	cd $@; git submodule init --quiet; git submodule update --recursive --quiet;\
	./configure 1> /dev/null ; make -j $(N_JOBS) 1> /dev/null
	@echo "< ! > Adding load_qemu alias to bashrc ..."
	@echo "< ! > run 'load_qemu' before trying to launch qemu!"
	echo "alias load_qemu='export PATH=\"\$$PATH\":$@/build/'" >> ~/.bashrc
	@echo "< / > Done !"

