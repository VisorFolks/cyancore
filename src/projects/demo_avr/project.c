#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
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

void project_loop()
{
	char c = getchar();
	printf("You Entered: %c\n", c);
	gpio_pin_toggle(0, 5);
	return;
}
