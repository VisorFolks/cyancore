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
#include <terravisor/bootstrap.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <platform.h>
#include <mmio.h>
#include <hal/clint.h>
#include <hal/gpio.h>

static unsigned long long t;

static void test()
{
	arch_di_mtime();
	t = clint_read_time();
	clint_config_tcmp(0, (t + 12500));
	arch_ei_mtime();
}

static gpio_port_t gled, bled, rled;

void plug()
{
	mret_t mres;
	bootstrap();
	driver_setup_all();
	platform_print_cpu_info();
	arch_machine_call(0, 100, 200, 300, &mres);
	link_interrupt(local, 7, test);

	gpio_pin_alloc(&gled, 0, 19);
	gpio_pin_alloc(&bled, 0, 21);
	gpio_pin_alloc(&rled, 0, 22);
	gpio_pin_mode(&gled, out);
	gpio_pin_mode(&bled, out);
	gpio_pin_mode(&rled, out);
	gpio_pin_set(&gled);
	gpio_pin_set(&bled);
	gpio_pin_set(&rled);

	t = clint_read_time();
	clint_config_tcmp(0, (t + 12500));
	arch_ei_mtime();
}

void play()
{
	printf("Time: %lu\n", (unsigned long)t);
	gpio_pin_toggle(&gled);
	gpio_pin_toggle(&bled);
	gpio_pin_toggle(&rled);
	arch_wfi();
}
