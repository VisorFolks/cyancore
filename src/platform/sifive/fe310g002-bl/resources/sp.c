/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
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

create_pmux(uart0, 0, serial, 16, 17);
create_swdev(consoleUart, console_uart, (uart | 0), add_pinmux(uart0));

create_swdev(schedTimer, sched_timer, (timer | 0));

create_pmux(obled0, 0, 0, 19, 21);
create_swdev(onBoardLED0, (onboard_led | 0), 0, add_pinmux(obled0));

create_pmux(obled1, 0, 0, 20);
create_swdev(onBoardLED1, (onboard_led | 1), 0, add_pinmux(obled1));

create_visor(terravisor, console_uart, sched_timer,
		(onboard_led | 0), (onboard_led | 1));

create_swdev_list(sw_devs, &consoleUart, &schedTimer, &onBoardLED0, &onBoardLED1);

create_sp(software_prop,
	  add_swdev(sw_devs),
	  add_terravisor(terravisor),
	);
