/*
 * CYANCORE LICENSE
 * Copyrights (C) 2023, Cyancore Team
 *
 * File Name		: platform_sp.c
 * Description		: This file contains sources for platform
 *			  software properties
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <plat_defines.h>
#include <resource.h>

static const uint8_t uart0pins[] = {16, 17};
static pinmux_t uart0 = addpins(0, uart0pins, serial);
swdev_t consoleUart =
{
	.swdev_id = console_uart,
	.hwdev_id = uart | 0,
	.pmux = &uart0
};

swdev_t schedTimer =
{
	.swdev_id = sched_timer,
	.hwdev_id = timer | 0,
};

const sw_devid_t terra_devs[] =
{
	console_uart, sched_timer,
};

visor_t terravisor = add_visor_devs(terra_devs);

swdev_t * const sw_devs[] =
{
	&consoleUart, &schedTimer,
};

sp_t software_prop =
{
	.terravisor = &terravisor,
	add_swdev(sw_devs),
};
