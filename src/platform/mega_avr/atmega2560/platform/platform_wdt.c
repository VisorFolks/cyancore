/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_wdt.c
 * Description		: This file contains sources for platform
 *			  wdt apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdio.h>
#include <platform.h>
#include <driver.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <hal/wdt.h>
#include <driver/watchdog.h>

/**
 * plat_wdt - platform driver instance for wdt
 */
static wdt_port_t plat_wdt;

/**
 * *callback_on_bark - Callback function pointer which needs
 * to be excuted in wdt irq
 */
static void (*callback_on_bark)(void);

void platform_wdt_handler();

/**
 * platform_wdt_setup - Performs wdt setup
 *
 * @brief This function performs the wdt setup by fetching information
 * form device proporties.
 *
 * @return status: returns function execution status
 */
status_t platform_wdt_setup()
{
	mret_t mres;
	module_t *dp;
	mres = arch_machine_call(fetch_dp, wdt, 0, 0);

	if(mres.status != success)
		return mres.status;
	dp = (module_t *) mres.p;
	plat_wdt.port_id = dp->id;
	plat_wdt.clk_id = dp->clk_id;
	plat_wdt.baddr = dp->baddr;
	plat_wdt.stride = dp->stride;
	plat_wdt.timeout = dp->clk;
	plat_wdt.wdt_irq = dp->interrupt_id[0];
	plat_wdt.wdt_handler = &platform_wdt_handler;

	return wdt_setup(&plat_wdt);
}

/**
 * platform_wdt_setup - Starts wdog device to monitor hangs
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
status_t platform_wdt_guard(size_t timeout, bool bite, void *cb_bark)
{
	status_t ret;
	plat_wdt.timeout = timeout;
	callback_on_bark = cb_bark;
	ret = wdt_set_timeout(&plat_wdt);
	ret |= bite ? wdt_sre(&plat_wdt) : wdt_srd(&plat_wdt);
	return ret;
}

/**
 * platform_wdt_hush - Resets and suspends wdog
 *
 * @brief This function reset wdt counter and suspends the wdog.
 *
 * @return status: returns function execution status
 */
status_t platform_wdt_hush()
{
	status_t ret;
	wdt_hush(&plat_wdt);
	plat_wdt.timeout = 0;
	ret = wdt_set_timeout(&plat_wdt);
	ret |= wdt_srd(&plat_wdt);
	return ret;
}

/**
 * platform_wdt_handler - WDT IRQ handler
 */
void platform_wdt_handler()
{
	printf("\n< ! > Watchdog Bark on core: [%d]\n", (int)arch_core_index());
	if(callback_on_bark)
		callback_on_bark();
}

/**
 * @brief This struct links top level and low level driver apis
 */
wdog_t plat_wdt_driver =
{
	.setup = &platform_wdt_setup,
	.guard = &platform_wdt_guard,
	.hush = &platform_wdt_hush
};

/**
 * plat_wdt_driver_setup
 * 
 * @brief This function is called to initialise wdt driver during boot
 */
status_t plat_wdt_driver_setup()
{
	return wdog_attach_device(&plat_wdt_driver);
}

/**
 * plat_wdt_driver_exit
 *
 * @brief This function is called to shutdown wdt device and unlink driver
 */
status_t plat_wdt_driver_exit()
{
	status_t ret;
	ret = wdog_release_device();
	ret |= wdt_shutdown(&plat_wdt);
	return ret;
}

/* Add driver to driver table */
INCLUDE_DRIVER(watchdog, plat_wdt_driver_setup, plat_wdt_driver_exit, 1, 1);
