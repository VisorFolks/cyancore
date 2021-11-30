/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_dp.c
 * Description		: This file contains sources for platform
 *			  device properties apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <status.h>
#include <resource.h>
#include <device.h>
#include <machine_call.h>
#include <platform.h>

status_t platform_dp_setup()
{
	extern dp_t device_prop;
	return dp_init(&device_prop);
}

mret_t platform_fetch_dp(unsigned int dev, unsigned int a0 _UNUSED, unsigned int a1 _UNUSED)
{
	mret_t ret;
	switch(dev)
	{
		case DEV_CLOCK:
			ret.p = (uintptr_t)dp_get_base_clock();
			ret.size = sizeof(unsigned long);
			ret.status = success;
			break;
#if UART == 1
		case DEV_CONSOLE:
			ret.p = (uintptr_t)dp_get_uart_info(a0);
			ret.size = sizeof(module_t);
			ret.status = success;
			break;
#endif
#if GPIO == 1
		case DEV_GPIO:
			ret.p = (uintptr_t)dp_get_port_info(a0);
			ret.size = sizeof(gpio_module_t);
			ret.status = success;
			break;
#endif
#if WDT == 1
		case DEV_WDT:
			ret.p = (uintptr_t) dp_get_wdt_info(a0);
			ret.size = sizeof(module_t);
			ret.status = success;
			break;
#endif
		default:
			ret.p = (uintptr_t)NULL;
			ret.size = 0x00;
			ret.status = error_inval_dev_id;
			break;
	}

	return ret;
}

INCLUDE_MCALL(atmega328p_fetch_dp, fetch_dp, platform_fetch_dp);
