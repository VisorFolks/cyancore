.PHONY: get_avr_tools

ifeq ($(MAKECMDGOALS),get_avr_tools)
ifeq ($(realpath $(TOOLS_ROOT)),)
$(error < ! > AVR-Toolchain is already present)
endif
endif

get_avr_tools:
	echo "< / > Fetching AVR Toolchain ..."
	mkdir -p toolchain
	cd toolchain; rm -rf avr8*\
	wget -q $(AVR_TOOLS_LINK) -o avr-toolchain.tar.gz;\
	tar -xzf avr-toolchain.tar.gz;\
	mv *.tar.gz avr_tc;\
	rm -f *.tar.gz
