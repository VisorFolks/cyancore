#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Paths >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

ARC_ROOT	:= .
TOOLS_ROOT	?= $(abspath $(ARC_ROOT))/toolchain

SRC		:= $(ARC_ROOT)/src
OUT		?= $(ARC_ROOT)/out/$(PROJECT)

GET_PATH	= $(patsubst %/,%,./$(dir $(lastword $(MAKEFILE_LIST))))
