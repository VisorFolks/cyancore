
#include <stdint.h>
#include <stdio.h>
#include <arch.h>
#include <mmio.h>

void exception_handler(uint32_t mcause, context_frame_t *frame)
{
	printf("Cause: %u -- EPC: %u", mcause, frame->mepc);
	frame->a0 = 1;
	frame->a1 = 2;
	frame->a2 = 3;
	frame->a3 = 0;
	asm("nop");
	frame->mepc += (MMIO8(frame->mepc) & 0x3) ? 4 : 2;
}
