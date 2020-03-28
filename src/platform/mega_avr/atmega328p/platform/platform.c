#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <status.h>
#include <hal/gpio.h>
#include <arch.h>
#include <driver.h>
#include <mega_avr_platform.h>

extern uint16_t _bss_start, _bss_size;

void platform_early_setup()
{
	status_t ret = success;
	// BSS Init
	memset(&_bss_start, 0, (size_t)&_bss_size);
	ret |= platform_clk_reset();
	ret |= platform_dp_setup();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_setup()
{
	status_t ret = success;
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

