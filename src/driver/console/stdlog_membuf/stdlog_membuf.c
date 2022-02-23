/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: earlycon_membuf.c
 * Description		: This file contains sources of memory buffer
 *			  early console
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <driver.h>
#include <driver/console.h>
#include <stdio.h>

/*
 * membuf is present in bss section hence will
 * be cleared during plaform boot
 */

char membuf[MEMBUF_SIZE];

static status_t membuf_setup()
{
	return success;
}

static status_t membuf_writeb(const char c)
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

static status_t membuf_read(char *c)
{
	static size_t pread = 0;
	*c = membuf[pread++];
	if(pread == MEMBUF_SIZE)
	{
		pread = 0;
		return success;
	}
	return error_generic;	// to be used in while loop to read the full buffer
}

static status_t membuf_flush()
{
	// This is necessary for cpus that uses cache
	return success;
}

static console_t membuf_driver =
{
	.write	= &membuf_writeb,
	.read = &membuf_read,
	.flush	= &membuf_flush
};

status_t membuf_driver_setup()
{
	status_t ret;
	ret = membuf_setup();
	ret |= logger_attach_device(ret, &membuf_driver);
	return ret;
}

status_t membuf_driver_exit()
{
	return logger_release_device();
}

#if STDLOG_MEMBUF==1
INCLUDE_DRIVER(mslog, membuf_driver_setup, membuf_driver_exit, 0, 0, 0);
#endif
