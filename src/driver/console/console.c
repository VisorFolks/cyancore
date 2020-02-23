#include <arc/stdio.h>
#include <driver/console.h>

int console_init()
{
	return 0;
}

int console_putc(int c)
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
