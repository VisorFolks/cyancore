/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019-2022, Cyancore Team
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
#include <syslog.h>
#include <resource.h>
#include <visor_call.h>
#include <platform.h>

/**
 * platform_resources_setup - Updates platform DP and SP
 *
 * @brief This function is responsible to update platform DP
 * and make it accessible to the system. This function needs
 * to be called during platform setup. 
 *
 * @return status: return the function execution status
 */
status_t platform_resources_setup()
{
	status_t ret = success;
	extern dp_t device_prop;
	extern sp_t software_prop;
	ret = dp_init(&device_prop);
	ret |= sp_init(&software_prop);
	return ret;
}

/**
 * platform_fetch_sp - vcall handler for fetch_sp
 *
 * @brief This function is a machine call hander for fetch_sp
 * access code. It is responsible to respond with hardware ID
 * to corresponding software properties. 
 *
 * @param[in] a0: arg0
 * @param[in] a1: arg1
 * @param[in] a2: arg2
 *
 * @return status: return the function execution status
 */
static void platform_fetch_sp(call_arg_t a0, call_arg_t a1 _UNUSED,
		call_arg_t a2 _UNUSED, vret_t *ret)
{
	sysdbg5("Fetch SP: Got request for %x\n", a0);
	ret->p = (uintptr_t) sp_terravisor_dev_info(a0);
	ret->size = (ret->p) ? sizeof(hw_devid_t) : 0;
	ret->status = (ret->p) ? success : error_device_id_inval;
	return;
}

INCLUDE_VCALL(sifive_fe310_fetch_sp, fetch_sp, platform_fetch_sp);

/**
 * platform_fetch_dp - vcall handler for fetch_dp
 *
 * @brief This function is a machine call hander for fetch_dp
 * access code. It is responsible to respond with pointer to
 * corresponding device properties. 
 *
 * @param[in] a0: arg0
 * @param[in] a1: arg1
 * @param[in] a2: arg2
 *
 * @return status: return the function execution status
 */
static void platform_fetch_dp(call_arg_t a0, call_arg_t a1 _UNUSED,
		call_arg_t a2 _UNUSED, vret_t *ret)
{
	sysdbg5("Fetch DP: Got request for %x\n", a0);
	switch(a0)
	{
		case clock:
			ret->p = (uintptr_t)dp_get_base_clock();
			ret->size = (ret->p) ? sizeof(uint64_t) : 0;
			break;
		case gpio:
			ret->p = (uintptr_t)dp_get_port_info(a0 | a1);
			ret->size = (ret->p) ? sizeof(gpio_module_t) : 0;
			break;
		default:
			ret->p = (uintptr_t) dp_get_module_info(a0 | a1);
			ret->size = (ret->p) ? sizeof(module_t) : 0;
			break;
	}
	ret->status = (ret->p) ? success : error_device_id_inval;
	return;
}

INCLUDE_VCALL(sifive_fe310_fetch_dp, fetch_dp, platform_fetch_dp);
