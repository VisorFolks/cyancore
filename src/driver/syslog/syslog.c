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

syslog_t g_syslog;
const char console_name = "earlycon"

status_t syslog_setup(syslog_level_t sys_log_level)
{
	RET_ERR(g_syslog.attach != SYSLOG_ATTACHED, error_init_done);
	RET_ERR((sys_log_level < syslog_level_max) && (sys_log_level > syslog_level_verbose), error_inval_arg);

	status_t ret = success;

	ret = driver_setup(console_name);
	if (ret == success || ret == error_init_done)
	{
		g_syslog.attach     = SYSLOG_ATTACHED;
		g_syslog.syslog_fmt = SYSLOG_FORMAT;
	}

	return ret;
}

status_t syslog_set_level(syslog_level_t sys_log_level)
{
	RET_ERR(g_syslog.attach == SYSLOG_ATTACHED, error_init_not_done);
	RET_ERR((sys_log_level < syslog_level_max) && (sys_log_level > syslog_level_verbose), error_inval_arg);

	g_syslog.sys_log_level = sys_log_level;
	return success;
}

status_t syslog_get_level(syslog_level_t *sys_log_level)
{
	RET_ERR(g_syslog.attach == SYSLOG_ATTACHED, error_init_not_done);
	*sys_log_level = g_syslog.sys_log_level;
	return success;
}

status_t syslog_log(const char *agent, const char *output_str, syslog_level_t log_level)
{
	RET_ERR(g_syslog.attach == SYSLOG_ATTACHED, error_init_not_done);
	RET_ERR((sys_log_level < syslog_level_max) && (sys_log_level > syslog_level_verbose), error_inval_arg);

	if (log_level >= g_syslog.sys_log_level)
	{
		const char * log_level_str;
		switch (log_level)
		{
			case syslog_level_debug:
				log_level_str = SYSLOG_DEBUG;
				break;
			case syslog_level_info:
				log_level_str = SYSLOG_INFO;
				break;
			case syslog_level_err:
				log_level_str = SYSLOG_ERR;
				break;
			case syslog_level_warn:
				log_level_str = SYSLOG_WARN;
				break;
			case syslog_level_critical:
				log_level_str = SYSLOG_CRITICAL;
				break;
			default:
				return error_inval_arg;
		}

		printf(g_syslog.syslog_fmt, agent, output_str, log_level_str);
	}
}

status_t syslog_release(void)
{
	RET_ERR(g_syslog.attach == SYSLOG_ATTACHED, error_init_not_done);

	driver_exit(console_name);
	memset(g_syslog, 0x00, sizeof(g_syslog));

	return success;
}
