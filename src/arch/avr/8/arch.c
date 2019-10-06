/*
 * ============================================================
 * File		: arch.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <arch.h>

void arch_setup()
{
	arch_di();
	return;
}

void arch_idle()
{
	asm volatile("SLEEP");
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

