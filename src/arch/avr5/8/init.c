/*
 * ============================================================
 * File		: init.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

#include <stdint.h>
#include <stdlib.h>
#include <mmio.h>
#include <plat_arch.h>
#include <arc.h>

extern uint16_t _stack_start, _bss_start, _bss_end;

void bss_clear()
{
	uint16_t ptr;
	for(ptr = (uint16_t)&_bss_start; ptr < (uint16_t)&_bss_end; ptr++)
	{
		MMIO16(ptr) = 0x00;
	}
}

extern void zero_reg(void);
extern void copy_data(void);

void init()
{
	uint16_t *stack_location = &_stack_start;
	MMIO8(SPL) = (uint8_t)((uint16_t)stack_location & 0x00ff);
	MMIO8(SPH) = (uint8_t)(((uint16_t)stack_location >> 8) & 0x00ff);
	zero_reg();
	copy_data();
	bss_clear();
	arc();
	exit(EXIT_FAILURE);
}
