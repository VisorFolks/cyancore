/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform.c
 * Description		: This file contains sources for platform apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <status.h>
#include <hal/gpio.h>
#include <arch.h>
#include <machine_call.h>
#include <terravisor/platform.h>
#include <terravisor/workers.h>
#include <platform.h>

/**
 * reset_syndrome - This varible is consists of reset syndrome in
 *		    bss section of memory. This variable is updated
 *		    in the platform_early_setup as this is the
 *		    earliest function which resets bss section.
 */
uint8_t reset_syndrome;

/**
 * platform_early_setup - Executes pre-setup functions
 *
 * @brief This function performs calls to certain function that
 * are necessary to be called to make the plaform ready for setup.
 * Function like bss clear, data copy, clock reset, etc are called
 * in this function. As reset_syndrome is bss variable, it must be
 * updated only after the bss is cleared. Ideally it should be
 * updated at last. < ! > This function should be made to run on 
 * boot core only!
 */
void platform_early_setup()
{
	status_t ret = success;

	ret |= platform_copy_data();
	ret |= platform_bss_clear();
	ret |= platform_clk_reset();

	reset_syndrome = MMIO8(MCUSR) & 0x1f;
	MMIO8(MCUSR) = 0;

	ret |= platform_wdt_reset();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

/**
 * platform_setup - Executes function to make platform read to init
 *
 * @brief This function performs calls to function which make the
 * framework ready to execute. In this case (MegaAVR), it is dp_setup.
 * < ! > This function should be made to run on boot core only!
 */
void platform_setup()
{
	status_t ret = success;
	ret |= platform_resources_setup();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

/**
 * platform_cpu_setup - Perform platform setup calls on all cpus
 *
 * @brief This function perform calls to functions that must be executed
 * on all corea to make the cpu ready for the platform drivers.
 */
void platform_cpu_setup()
{
	status_t ret = success;
	ret |= platform_mcall_update(&machine_call);
	arch_ei();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

