#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: copy_to_target.mk
# Description		: This file has build target to copy to
#			  remote machine if any
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

R_UNAME		?= $(USER)
SSH_HOST	?=
SSH_PORT	?=
SSH_PATH	?=

--cpremote: $(ELF)
	@echo "< ! > Copying to remote ($(SSH_HOST))..."
	ssh -p $(SSH_PORT) $(R_UNAME)@$(SSH_HOST) "mkdir -p $(SSH_PATH)/$(PROJECT)"
	scp -r -P $(SSH_PORT) $(^:.elf=.*) $(R_UNAME)@$(SSH_HOST):$(SSH_PATH)/$(PROJECT)

--rmremote:
	@echo "< ! > Cleaning remote ($(SSH_HOST))..."
	ssh -p $(SSH_PORT) $(R_UNAME)@$(SSH_HOST) "rm -rf $(SSH_PATH)/$(PROJECT)"
