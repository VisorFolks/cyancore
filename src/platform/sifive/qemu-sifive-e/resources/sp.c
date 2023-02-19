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

static const uint8_t led0pins[] = {19, 21};
static pinmux_t obled0 = addpins(0, led0pins, 0);
swdev_t onBoardLED0 =
{
	.swdev_id = onboard_led | 0,
	.pmux = &obled0
};

static const uint8_t led1pins[] = {20};
static pinmux_t obled1 = addpins(0, led1pins, 0);
swdev_t onBoardLED1 =
{
	.swdev_id = onboard_led | 1,
	.pmux = &obled1
};

const sw_devid_t terra_devs[] =
{
	console_uart, sched_timer, (onboard_led | 0),
	(onboard_led | 1),
};

visor_t terravisor = add_visor_devs(terra_devs);

swdev_t * const sw_devs[] =
{
	&consoleUart, &schedTimer, &onBoardLED0,
	&onBoardLED1,
};

sp_t software_prop =
{
	.terravisor = &terravisor,
	add_swdev(sw_devs),
};
