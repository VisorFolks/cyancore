#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file builds worker sources
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

MCALL_DIR	:= $(GET_PATH)

LD_SUPPLEMENT	+= $(MCALL_DIR)/mcall.ld.sx

DIR		:= $(MCALL_DIR)

include mk/obj.mk
