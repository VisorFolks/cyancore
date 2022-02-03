/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: syslog.c
 * Description		: This file is the source for the syscalls of system console logging
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <syslog.h>
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
	.set_level	= syslog_set_level,
	.reg_cb		= syslog_reg_cb,
	.dereg_cb	= syslog_dereg_cb
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
 * syslog_buffer - Chracter buffer used by syslog system.
 *
 * This variable is used internally by the API(s)
 * This variable is not globally available for user space.
 */
static char syslog_buffer [SYSLOG_BUFFER_LEN];

/**
 * @fn 		syslog_setup - Initialize the logging system
 * @brief	This function is to setup the system logging module to be used by all the levels of the system
 *
 * @param[in]	sys_log_level	This is the initial logging level of the logging system.
 * @param[in]	cb		Syslog minimal callback. Default: NULL, selects: syslog_default_cb (weak)
 *
 * @return	status
 * @exception	error_func_inval_arg		for argument errors
 * @exception	error_driver_init_done		if the initialisation is already done
 */
status_t syslog_setup(syslog_level_t sys_log_level, syslog_cb_t cb)
{
	RET_ERR(syslog_ctrl.attach != SYSLOG_ATTACHED, error_driver_init_done);
	RET_ERR((sys_log_level < syslog_level_max) && (sys_log_level >= syslog_level_verbose), error_func_inval_arg);

	status_t ret = success;

	ret = console_setup();
	if (ret == success || ret == error_driver_init_done)
	{
		syslog_ctrl.syslog_fmt = SYSLOG_FMT_DEF;
		syslog_ctrl.syslog_table_reg_len = SYSLOG_VAR_INIT;
		memset(&(syslog_ctrl.syslog_cb_table), SYSLOG_VAR_INIT, SYSLOG_MAX_CALLBACKS);
		if(cb == NULL)
		{
			syslog_ctrl.syslog_cb_table[SYSLOG_VAR_INIT] = syslog_default_cb;
		}
		syslog_ctrl.attach     = SYSLOG_ATTACHED;
	}

	return ret;
}

/**
 * @fn		syslog_set_level	Set new logging level for system logging
 * @brief	This function helps to set a new level of system logging
 * 		Logging levels available:
 * 		1. syslog_level_debug (minimum)
 *		2. syslog_level_info
 *		3. syslog_level_warn
 *		4. syslog_level_err
 *		5. syslog_level_critical (maximum)
 *
 * @param[in]	sys_log_level	This is the new logging level of the logging system.
 *
 * @return	status_t
 * @exception	error_func_inval_arg		for argument errors
 * @exception	error_driver_init_failed	if the initialisation is not done
 */
status_t syslog_set_level(syslog_level_t sys_log_level)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_driver_init_failed);
	RET_ERR((sys_log_level < syslog_level_max) && (sys_log_level >= syslog_level_verbose), error_func_inval_arg);

	syslog_ctrl.sys_log_level = sys_log_level;
	return success;
}

/**
 * @fn 		syslog_get_level - Get the current logging level for system logging
 * @brief	This function helps to get the current level of system logging
 *
 * @param[out] 	sys_log_level	This is the current logging level of the logging system.
 *
 * @return	status
 * 		error_func_inval_arg		for argument errors
 * 		error_driver_init_failed	if the initialisation is not done
 */
status_t syslog_get_level(syslog_level_t *sys_log_level)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_driver_init_failed);
	*sys_log_level = syslog_ctrl.sys_log_level;
	return success;
}

/**
 * @fn 		syslog_log - Produce log.
 * @brief	This function helps to create a log on the console output.
 * 		Logging levels available:
 * 		1. syslog_level_debug (minimum)
 *		2. syslog_level_info
 *		3. syslog_level_warn
 *		4. syslog_level_err
 *		5. syslog_level_critical (maximum)
 *
 * @param[in]	agent		Pointer to the agent string (limit: 15 char). Default: \b CYANCORE, if NULL
 * @param[in]	fname		Pointer to file_name string. Default: NULL. Usage: pass __FILE__ macro to automatically fetch file location.
 * @param[in]	line		Pointer to line number string. Default: NULL. Usage: pass __LINE__ macro to automatically fetch current line number.
 * @param[in]	output_str	string that is to be part of the information
 * @param[in]	log_level	Level of the output log (Ref: Logging levels available)
 *
 * @return	status
 * @exception	error_func_inval_arg		for argument errors
 * @exception	error_driver_init_failed	if the initialisation is not done
 */
