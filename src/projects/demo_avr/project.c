#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <driver/console.h>
#include <hal/gpio.h>
#include <terravisor/bootloader.h>

extern char cyancore_logo[];

void project_setup()
{
	bootloader();
	printf("%s", cyancore_logo);
	gpio_pin_config(0, 5, out);
	gpio_pin_clear(0, 5);
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

void project_loop()
{
	static int i = 0;
	gpio_pin_toggle(0, 5);
	printf("%c]", progress[i++]);
	i = i > 3 ? 0 : i;
	delay(500000);
	printf("\b\b");
	return;
}
