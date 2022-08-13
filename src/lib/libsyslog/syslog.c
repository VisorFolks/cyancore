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
#include <time.h>

static lock_t syslog_lock;
static bool flag_enable_stdout;


int __syslog(logtype_t t, const char *c, ...)
{
	int ret;
	va_list va;
	uint64_t time;
	char logsign[] = {'/', 'i', '!', 'x', '$'};
	va_start(va, c);
	get_timestamp(&time);
	time /= 1000U;
	ret = fprintf(stdlog, flag_enable_stdout,"[%08llu] < %c > ", time,  logsign[t]);
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
	if(NOLOGS)
		return;
	lock_acquire(&syslog_lock);
	flag_enable_stdout = true;
	lock_release(&syslog_lock);
}

void syslog_stdout_disable()
{
	if(NOLOGS)
		return;
	lock_acquire(&syslog_lock);
	flag_enable_stdout = false;
	lock_release(&syslog_lock);
}
