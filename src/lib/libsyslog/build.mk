#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates sources of syslog driver
# Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
# Organisation		: Cyancore Core-Team
#

LIBSYSLOG_PATH	:= $(GET_PATH)
LIB_OBJS	:=

LIB		+= libsyslog.a
LIB_INCLUDE	+= $(LIBSYSLOG_PATH)/include
DEP_LIB_ARG	+= -lsyslog

include $(LIBSYSLOG_PATH)/config.mk

DIR		:= $(LIBSYSLOG_PATH)
include mk/lib.mk
