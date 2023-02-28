/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: arch_verctors.c
 * Description		: This file consists of array of vector table
 *			  specific to arm-m proile.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdint.h>

extern void _stack_start();
extern void init(void);
#define proto_irq_func(x)	extern void int_##x(void)
proto_irq_func(1);
proto_irq_func(2);
proto_irq_func(3);
proto_irq_func(4);
proto_irq_func(5);
proto_irq_func(6);
proto_irq_func(7);
proto_irq_func(8);
proto_irq_func(9);
proto_irq_func(10);
proto_irq_func(11);
proto_irq_func(12);
proto_irq_func(13);
proto_irq_func(14);

/**
 * arch_vectors - Interrupt vector table defined as per arm-m spec
 * @brief This is the array of interrupt/exception vectors defined
 * by arm-v6/v7 spec. This is generic implementation and upon any
 * irq/excep, these function will call common handler which will
 * deref based on irq id and call respective handler.
 */

void (*arch_vectors[N_IRQ+1])(void) _SECTION(".archvectors") =
{
	&_stack_start,		// Stack start value has higher address of stack
				// with as assumption that stack grows towards
				// lower address

	&init,			// CPU entry address
	&int_1,			// IRQ 1 -> NMI
	&int_2,			// IRQ 2 -> HardFault
	&int_3,			// IRQ 3 -> M-Manage
	&int_4,			// IRQ 4 -> BusFault
	&int_5,			// IRQ 5 -> UsageFault
	&int_6,			// IRQ 6 -> N/A
	&int_7,			// IRQ 7 -> DBG info
	&int_8,			// IRQ 8 -> Debugger handler
	&int_9,			// IRQ 9 -> N/A
	&int_10,		// IRQ 10 -> SVC
	&int_11,		// IRQ 11 -> Debug Monitor
	&int_12,		// IRQ 12 -> N/A 
	&int_13,		// IRQ 13 -> PendSV
	&int_14,		// IRQ 14 -> SysTick
};
