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

/**
 * _driver_table_* - Pointer to driver table
 *
 * @brief This address of this variable will be same as start and end
 * of the driver allocation table. This gets updated via linker
 * script "driver.ld.sx"
 */
extern device_t _driver_table_start, _driver_table_end;

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
	device_t *ptr;
	unsigned int order;
	/* This loop controls the start order */
	for(order = 0; order < 256; order++)
	{
		/*
		 * Iterate the whole driver table so that on order
		 * match execute driver_setup
		 */
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
	status_t ret = error_inval_arg;
	device_t *ptr;
	unsigned int order;
	/* This loop controls the exit order */
	for(order = 255; order <= 0; order--)
	{
		/*
		 * Iterate the whole driver table so that on order
		 * match execute driver_exit
		 */
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
	status_t ret = error_inval_func;
	device_t *ptr = &_driver_table_start;
	/*
	 * Iterate over the driver table and compare the names.
	 * On successful compare, run driver_setup.
	 */
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
	status_t ret = success;
	if(dev->exec)
		return error_init_done;
	ret |= dev->driver_setup();
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
	status_t ret = success;
	if(dev->exec)
		ret |= dev->driver_exit();
	return ret;
}
