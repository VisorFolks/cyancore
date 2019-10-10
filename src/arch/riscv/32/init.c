#include <arc.h>
#include <platform.h>
#include <stdint.h>

extern uint32_t * _bss_start, * _bss_end;

void bss_clear()
{
	uint32_t * ptr;
	for(ptr = _bss_start; ptr <= _bss_end; ptr++)
	{
		*(volatile uint32_t *)(ptr) = 0x00;
	}
	return;
}

extern void zero_reg(void);

void init() __attribute__((section(".text")));
void init()
{
	zero_reg();
	asm volatile ("la	sp, _stack_start");
	asm volatile ("la	gp, _gptr");
	bss_clear();
	arc();
	asm volatile ("j	.");
}
