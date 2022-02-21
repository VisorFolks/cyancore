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
	.clk = 115200,
	.interrupt_id[0] = 18,
	.interrupt_id[1] = 20,
	.interrupt_trigger[0] = i_level,
	.interrupt_trigger[1] = i_level
};

gpio_module_t port0 =
{
	.id = gpio | PORTB,
	.baddr = 0x23,
	.stride = 3
};

gpio_module_t port1 =
{
	.id = gpio | PORTC,
	.baddr = 0x26,
	.stride = 3
};

gpio_module_t port2 =
{
	.id = gpio | PORTD,
	.baddr = 0x29,
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

module_t timer0 =
{
	.id = timer | 0x00,
	.baddr = 0x44,
	.stride = 5,
	.interrupt_id[0] = 14,
	.interrupt_id[1] = 15,
	.clk_id = 5,
};

module_t timer1 =
{
	.id = timer | 0x10,
	.baddr = 0x80,
	.stride = 12,
	.interrupt_id[0] = 11,
	.interrupt_id[1] = 12,
	.clk_id = 3,
};

module_t timer2 =
{
	.id = timer | 0x20,
	.baddr = 0xb0,
	.stride = 5,
	.interrupt_id[0] = 7,
	.interrupt_id[1] = 8,
	.clk_id = 6,
};

gpio_module_t *port_list[] =
{
	&port0, &port1, &port2,
};

module_t *mod_list[] =
{
	&uart0, &wdt0, &timer0, &timer1, &timer2,
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
