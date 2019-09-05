.PHONY: get_arm_tools

ifeq ($(MAKECMDGOALS),get_arm_tools)
ifeq ($(realpath $(TOOLS_ROOT)),)
$(error < ! > ARM-Toolchain is already present)
endif
endif

get_arm_tools:
	echo "< / > Fetching ARM Toolchain ..."
	mkdir -p toolchain
	cd toolchain; rm -rf *-arm-*\
	wget -q $(ARM_TOOLS_LINK) -o arm-toolchain.tar.gz;\
	tar -xzf arm-toolchain.tar.gz;\
	mv *.tar.gz arm_tc;\
	rm -f *.tar.gz
