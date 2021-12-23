#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: sources.mk
# Description		: This build script accumalates build scripts from
#			  all the other directories. Also this scripts defines
#			  and initialises most of the build environment variables.
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#
# !NOTE!		: IT IS RECOMMENDED NOT TO MODIFY THIS FILE FOR BEST RESULTS
#

DEBUG		?= 1
TARGET_FLAGS	?=

INCLUDE		+= $(SRC)/include/ $(PROJECT_INCLUDES)	\
		   $(SRC)/include/compiler/$(COMPILER)/	\
		   $(LIB_INCLUDE) $(PLAT_INCLUDE)	\
		   $(TI)

OPTIMIZATION	?= s

CFLAGS		+= $(foreach i,$(INCLUDE),-I$(i))	\
		   -O$(strip $(OPTIMIZATION))		\
		   $(TARGET_FLAGS) -DARCH_$(BIT)	\
		   -Wall -Wextra -Werror		\
		   -ffunction-sections -fdata-sections	\
		   -fno-builtin	-nostdinc -nostdlib

ifeq ($(DEBUG),1)
CFLAGS		+= -g
$(eval $(call add_define,DEBUG))
endif

ASFLAGS		+= $(foreach i,$(INCLUDE),-I$(i))	\
		   $(TARGET_FLAGS)			\
		   --fatal-warnings

LD_FLAGS	+= --error-unresolved-symbols		\
		   --warn-common --fatal-warnings	\
		   --check-sections -nostdlib		\
		   --gc-sections -b $(OUTPUT_FORMAT)

LINT_FLAGS	+= $(foreach i,$(INCLUDE),-I$(i))	\
		   $(filter -D%,$(CFLAGS))

DEP_LIB_PATH	:=
DEP_LIBS_ARG	:=
DEP_LIBS	:=
DEP_OBJS	:=
DEP_SRCS	:=
PLAT_INCLUDE	:=
PROJECT_INCLUDE	:=
LIB_INCLUDE	:=

# Below order needs to be strictly maintained
include $(SRC)/projects/$(PROJECT)/build.mk
include $(SRC)/platform/build.mk
include $(SRC)/arch/build.mk
include $(SRC)/driver/build.mk
include $(SRC)/visor/build.mk
include $(SRC)/lib/build.mk
include $(SRC)/engine/build.mk
