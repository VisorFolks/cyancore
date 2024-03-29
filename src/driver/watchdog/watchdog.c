/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: watchdog.c
 * Description		: This file contains sources of watchdog engine
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdbool.h>
#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <arch.h>
#include <lock/lock.h>
#include <driver/watchdog.h>

/**
 * *port - Individual driver instance for each core
 */
static wdog_t *port[N_CORES];

/**
 * wdog_attached - Individual flags for each core
 */
static bool wdog_attached[N_CORES] = {[0 ... N_CORES-1] = false};
static lock_t wdog_lock[N_CORES];

/**
 * wdog_attach_device - Link lower level driver with wdog driver
 *
 * @brief This function links the functions of low level driver
 * with the user callable functions present in this file. It also
 * performs per core initialization.
 *
 * @param[in] *pwdog: Lower level driver structure to link
 *
 * @return status: returns initialization status
 */
status_t wdog_attach_device(status_t dev_status, wdog_t *pwdog)
{
	status_t ret;
	size_t cpu_index = arch_core_index();
	lock_t *lock = &wdog_lock[cpu_index];

	lock_acquire(lock);
	/* Link the driver structs */
	port[cpu_index] = pwdog;

	/* Check if the link is valid */
	if(port[cpu_index] != NULL)
	{
		ret = dev_status;
		wdog_attached[cpu_index] = (ret == success) ? true : false;
	}
	else
		ret = error_device_inval;
	lock_release(lock);
	return ret;
}

/**
 * wdog_release_device - Unlinks the driver with lower level calls
 *
 * @brief This function unlinks the lower level driver calls.
 *
 * @return status: Always success
 */
status_t wdog_release_device()
{
	size_t cpu_index = arch_core_index();
	lock_t *lock = &wdog_lock[cpu_index];
	lock_acquire(lock);
	port[cpu_index] = NULL;
	wdog_attached[cpu_index] = false;
	lock_release(lock);
	return success;
}

/**
 * wdog_guard - Starts wdog device to monitor hangs
 *
 * @brief This function starts wdog device to start ticking
 * and triggers interrupt or perform system reset based on
 * config params when the core hangs or wdt isn't reset.
 *
 * @param[in] timeout: WDog Timeout value
 * @param[in] bite: This arg when set, wdog perform system reset
 * @param[in] *cb_bark: Callback function for wdog bark irq
 *
 * @return status: returns function execution status
 */
status_t wdog_guard(size_t timeout, bool bite, void *cb_bark)
{
	status_t ret = error_func_inval;
	size_t cpu_index = arch_core_index();
	lock_t *lock = &wdog_lock[cpu_index];
	lock_acquire(lock);
	if(wdog_attached[cpu_index] && port[cpu_index]->guard != NULL)
		ret = port[cpu_index]->guard(timeout, bite, cb_bark);
	lock_release(lock);
	return ret;
}

/**
 * wdog_hush - Resets and suspends wdog
 *
 * @brief This function reset wdt counter and suspends the wdog.
 * Everytime wdog_guard needs to be invoked after call this function
 * to monitor core hangs.
 *
 * @return status: returns function execution status
 */
status_t wdog_hush()
{
	status_t ret = error_func_inval;
	size_t cpu_index = arch_core_index();
	lock_t *lock = &wdog_lock[cpu_index];
	lock_acquire(lock);
	if(wdog_attached[cpu_index] && port[cpu_index]->hush != NULL)
	{
		port[cpu_index]->hush();
		ret = success;
	}
	lock_release(lock);
	return ret;
}

extern void plat_panic_handler();

/**
 * wdog_reset_handler - wdog bite handler
 *
 * @brief This function is invoked by reset handler when wdog
 * bite is detected as reset source.
 */
void wdog_reset_handler()
{
	syslog(fail, "Watchdog Bite on Core: [%d]\n", (int)arch_core_index());
	plat_panic_handler();
}