status_t syslog_log(const char * agent, const char * fname _UNUSED, int line _UNUSED, const char * output_str, syslog_level_t log_level)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_driver_init_failed);
	RET_ERR((log_level < syslog_level_max) && (log_level >= syslog_level_verbose), error_func_inval_arg);
	RET_ERR(output_str != NULL, error_func_inval_arg);

	char * agent_str = (char *)agent;

	if (agent == NULL)
	{
		agent_str = SYSLOG_DEFAULT_AGENT;
	}
	if (log_level >= syslog_ctrl.sys_log_level)
	{
		snprintf(syslog_buffer, SYSLOG_BUFFER_LEN, syslog_ctrl.syslog_fmt, agent_str, syslog_loglevel_table[log_level],
#ifdef 	SYSLOG_SHOW_FILENAME_LINENO
		fname, line,
#endif
		output_str);
		for(syslog_cb_fd_t index = 0; index < syslog_ctrl.syslog_table_reg_len; index++)
		{
			if (syslog_ctrl.syslog_cb_table[index] != NULL)
			{
				syslog_ctrl.syslog_cb_table[index](syslog_buffer, strlen(syslog_buffer));
			}
		}
	}
	return success;
}

/**
 * @fn 		syslog_reg_cb - Register syslog callback
 * @brief	This function helps to register the syslog callback
 *
 * @param[in]	cb		Pointer to callback function.
 * @param[out]	fd		File descriptor pointer as received during registration
 *
 * @return	status
 * @exception	error_generic			if maximum possible callback registered
 * @exception	error_func_inval_arg		for argument errors
 * @exception	error_driver_init_failed	if the initialisation is not done
 */
status_t syslog_reg_cb(syslog_cb_t cb, syslog_cb_fd_t *fd)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_driver_init_failed);
	RET_ERR(syslog_ctrl.syslog_table_reg_len < SYSLOG_MAX_CALLBACKS, error_generic);
	RET_ERR(cb != NULL, error_func_inval_arg);
	RET_ERR(fd != NULL, error_func_inval_arg);

	*fd = (syslog_cb_fd_t) error_func_inval_arg;
	for(syslog_cb_fd_t index = 0; index < syslog_ctrl.syslog_table_reg_len; index++)
	{
		if(syslog_ctrl.syslog_cb_table[index] == NULL)
		{
			*fd = index;
			break;
		}
		else
		{
			continue;
		}
	}

	RET_ERR(!(syslog_ctrl.syslog_table_reg_len >= SYSLOG_MAX_CALLBACKS && *fd == (syslog_cb_fd_t) error_func_inval_arg), error_generic);

	if(*fd == (syslog_cb_fd_t) error_func_inval_arg)
	{
		syslog_ctrl.syslog_cb_table[syslog_ctrl.syslog_table_reg_len] = cb;
		*fd = syslog_ctrl.syslog_table_reg_len;
		syslog_ctrl.syslog_table_reg_len ++;
	}
	else
	{
		syslog_ctrl.syslog_cb_table[*fd] = cb;
	}

	return success;
}

/**
 * @fn 		syslog_dereg_cb - De-register syslog callback
 * @brief	This function helps to release the syslog callback
 *
 * @param[in]	fd		File descriptor pointer as received during registration
 *
 * @return	status
 * @exception	error_func_inval_arg		for argument errors
 * @exception	error_driver_init_failed	if the initialisation is not done
 */
status_t syslog_dereg_cb(syslog_cb_fd_t *fd)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_driver_init_failed);
	RET_ERR(fd != NULL, error_func_inval_arg);
	RET_ERR(*fd < syslog_ctrl.syslog_table_reg_len, error_func_inval_arg);

	syslog_ctrl.syslog_cb_table[*fd] = NULL;
	*fd = SYSLOG_VAR_INIT;

	return success;
}

/**
 * @fn 		syslog_release - Release syslog module
 * @brief	This function helps to release the syslog module
 *
 * @param[in/out]	void
 *
 * @return	status
 * @exception	error_func_inval_arg		for argument errors
 * @exception	error_driver_init_failed	if the initialisation is not done
 */
status_t syslog_release(void)
{
	RET_ERR(syslog_ctrl.attach == SYSLOG_ATTACHED, error_driver_init_failed);

	memset(&syslog_ctrl, MEMSET_CLEAR, sizeof(syslog_ctrl));
	return success;
}

/**
 * @fn 		syslog_default_cb - Default syslog callback to print on console
 * @brief	This function is a re-definable function.
 *
 * @param[in]	str_in		Callback input strng
 * @param[in]	len		Callback input length
 *
 * @return	void
 */
_WEAK void syslog_default_cb(char * str_in, size_t len _UNUSED)
{
	printf(str_in);
}
