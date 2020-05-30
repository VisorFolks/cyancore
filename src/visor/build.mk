VISOR_DIR	:= $(GET_PATH)

INCLUDE		+= $(SRC)/include/visor/

ifneq ($(EXE_MODE),)
include $(VISOR_DIR)/$(EXE_MODE)/build.mk
endif
