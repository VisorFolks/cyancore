#include <stdio.h>
#include <status.h>
#include <insignia.h>
#include <terravisor/platform.h>
#include <terravisor/bootstrap.h>
#include <driver.h>
#include <hal/gpio.h>

gpio_port_t led_13;

void plug()
{
	bootstrap();
	driver_setup("earlycon");
	printf("Reset Status: %d\n", platform_get_reset_syndrome());
	cyancore_insignia();
	gpio_pin_alloc(&led_13, 0, 5);
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

void play()
{
	static int i = 0;
	gpio_pin_toggle(&led_13);
	printf("%c]", progress[i++]);
	i = i > 3 ? 0 : i;
	delay(500000);
	printf("\b\b");
	return;
}
