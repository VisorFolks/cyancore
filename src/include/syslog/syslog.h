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
#include <driver/console.h>

#ifdef SYSLOG_SHOW_FILENAME_LINENO
	#define SYSLOG_FMT_DEF		"%15s : [ %s ] : %s : %s: %s\r\n"	///> "Agent" : [ LOG_LEVEL ] : File_Name : Line_Number : "Output String"
#else
	#define SYSLOG_FMT_DEF		"%15s : [ %s ] : %s\r\n"		///> "Agent" : [ LOG_LEVEL ] : "Output String"
#endif
#define SYSLOG_DEBUG		"DEB"
#define SYSLOG_INFO 		"INF"
#define SYSLOG_WARN 		"WAR"
#define SYSLOG_ERR 		"ERR"
#define SYSLOG_CRITICAL		"CRI"

#define SYSLOG_DEFAULT_AGENT	"CYANCORE"

#define SYSLOG_ATTACHED		0x25

#define RET_ERR(x, err)		{ if(x){ (void)0; } else return err;}

typedef enum syslog_level
{
	syslog_level_verbose,
	syslog_level_debug,
	syslog_level_info,
	syslog_level_warn,
	syslog_level_err,
	syslog_level_critical,
	syslog_level_max
} syslog_level_t;

typedef struct syslog_ctrl
{
	uint8_t attach;
	char * syslog_fmt;
	syslog_level_t sys_log_level;
} syslog_ctrl_t;

typedef struct syslog_api
{
	status_t (*setup)(syslog_level_t);
	status_t (*release)(void);
	status_t (*log)(const char *, const char *, const char *, const char *, syslog_level_t);
	status_t (*set_level)(syslog_level_t);
	status_t (*get_level)(syslog_level_t *);
} syslog_api_t;

typedef struct syslog_interface
{
	syslog_ctrl_t *ctrl;
	syslog_api_t  *api;
} syslog_interface_t;


extern syslog_interface_t g_syslog;

status_t syslog_setup(syslog_level_t sys_log_level);
status_t syslog_set_level(syslog_level_t sys_log_level);
status_t syslog_get_level(syslog_level_t * sys_log_level);
status_t syslog_log(const char * agent, const char * fname, const char * line, const char * output_str, syslog_level_t log_level);
status_t syslog_release(void);
