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

status_t syslog_attach(syslog_level_e sys_log_level)
{
	ASSERT_LOG(g_syslog.attach != SYSLOG_ATTACHED);
	ASSERT_LOG(sys_log_level < syslog_level_max);
	ASSERT_LOG(sys_log_level >= syslog_level_notset);

	g_syslog.attach = SYSLOG_ATTACHED;

	return success;
}
status_t syslog_change_level(syslog_level_e sys_log_level)
{
}
status_t syslog_log(const char *agent, const char *output_str, syslog_level_e syslog_level)
{
}
status_t syslog_dettach(void)
{
}
