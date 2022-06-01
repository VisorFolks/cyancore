/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: timer.c
 * Description		: This file contains sources of terravisor timer
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdbool.h>
#include <status.h>
#include <syslog.h>
#include <arch.h>
#include <lock/lock.h>
#include <time.h>
#include <terravisor/timer.h>

static tvisor_timer_t *port[N_CORES];
static bool timer_attached[N_CORES] = {[0 ... N_CORES-1] = false};
static lock_t tlock[N_CORES];

status_t timer_attach_device(status_t dev_status, tvisor_timer_t *ptmr)
{
	status_t ret;
	size_t cpu_index = arch_core_index();
	lock_t *lock = &tlock[cpu_index];

	lock_acquire(lock);
	/* Link the driver instance */
	port[cpu_index] = ptmr;

	if(port[cpu_index] != NULL)
	{
		ret = dev_status;
		timer_attached[cpu_index] = true;
	}
	else
		ret = error_device_inval;
	lock_release(lock);
	return ret;
}

status_t timer_release_device()
{
	size_t cpu_index = arch_core_index();
	lock_t *lock = &tlock[cpu_index];
	lock_acquire(lock);
	port[cpu_index] = NULL;
	timer_attached[cpu_index] = false;
	lock_release(lock);
	return success;
}

status_t timer_link_callback(unsigned int p, void *cb)
{
	size_t cpu_index = arch_core_index();
	lock_t *lock = &tlock[cpu_index];
	tvisor_timer_t *ptr = port[cpu_index];
	if(!timer_attached[cpu_index])
		return error_driver_init_failed;
	lock_acquire(lock);
	ptr->set_period(p);
	ptr->reg_cb(cb);
	lock_release(lock);
	return success;
}

/* This function's prototype is located in libc */
status_t get_timestamp(uint64_t *t)
{
	size_t cpu_index = arch_core_index();
	lock_t *lock = &tlock[cpu_index];
	tvisor_timer_t *ptr = port[cpu_index];
	if(!timer_attached[cpu_index])
		return error_driver_init_failed;
	lock_acquire(lock);
	*t = ptr->read_time();
	lock_release(lock);
	return success;
}

/* This function's prototype is located in libc */
status_t get_timeticks(uint64_t *t)
{
	size_t cpu_index = arch_core_index();
	lock_t *lock = &tlock[cpu_index];
	tvisor_timer_t *ptr = port[cpu_index];
	if(!timer_attached[cpu_index])
		return error_driver_init_failed;
	lock_acquire(lock);
	*t = ptr->read_ticks();
	lock_release(lock);
	return success;
}
