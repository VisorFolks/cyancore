#
# CYANCORE LICENSE
# Copyrights (C) 2022, Cyancore Team
#
# File Name		: picotool.mk
# Description		: This is a build script to generate picotool
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

PICO_SDK_GIT	:= git@github.com:raspberrypi/pico-sdk.git
PICO_TOOL_GIT	:= git@github.com:raspberrypi/picotool.git
PICO_SDK_PATH	:= $(TOOLS_ROOT)/pico-sdk/
PICO_TOOL_PATH	:= $(TOOLS_ROOT)/picotool/
PICO_TOOL	:= $(MISC_TOOLS)/picotool
PICO_TOOL_BUILD	:= $(PICO_TOOL_PATH)/build/picotool

ifneq ($(V),1)
SILENT_LOGS	:= > cbuild.log 2> /dev/null
endif

T_ALLOWLIST	+= get_picotool pt_clean install_pt_dep

get_picotool: $(PICO_TOOL)

$(PICO_TOOL): $(PICO_TOOL_BUILD)
	mkdir -p $(dir $@)
	cp $(PICO_TOOL_PATH)/build/picotool $@

$(PICO_TOOL_BUILD): $(PICO_SDK_PATH) $(PICO_TOOL_PATH)
	@echo "Building picotool ..."
	cd $(PICO_TOOL_PATH) && mkdir -p build && \
	cd build && export PICO_SDK_PATH=$(PICO_SDK_PATH) && \
	cmake ../ $(SILENT_LOGS) \
	&& make $(SILENT_LOGS)

$(PICO_SDK_PATH):
	@echo "Fetching PICO SDK ..."
	git clone $(PICO_SDK_GIT) --quiet $@

$(PICO_TOOL_PATH):
	@echo "Fetching PICO Tool ..."
	git clone $(PICO_TOOL_GIT) --quiet $@

install_pt_dep:
	@echo "Installing Dependencies ..."
	@sudo apt-get install build-essential pkg-config libusb-1.0-0-dev -y -qq > /dev/null

pt_clean:
	rm -rf $(PICO_SDK_PATH) $(PICO_TOOL_PATH) $(PICO_TOOL)
