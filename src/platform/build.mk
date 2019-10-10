PLAT_DIR	:= $(GET_PATH)

ifeq ($(FAMILY),)
$(info < ! > Family of chip used in  project is not defined !)
$(error < x > Build Failed !)
endif
ifeq ($(PLATFORM),)
$(info < ! > Platform for project is not defined !)
$(error < x > Build Failed !)
endif

include $(PLAT_DIR)/$(FAMILY)/$(PLATFORM)/build.mk
