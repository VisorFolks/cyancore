PROJECT_DIR	:= $(GET_PATH)

OPTIMIZATION	:=

include $(PROJECT_DIR)/config.mk

# You can add another folder with necessary files to build the project
# The below path should be valid
# include $(PROJECT_DIR)/<folder>/build.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
