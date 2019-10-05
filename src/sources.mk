#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#----------< Sources Makefile >----------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

DEBUG		?=0
TARGET_FLAGS	?=

GENERATE_BIN	?= 0

INCLUDE		+= -I $(SRC)/include	\
		   -I $(TI)		\
		   -I $(OUT)		\
		   $(PLAT_INCLUDE)	\
		   $(PROJECT_INCLUDES)

OPTIMIZATION	?= 0

CFLAGS		+= $(INCLUDE)		\
		   -O$(strip $(OPTIMIZATION))	\
		   $(TARGET_FLAGS)	\
		   -DDEBUG=$(DEBUG)	\
		   -Wall -Werror	\
		   -ffunction-sections	\
		   -fdata-sections

ASFLAGS		+= $(INCLUDE)		\
		   $(TARGET_FLAGS)	\
		   --fatal-warnings

LD_SCRIPT	:= $(OUT)/arc.ld

LD_FLAGS	+= --error-unresolved-symbols	\
		   --warn-common		\
		   --fatal-warnings		\
		   --gc-sections		\
		   -b $(OUTPUT_FORMAT)

DEP_LIB_PATH	+= -L $(OUT)
DEP_LIBS	+=

DEPS_OBJS	:=
PLAT_INCLUDE	:=
PROJECT_INCLUDES:=

include $(SRC)/lib/build.mk
include $(SRC)/projects/$(PROJECT)/config.mk
include $(SRC)/projects/$(PROJECT)/build.mk
include $(SRC)/platform/build.mk
include $(SRC)/arch/build.mk
include $(SRC)/driver/build.mk
#include $(SRC)/kernel/build.mk
#include $(SRC)/network/build.mk
#incldue $(SRC)/fs/build.mk
include $(SRC)/Arc/build.mk
