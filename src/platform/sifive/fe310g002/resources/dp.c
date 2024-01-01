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

#ifndef XCLK
#define XCLK 0
WARN(< ! > XCLK is not defined!)
#endif

create_cpu(core0, "riscv-e310", 0);

create_memory(mem, V_DMEM_START, DMEM_LENGTH);

create_module(plic0, plic, 0x0c000000, 0x04000000, 0, 0,
		add_irq(0, int_local, 11, int_rising_edge));

create_module(clint0, clint, 0x02000000, 0xc000, 0, 0);

create_module(uart0, (uart | 0), 0x10013000, 0x20, 115200, 0,
		add_irq(0, int_plat, 3, int_rising_edge));

create_module(uart1, (uart | 1), 0x10023000, 0x20, 115200, 0,
		add_irq(0, int_plat, 4, int_rising_edge));

create_module(prci0, prci, 0x10008000, 0x1000, 0, 0);

create_module(aon0, (aon | 0), 0x10000000, 0x1000, 0, 0);

create_module(timer_core0, (timer | 0), 0, 0, 32768, 0,
		add_irq(0, int_local, 7, int_level));

create_gpio_module(port0, (gpio | PORTA), 0x10012000, 0x4c);

create_gpio_list(port_list, &port0);

create_module_list(mod_list, &plic0, &uart0, &prci0,
		&clint0, &aon0, &uart1, &timer_core0);

create_dp(device_prop, XCLK, mem, port_list, mod_list,
	add_cpu(0, core0));
