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
#include <insignia.h>
#include <terravisor/platform.h>
#include <terravisor/bootstrap.h>
#include <driver.h>
#include "gpio_bit_banding.h"

void plug()
{
	bootstrap();
	driver_setup("earlycon");
	printf("Reset Status: %d\n", platform_get_reset_syndrome());
	cyancore_insignia_lite();
	gpio_init();
	printf("Demo Program!\n");
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
	gpio_toggle();
	printf("%c]", progress[i++]);
	i = i > 3 ? 0 : i;
	delay(500000);
	printf("\b\b");
	return;
}
