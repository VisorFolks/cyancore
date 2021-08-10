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
				ret |= driver_register(ptr);
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
				ret = driver_deregister(ptr);
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
			ret = driver_register(ptr);
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
			ret = driver_deregister(ptr);
			break;
		}
		ptr++;
	}
	return ret;
}

status_t driver_register(device_t *dev)
{
	status_t ret = success;
	if(dev->exec)
		return error_init_done;
	ret |= dev->driver_setup();
	return ret;
}

status_t driver_deregister(device_t *dev)
{
	status_t ret = success;
	if(dev->exec)
		ret |= dev->driver_exit();
	return ret;
}
