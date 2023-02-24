/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: project.cpp
 * Description		: This file consists of project srouces in cpp
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/* Include C headers incapsulated in 'extern "C"' */
extern "C"
{
	#include <stdio.h>
	#include <status.h>
	#include <terravisor/platform.h>
	#include <terravisor/bootstrap.h>
	#include <driver.h>
	#include <driver/watchdog.h>
	#include <platform.h>
	#include <hal/gpio.h>
}

#include "gpio.h"


class onBoardLed led;

/* Use EXPORT_C macro for calling cpp function in c file */
EXPORT_C(void plug())
{
	bootstrap();
	driver_setup_all();

	/* call the constructor and setup member of led object */
	led = onBoardLed();
	led.setup();

	printf("Demo Program! - Cpp\n");
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

static unsigned char i = 0;
EXPORT_C(void play())
{
	wdog_guard(WDT_64MS, true, NULL);

	/* call the toggle member of led object */
	led.toggle();
	printf("%c]", progress[(i++) % 4]);
	wdog_hush();
	delay(500000);
	printf("\b\b");
	return;
}
