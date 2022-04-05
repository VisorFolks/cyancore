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
#include <platform.h>
#include <driver.h>
#include <driver/watchdog.h>
#include <hal/gpio.h>

gpio_port_t onboad_led;

void plug()
{
	bootstrap();
	driver_setup_all();
	gpio_pin_alloc(&onboad_led, PORTB, 5);
	gpio_pin_mode(&onboad_led, out);
	gpio_pin_clear(&onboad_led);
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
	static unsigned int i = 0;
	wdog_guard(WDT_64MS, true, NULL);
	gpio_pin_toggle(&onboad_led);
	printf("%c]", progress[(i++) % strlen(progress)]);
	wdog_hush();
	delay(500000);
	printf("\b\b");
	return;
}
