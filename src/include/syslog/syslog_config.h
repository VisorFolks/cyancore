 /*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: syslog.h
 * Description		: This file defines the syscalls for system console logging
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */


#ifndef SYSLOG_SHOW_FILENAME_LINENO
#define SYSLOG_SHOW_FILENAME_LINENO	0
#endif

#ifndef SYSLOG_MAX_CALLBACKS
#define SYSLOG_MAX_CALLBACKS		1U
#endif

#ifndef SYSLOG_BUFFER_LEN
#define SYSLOG_BUFFER_LEN		256U
#endif

#ifndef SYSLOG_COLORED_LOG
#define SYSLOG_COLORED_LOG		0
#endif

#if SYSLOG_MAX_CALLBACKS < 1
ERROR(SYSLOG_MAX_CALLBACKS shall be greater than 0)
#endif

#if SYSLOG_BUFFER_LEN < 256
ERROR(SYSLOG_BUFFER_LEN shall be greater than 255 bytes)
#endif

#if SYSLOG_COLORED_LOG
ERROR(SYSLOG_COLORED_LOG not supported yet in cyancore)
#endif
