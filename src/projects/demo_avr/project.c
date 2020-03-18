#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <status.h>
#include <hal/gpio.h>

extern void platform_early_setup();

void project_setup()
{
	printf("Demo AVR: Running Blinky... [ ]\b");
	gpio_pin_config(0, 5, out);
	gpio_pin_clear(0, 5);
	return;
}

void delay()
{
	for(long i = 0; i < 500000; i++)
		asm volatile("nop");
}

void project_loop()
{
	gpio_pin_toggle(0, 5);
	printf("\b|");
	delay();
	gpio_pin_toggle(0, 5);
	printf("\b/");
	delay();
	gpio_pin_toggle(0, 5);
	printf("\b-");
	delay();
	gpio_pin_toggle(0, 5);
	printf("\b\\");
	delay();
	return;
}
