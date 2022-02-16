/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: syslog.h
 * Description		: This file defines the prototypes for syslog
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SYSLOG_H_

typedef enum logtype
{
	pass = 0,
	info = 1,
	warn = 2,
	fail = 3,
	dbug = 4
} logtype_t;

int syslog(logtype_t, const char *, ...);
status_t syslog_print();
void syslog_stdout_enable();
void syslog_stdout_disable();
