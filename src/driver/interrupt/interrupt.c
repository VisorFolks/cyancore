/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: interrupt.c
 * Description		: This file contains sources of interrupt controller
 *			  core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdint.h>
#include <stdbool.h>
#include <interrupt.h>
#include <arch.h>
#include <platform.h>
#include <driver/interrupt_controller.h>

status_t link_interrupt(int_module_t target, unsigned int id, void (*handler)(void))
{
	status_t ret = success;
	switch(target)
	{
		case arch:
			arch_register_interrupt_handler(id, handler);
			break;
#if LOCAL_INTERRUPT_DEVICE==1
		case local:
			local_register_interrupt_handler(id, handler);
			break;
#endif
#if PLAT_INTERRUPT_DEVICE==1
		case plat:
			ic_register_interrupt_handler(id, handler);
			break;
#endif
		default:
			ret = error_system_irq_link_fail;
			break;
	}
	return ret;
}

status_t unlink_interrupt(int_module_t target, unsigned int id)
{
	status_t ret = success;
	switch(target)
	{
		case arch:
			arch_register_interrupt_handler(id, &arch_panic_handler);
			break;
#if LOCAL_INTERRUPT_DEVICE==1
		case local:
			local_register_interrupt_handler(id, &plat_panic_handler);
			break;
#endif
#if PLAT_INTERRUPT_DEVICE==1
		case plat:
			ic_register_interrupt_handler(id, &plat_panic_handler);
			break;
#endif
		default:
			ret = error_system_irq_unlink_fail;
			break;
	}
	return ret;
}

status_t wait_till_irq(int_wait_t *var)
{
	var->lock = 1;
	do
		arch_wfi();
	while(var->lock == 1);
	return success;
}

status_t wait_release_on_irq(int_wait_t *var)
{
	var->lock = 0;
	return success;
}
