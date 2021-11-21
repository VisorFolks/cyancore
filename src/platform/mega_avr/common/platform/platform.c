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
	 * is called during bootstrap. Also this is the very function
	 * where bss is cleared, so it is best that reset syndrome is
	 * obtained at the start and stored on stack.
	 * Later after bss is cleared, "reset_syndrome" can be updated.
	 */
	uint8_t mcusr = MMIO8(MCUSR);
	MMIO8(MCUSR) = 0x00;
	ret |= platform_copy_data();
	ret |= platform_bss_clear();
	
	/*
	 * Update the variable in global memory (bss) section
	 * 0x1f - mask is for extracting reset syndrome
	 */
	reset_syndrome = mcusr & 0x1f;
	ret |= platform_clk_reset();
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

