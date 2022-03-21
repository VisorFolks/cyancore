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
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <platform.h>
#include <mmio.h>
#include <hal/clint.h>
#include <hal/gpio.h>

static unsigned long long t;
static unsigned int ticks = 16384;

static void test()
{
	arch_di_mtime();
	t = clint_read_time();
	clint_config_tcmp(0, (t + ticks));
	arch_ei_mtime();
}

static gpio_port_t gled, bled;

void plug()
{
	bootstrap();
	driver_setup_all();
	platform_print_cpu_info();
	link_interrupt(int_local, 7, test);

	gpio_pin_alloc(&gled, PORTA, 19);
	gpio_pin_alloc(&bled, PORTA, 21);
	gpio_pin_mode(&gled, out);
	gpio_pin_mode(&bled, out);
	gpio_pin_set(&gled);
	gpio_pin_set(&bled);

	t = clint_read_time();
	clint_config_tcmp(0, (t + ticks));
	arch_ei_mtime();
	printf("Demo Program!\n");
	printf("< ! > Running Blinky ... [");
	return;
}

char progress[] = "-\\|/";

void play()
{
	static unsigned int i = 0;
	printf("%c]", progress[(i++) % strlen(progress)]);
	gpio_pin_toggle(&gled);
	gpio_pin_toggle(&bled);
	arch_wfi();
	printf("\b\b");
	return;
}
