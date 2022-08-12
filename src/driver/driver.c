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
#include <status.h>
#include <syslog.h>
#include <string.h>
#include <arch.h>
#include <driver.h>

/**
 * _driver_table_* - Pointer to driver table
 *
 * @brief This address of this variable will be same as start and end
 * of the driver allocation table. This gets updated via linker
 * script "driver.ld.sx"
 */
extern device_t _driver_table_start, _driver_table_end;

static status_t driver_register_with_order(device_t *start, device_t *end, unsigned int order)
{
	status_t ret = success;
	device_t *ptr = start;
	/*
	 * Iterate the whole driver table so that on order
	 * match execute driver_setup
	 */
	while(ptr < end)
	{
		if(order == ptr->sorder)
			ret |= driver_register(ptr);
		ptr++;
	}
	return ret;
}

static status_t driver_deregister_with_order(device_t *start, device_t *end, unsigned int order)
{
	status_t ret = success;
	device_t *ptr = start;
	/*
	 * Iterate the whole driver table so that on order
	 * match execute driver_exit
	 */
	while(ptr < end)
	{
		if(order == ptr->sorder)
			ret |= driver_deregister(ptr);
		ptr++;
	}
	return ret;
}

static status_t driver_setup_with_name(device_t *start, device_t *end, const char *name)
{
	device_t *ptr = start;
	/*
	 * Iterate over the driver table and compare the names.
	 * On successful compare, run driver_setup.
	 */
	while(ptr < end)
	{
		if(strcmp(ptr->name, name) == 0)
			return driver_register(ptr);
		ptr++;
	}
	return error_func_inval;
}

static status_t driver_exit_with_name(device_t *start, device_t *end, const char *name)
{
	device_t *ptr = start;
	/*
	 * Iterate over the driver table and compare the names.
	 * On successful compare, run driver_setup.
	 */
	while(ptr < end)
	{
		if(strcmp(ptr->name, name) == 0)
			return driver_deregister(ptr);
		ptr++;
	}
	return error_func_inval;
}

/**
 * driver_setup_all - API call to initialize all the drivers
 * available in driver table
 *
 * @brief This function parses all the drivers in the table and runs
 * setup call of each driver. The driver_setup is called based
 * on the start order or rank. 0 to be started first and 255 at
 * last.
 *
 * @return status: returns the execution status of all drivers_setup
 *           in "or" method
 */
status_t driver_setup_all()
{
	status_t ret = success;
	unsigned int order;
	/* This loop controls the start order */
	for(order = 0; order < 256; order++)
		ret |= driver_register_with_order(&_driver_table_start,
				&_driver_table_end, order);
	return ret;
}

/**
 * driver_exit_all - API call to release all the drivers
 * available in driver table
 *
 * @brief This function parses all the drivers in the table and runs
 * exit call of each driver. The driver_exit is called based
 * on the exit order or rank. 255 to be exited first and 0 at
 * last.
 *
 * @return status: returns the execution status of all driver_exit
 *           in "or" method
 */
status_t driver_exit_all()
{
	status_t ret = success;
	int order;
	/* This loop controls the exit order */
	for(order = 255; order >= 0; order--)
		ret |= driver_deregister_with_order(&_driver_table_start,
				&_driver_table_end, order);
	return ret;
}

/**
 * driver_setup - API call to initialize driver using name
 *
 * @brief This function parses all the drivers in table and compares
 * the name of driver to be executed. On successful match, the
 * driver_setup is called.
 *
 * @param[in] *name: Take name of driver (string) as argument
 * @return status: return the execution status of driver_setup
 */
status_t driver_setup(const char *name)
{
	return driver_setup_with_name(&_driver_table_start,
			&_driver_table_end, name);
}

/**
 * driver_exit - API call to release driver using name
 *
 * @brief This function parses all the drivers in table and compares
 * the name of driver to be executed. On successful match, the
 * driver_exit is called.
 *
 * @param[in] *name: Take name of driver (string) as argument
 * @return status: return the execution status of driver_exit
 */
status_t driver_exit(const char *name)
{
	return driver_exit_with_name(&_driver_table_start,
			&_driver_table_end, name);
}

/**
 * driver_register - API call register driver for a device
 *
 * @brief This function is responsible to invoke driver_setup api
 * of corresponding device driver.
 *
 * @param[in] *dev: Device driver pointer
 * @return status: function exexcution status
 */
status_t driver_register(device_t *dev _UNUSED)
{
	status_t ret;
	uint8_t flag;

	if(!dev->percpu)
	{
		lock_acquire(&dev->key);
		flag = dev->exec;
		lock_release(&dev->key);

		if(flag)
		{
			ret = error_driver_init_done;
			goto exit;
		}

		lock_acquire(&dev->key);
		dev->exec = 1;
		arch_dmb();
		lock_release(&dev->key);
	}

	ret = dev->driver_setup();
	(ret == success) ? syslog(pass, "Started %s\n", dev->name) :
		syslog(fail, "Couldn't start %s (Err: -%p)\n", dev->name, -ret);
exit:
	return ret;
}

/**
 * driver_deregister - API call deregister driver for a device
 *
 * @brief This function is responsible to invoke driver_exit api
 * of corresponding device driver.
 *
 * @param[in] *dev: Device driver pointer
 * @return status: function exexcution status
 */
status_t driver_deregister(device_t *dev _UNUSED)
{
	status_t ret;
	uint8_t flag;

	if(!dev->percpu)
	{
		lock_acquire(&dev->key);
		flag = dev->exec;
		lock_release(&dev->key);

		if(!flag)
		{
			ret = error_driver;
			goto exit;
		}

		lock_acquire(&dev->key);
		dev->exec = 0;
		arch_dmb();
		lock_release(&dev->key);
	}

	syslog(pass, "Stopping %s\n", dev->name);
	ret = dev->driver_exit();
exit:
	return ret;
}
