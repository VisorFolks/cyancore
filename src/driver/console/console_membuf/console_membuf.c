/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: console_membuf.c
 * Description		: This file contains sources of memory buffer console
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <driver.h>
#include <driver/console.h>

/*
 * membuf is present in bss section hence will
 * be cleared during plaform boot
 */

char membuf[MEMBUF_SIZE];

status_t membuf_setup()
{
	return success;
}

status_t membuf_writeb(const char c)
{
	static size_t pointer = 0;
	if(c == '\b' && pointer)
	{
		pointer --;
		return success;
	}
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
	.setup	= membuf_setup,
	.write	= membuf_writeb,
	.error	= membuf_writeb,
	.flush	= membuf_flush
};

status_t membuf_driver_setup()
{
	return console_attach_device(&membuf_driver);
}

status_t membuf_driver_exit()
{
	return console_release_device();
}

#if EARLYCON_MEMBUF==1
INCLUDE_DRIVER(earlycon, membuf_driver_setup, membuf_driver_exit, 0, 0, 0);
#endif
