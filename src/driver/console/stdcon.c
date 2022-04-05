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
#include <status.h>
#include <syslog.h>
#include <stdio.h>
#include <stddev.h>
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
		ret |= stdout_register(&console_putc);
		sysdbg3("Registering stdout\n");
		ret |= stderr_register(&console_putc);
		sysdbg3("Registering stderr\n");
		ret |= stdin_register(&console_getc);
		sysdbg3("Registering stdin\n");
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
	if(console_attached && con->write != NULL)
		ret = con->write(c);
	return ret;
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
	if(console_attached && con->read != NULL)
		ret = con->read(c);
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
	if(console_attached && con->flush != NULL)
		ret = con->flush();
	return ret;
}

/*
 * console_get_payload_size - Returns the size of payload available to read
 *
 * @return uint: size of payload to read
 */
unsigned int console_get_payload_size(void)
{
	status_t ret = 0;
	if(console_attached && con->payload_size != NULL)
		ret = *(con->payload_size);
	return ret;
}

static console_t *log;
static lock_t log_lock;
static bool logger_attached;

status_t logger_attach_device(status_t dev_status, console_t *pcon)
{
	status_t ret;
	lock_acquire(&log_lock);
	logger_attached = false;
	log = pcon;
	if(log != NULL)
	{
		ret = dev_status;
		logger_attached = (ret == success) ? true : false;
		ret |= stdlog_register(&logger_putc);
	}
	else
		ret = error_device_inval;
	lock_release(&log_lock);
	return ret;
}

status_t logger_release_device()
{
	lock_acquire(&log_lock);
	log = NULL;
	logger_attached = false;
	lock_release(&log_lock);
	return success;
}

status_t logger_putc(const char c)
{
	status_t ret = error_func_inval;
	if(logger_attached && log->write != NULL)
		ret = log->write(c);
	return ret;
}

status_t logger_dprint(const FILE *device)
{
	status_t lvar;
	char c;
	if(!device || !logger_attached)
		return error_device_inval;
	do
	{
		lvar = log->read(&c);
		fputc(device, c);
	}
	while(lvar);
	return success;
}
