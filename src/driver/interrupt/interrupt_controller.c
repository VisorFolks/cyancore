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
#include <arch.h>
#include <lock/lock.h>
#include <interrupt.h>
#include <driver/interrupt_controller.h>
#include <platform.h>

static ic_t *ic;
static bool ic_attached = false;
static lock_t ic_lock;

status_t ic_attach_device(status_t dev_status, ic_t *pic)
{
	status_t ret;
	lock_acquire(&ic_lock);
	ic_attached = false;
	ic = pic;

	if(ic != NULL)
	{
		ret = dev_status;
		ic_attached = (ret == success) ? true : false;
	}
	else
		ret = error_device_inval;
	lock_release(&ic_lock);
	return ret;
}

status_t ic_release_device()
{
	lock_acquire(&ic_lock);
	ic = NULL;
	ic_attached = false;
	lock_release(&ic_lock);
	return success;
}

unsigned int ic_get_irq()
{
	/* 0 is invalid irq id as 0 is usually
	 * associated to reset
	 */
	unsigned int ret = 0;
	lock_acquire(&ic_lock);
	if(ic_attached)
		ret = ic->get_irq();
	lock_release(&ic_lock);
	return ret;
}

status_t ic_set_priority_of_irq(unsigned int irq_id, unsigned int priority)
{
	status_t ret = error_driver_init_failed;
	lock_acquire(&ic_lock);
	if(ic_attached)
		ret = ic->set_priority(irq_id, priority);
	lock_release(&ic_lock);
	return ret;
}

unsigned int ic_get_priority_of_irq(unsigned int irq_id)
{
	unsigned int ret = 0;
	lock_acquire(&ic_lock);
	if(ic_attached)
		ret = ic->get_priority(irq_id);
	lock_release(&ic_lock);
	return ret;
}

status_t ic_en_irq(unsigned int irq_id)
{
	status_t ret = error_driver_init_failed;
	lock_acquire(&ic_lock);
	if(ic_attached)
		ret = ic->en_irq(irq_id);
	lock_release(&ic_lock);
	return ret;
}

status_t ic_dis_irq(unsigned int irq_id)
{
	status_t ret = error_driver_init_failed;
	lock_acquire(&ic_lock);
	if(ic_attached)
		ret = ic->dis_irq(irq_id);
	lock_release(&ic_lock);
	return ret;
}

unsigned int ic_get_affinity_of_core()
{
	unsigned int ret = 0;
	unsigned int core_id = arch_core_index();
	lock_acquire(&ic_lock);
	if(ic_attached)
		ret = ic->get_affinity(core_id);
	lock_release(&ic_lock);
	return ret;
}

status_t ic_set_affinity_of_core(unsigned int irq_id)
{
	status_t ret = error_driver_init_failed;
	unsigned int core_id = arch_core_index();
	lock_acquire(&ic_lock);
	if(ic_attached)
		ret = ic->set_affinity(core_id, irq_id);
	lock_release(&ic_lock);
	return ret;
}

void ic_register_interrupt_handler(unsigned int id, void (* handler)(void))
{
	lock_acquire(&ic_lock);
	if(ic_attached && (handler != NULL) && id)
		ic->register_handler(id, handler);
	lock_release(&ic_lock);
}
