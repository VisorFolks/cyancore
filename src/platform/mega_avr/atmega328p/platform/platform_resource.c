/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_resource.c
 * Description		: This file contains sources for platform
 *			  resource apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <status.h>
#include <resource.h>
#include <machine_call.h>
#include <platform.h>

status_t platform_resources_setup()
{
	status_t ret;
	extern dp_t device_prop;
	extern sp_t software_prop;
	ret = dp_init(&device_prop);
	ret |= sp_init(&software_prop);
	return ret;
}

mret_t platform_fetch_sp(unsigned int a0, unsigned int a1 _UNUSED, unsigned int a2 _UNUSED)
{
	mret_t ret;
	ret.p = (uintptr_t) sp_terravisor_dev_info(a0);
	ret.size = sizeof(hw_devid_t);
	ret.status = success;
	return ret;
}

INCLUDE_MCALL(atmega328p_fetch_sp, fetch_sp, platform_fetch_sp);

mret_t platform_fetch_dp(unsigned int dev, unsigned int a0 _UNUSED, unsigned int a1 _UNUSED)
{
	mret_t ret;
	switch(dev)
	{
		case clock:
			ret.p = (uintptr_t)dp_get_base_clock();
			ret.size = sizeof(unsigned long);
			ret.status = success;
			break;
#if UART == 1
		case uart:
			ret.p = (uintptr_t)dp_get_uart_info(a0);
			ret.size = sizeof(module_t);
			ret.status = success;
			break;
#endif
#if GPIO == 1
		case gpio:
			ret.p = (uintptr_t)dp_get_port_info(a0);
			ret.size = sizeof(gpio_module_t);
			ret.status = success;
			break;
#endif
#if WDT == 1
		case wdt:
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
