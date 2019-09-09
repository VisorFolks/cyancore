PLAT_DIR	:= $(GET_PATH)

ifeq ($(PLATFORM),)
$(info < ! > Platform for project is not defined !)
$(error < x > Build Failed !)
endif

include $(PLAT_DIR)/$(PLATFORM)/build.mk
