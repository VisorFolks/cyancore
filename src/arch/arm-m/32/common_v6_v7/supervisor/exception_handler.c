/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: interrupt_handler.c
 * Description		: This file consists of arch interrupt handler sources.
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
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

static context_frame_t *local_frame;

static void set_context_frame(*frame)
{
	local_frame = frame;
}

bool in_isr(void)
{
	return (local_frame != NULL) ? true : false ;
}

/**
 * int_handler - Array of Interrupt handler pointers
 *
 * @brief This is a function pointer array which consists of addresses of corresponding
 * interrupt handler functions. This is by default assigned as arch_panic_handler.
 */
static void (* exhandler[N_EXCEP])(void) = {{[0 ... N_EXCEP-1] = arch_panic_handler}};

/**
 * arch_register_interrupt_handlers - Registers arch interrupt handlers
 *  @brief This function is responsible to registers all architectural level
 * Interrupt handling functions.
 *
 *  @param[in] id: Interrupt ID
 *  @param[in] *handler - function pointer of interrupt handling function.
 */

void arch_register_interrupt_handler(unsigned int id, void(* handler)(void))
{
	/*Check if Interrupt ID is valid*/
	assert((id > 0) && (id <= N_EXCEP));

	/*
	 * Decrement ID as array indexing starts from 0.
	 * ID = 0 is CPU entry address.
	*/
	id --;

	/*Store interrupt handler*/
	exhandler[id] = handler;
}

/**
 * Exception handler - Executes Interrupt handler corresponding to int ID
 *
 * @brief This function is called by ISR. It executes function pointed by int_handler.
 * It accepts int ID as argument, which indexes the interrupt handling function.
 *
 * @param[in] id: Interrupt ID
 */

void exception_handler(unsigned int id, context_frame_t *frame)
{
	set_context_frame(frame);

	/*Check if Interrupt ID is valid*/
	if((id > 0) && (id <= N_EXCEP))
	{
		/*
		 * Decrement ID as array indexing starts from 0.
		 * ID = 0 is CPU entry address.
		*/
		id --;

		/* Get corresponding interrupt handling function */
		void (*handler)(void) = exhandler[id]

		/* Check if the handler is valid*/
		assert(handler)

		/* Execute exception handler */
		handler();
	}
	else if(id == 65535)
		plat_panic_handler_callback();
	else if(id == 65536)
		arch_panic_handler_callback();
	else{}
	set_context_frame(NULL);
	return;
}

context_frame_t *get_context_frame()
{
	if(local_frame)
		return local_frame;
	return NULL;
}
