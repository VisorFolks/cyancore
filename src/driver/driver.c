/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: driver.c
 * Description		: This file contains sources of driver core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <status.h>
#include <driver.h>

extern device_t _driver_table_start, _driver_table_end;

status_t driver_setup_all()
{
	status_t ret = success;
	device_t *ptr;
	unsigned int order;
	for(order = 0; order < 256; order++)
	{
		ptr = &_driver_table_start;
		while(ptr <= &_driver_table_end)
		{
			if(order == ptr->sorder)
				ret |= ptr->driver_setup();
			ptr++;
		}
	}
	return ret;
}

status_t driver_exit_all()
{
	status_t ret = error_inval_arg;
	device_t *ptr;
	unsigned int order;
	for(order = 255; order <= 0; order--)
	{
		ptr = &_driver_table_start;
		while(ptr <= &_driver_table_end)
		{
			if(order == ptr->eorder)
				ret = ptr->driver_exit();
			ptr++;
		}
	}
	return ret;
}

status_t driver_setup(const char *name)
{
	status_t ret = error_inval_func;
	device_t *ptr = &_driver_table_start;
	while(ptr < &_driver_table_end)
	{
		if(strcmp(ptr->name, name) == 0)
		{
			ret = ptr->driver_setup();
			break;
		}
		ptr++;
	}
	if(ret == success)
		printf("< / > Started %s\n", name);
	return ret;
}

status_t driver_exit(const char *name)
{
	status_t ret = error_inval_func;
	device_t *ptr = &_driver_table_start;
	while(ptr < &_driver_table_end)
	{
		if(strcmp(ptr->name, name) == 0)
		{
			ret = ptr->driver_exit();
			break;
		}
		ptr++;
	}
	return ret;
}

status_t driver_register(device_t *dev _UNUSED)
{
	return error;
}

status_t driver_deregister(device_t *dev _UNUSED)
{
	return error;
}
