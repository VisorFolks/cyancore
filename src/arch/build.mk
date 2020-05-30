ARCH_DIR	:= $(GET_PATH)

ifeq ($(ARCH),)
$(info < ! > CPU - Architecture is not defined !)
$(error < x > Build Failed !)
endif

ifeq ($(BIT),)
$(info < ! > CPU - Data Width is not defined !)
$(error < x > Build Failed !)
endif

ifeq ($(ARCH_VARIANT),)
$(info < ! > CPU - Architecture Variant is not defined !)
$(error < x > Build Failed !)
endif

ifeq ($(EXE_MODE),)
$(info < ! > CPU - Execution mode is not defined !)
$(error < x > Build Failed !)
endif

CFLAGS		+= -DARCHITECTURE=$(ARCH)	\
		   -DBITWIDTH=$(BIT)		\
		   -DARCH_VARIANT=$(ARCH_VARIANT)

include $(ARCH_DIR)/$(ARCH)/$(BIT)/$(ARCH_VARIANT)/$(EXE_MODE)/build.mk
