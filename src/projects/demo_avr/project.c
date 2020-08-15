#include <stdio.h>
#include <status.h>
#include <terravisor/bootloader.h>
#include <driver.h>
#include <hal/gpio.h>

extern char cyancore_insignia[];
gpio_port_t led_13;

void launch()
{
	bootloader();
	driver_setup("earlycon");
	printf("%s", cyancore_insignia);
	gpio_setup(&led_13, 0, 5);
	gpio_pin_mode(&led_13, out);
	gpio_pin_clear(&led_13);
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

void encore()
{
	static int i = 0;
	gpio_pin_toggle(&led_13);
	printf("%c]", progress[i++]);
	i = i > 3 ? 0 : i;
	delay(500000);
	printf("\b\b");
	return;
}
