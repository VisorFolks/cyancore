PROJECT_DIR	:= $(GET_PATH)

FAMILY		:= mega_avr
PLATFORM	:= atmega328p
AUTOINIT	:= 1

OPTIMIZATION	:= s

include $(PROJECT_DIR)/config.mk

DIR		:= $(PROJECT_DIR)
include mk/obj.mk
