/*
 * ============================================================
 * File		: arch.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <avr/io.h>
#include <arch.h>

void arch_init()
{
	arch_cli();
	return;
}

void arch_idle()
{
	asm volatile("SLEEP");
	return;
}

void arch_cli()
{
	asm volatile("cli");
	return;
}

void arch_sei()
{
	asm volatile("sei");
	return;
}

