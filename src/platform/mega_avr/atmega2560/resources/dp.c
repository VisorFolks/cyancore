/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: dp.c
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

create_cpu(core0, "avr5", 0);

create_memory(mem, 0, DMEM_LENGTH);

create_module(uart0, (uart | 0), 0xc0, 0x06, 115200, 1,
		add_irq(0, int_arch, 25, int_level),
		add_irq(1, int_arch, 27, int_level));

create_gpio_module(port0, (gpio | PORTA), 0x20, 3);
create_gpio_module(port1, (gpio | PORTB), 0x23, 3);
create_gpio_module(port2, (gpio | PORTC), 0x26, 3);
create_gpio_module(port3, (gpio | PORTD), 0x29, 3);
create_gpio_module(port4, (gpio | PORTE), 0x2c, 3);
create_gpio_module(port5, (gpio | PORTF), 0x2f, 3);
create_gpio_module(port6, (gpio | PORTG), 0x32, 3);
create_gpio_module(port7, (gpio | PORTH), 0x100, 3);
create_gpio_module(port8, (gpio | PORTJ), 0x103, 3);
create_gpio_module(port9, (gpio | PORTK), 0x106, 3);
create_gpio_module(port10, (gpio | PORTL), 0x109, 3);

create_module(wdt0, (wdt | 0), 0x60, 0x1, 0x7, 0,
		add_irq(0, int_arch, 0x6, int_level));

create_module(timer0, (timer | 0x00), 0x44, 5, FCLK, 5,
		add_irq(0, int_arch, 21, int_level),
		add_irq(1, int_arch, 22, int_level));

create_module(timer1, (timer | 0x10), 0x80, 12, FCLK, 3,
		add_irq(0, int_arch, 17, int_level),
		add_irq(1, int_arch, 18, int_level));

create_module(timer2, (timer | 0x20), 0xb0, 5, FCLK, 6,
		add_irq(0, int_arch, 13, int_level),
		add_irq(1, int_arch, 24, int_level));

create_module(timer3, (timer | 0x30), 0x90, 12, FCLK, 11,
		add_irq(0, int_arch, 32, int_level),
		add_irq(1, int_arch, 33, int_level));

create_module(timer4, (timer | 0x40), 0xa0, 12, FCLK, 12,
		add_irq(0, int_arch, 42, int_level),
		add_irq(1, int_arch, 43, int_level));

create_module(timer5, (timer | 0x50), 0x120, 12, FCLK, 13,
		add_irq(0, int_arch, 47, int_level),
		add_irq(1, int_arch, 48, int_level));

create_gpio_list(port_list, &port0, &port1, &port2, &port3, &port4,
		&port5, &port6, &port7, &port8, &port9, &port10);

create_module_list(mod_list, &uart0, &wdt0, &timer0,
		&timer1, &timer2, &timer3, &timer4, &timer5);

create_dp(device_prop, FCLK, mem, port_list, mod_list,
		add_cpu(0, core0));
