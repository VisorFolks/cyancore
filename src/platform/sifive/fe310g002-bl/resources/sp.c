/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
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

static uint8_t uart0pins[] = {16, 17};
static pinmux_t uart0 = addpins(0, uart0pins, serial);
swdev_t consoleUart =
{
	.swdev_id = console_uart,
	.hwdev_id = uart | 0,
	.pmux = &uart0
};

sw_devid_t terra_devs[] =
{
	console_uart,
};

visor_t terravisor = add_visor_devs(terra_devs);

swdev_t *sw_devs[] =
{
	&consoleUart,
};

sp_t software_prop =
{
	.terravisor = &terravisor,
	add_swdev(sw_devs),
};
