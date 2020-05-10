PROJECT_DIR	:= $(GET_PATH)

OPTIMIZATION	:= s

include $(PROJECT_DIR)/config.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
