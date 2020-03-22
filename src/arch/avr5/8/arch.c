/*
 * ============================================================
 * File		: arch.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <stdint.h>
#include <status.h>
#include <plat_arch.h>
#include <mmio.h>
#include <machine_call.h>
#include <arch.h>

void arch_early_setup()
{
	return;
}

void arch_setup()
{
	arch_di();
	return;
}

void arch_wfi()
{
	MMIO8(SMCR) = 0x00;
	arch_ei();
	asm volatile("sleep");
	return;
}

void arch_di()
{
	asm volatile("cli");
	return;
}

void arch_ei()
{
	asm volatile("sei");
	return;
}

void machine_call(unsigned int, unsigned int, unsigned int, unsigned int, mret_t *);

mret_t arch_machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2)
{
	mret_t ret;
	machine_call(code, a0, a1, a2, &ret);
	return ret;
}
