/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: console.h
 * Description		: This file consists of console core prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _CONSOLE_H_

typedef struct console
{
	status_t (*write)(const char);
	status_t (*read)(char *);
	status_t (*flush)(void);
} console_t;

status_t console_attach_device(status_t, console_t *);
status_t console_release_device();
status_t console_setup();
status_t console_putc(const char);
status_t console_puts(const char *);
status_t console_getc(char *);
status_t console_flush(void);

status_t logger_attach_device(status_t, console_t *);
status_t logger_release_device();
status_t logger_putc(const char);

#ifdef _STDIO_H_
status_t logger_dprint(FILE *);
#endif
