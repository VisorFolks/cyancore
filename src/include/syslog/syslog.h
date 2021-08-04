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

#include <stdio.h>
#include <status.h>

#include <driver.h>

#define SYSLOG_FORMAT		"%s : [ %s ] : %s\r\n"	///> "Agent" : [ LOG_LEVEL ] : "Output String"
#define SYSLOG_DEBUG		"DEB"
#define SYSLOG_INFO 		"INF"
#define SYSLOG_WARN 		"WAR"
#define SYSLOG_ERR 		"ERR"
#define SYSLOG_CRITICAL		"CRI"

#define SYSLOG_ATTACHED		0x1425

#define CHECK_ARGS(x)		{ if(x){ (void)0; } else return error_inval_arg;}

typedef enum
{
	syslog_level_min	= 0,
	syslog_level_debug	= 10,
	syslog_level_info	= 20,
	syslog_level_warn	= 30,
	syslog_level_err	= 40,
	syslog_level_critical	= 50,
	syslog_level_max
} syslog_level_t;

typedef struct syslog
{
	int attach;
	char * syslog_fmt;
	syslog_level_t sys_log_level;
} syslog_t;

status_t syslog_setup(syslog_level_t sys_log_level);
status_t syslog_set_level(syslog_level_t sys_log_level);
status_t syslog_get_level(syslog_level_t * sys_log_level);
status_t syslog_log(const char * agent, const char * output_str, syslog_level_t syslog_level);
status_t syslog_release(void);
