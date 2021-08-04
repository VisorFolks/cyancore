/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: syslog.h
 * Description		: This file defines the syscalls for system console logging
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <syslog/syslog.h>

syslog_t g_syslog;
const char console_name = "earlycon"

status_t syslog_setup(syslog_level_t sys_log_level)
{
	CHECK_ARGS(g_syslog.attach != SYSLOG_ATTACHED);
	CHECK_ARGS((sys_log_level < syslog_level_max) && (sys_log_level > syslog_level_min));

	status_t ret = success;

	ret = driver_setup(console_name);
	if (ret == success)
	{
		g_syslog.attach     = SYSLOG_ATTACHED;
		g_syslog.syslog_fmt = SYSLOG_FORMAT;
	}

	return ret;
}
status_t syslog_set_level(syslog_level_t sys_log_level)
{
	CHECK_ARGS(g_syslog.attach == SYSLOG_ATTACHED);
	CHECK_ARGS((sys_log_level < syslog_level_max) && (sys_log_level > syslog_level_min));

	g_syslog.sys_log_level = sys_log_level;
	return success;
}
status_t syslog_get_level(syslog_level_t *sys_log_level)
{
	CHECK_ARGS(g_syslog.attach == SYSLOG_ATTACHED);
	*sys_log_level = g_syslog.sys_log_level;
	return success;
}
status_t syslog_log(const char *agent, const char *output_str, syslog_level_t syslog_level)
{
	CHECK_ARGS(g_syslog.attach == SYSLOG_ATTACHED);
	CHECK_ARGS((sys_log_level < syslog_level_max) && (sys_log_level > syslog_level_min));

	if (syslog_level >= g_syslog.sys_log_level)
	{
		const char * log_level;
		switch (syslog_level)
		{
			case syslog_level_debug:
				log_level = SYSLOG_DEBUG;
				break;
			case syslog_level_info:
				log_level = SYSLOG_INFO;
				break;
			case syslog_level_err:
				log_level = SYSLOG_ERR;
				break;
			case syslog_level_warn:
				log_level = SYSLOG_WARN;
				break;
			case syslog_level_critical:
				log_level = SYSLOG_CRITICAL;
				break;
			default:
				return error_inval_arg;
		}

		printf(g_syslog.syslog_fmt, agent, output_str, log_level);
	}
}
status_t syslog_release(void)
{
	CHECK_ARGS(g_syslog.attach == SYSLOG_ATTACHED);

	driver_exit(console_name);
	memset(g_syslog, 0x00, sizeof(g_syslog));

	return success;
}
