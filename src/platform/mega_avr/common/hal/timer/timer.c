/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: timer.c
 * Description		: This file contains sources for mega-avr
 *			  HAL timer/pwm apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <lock/lock.h>
#include <status.h>
#include <mmio.h>
#include <interrupt.h>
#include <platform.h>
#include <device.h>
#include <machine_call.h>
#include <arch.h>
#include "timer8.h"
#include "timer16.h"
#include "pwm8.h"
#include "pwm16.h.h"

lock_t timer_hal_lock;
/* Assuming max of 32 timers can be present on board */
uint32_t timer_used = 0x00;

/*internal function*/
status_t timer_alloc(size_t id)
{
	status_t ret = success;
	lock_acquire(&timer_hal_lock);
	if(timer_used & (1 << id))
		ret = error_busy;
	else
		timer_used |= (1 << id);
	lock_release(&timer_hal_lock);
	return ret;
}

/*internal function*/
status_t timer_release(size_t id)
{
	status_t ret = success;
	lock_acquire(&timer_hal_lock);
	timer_used &= ~(1 << id);
	lock_release(&timer_hal_lock);
	return ret;
}


status_t timer_setup(timer_port_t *port, timer_mode_t mode, timer_ps_t ps)
{
}

status_t timer_shutdown(timer_port_t *port)
{
}

status_t timer_read(timer_port_t *port, size_t *value)
{
}

status_t timer_pwm_set(timer_port_t *port, size_t value)
{
}

status_t timer_int_en(timer_port_t *port)
{
}

status_t timer_int_dis(timer_port_t *port)
{
}
