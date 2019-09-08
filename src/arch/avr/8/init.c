/*
 * ============================================================
 * File		: init.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <arc.h>
#include <avr/io.h>
#include <stdint.h>

extern uint16_t _stack_start, * _bss_start, * _bss_end;

void bss_clear()
{
	uint16_t *ptr;
	for(ptr = _bss_start; ptr <= _bss_end; ptr++)
	{
		*(volatile uint16_t *)(ptr)=0x00;
	}
}


void init() __attribute__((section(".text")));
void init()
{
	SP = _stack_start;
	bss_clear();
	arc();
	asm volatile("jmp	.");
}
