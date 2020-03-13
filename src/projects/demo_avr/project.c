#include <stdint.h>
#include <stdio.h>
#include <mmio.h>
#include <platform.h>

extern void platform_early_setup();

void project_setup()
{
	printf("Demo AVR: Running Blinky... [ ]\b");
	MMIO8(DDRB) = 0x20;
	return;
}

void delay()
{
	for(long i =0; i < 500000; i++)
		asm volatile("nop");
}

void project_loop()
{
	MMIO8(PORTB) |= 0x20;
	printf("\b|");
	delay();
	MMIO8(PORTB) &= ~(0x20);
	printf("\b/");
	delay();
	MMIO8(PORTB) |= 0x20;
	printf("\b-");
	delay();
	MMIO8(PORTB) &= ~(0x20);
	printf("\b\\");
	delay();
	return;
}
