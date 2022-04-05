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
	.interrupt[0] = {int_arch, 18, int_level},
	.interrupt[1] = {int_arch, 20, int_level},
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
	.interrupt[0] = {int_arch, 0x6, int_level},
	.clk = 0x7
};

module_t timer0 =
{
	.id = timer | 0x00,
	.baddr = 0x44,
	.stride = 5,
	.interrupt[0] = {int_arch, 14, int_level},
	.interrupt[1] = {int_arch, 15, int_level},
	.clk_id = 5,
};

module_t timer1 =
{
	.id = timer | 0x10,
	.baddr = 0x80,
	.stride = 12,
	.interrupt[0] = {int_arch, 11, int_level},
	.interrupt[1] = {int_arch, 12, int_level},
	.clk_id = 3,
};

module_t timer2 =
{
	.id = timer | 0x20,
	.baddr = 0xb0,
	.stride = 5,
	.interrupt[0] = {int_arch, 7, int_level},
	.interrupt[1] = {int_arch, 8, int_level},
	.clk_id = 6,
};

module_t adc0 =
{
	.id = adc | 0x00,
	.baddr = 0x78,
	.stride = 8,
	.interrupt[0] = {int_arch, 21, int_level},
	.interrupt[1] = {int_arch, 23, int_level},
	.clk_id = 0,
};

gpio_module_t *port_list[] =
{
	&port0, &port1, &port2,
};

module_t *mod_list[] =
{
	&uart0, &wdt0, &timer0, &timer1, &timer2, &adc0,
};

dp_t device_prop =
{
	.base_clock = FCLK,
	.core[0] = &core0,
	.memory = &mem,

	add_ports(port_list),

	add_modules(mod_list),
};
