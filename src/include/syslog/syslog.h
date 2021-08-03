/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: syslog.h
 * Description		: This file defines the syscalls for system console logging
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SYSLOG_H_

#include "stdio.h"
#include "status.h"

#define SYSLOG_FORMAT		"%s : [ %s ] : %s\r\n"	///> "Agent" : [ LOG_LEVEL ] : "Output String"
#define SYSLOG_DEBUG		"DEB"
#define SYSLOG_INFO 		"INF"
#define SYSLOG_WARN 		"WAR"
#define SYSLOG_ERR 		"ERR"
#define SYSLOG_CRITICAL		"CRI"

#define SYSLOG_ATTACHED		0x1425

#define ASSERT_LOG(x)\
{					\
	if(x)				\
	{				\
		;			\
	}				\
	else				\
	{				\
		return error_assertion;	\
	}				\
}

typedef enum
{
	syslog_level_notset,
	syslog_level_debug,
	syslog_level_info,
	syslog_level_warn,
	syslog_level_err,
	syslog_level_critical,
	syslog_level_max
} syslog_level_e;

typedef struct syslog
{
	int attach;
	syslog_level_e sys_log_level;
} syslog_t;

status_t syslog_attach(syslog_level_e sys_log_level);
status_t syslog_change_level(syslog_level_e sys_log_level);
status_t syslog_log(const char * agent, const char * output_str, syslog_level_e syslog_level);
status_t syslog_dettach(void);
