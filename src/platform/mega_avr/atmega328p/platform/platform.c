#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <status.h>
#include <hal/gpio.h>
#include <arch.h>
#include <driver.h>
#include <mega_avr_platform.h>

void platform_early_setup()
{
	status_t ret;
	ret = success;
	ret |= platform_copy_data();
	ret |= platform_bss_clear();
	ret |= platform_clk_reset();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_setup()
{
	status_t ret = success;
	ret |= platform_dp_setup();
	ret |= driver_setup("earlycon");
	ret |= gpio_setup();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_cpu_setup()
{
	status_t ret = success;
	arch_ei();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

