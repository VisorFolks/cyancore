/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: interrupt_handler.c
 * Description		: This file consists of arch interrupt handler sources.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stddef.h>
#include <assert.h>
#include <arch.h>

/**
 * int_handler - Array of interrupt handler pointers
 *
 * This is the function pointer array which consists of addresses of
 * corresponding interrupt handler functions. This is by  default
 * assigned as arch_panic_handler.
 */
static void (* int_handler[N_IRQ])(void) = {[0 ... N_IRQ-1] = arch_panic_handler};

/**
 * arch_register_interrupt_handler - Registers arch interrupt handlers
 *
 * This function is responsible to register all the architecture level
 * interrupt handling functions.
 *
 * @id - Interrupt ID
 * @*handler - function pointer of the interrupt handling function
 */
void arch_register_interrupt_handler(unsigned int id, void (* handler)(void))
{
	/* Check for valid interrupt ID */
	assert((id > 0) && (id <= N_IRQ));

	/*
	 * Decrement ID as array indexing starts from 0.
	 * ID = 0 is reset vector. Hence, int_handler[0]
	 * points to handler of interrupt ID = 1.
	 */
	id --;

	/* Store interrupt handler */
	int_handler[id] = handler;
}

/**
 * interrupt_handler - Executes int ID correspoding interrupt handler
 *
 * This function is called by ISR. It executes function pointed by the
 * int_handler. It accepts interrupt ID as argument, which indexes the
 * interrupt handling function.
 *
 * @id - Interrupt ID
 */
void interrupt_handler(unsigned char id)
{
	void (*handler)(void);

	/* Check for valid interrupt ID */
	assert((id > 0) && (id <= N_IRQ));

	/*
	 * Decrement ID as array indexing starts from 0.
	 * ID = 0 is reset vector. Hence, int_handler[0]
	 * points to handler of interrupt ID = 1.
	 */
	id --;

	/* Get corresponding interrupt handling function */
	handler = int_handler[id];

	/* Check if the interrupt handler is valid */
	assert(handler);

	/* Execute interrupt handler */
	handler();
	return;
}

