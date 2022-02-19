/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: console.c
 * Description		: This file contains sources of console engine
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <lock/lock.h>
#include <driver/console.h>

/**
 * *con - Console driver pointer
 *
 * This variable is updated by the console_attach_device
 * when the device driver is initialized
 */
static console_t *con;
static lock_t console_lock;

/**
 * console_attached - Flag to indicate the console status
 *
 * If True, the console is attached and if False the console
 * is detached.
 */
static bool console_attached = false;

/**
 * console_attach_device - This function links hardware driver
 * and device driver.
 *
 * @brief This function links the hardware driver and console device.
 * On successful linking, it updates the status flag so that
 * other functions know console is attached.
 *
 * @param[in] *pcon: pointer for console hardware driver
 * @return status: status of device/hardware driver
 */
status_t console_attach_device(status_t dev_status, console_t *pcon)
{
	status_t ret;
	lock_acquire(&console_lock);
	console_attached = false;
	con = pcon;
	if(con != NULL)
	{
		ret = dev_status;
		console_attached = (ret == success) ? true : false;
	}
	else
		ret = error_device_inval;
	lock_release(&console_lock);
	return ret;
}

/**
 * console_release_device - This function unlinks hardware driver
 * and device driver.
 *
 * @brief This function simply clear hardware driver pointer and updates
 * console status flag
 *
 * @return status: always a success.
 */
status_t console_release_device()
{
	lock_acquire(&console_lock);
	con = NULL;
	console_attached = false;
	lock_release(&console_lock);
	return success;
}

/**
 * console_putc - Send char data to console device
 *
 * @brief This API call writes the char data to "write" method of driver.
 * If the console is not attached, this API returns error which
 * needs to be handled by the caller function.
 *
 * @param[in] c: char (8-bits) data as input
 * @return status: function execution status
 */
status_t console_putc(const char c)
{
	status_t ret = error_func_inval;
	/* Check if the console is attached and write methos is valid */
	lock_acquire(&console_lock);
	if(console_attached && con->write != NULL)
		ret = con->write(c);
	lock_release(&console_lock);
	return ret;
}

/**
 * console_puts - Sends series of char data to console device
 *
 * @brief This API call sends char data console_putc until the stream
 * of data end with a null char.
 *
 * @param[in] *s: stream of char data
 * @return status: function execution status
 */
status_t console_puts(const char *s)
{
	status_t ret;
	while(*s != '\0')
	{
		ret = console_putc(*s);
		if(ret == error_func_inval)
			return ret;
		s++;
	}
	return success;
}

/**
 * console_getc - Fetch a char (8-bits) data form device driver
 *
 * @param[out] *c: pointer to store the read data
 * @return status: function execution status
 */
status_t console_getc(char *c)
{
	status_t ret = error_func_inval;
	lock_acquire(&console_lock);
	if(console_attached && con->read != NULL)
		ret = con->read(c);
	lock_release(&console_lock);
	return ret;
}

/**
 * console_flush - Flushes the console
 *
 * @return status: function execution status
 */
status_t console_flush()
{
	status_t ret = error_func_inval;
	lock_acquire(&console_lock);
	if(console_attached && con->flush != NULL)
		ret = con->flush();
	lock_release(&console_lock);
	return ret;
}
