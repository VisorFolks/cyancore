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
#include <hal/gpio.h>

#ifndef XCLK
#define XCLK 0
WARN(< ! > XCLK is not defined!)
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
	.interrupt[0] = {int_local, 11, int_rising_edge},
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
	.interrupt[0] = {int_plat, 3, int_rising_edge},
};

module_t uart1 =
{
	.id = uart | 1,
	.baddr = 0x10023000,
	.stride = 0x20,
	.clk = 115200,
	.interrupt[0] = {int_plat, 4, int_rising_edge},
};

module_t prci0 =
{
	.id = prci,
	.baddr = 0x10008000,
	.stride = 0x1000,
};

gpio_module_t port0 =
{
	.id = gpio | PORTA,
	.baddr = 0x10012000,
	.stride = 0x4c,
};

module_t aon0 =
{
	.id = aon | 0,
	.baddr = 0x10000000,
	.stride = 0x1000,
};

module_t timer_core0 =
{
	.id = timer | 0,
	.clk = 1e7,
	.interrupt[0] = {int_local, 7, int_level},
};

gpio_module_t * const port_list[] =
{
	&port0,
};

module_t * const mod_list[] =
{
	&plic0, &uart0, &prci0, &clint0, &aon0, &uart1,
	&timer_core0,
};

dp_t device_prop =
{
	.base_clock = XCLK,
	.core[0] = &core0,
	.memory = &mem,

	add_ports(port_list),

	add_modules(mod_list),
};
