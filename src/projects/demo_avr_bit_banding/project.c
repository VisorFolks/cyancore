/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: project.c
 * Description		: This file consists of project srouces
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdio.h>
#include <status.h>
#include <terravisor/platform.h>
#include <terravisor/bootstrap.h>
#include <driver.h>
#include <driver/watchdog.h>
#include "gpio_bit_banding.h"

void plug()
{
	bootstrap();
	driver_setup_all();
	gpio_init();
	printf("Demo Program! - Bit Banding\n");
	printf("< ! > Running Blinky ... [");
	return;
}

char progress[] = "-\\|/";

void delay(unsigned long d)
{
	unsigned long c;
	for(c = 0; c < d; c++)
		asm volatile("nop");
}

void play()
{
	static int i = 0;
	wdog_guard(3, true, NULL);
	gpio_toggle();
	printf("%c]", progress[i++]);
	i = i > 3 ? 0 : i;
	wdog_hush();
	delay(500000);
	printf("\b\b");
	return;
}
