/*
 * ============================================================
 * File		: arch.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <stdint.h>
#include <status.h>
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

void arch_idle()
{
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

void machine_call(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int *, status_t *);

unsigned int arch_machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2, status_t *status)
{
	unsigned int ret;
	machine_call(code, a0, a1, a2, &ret, status);
	return ret;
}
