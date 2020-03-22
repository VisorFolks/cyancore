#include <stdbool.h>
#include <stdint.h>
#include <status.h>
#include <driver/console.h>
#include <hal/gpio.h>

void project_setup()
{
	gpio_pin_config(0, 5, out);
	gpio_pin_clear(0, 5);
	console_puts("Type Something! \r\n");
	return;
}

/*
void delay()
{
	for(long i = 0; i < 500000; i++)
		asm volatile("nop");
}
*/

void console_loop_back()
{
	char c;
	console_getc(&c);
	console_putc(c);
}

void project_loop()
{
	gpio_pin_toggle(0, 5);
//	delay();
	console_loop_back();
	return;
}
