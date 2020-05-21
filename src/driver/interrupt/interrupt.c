#include <status.h>
#include <stdint.h>
#include <interrupt.h>
#include <arch.h>
#if LOCAL_INTERRUPT_DEVICE==1
#include <hal/local_interrupt.h>
#endif
#if PLAT_INTERRUPT_DEVICE==1
#include <hal/plat_interrupt.h>
#endif

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
			plat_register_interrupt_handler(id, handler);
			break;
#endif
		default:
			ret = error_inval_arg;
			break;
	}
	return ret;
}

void plat_panic_handler();

status_t unlink_interrupt(int_module_t target, unsigned int id)
{
	status_t ret = success;
	switch(target)
	{
		case arch:
			arch_register_interrupt_handler(id, &plat_panic_handler);
			break;
#if LOCAL_INTERRUPT_DEVICE==1
		case local:
			local_register_interrupt_handler(id, &plat_panic_handler);
			break;
#endif
#if PLAT_INTERRUPT_DEVICE==1
		case plat:
			plat_register_interrupt_handler(id, &plat_panic_handler);
			break;
#endif
		default:
			ret = error_inval_arg;
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
