/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: interrupt_handler.c
 * Description		: This file consists of arch interrupt handler sources.
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com],
 *			  Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <status.h>
#include <string.h>
#include <assert.h>
#include <arch.h>
#include <assert.h>

static void (* exhandler[N_CORES][N_EXCEP])(void) = {{[0 ... N_EXCEP-1] = arch_panic_handler}};
static void (* irqhandler[N_CORES][N_IRQ])(void) = {{[0 ... N_IRQ-1] = arch_unhandled_irq}};
static context_frame_t *local_frame[N_CORES];

bool in_isr(void)
{
	unsigned int cpuid = arch_core_index();
	return (local_frame[cpuid] != NULL) ? true : false;
}

static void set_context_frame(context_frame_t *frame)
{
	unsigned int cpuid = arch_core_index();
	local_frame[cpuid] = frame;
	arch_dsb();
}

context_frame_t *get_context_frame()
{
	unsigned int cpuid = arch_core_index();
	return local_frame[cpuid];
}

void arch_register_interrupt_handler(unsigned int id, void (*handler)(void))
{
	unsigned int cpuid = arch_core_index();
	id--;
	exhandler[cpuid][id] = handler;
	arch_dsb();
}

void local_register_interrupt_handler(unsigned int id, void (*handler)(void))
{
	unsigned int cpuid = arch_core_index();
	id--;
	irqhandler[cpuid][id] = handler;
	arch_dsb();
}

void exception_handler(uint32_t id, context_frame_t *frame)
{
	unsigned int cpuid = arch_core_index();

	set_context_frame(frame);
	id--;

	if(id >= N_EXCEP)
		irqhandler[cpuid][id - N_EXCEP]();
	else
	{
		exhandler[cpuid][id]();
	}
	set_context_frame(NULL);
	arch_dsb();
}
