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

module_t clint0 =
{
	.id = clint,
	.baddr = 0x02000000,
	.stride = 0xc000,
};

module_t uart0 =
{
	.id = uart | 0,
	.baddr = 0x10013000,
	.stride = 0x20,
	.clk = 115200,
	.interrupt_id[0] = 3,
};

module_t prci0 =
{
	.id = prci,
	.baddr = 0x10008000,
	.stride = 0x1000,
};

gpio_module_t port0 =
{
	.id = gpio | 0,
	.baddr = 0x10012000,
	.stride = 0x4c,
};

module_t aon0 =
{
	.id = aon | 0,
	.baddr = 0x10000000,
	.stride = 0x1000,
};

gpio_module_t *port_list[] =
{
	&port0,
};

module_t *mod_list[] =
{
	&plic0, &uart0, &prci0, &clint0, &aon0,
};

dp_t device_prop =
{
	.base_clock = FCLK,
	.core[0] = &core0,
	.memory = &mem,

	.ports = port_list,
	.n_ports = sizeof(port_list)/sizeof(gpio_module_t *),

	.modules = mod_list,
	.n_mods = sizeof(mod_list)/sizeof(module_t *)
};
