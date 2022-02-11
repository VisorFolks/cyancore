/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: project.c
 * Description		: This file consists of project srouces
 * Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
 * Organisation		: Cyancore Contributor
 */

#include <stdio.h>
#include <status.h>
#include <string.h>
#include <terravisor/platform.h>
#include <terravisor/bootstrap.h>
#include <driver.h>
#include <driver/watchdog.h>
#include <hal/gpio.h>

gpio_port_t onboard_led;

void plug()
{
	bootstrap();
	driver_setup_all();
	gpio_pin_alloc(&onboard_led, PORTB, 7);
	gpio_pin_mode(&onboard_led, out);
	gpio_pin_clear(&onboard_led);
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
	wdog_guard(3, true, NULL);
	gpio_pin_toggle(&onboard_led);
	printf("%c]", progress[i++ % strlen(progress)]);
	wdog_hush();
	delay(500000);
	printf("\b\b");
	return;
}
