/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_reset.c
 * Description		: This file contains sources for platform
 *			  reset apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <platform.h>
#include <driver/watchdog.h>
#include <terravisor/platform.h>

extern unsigned int reset_syndrome;

/**
 * platform_get_reset_syndrome - returns the cause of reset
 *
 * @brief This function returns the information related to
 * the reset sources. 
 *
 * @return reset_cause: This function returs the reset cause
 */
reset_t platform_get_reset_syndrome()
{
	if(reset_syndrome & 1)		/* Power on Reset */
		return power_on_reset;
	else
		return inval_reset;
}


/**
 * platform_reset_handler - handles the reset conditions
 *
 * @brief This function is responsible to handle the reset
 * sources like watchdog, brownout, external reset, etc.
 *
 * @param[in] rsyn: Reset syndrome
 *
 * @return void
 */
void platform_reset_handler(reset_t rsyn)
{
	if(rsyn == power_on_reset)
		return;
	else
		plat_panic_handler();
}

