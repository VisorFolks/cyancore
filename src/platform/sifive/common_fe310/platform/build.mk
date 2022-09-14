#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file builds sources from fe310
#			  common platform directory
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

DIR	:= $(GET_PATH)

PRINT_MEMORY_LAYOUT	?= 0
$(eval $(call add_define,PRINT_MEMORY_LAYOUT))

include mk/obj.mk
