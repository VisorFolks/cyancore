/*
 * ============================================================
 * File		: init.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <arc.h>
#include <avr/io.h>
#include <stdint.h>

extern uint16_t STACK_START, * BSS_START, * BSS_END;

void bss_clear()
{
	uint16_t *ptr;
	for(ptr = BSS_START; ptr <= BSS_END; ptr++)
	{
		*(volatile uint16_t *)(ptr)=0x00;
	}
}

void init()
{
	SP = STACK_START;
	bss_clear();
	arc();
	return;
}
