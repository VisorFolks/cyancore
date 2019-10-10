/*
 * ============================================================
 * File		: init.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <arc.h>
#include <platform.h>
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

extern void zero_reg(void);

void init() __attribute__((section(".text")));
void init()
{
	zero_reg();
	REG(SPL) = (uint8_t)(_stack_start & 0x00ff);
	REG(SPH) = (uint8_t)((_stack_start >> 8) & 0x00ff);
	bss_clear();
	arc();
	asm volatile ("rjmp	.");
}
