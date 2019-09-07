/*
 * ============================================================
 * File		: arch.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <avr/io.h>
#include <avr/interrupt.h>
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
	cli();
	return;
}

void arch_sei()
{
	sei();
	return;
}

