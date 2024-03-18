/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: platform_resource.c
 * Description		: This file contains sources for platform
 *			  resource apis
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
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
 * and make it accessible to the system. This function needs to be called
 * during platform setup.
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
