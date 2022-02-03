#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: config.mk
# Description		: This file provides configurations to syslog library
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

SYSLOG_SHOW_FILENAME_LINENO	?= 4
$(eval $(call add_define,SYSLOG_SHOW_FILENAME_LINENO))

SYSLOG_MAX_CALLBACKS		?= 1U
$(eval $(call add_define,SYSLOG_MAX_CALLBACKS))

SYSLOG_BUFFER_LEN		?= 256U
$(eval $(call add_define,SYSLOG_BUFFER_LEN))

SYSLOG_COLORED_LOG		?= 0
$(eval $(call add_define,SYSLOG_COLORED_LOG))
