/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: project.c
 * Description		: This file consists of project srouces
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdio.h>
#include <string.h>
#include <terravisor/bootstrap.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <platform.h>
#include <mmio.h>
#include <hal/gpio.h>
#include <time.h>

static gpio_port_t gled, bled;

void plug()
{
	bootstrap();
	driver_setup_all();
	platform_print_cpu_info();

	gpio_pin_alloc(&gled, PORTA, 19);
	gpio_pin_alloc(&bled, PORTA, 21);
	gpio_pin_mode(&gled, out);
	gpio_pin_mode(&bled, out);
	gpio_pin_set(&gled);
	gpio_pin_set(&bled);

	printf("Demo Program!\n");
	printf("< ! > Running Blinky ... [");
	return;
}


void play()
{
	char progress[] = "-\\|/";
	static unsigned char i = 0;
	printf("%c]", progress[(i++) % strlen(progress)]);

	gpio_pin_toggle(&gled);
	gpio_pin_toggle(&bled);

	mdelay(500);

	printf("\b\b");
	return;
}
