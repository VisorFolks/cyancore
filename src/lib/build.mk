#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Descrption		: This script accumulates all the lib build.mk
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

LIB_DIR		:= $(GET_PATH)

#==================================================
# Mandatory libraries
include $(LIB_DIR)/libc/build.mk
include $(LIB_DIR)/libresource/build.mk
include $(LIB_DIR)/libsyslog/build.mk
include $(LIB_DIR)/libccfs/build.mk
#==================================================

include $(LIB_DIR)/libnmath/build.mk
$(eval $(call check_and_include,POSIX,$(LIB_DIR)/libposix/build.mk))
