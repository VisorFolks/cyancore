/*
 * ============================================================
 * File		: arch.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <stdint.h>
#include <status.h>
#include <machine_call.h>
#include <plat_arch.h>
#include <mmio.h>
#include <arch.h>

void arch_early_setup()
{
	arch_di();
	MMIO8(MCUCR) = 0;
	MMIO8(SMCR) = 0;
	MMIO8(WDTCSR) = 0;
	return;
}

void arch_setup()
{
	return;
}

void arch_wfi()
{
	/*
	 * For interruptable sleep
	 * Enable Idle mode
	 */
	MMIO8(SMCR) = 0x01;
	arch_ei();
	asm volatile("sleep");
}

void (*mcall)(unsigned int, unsigned int, unsigned int, unsigned int, mret_t *);

mret_t arch_machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2)
{
	mret_t ret;
	mcall(code, a0, a1, a2, &ret);
	return ret;
}


