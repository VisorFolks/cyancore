#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#----------< Sources Makefile >----------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

DEBUG		?= 1
TARGET_FLAGS	?=
AUTOINIT	?= 0

INCLUDE		+= $(SRC)/include/	\
		   $(TI)		\
		   $(LIB_INCLUDE)	\
		   $(PLAT_INCLUDE)	\
		   $(PROJECT_INCLUDES)

OPTIMIZATION	?= s

CFLAGS		+= $(foreach i,$(INCLUDE),-I$(i))	\
		   -DDEBUG=$(DEBUG)			\
		   -DAUTOINIT=$(AUTOINIT)		\
		   -O$(strip $(OPTIMIZATION))		\
		   $(TARGET_FLAGS) -DARCH_$(BIT)	\
		   -Wall -Wextra -Werror		\
		   -ffunction-sections -fdata-sections	\
		   -fno-builtin	-nostdinc -nostdlib

ifeq ($(DEBUG),1)
CFLAGS		+= -g
else
LD_FLAGS	+= --gc-sections
endif

ASFLAGS		+= $(foreach i,$(INCLUDE),-I$(i))	\
		   $(TARGET_FLAGS)			\
		   --fatal-warnings

LD_SCRIPT	:= $(OUT)/arc.ld

LD_FLAGS	+= --error-unresolved-symbols	\
		   --warn-common		\
		   --fatal-warnings		\
		   -nostdlib			\
		   -b $(OUTPUT_FORMAT)

LIBGCC_PATH	:=
DEP_LIB_PATH	:=
DEP_LIBS	:=
DEPS_OBJS	:=
PLAT_INCLUDE	:=
PROJECT_INCLUDES:=
LIB_INCLUDES	:=

# Below order needs to be strictly maintained
include $(SRC)/projects/$(PROJECT)/config.mk
include $(SRC)/projects/$(PROJECT)/build.mk
include $(SRC)/platform/build.mk
include $(SRC)/arch/build.mk
include $(SRC)/driver/build.mk
#include $(SRC)/kernel/build.mk
#include $(SRC)/network/build.mk
#incldue $(SRC)/fs/build.mk
include $(SRC)/lib/build.mk
include $(SRC)/Arc/build.mk
