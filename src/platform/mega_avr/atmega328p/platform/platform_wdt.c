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
#include <device.h>
#include <driver.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <hal/wdt.h>
#include <driver/watchdog.h>

wdt_port_t plat_wdt;

void platform_wdt_handler();

status_t platform_wdt_setup()
{
	mret_t mres;
	module_t *dp;
	mres = arch_machine_call(fetch_dp, DEV_WDT, 0, 0);

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

	wdt_setup(&plat_wdt);
	wdt_sre(&plat_wdt);
	return success;
}


status_t platform_wdt_hush()
{
	wdt_hush(&plat_wdt);
	return success;
}

void platform_wdt_handler()
{
	printf("\n< ! > Watchdog Bark on core:[%d]\n", (int)arch_core_id());
}

wdog_t plat_wdt_driver =
{
	.setup = &platform_wdt_setup,
	.hush = &platform_wdt_hush
};

status_t plat_wdt_driver_setup()
{
	return wdog_attach_device(&plat_wdt_driver);
}

status_t plat_wdt_driver_exit()
{
	status_t ret;
	ret = wdog_release_device();
	ret |= wdt_shutdown(&plat_wdt);
	return ret;
}

INCLUDE_DRIVER(watchdog, plat_wdt_driver_setup, plat_wdt_driver_exit, 1, 1);
