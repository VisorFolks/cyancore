/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: syslog.c
 * Description		: This file is the source for the syscalls of system console logging
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <syslog/syslog.h>
#include <string.h>

#define MEMSET_CLEAR	0x00

/**
 * *syslog_loglevel_table - String table of SYSLOG Levels
 *
 * This variable is used to contain the array representing the syslog level strings.
 * This would be used to print the syslog level by syslog_log API.
 */
static const char * syslog_loglevel_table[] =
{
	SYSLOG_DEBUG,
	SYSLOG_INFO,
	SYSLOG_WARN,
	SYSLOG_ERR,
	SYSLOG_CRITICAL
};

/**
 * syslog_ctrl - Syslog control variable
 *
 * This variable is used to contain the syslog control parameters.
 * This would be used by all the functions to update the state of the control.
 * This variable is only accesable using syslog interface to the other layers i.e. g_syslog
 */
static syslog_ctrl_t syslog_ctrl;

/**
 * syslog_api - Placeholder pointing to all the API related to syslog
 *
 * This variable is used to contain the pointers to syslog APIs to be used by the user.
 * This variable is only accesable using syslog interface i.e. g_syslog
 */
static syslog_api_t syslog_api =
{
	.setup		= syslog_setup,
	.release	= syslog_release,
	.log		= syslog_log,
	.get_level	= syslog_get_level,
	.set_level	= syslog_set_level
};

/**
 * g_syslog - Global syslog interface to be used by the higher levels
 *
 * This variable is used to contain the pointers to syslog APIs and control
 * This variable is globally available for further integrations.
 */
syslog_interface_t g_syslog =
{
	.ctrl	= &syslog_ctrl,
	.api	= &syslog_api
};

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
status_t syslog_setup(syslog_level_t sys_log_level)
{
	RET_ERR(syslog_ctrl.attach != SYSLOG_ATTACHED, error_init_done);
	RET_ERR((sys_log_level < syslog_level_max) && (sys_log_level >= syslog_level_verbose), error_inval_arg);

	status_t ret = success;

	ret = console_setup();
	if (ret == success || ret == error_init_done)
	{
		syslog_ctrl.attach     = SYSLOG_ATTACHED;
		syslog_ctrl.syslog_fmt = SYSLOG_FMT_DEF;
	}

	return ret;
}

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
status_t syslog_set_level(syslog_level_t sys_log_level)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_init_not_done);
	RET_ERR((sys_log_level < syslog_level_max) && (sys_log_level >= syslog_level_verbose), error_inval_arg);

	syslog_ctrl.sys_log_level = sys_log_level;
	return success;
}

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
status_t syslog_get_level(syslog_level_t *sys_log_level)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_init_not_done);
	*sys_log_level = syslog_ctrl.sys_log_level;
	return success;
}

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
status_t syslog_log(const char * agent, const char * fname _UNUSED, const char * line _UNUSED, const char * output_str, syslog_level_t log_level)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_init_not_done);
	RET_ERR((log_level < syslog_level_max) && (log_level >= syslog_level_verbose), error_inval_arg);
	RET_ERR(agent != NULL, error_inval_arg);
	RET_ERR(output_str != NULL, error_inval_arg);

	if (log_level >= syslog_ctrl.sys_log_level)
	{
		printf(syslog_ctrl.syslog_fmt, agent, syslog_loglevel_table[log_level],
#ifdef 	SYSLOG_SHOW_FILENAME_LINENO
		fname, line,
#endif
		output_str);
	}
	return success;
}

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
status_t syslog_release(void)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_init_not_done);

	memset(&syslog_ctrl, MEMSET_CLEAR, sizeof(syslog_ctrl));
	return success;
}
