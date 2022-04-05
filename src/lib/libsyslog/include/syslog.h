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

/* General Debug */
#define sysdbg(fmt, ...)	if(DEBUG) syslog(dbug, fmt, ##__VA_ARGS__)
/* Level 1 Debug: Application level logging */
#define sysdbg1(fmt, ...)	if(DEBUG>=1) syslog(dbug, fmt, ##__VA_ARGS__)
/* Level 2 Debug: Driver level logging */
#define sysdbg2(fmt, ...)	if(DEBUG>=2) syslog(dbug, fmt, ##__VA_ARGS__)
/* Level 3 Debug: Functional level logging */
#define sysdbg3(fmt, ...)	if(DEBUG>=3) syslog(dbug, fmt, ##__VA_ARGS__)
/* Level 4 Debug: Module level logging */
#define sysdbg4(fmt, ...)	if(DEBUG>=4) syslog(dbug, fmt, ##__VA_ARGS__)
/* Level 5 Debug: Register level logging */
#define sysdbg5(fmt, ...)	if(DEBUG>=5) syslog(dbug, fmt, ##__VA_ARGS__)
