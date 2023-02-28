/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_reset.c
 * Description		: This file contains sources for platform
 *			  reset apis
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <assert.h>
#include <reset.h>
#include <resource.h>
#include <arch.h>
#include <driver/watchdog.h>
#include <platform.h>
#include <terravisor/platform.h>

extern uint32_t reset_syndrome;
/**
 * platform_get_reset_syndrome - returns the cause of reset
 *
 * @brief This function returns the infromation related to
 * the reset sources.
 *
 * @return reset_cause : This function returns the reset cause
 */

reset_t platform_get_reset_syndrome()
{
	sysdbg5("Reset Syndrome = %u\n", reset_syndrome);
	if(reset_syndrome & (1 << 8))
		return power_on_reset;

	if(reset_syndrome & (1 << 16))
		return external_reset;

	else
		return inval_reset;
}

/**
 * platform_reset_handler - handles the reset conditions
 *
 * @brief This function is responsible to handle the reset
 * sources like watchdog , brownout, etxernal reset, etc.
 *
 * @param[in] rsyn: Reset syndrome
 *
 * @return void
 */
void platform_reset_handler(reset_t rsyn)
{
	if(rsyn == power_on_reset)
		return;
	if(rsyn == external_reset)
		return;
	else
		plat_panic_handler();
}
