#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <status.h>
#include <hal/gpio.h>
#include <arch.h>
#include <machine_call.h>
#include <terravisor/platform.h>
#include <terravisor/workers.h>
#include <platform.h>

/**
 * reset_syndrome - This varible is consists of reset syndrome in
 *		    bss section of memory. This variable is updated
 *		    in the platform_early_setup as this is the
 *		    earliest function which resets bss section.
 */
uint8_t reset_syndrome;

void platform_early_setup()
{
	status_t ret = success;

	/*
	 * Platform Early Setup is the first platform function that
	 * is called during bootstrap.
	 * Later after bss is cleared, "reset_syndrome" can be updated.
	 */
	ret |= platform_copy_data();
	ret |= platform_bss_clear();
	ret |= platform_clk_reset();

	reset_syndrome = MMIO8(MCUSR) & 0x1f;
	MMIO8(MCUSR) = 0;

	extern void write_wdtcsr(uint8_t);
	write_wdtcsr(0x00);

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_setup()
{
	status_t ret = success;
	ret |= platform_dp_setup();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_cpu_setup()
{
	status_t ret = success;
	ret |= platform_mcall_update(&machine_call);
	arch_ei();
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

