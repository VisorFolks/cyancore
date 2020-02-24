#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#
#----------< Sources Makefile >----------#
#*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.#

DEBUG		?= 1
TARGET_FLAGS	?=

INCLUDE		+= -I $(SRC)/include/	\
		   -I $(OUT)		\
		   $(LIB_INCLUDE)	\
		   $(PLAT_INCLUDE)	\
		   $(PROJECT_INCLUDES)

OPTIMIZATION	?= 0

CFLAGS		+= $(INCLUDE)			\
		   -O$(strip $(OPTIMIZATION))	\
		   $(TARGET_FLAGS) -DARCH_$(BIT)\
		   -Wall -Wextra -Werror	\
		   -ffunction-sections		\
		   -fdata-sections
ifeq ($(DEBUG),1)
CFLAGS		+= -g				\
		   -DDEBUG=$(DEBUG)
else
LD_FLAGS	+= --gc-sections
endif

ASFLAGS		+= $(INCLUDE)		\
		   $(TARGET_FLAGS)	\
		   --fatal-warnings

LD_SCRIPT	:= $(OUT)/arc.ld

LD_FLAGS	+= --error-unresolved-symbols	\
		   --warn-common		\
		   --fatal-warnings		\
		   -b $(OUTPUT_FORMAT)

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
