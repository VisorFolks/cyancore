/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: interrupt_controller.c
 * Description		: This file contains sources of interrupt controller
 *			  core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <interrupt.h>
#include <driver/interrupt_controller.h>
#include <arch.h>
#include <platform.h>

static ic_t *ic;
static bool ic_attached = false;

status_t ic_attach_device(ic_t *pic)
{
	status_t ret;
	ic_attached = false;
	ic = pic;

	if(ic != NULL)
	{
		ret = ic->setup();
		ic_attached = (ret == success) ? true : false;
	}
	else
		ret = error_device_inval;
	return ret;
}

status_t ic_release_device()
{
	ic = NULL;
	ic_attached = false;
	return success;
}

unsigned int ic_get_irq()
{
	if(ic_attached)
		return ic->get_irq();
	/* 0 is invalid irq id as 0 is usually
	 * associated to reset
	 */
	return 0;
}

status_t ic_set_priority_of_irq(unsigned int irq_id, unsigned int priority)
{
	if(ic_attached)
		return ic->set_priority(irq_id, priority);
	return error_driver_init_failed;
}

unsigned int ic_get_priority_of_irq(unsigned int irq_id)
{
	if(ic_attached)
		return ic->get_priority(irq_id);
	return 0;
}

status_t ic_en_irq(unsigned int irq_id)
{
	if(ic_attached)
		return ic->en_irq(irq_id);
	return error_driver_init_failed;
}

status_t ic_dis_irq(unsigned int irq_id)
{
	if(ic_attached)
		return ic->dis_irq(irq_id);
	return error_driver_init_failed;
}

unsigned int ic_get_affinity_of_core()
{
	unsigned int core_id = arch_core_index();
	if(ic_attached)
		return ic->get_affinity(core_id);
	return 0;
}

status_t ic_set_affinity_of_core(unsigned int irq_id)
{
	unsigned int core_id = arch_core_index();
	if(ic_attached)
		return ic->set_affinity(core_id, irq_id);
	return error_driver_init_failed;
}

void ic_register_interrupt_handler(unsigned int id, void (* handler)(void))
{
	if(ic_attached && (handler != NULL) && id)
		return ic->register_handler(id, handler);
}
