/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: bootstrap.c
 * Description		: This file contains sources of bootstrap routine
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <arch.h>
#include <driver.h>
#include <insignia.h>
#include <terravisor/platform.h>
#include <terravisor/bootstrap.h>


status_t bootstrap()
{
	reset_t resetSyndrome;

	arch_early_setup();

	if(arch_core_index() == BOOT_CORE_ID)
		platform_early_setup();

	arch_setup();

	if(arch_core_index() == BOOT_CORE_ID)
		platform_setup();

	resetSyndrome = platform_get_reset_syndrome();
	platform_reset_handler(resetSyndrome);

	platform_cpu_setup();

	return success;
}
