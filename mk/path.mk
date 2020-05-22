#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Paths >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

ARC_ROOT	:= .
TOOLS_ROOT	?= $(abspath $(ARC_ROOT))/toolchain

SRC		:= $(ARC_ROOT)/src
OUT_PATH	?= $(ARC_ROOT)/out
OUT		?= $(OUT_PATH)/$(PROJECT)

GET_PATH	= $(patsubst %/,%,./$(dir $(lastword $(MAKEFILE_LIST))))

$(OUT)/%:
	mkdir -p $@
