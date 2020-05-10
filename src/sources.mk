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

add_define	= -D$(1)=$($(1))

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
endif

ASFLAGS		+= $(foreach i,$(INCLUDE),-I$(i))	\
		   $(TARGET_FLAGS)			\
		   --fatal-warnings

LD_SCRIPT	:= $(OUT)/arc.ld

LD_FLAGS	+= --error-unresolved-symbols	\
		   --warn-common		\
		   --fatal-warnings		\
		   -nostdlib --gc-sections	\
		   -b $(OUTPUT_FORMAT)

DEP_LIB_PATH	:=
DEP_LIBS	:=
DEPS_OBJS	:=
PLAT_INCLUDE	:=
PROJECT_INCLUDES:=
LIB_INCLUDES	:=

# Below order needs to be strictly maintained
include $(SRC)/projects/$(PROJECT)/build.mk
include $(SRC)/platform/build.mk
include $(SRC)/arch/build.mk
include $(SRC)/driver/build.mk
include $(SRC)/visor/build.mk
include $(SRC)/lib/build.mk
include $(SRC)/LattiX/build.mk
