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

#define SYSLOG_ATTACHED		0x1425

#define RET_ERR(x, err)		{ if(x){ (void)0; } else return err;}

typedef enum syslog_level
{
	syslog_level_verbose	= 0,
	syslog_level_debug	= 10,
	syslog_level_info	= 20,
	syslog_level_warn	= 30,
	syslog_level_err	= 40,
	syslog_level_critical	= 50,
	syslog_level_max
} syslog_level_t;

typedef struct syslog_ctrl
{
	int attach;
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

/**
 * syslog_setup - Initialize the logging system
 * This function is to setup the system logging module to be used by all the levels of the system
 *
 * @in		sys_log_level - This is the initial logging level of the logging system.
 *
 * @return	status:
 * 		success
 * 		error_inval_arg		for argument errors
 * 		error_init_done		if the initialisation is already done
 */
status_t syslog_setup(syslog_level_t sys_log_level);

/**
 * syslog_set_level - Set new logging level for system logging
 * This function helps to set a new level of system logging
 * Logging levels available:
 * 	1. syslog_level_debug (minimum)
 *	2. syslog_level_info
 *	3. syslog_level_warn
 *	4. syslog_level_err
 *	5. syslog_level_critical (maximum)
 *
 * @in		sys_log_level - This is the new logging level of the logging system.
 *
 * @return	status:
 * 		success
 * 		error_inval_arg		for argument errors
 * 		error_init_not_done	if the initialisation is not done
 */
status_t syslog_set_level(syslog_level_t sys_log_level);

/**
 * syslog_get_level - Get the current logging level for system logging
 * This function helps to get the current level of system logging
 *
 * @out 	sys_log_level - This is the current logging level of the logging system.
 *
 * @return	status:
 * 		success
 * 		error_inval_arg		for argument errors
 * 		error_init_not_done	if the initialisation is not done
 */
status_t syslog_get_level(syslog_level_t * sys_log_level);

/**
 * syslog_log - Produce log
 * This function helps to create a log on the console output.
 * Logging levels available:
 * 	1. syslog_level_debug (minimum)
 *	2. syslog_level_info
 *	3. syslog_level_warn
 *	4. syslog_level_err
 *	5. syslog_level_critical (maximum)
 *
 * @in		agent - Pointer to the agent string (limit: 15 char)
 * @in		fname - Pointer to file_name string. Default: NULL. Usage: pass __FILE__ macro to automatically fetch file location.
 * @in		line  - Pointer to line number string. Default: NULL. Usage: pass __LINE__ macro to automatically fetch current line number.
 * @in		output_str - string that is to be part of the information
 * @in		log_level - Level of the output log (Ref: Logging levels available)
 *
 * @return	status:
 * 		success
 * 		error_inval_arg		for argument errors
 * 		error_init_not_done	if the initialisation is not done
 */
status_t syslog_log(const char * agent, const char * fname, const char * line, const char * output_str, syslog_level_t log_level);

/**
 * syslog_release - Release syslog module
 * This function helps to release the syslog module
 *
 * @in/out	void
 *
 * @return	status:
 * 		success
 * 		error_inval_arg		for argument errors
 * 		error_init_not_done	if the initialisation is not done
 */
status_t syslog_release(void);
