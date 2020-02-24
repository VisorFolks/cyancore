#pragma once

typedef struct console
{
	status_t (*setup)(void);
	status_t (*putc)(const char);
	status_t (*puts)(const char *);
	status_t (*flush)(void);
} console_t;

void console_attach_driver(console_t *);
int console_early_setup();
int console_setup();
int console_putc(const char);
int console_puts(const char *);
int console_flush(void);
