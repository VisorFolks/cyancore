/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: dp.c
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

create_cpu(core0, "avr5", 0);

create_memory(mem, 0, DMEM_LENGTH);

create_module(uart0, (uart | 0), 0xc0, 0x06, 115200, 1,
		add_irq(0, int_arch, 18, int_level),
		add_irq(1, int_arch, 20, int_level));

create_gpio_module(port0, (gpio | PORTB), 0x23, 3);
create_gpio_module(port1, (gpio | PORTC), 0x26, 3);
create_gpio_module(port2, (gpio | PORTD), 0x29, 3);

create_module(wdt0, (wdt | 0), 0x60, 0x1, 0x7, 0,
		add_irq(0, int_arch, 0x6, int_level));

create_module(timer0, (timer | 0x00), 0x44, 5, FCLK, 5,
		add_irq(0, int_arch, 14, int_level),
		add_irq(1, int_arch, 15, int_level));

create_module(timer1, (timer | 0x10), 0x80, 12, FCLK, 3,
		add_irq(0, int_arch, 11, int_level),
		add_irq(1, int_arch, 12, int_level));

create_module(timer2, (timer | 0x20), 0xb0, 5, FCLK, 6,
		add_irq(0, int_arch, 7, int_level),
		add_irq(1, int_arch, 8, int_level));

create_module(adc0, (adc | 0x00), 0x78, 8, 0, 0,
		add_irq(0, int_arch, 21, int_level),
		add_irq(1, int_arch, 23, int_level));

create_gpio_list(port_list, &port0, &port1, &port2);

create_module_list(mod_list, &uart0, &wdt0, &timer0,
		&timer1, &timer2, &adc0);

create_dp(device_prop, FCLK, mem, port_list, mod_list,
		add_cpu(0, core0));
