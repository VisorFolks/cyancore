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

#if SYSLOG_MAX_CALLBACKS < 1
ERROR(SYSLOG_MAX_CALLBACKS shall be greater than 0)
#endif

#if SYSLOG_BUFFER_LEN < 256
ERROR(SYSLOG_BUFFER_LEN shall be greater than 255 bytes)
#endif

#if SYSLOG_COLORED_LOG
ERROR(SYSLOG_COLORED_LOG not supported yet in cyancore)
#endif

#if SYSLOG_SHOW_FILENAME_LINENO
#define SYSLOG_FMT_DEF		"%15s : [ %s ] : %s : %d: %s\r\n"	///> "Agent" : [ LOG_LEVEL ] : File_Name : Line_Number : "Output String"
#else
#define SYSLOG_FMT_DEF		"%15s : [ %s ] : %s\r\n"		///> "Agent" : [ LOG_LEVEL ] : "Output String"
#endif

#if (!SYSLOG_COLORED_LOG)
#define SYSLOG_DEBUG		"DEB"
#define SYSLOG_INFO 		"INF"
#define SYSLOG_WARN 		"WAR"
#define SYSLOG_ERR 		"ERR"
#define SYSLOG_CRITICAL		"CRI"
#else
#define SYSLOG_DEBUG		"DEB"
#define SYSLOG_INFO 		"INF"
#define SYSLOG_WARN 		"WAR"
#define SYSLOG_ERR 		"ERR"
#define SYSLOG_CRITICAL		"CRI"
#endif

#define SYSLOG_DEFAULT_AGENT	"CYANCORE"

#define SYSLOG_ATTACHED		0x25

#define SYSLOG_VAR_INIT		0x00

#define DO_NOTHING
#define RET_ERR(x, err)		{ if(x){ DO_NOTHING } else return err;}

/**
 * @enum syslog_level_t
 *
 * Provides the possible syslog levels
 */
typedef enum syslog_level
{
	syslog_level_verbose,	///> Minimum possible syslog level. Enables all above levels.
	syslog_level_debug,	///> Minimum syslog level set to DEBUG.
	syslog_level_info,	///> Minimum syslog level set to INFO.
	syslog_level_warn,	///> Minimum syslog level set to WARNING.
	syslog_level_err,	///> Minimum syslog level set to ERROR.
	syslog_level_critical,	///> Maximum possible syslog level set to CRITICAL. Majorly shall be used by kernel.
	syslog_level_max	///> Unused in any context
} syslog_level_t;

/**
 * @typedef syslog_cb_t
 *
 * Prototype of syslog callbacks
 */
typedef void(*syslog_cb_t)(char *, size_t );

/**
 * @typedef syslog_cb_fd_t
 *
 * Typedef of syslog file descriptor
 */
typedef uint8_t syslog_cb_fd_t;

/**
 * @struct syslog_ctrl_t
 *
 * Provides the Syslog control structure
 */
typedef struct syslog_ctrl
{
	char * syslog_fmt;
	uint8_t attach;
	syslog_level_t sys_log_level;
	syslog_cb_fd_t syslog_table_reg_len;
	syslog_cb_t syslog_cb_table [SYSLOG_MAX_CALLBACKS];
} syslog_ctrl_t;

/**
 * @struct syslog_api_t
 *
 * Provides the API interface structure
 */
typedef struct syslog_api
{
	status_t (*setup)(syslog_level_t, syslog_cb_t);
	status_t (*release)(void);
	status_t (*log)(const char *, const char *, int, const char *, syslog_level_t);
	status_t (*set_level)(syslog_level_t);
	status_t (*get_level)(syslog_level_t *);
	status_t (*reg_cb)(syslog_cb_t, syslog_cb_fd_t *);
	status_t (*dereg_cb)(syslog_cb_fd_t *);
} syslog_api_t;

/**
 * @struct syslog_interface_t
 *
 * Provides the syslog interface pointer
 */
typedef struct syslog_interface
{
	syslog_ctrl_t *ctrl;
	syslog_api_t  *api;
} syslog_interface_t;

/**
 * Extern Variables
 */
extern syslog_interface_t g_syslog;

/**
 * Function Prototypes
 */
status_t syslog_setup(syslog_level_t sys_log_level, syslog_cb_t cb);
status_t syslog_set_level(syslog_level_t sys_log_level);
status_t syslog_get_level(syslog_level_t *sys_log_level);
status_t syslog_log(const char *agent, const char *fname, int line, const char *output_str, syslog_level_t log_level);
status_t syslog_reg_cb(syslog_cb_t cb, syslog_cb_fd_t *fd);
status_t syslog_dereg_cb(syslog_cb_fd_t *fd);
status_t syslog_release(void);

_WEAK extern void syslog_default_cb(char * str_in, size_t len _UNUSED);
