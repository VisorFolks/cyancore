#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#------------< Paths >-------------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

ARC_ROOT	:= $(PWD)
TOOLS_ROOT	:= $(ARC_ROOT)/toolchain

SRC		:= $(PWD)/src
OUT		?= $(PWD)/out/$(PROJECT)

GET_PATH	= $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
