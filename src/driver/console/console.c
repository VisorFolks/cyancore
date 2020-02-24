#include <arc/stdio.h>
#include <status.h>
#include <driver/console.h>

console_t *con;

void console_attach_driver(console_t *pcon)
{
	con = pcon;
}

int console_early_setup()
{
	return 0;
}

int console_setup()
{
	return 0;
}

int console_putc(const char c)
{
	return c;
}

int console_puts(const char *s)
{
	return *s;
}

int console_flush()
{
	return 0;
}
