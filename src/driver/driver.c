#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <status.h>
#include <driver.h>

extern device_t _driver_table_start, _driver_table_end;

status_t driver_setup_all()
{
	status_t ret = error_inval_arg;
	device_t *ptr = &_driver_table_start;
	while(ptr <= &_driver_table_end)
	{
		ret = ptr->driver_setup();
		ptr++;
	}
	return ret;
}

status_t driver_exit_all()
{
	status_t ret = error_inval_arg;
	device_t *ptr = &_driver_table_start;
	while(ptr <= &_driver_table_end)
	{
		ret = ptr->driver_exit();
		ptr++;
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

status_t driver_register(device_t *dev)
{
	dev->driver_setup();
	return success;
}

status_t driver_deregister(device_t *dev)
{
	dev->driver_setup = NULL;
	return success;
}
