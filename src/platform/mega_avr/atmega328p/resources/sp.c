/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_sp.c
 * Description		: This file contains sources for platform
 *			  software properties
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <resource.h>

swdev_t consoleUart =
{
	.swdev_id = console_uart,
	.hwdev_id = uart
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
