/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_dp.c
 * Description		: This file contains sources for platform
 *			  device properties
 * Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
 * Organisation		: Cyancore Contributor
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
	.clk = 19200,
	.interrupt_id[0] = 25,
	.interrupt_id[1] = 27,
	.interrupt_trigger[0] = i_level,
	.interrupt_trigger[1] = i_level
};

gpio_module_t port0 =
{
	.id = gpio | PORTA,
	.baddr = 0x20,
	.stride = 3
};

gpio_module_t port1 =
{
	.id = gpio | PORTB,
	.baddr = 0x23,
	.stride = 3
};

gpio_module_t port2 =
{
	.id = gpio | PORTC,
	.baddr = 0x26,
	.stride = 3
};

gpio_module_t port3 =
{
	.id = gpio | PORTD,
	.baddr = 0x29,
	.stride = 3
};

gpio_module_t port4 =
{
	.id = gpio | PORTE,
	.baddr = 0x2c,
	.stride = 3
};

gpio_module_t port5 =
{
	.id = gpio | PORTF,
	.baddr = 0x2f,
	.stride = 3
};

gpio_module_t port6 =
{
	.id = gpio | PORTG,
	.baddr = 0x32,
	.stride = 3
};

gpio_module_t port7 =
{
	.id = gpio | PORTH,
	.baddr = 0x100,
	.stride = 3
};

gpio_module_t port8 =
{
	.id = gpio | PORTJ,
	.baddr = 0x103,
	.stride = 3
};

gpio_module_t port9 =
{
	.id = gpio | PORTK,
	.baddr = 0x106,
	.stride = 3
};

gpio_module_t port10 =
{
	.id = gpio | PORTL,
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

module_t timer0 =
{
	.id = timer | 0x00,
	.baddr = 0x44,
	.stride = 5,
	.interrupt_id[0] = 21,
	.interrupt_id[1] = 22,
	.clk_id = 5,
};

module_t timer1 =
{
	.id = timer | 0x10,
	.baddr = 0x80,
	.stride = 12,
	.interrupt_id[0] = 17,
	.interrupt_id[1] = 18,
	.clk_id = 3,
};

module_t timer2 =
{
	.id = timer | 0x20,
	.baddr = 0xb0,
	.stride = 5,
	.interrupt_id[0] = 13,
	.interrupt_id[1] = 14,
	.clk_id = 6,
};

module_t timer3 =
{
	.id = timer | 0x30,
	.baddr = 0x90,
	.stride = 12,
	.interrupt_id[0] = 32,
	.interrupt_id[1] = 33,
	.clk_id = 11,
};

module_t timer4 =
{
	.id = timer | 0x40,
	.baddr = 0xa0,
	.stride = 12,
	.interrupt_id[0] = 42,
	.interrupt_id[1] = 43,
	.clk_id = 12,
};

module_t timer5 =
{
	.id = timer | 0x50,
	.baddr = 0x120,
	.stride = 12,
	.interrupt_id[0] = 47,
	.interrupt_id[1] = 48,
	.clk_id = 13,
};

gpio_module_t *port_list[] =
{
	&port0, &port1, &port2, &port3, &port4, &port5,
	&port6, &port7, &port8, &port9, &port10
};

module_t *mod_list[] =
{
	&uart0, &wdt0,
	&timer0, &timer1, &timer2,
	&timer3, &timer4, &timer5,
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
