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
#include <stdio.h>
#include <status.h>
#include <arch.h>
#include <driver/watchdog.h>

/**
 * *port - Individual driver instance for each core
 */
static wdog_t *port[N_CORES];

/**
 * wdog_attached - Individual flags for each core
 */
static bool wdog_attached[N_CORES] = {[0 ... N_CORES-1] = false};

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
status_t wdog_attach_device(wdog_t *pwdog)
{
	status_t ret;
	size_t cpu_id = arch_core_id();

	/* Link the driver structs */
	port[cpu_id] = pwdog;

	/* Check if the link is valid */
	if(port[cpu_id] != NULL)
	{
		ret = port[cpu_id]->setup();
		wdog_attached[cpu_id] = (ret == success) ? true : false;
	}
	else
		ret = error_inval_arg;
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
	size_t cpu_id = arch_core_id();
	port[cpu_id] = NULL;
	wdog_attached[cpu_id] = false;
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
	size_t cpu_id = arch_core_id();
	if(wdog_attached[cpu_id] && port[cpu_id]->guard != NULL)
		return port[cpu_id]->guard(timeout, bite, cb_bark);
	return error_inval_func;
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
	size_t cpu_id = arch_core_id();
	if(wdog_attached[cpu_id] && port[cpu_id]->hush != NULL)
	{
		port[cpu_id]->hush();
		return success;
	}
	return error_inval_func;
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
	printf("\n< x > Watchdog Bite on Core: [%d]\n", (int)arch_core_id());
	plat_panic_handler();
}
