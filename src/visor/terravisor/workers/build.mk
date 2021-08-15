#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file builds worker sources
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

TWORKER_DIR	:= $(GET_PATH)

include $(TWORKER_DIR)/mcall/build.mk

DIR		:= $(TWORKER_DIR)

include mk/obj.mk
