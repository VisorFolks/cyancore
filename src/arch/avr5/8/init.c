/*
 * ============================================================
 * File		: init.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <arc.h>
#include <platform.h>
#include <stdint.h>
#include <stdlib.h>

extern uint16_t _stack_start, _bss_start, _bss_end;

void bss_clear()
{
	uint16_t ptr;
	for(ptr = (uint16_t)&_bss_start; ptr < (uint16_t)&_bss_end; ptr++)
	{
		*(volatile uint16_t *)(ptr)=0x00;
	}
}

extern void zero_reg(void);
extern void copy_data(void);

void init()
{
	uint16_t *stack_location = &_stack_start;
	REG(SPL) = (uint8_t)((uint16_t)stack_location & 0x00ff);
	REG(SPH) = (uint8_t)(((uint16_t)stack_location >> 8) & 0x00ff);
	zero_reg();
	copy_data();
	bss_clear();
	arc();
	exit(EXIT_FAILURE);
}
