ARCH_DIR	:= $(GET_PATH)

ifeq ($(ARCH),)
$(info < ! > CPU - Architecture is not defined !)
$(error < x > Build Failed !)
endif

ifeq ($(BIT),)
$(info < ! > CPU - Data Width is not defined !)
$(error < x > Build Failed !)
endif

include $(ARCH_DIR)/$(ARCH)/$(BIT)/build.mk
