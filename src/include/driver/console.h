#pragma once
#define _CONSOLE_H_

typedef struct console
{
	status_t (*setup)(void);
	status_t (*write)(const char);
	status_t (*read)(char *);
	status_t (*error)(const char);
	status_t (*flush)(void);
} console_t;

status_t console_attach_device(console_t *);
status_t console_release_device();
status_t console_setup();
status_t console_putc(const char);
status_t console_puts(const char *);
status_t console_getc(char *);
status_t console_flush(void);
