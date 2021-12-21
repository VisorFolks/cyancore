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

#include <stdint.h>
#include <status.h>
#include <mmio.h>
#include <plat_arch.h>
#include <platform.h>
#include <../hal/wdt/wdt_private.h>

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
