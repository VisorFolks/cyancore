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
#include <syslog.h>
#include <stdlib.h>
#include <platform.h>
#include <driver.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <hal/wdt.h>
#include <driver/watchdog.h>
#include <../hal/wdt/wdt_private.h>

/**
 * plat_wdt - platform driver instance for wdt
 */
static wdt_port_t *plat_wdt;

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
static status_t platform_wdt_setup()
{
	mret_t mres;
	module_t *dp;
	arch_machine_call(fetch_dp, wdt, 0, 0, &mres);

	if(mres.status != success)
	{
		sysdbg2("WDT not found in DP\n");
		return mres.status;
	}
	dp = (module_t *) mres.p;
	plat_wdt = (wdt_port_t *)malloc(sizeof(wdt_port_t));
	if(!plat_wdt)
		return error_memory_low;
	plat_wdt->port_id = dp->id;
	plat_wdt->clk_id = dp->clk_id;
	plat_wdt->baddr = dp->baddr;
	plat_wdt->stride = dp->stride;
	plat_wdt->timeout = (size_t) dp->clk;
	plat_wdt->wdt_irq = (unsigned int) dp->interrupt[0].id;
	plat_wdt->wdt_handler = &platform_wdt_handler;

	sysdbg2("WDT engine @ %p\n", plat_wdt->baddr);

	return wdt_setup(plat_wdt);
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
static status_t platform_wdt_guard(size_t timeout, bool bite, void *cb_bark)
{
	status_t ret;
	sysdbg3("Configuring WDT timeout to gear %d\n", timeout);
	plat_wdt->timeout = timeout;
	callback_on_bark = cb_bark;
	ret = wdt_set_timeout(plat_wdt);
	sysdbg3("WDT Bite %s\n", bite ? "enabled" : "disabled");
	ret |= bite ? wdt_sre(plat_wdt) : wdt_srd(plat_wdt);
	return ret;
}

/**
 * platform_wdt_hush - Resets and suspends wdog
 *
 * @brief This function reset wdt counter and suspends the wdog.
 *
 * @return status: returns function execution status
 */
static status_t platform_wdt_hush()
{
	status_t ret;
	wdt_hush(plat_wdt);
	sysdbg3("WDT Hush!\n");
	plat_wdt->timeout = 0;
	ret = wdt_set_timeout(plat_wdt);
	ret |= wdt_srd(plat_wdt);
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
static wdog_t *plat_wdt_driver;
static status_t plat_wdt_driver_exit();

/**
 * plat_wdt_driver_setup
 * 
 * @brief This function is called to initialise wdt driver during boot
 */
static status_t plat_wdt_driver_setup()
{
	status_t ret;
	sysdbg3("In %s\n", __func__);
	plat_wdt_driver = (wdog_t *)malloc(sizeof(wdog_t));
	if(!plat_wdt_driver)
		return error_memory_low;
	plat_wdt_driver->guard = &platform_wdt_guard;
	plat_wdt_driver->hush = &platform_wdt_hush;
	ret = platform_wdt_setup();
	if(ret)
		goto cleanup_exit;
	ret = wdog_attach_device(ret, plat_wdt_driver);
	if(!ret)
		goto exit;
cleanup_exit:
	plat_wdt_driver_exit();
exit:
	return ret;
}

/**
 * plat_wdt_driver_exit
 *
 * @brief This function is called to shutdown wdt device and unlink driver
 */
static status_t plat_wdt_driver_exit()
{
	status_t ret;
	ret = wdog_release_device();
	if(plat_wdt)
		ret |= wdt_shutdown(plat_wdt);
	free(plat_wdt_driver);
	free(plat_wdt);
	return ret;
}

/* Add driver to driver table */
INCLUDE_DRIVER(watchdog, plat_wdt_driver_setup, plat_wdt_driver_exit, 1, 1, 1);

/**
 * platform_wdt_reset - reset wdt counter at platform setup
 *
 * @brief This function should be invoked during the platform
 * boot or setup. This resets the WDT config register.
 *
 * @return status: return the execution status of platform_wdt_reset
 */
status_t platform_wdt_reset()
{
	uint8_t val;
	write_wdtcsr(0x00);
	val = MMIO8(WDTCSR);
	if(val == 0)
		return success;
	return error_driver_data;
}
