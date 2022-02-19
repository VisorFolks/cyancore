/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: stddev.c
 * Description		: This file contains sources of libc-stddev
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdio.h>
#include <stddev.h>
#include <stdint.h>
#include <status.h>

FILE stddev[N_STDDEV];

status_t stdin_register(status_t (*read)(char *))
{
	if(!read)
		return error_device_inval;
	stddev[0].read = read;
	return success;
}

status_t stdout_register(status_t (*write)(const char))
{
	if(!write)
		return error_device_inval;
	stddev[1].write = write;
	return success;
}

status_t stderr_register(status_t (*write)(const char))
{
	if(!write)
		return error_device_inval;
	stddev[2].write = write;
	return success;
}

status_t stdlog_register(status_t (*write)(const char))
{
	if(!write)
		return error_device_inval;
	stddev[3].write = write;
	return success;
}
