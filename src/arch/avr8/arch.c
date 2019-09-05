/*
 * ============================================================
 * File		: arch.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <platform.h>
#include <arch.h>

void arch_init()
{
	cli();
	return;
}

void arch_idle()
{
	SLEEP;
	return;
}

