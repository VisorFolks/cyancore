#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#----------< Sources Makefile >----------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

TARGET_FLAGS	?=
INCLUDE		+= -I $(SRC)/include	\
		   -I $(TI)		\
		   $(PROJECT_INCLUDES)

CFLAGS		+= $(INCLUDE)		\
		   $(TARGET_FLAGS)	\
		   -Wall -Werror	\
		   -ffunction-sections	\
		   -fdata-sections

LD_SCRIPT	:= $(OUT)/Arc.ld

LD_FLAGS	+= --error-unresolved-symbols	\
		   --warn-common		\
		   --fatal-warnings		\
		   --gc-sections

LIB_PATH	+=
LIBS		+=
DEPS_OBJS	:=
PROJECT_INCLUDES:=

include $(SRC)/lib/build.mk
include $(SRC)/projects/$(PROJECT)/build.mk
include $(SRC)/arch/build.mk
#include $(SRC)/kernel/build.mk
#include $(SRC)/platform/build.mk
#include $(SRC)/network/build.mk
#include $(SRC)/init/build.mk
