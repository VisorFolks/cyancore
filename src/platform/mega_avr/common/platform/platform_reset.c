/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_reset.c
 * Description		: This file contains sources for platform reset
 *			  dummy apis. This is necessary to avoid comilation
 *			  failure when reset handling functions arent setup.
 *			  Original file can be found at
 *			  <Platform>/platform/platform_dp.c
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <platform.h>
#include <terravisor/platform.h>

extern uint8_t reset_syndrome;

/**
 * platform_get_reset_syndrome - returns the cause of reset
 *
 * @brief This function returns the information related to
 * the reset sources. Here it is a weak functiona actual
 * implementation can be found in the original file
 * mentioned in the file description.
 *
 * @return reset_cause: This function returs the reset cause
 */
_WEAK reset_t plarform_get_reset_syndrome()
{
	return (reset_t) reset_syndrome;
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
_WEAK void platform_reset_handler(reset_t rsyn)
{
	if(rsyn > external_reset)
		plat_panic_handler();
	return;
}
