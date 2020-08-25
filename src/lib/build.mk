LIB_DIR		:= $(GET_PATH)

#==================================================
# Mandatory libraries
include $(LIB_DIR)/libresource/build.mk
include $(LIB_DIR)/libc/build.mk
#==================================================

include $(LIB_DIR)/libnmath/build.mk
