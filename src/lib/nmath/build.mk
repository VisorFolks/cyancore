DIR		:= $(GET_PATH)

DEPS_SRCS	:= nmath.c

LIB		:= libnmath.a

LIB_INCLUDE_PATH:= $(DIR)/include

PROJECT_INCLUDES+= $(LIB_INCLUDE_PATH)

LIB_HEADER	:= nmath.h

include mk/lib.mk
