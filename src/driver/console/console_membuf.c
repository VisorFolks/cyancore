#include <stdint.h>
#include <platform.h>
#include <status.h>
#include <driver.h>
#include <driver/console.h>

/* 
 * membuf is present in bss section hence will
 * be cleared during plaform boot
 */
char membuf[MEMBUF_SIZE];

status_t membuf_writeb(const char c)
{
	static size_t pointer = 0;
	if(pointer == MEMBUF_SIZE)	// Roll over after buffer is full
		pointer = 0;
	membuf[pointer++] = c;
	return success;
}

status_t membuf_flush()
{
	// This is necessary for cpus that uses cache
	return success;
}

console_t membuf_driver =
{
	.write	= membuf_writeb,
	.error	= membuf_writeb,
	.flush	= membuf_flush
};

status_t membuf_driver_setup()
{
	return console_attach_device(&membuf_driver);
}

#if EARLYCON_MEMBUF==1
INCLUDE_DRIVER(earlycon, &membuf_driver_setup);
#endif

#if CONSOLE_MEMBUF==1
INCLUDE_DRIVER(console, &membuf_driver_setup);
#endif
