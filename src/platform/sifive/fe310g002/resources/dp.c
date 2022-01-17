/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_dp.c
 * Description		: This file contains sources for platform
 *			  device properties
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <resource.h>
#include <plat_mem.h>

#ifndef FCLK
#define FCLK 0
WARN(< ! > FCLK is not defined!)
#endif

cpu_t core0 =
{
	.name = "riscv-e310",
	.id = 0x0000
};

memory_t mem =
{
	.start = V_DMEM_START,
	.size = DMEM_LENGTH
};

module_t plic0 =
{
	.id = plic,
	.baddr = 0x0c000000,
	.stride = 0x04000000,
	.interrupt_id[0] = 11,
};

module_t *mod_list[] =
{
	&plic0,
};

dp_t device_prop =
{
	.base_clock = FCLK,
	.core[0] = &core0,
	.memory = &mem,

	.modules = mod_list,
	.n_mods = sizeof(mod_list)/sizeof(module_t *)
};
