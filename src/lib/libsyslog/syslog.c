/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: syslog.c
 * Description		: This file is the source for the syslog
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <status.h>
#include <stdio.h>
#include <stddev.h>
#include <lock/lock.h>
#include <driver/console.h>
#include <syslog.h>

static lock_t syslog_lock;
static bool flag_enable_stdout;

static char *logsign[] = {"< / >", "< i >", "< ! >", "< x >", "< $ >"};

int syslog(logtype_t t, const char *c, ...)
{
	int ret;
	va_list va;
	va_start(va, c);
	ret = fprintf(stdlog, flag_enable_stdout,"%s ", logsign[t]);
	ret += vprintf(stdlog, flag_enable_stdout, c, va);
	va_end(va);
	return ret;
}

status_t syslog_print()
{
	return logger_dprint(stdout);
}

void syslog_stdout_enable()
{
	lock_acquire(&syslog_lock);
	flag_enable_stdout = true;
	lock_release(&syslog_lock);
}

void syslog_stdout_disable()
{
	lock_acquire(&syslog_lock);
	flag_enable_stdout = false;
	lock_release(&syslog_lock);
}
