/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: sp.c
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

create_visor(terravisor, console_uart, sched_timer);

create_swdev_list(sw_devs, &consoleUart, &schedTimer);

create_sp(software_prop,
	  add_swdev(sw_devs),
	  add_terravisor(terravisor),
	);
