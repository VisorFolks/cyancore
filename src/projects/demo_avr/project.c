#include <stdbool.h>
#include <stdint.h>
#include <status.h>
#include <hal/gpio.h>

void project_setup()
{
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
	delay();
	return;
}
