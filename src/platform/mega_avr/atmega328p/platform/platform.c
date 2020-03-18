#include <stdint.h>
#include <stdbool.h>
#include <status.h>
#include <platform.h>
#include <hal/gpio.h>
#include <mega_avr_platform.h>

void platform_early_setup()
{
	platform_clk_reset();
	platform_dp_setup();
	return;
}

void platform_setup()
{
	gpio_setup();
	return;
}

void platform_cpu_setup()
{
	return;
}

