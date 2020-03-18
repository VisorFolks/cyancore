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

char arr[] = {'|', '/', '-', '\\'};

void project_loop()
{
	static uint8_t i = 0;
	gpio_pin_toggle(0, 5);
	printf("\b%c", arr[i]);
	i = i >= 3 ? 0 : (i + 1);
	delay();
	return;
}
