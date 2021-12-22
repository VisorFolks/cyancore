/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_dp.c
 * Description		: This file contains sources for platform
 *			  device properties
 * Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
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
	.name = "avr5",
	.id = 0x0000
};

memory_t mem =
{
	.start = 0,
	.size = DMEM_LENGTH
};

module_t uart0 =
{
	.id = uart | 0,
	.baddr = 0xc0,
	.clk_id = 0x01,
	.stride = 0x06,
	.clk = 19200,
	.interrupt_id[0] = 18,
	.interrupt_id[1] = 20,
	.interrupt_trigger[0] = i_level,
	.interrupt_trigger[1] = i_level
};

gpio_module_t port0 =
{
	.id = gpio | 0,
	.baddr = 0x20,
	.stride = 3
};

gpio_module_t port1 =
{
	.id = gpio | 1,
	.baddr = 0x23,
	.stride = 3
};

gpio_module_t port2 =
{
	.id = gpio | 2,
	.baddr = 0x26,
	.stride = 3
};

gpio_module_t port3 =
{
	.id = gpio | 3,
	.baddr = 0x29,
	.stride = 3
};

gpio_module_t port4 =
{
	.id = gpio | 4,
	.baddr = 0x2c,
	.stride = 3
};

gpio_module_t port5 =
{
	.id = gpio | 5,
	.baddr = 0x2f,
	.stride = 3
};

gpio_module_t port6 =
{
	.id = gpio | 6,
	.baddr = 0x32,
	.stride = 3
};

gpio_module_t port7 =
{
	.id = gpio | 7,
	.baddr = 0x100,
	.stride = 3
};

gpio_module_t port8 =
{
	.id = gpio | 8,
	.baddr = 0x103,
	.stride = 3
};

gpio_module_t port9 =
{
	.id = gpio | 9,
	.baddr = 0x106,
	.stride = 3
};

gpio_module_t port10 =
{
	.id = gpio | 10,
	.baddr = 0x109,
	.stride = 3
};

module_t wdt0 =
{
	.id = wdt | 0,
	.baddr=0x60,
	.stride=0x1,
	.interrupt_id[0] = 0x6,
	.interrupt_trigger[0] = i_level,
	.clk = 0x7
};

gpio_module_t *port_list[] =
{
	&port0, &port1, &port2, &port3, &port4, &port5, &port6, &port7, &port8, &port9, &port10
};

module_t *mod_list[] =
{
	&uart0, &wdt0,
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
