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
	.id = 0x00,
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
	.baddr = 0x23,
	.stride = 3
};

gpio_module_t port1 =
{
	.baddr = 0x26,
	.stride = 3
};

gpio_module_t port2 =
{
	.baddr = 0x29,
	.stride = 3
};

module_t wdt0 =
{
	.id = 0,
	.baddr=0x60,
	.stride=0x1,
	.interrupt_id[0] = 0x6,
	.interrupt_trigger[0] = i_level,
	.clk = 0x7
};

dp_t device_prop =
{
	.datawidth = 8,
	.base_clock = FCLK,
	.core[0] = &core0,
	.memory = &mem,

#if GPIO == 1
	.port[0] = &port0,
	.port[1] = &port1,
	.port[2] = &port2,
#endif

#if UART == 1
	.uart[0] = &uart0,
#endif

#if WDT == 1
	.wdt[0] = &wdt0,
#endif
};
