#include <arc/stdint.h>
#include <platform.h>
#include <status.h>
#include <driver.h>
#include <driver/console.h>

/* 
 * membuf is present in bss section hence will
 * be cleared during plaform boot
 */
char membuf[MEMBUF_SIZE];

status_t membuf_putc(const char c)
{
	static size_t pointer = 0;
	if(pointer == MEMBUF_SIZE)
		pointer = 0;
	membuf[pointer++] = c;
	return success;
}

status_t membuf_puts(const char *s)
{
	while(*s != '\0')
		membuf_putc(*s++);
	return success;
}

status_t membuf_flush()
{
	return success;
}

console_t membuf_driver =
{
	.putc	= membuf_putc,
	.puts	= membuf_puts,
	.flush	= membuf_flush
};

void membuf_driver_setup()
{
	console_attach_driver(&membuf_driver);
}

INCLUDE_DRIVER(console, &membuf_driver_setup);
