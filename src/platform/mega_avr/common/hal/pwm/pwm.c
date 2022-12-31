/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: pwm.c
 * Description		: This file contains sources for mega-avr
 *			  HAL pwm apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdbool.h>
#include <stdlib.h>
#include <syslog.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <hal/timer.h>
#include <hal/pwm.h>

static void pwm_to_timer(const pwm_port_t *p, timer_port_t *t)
{
	t->port_id = p->port_id;
	t->clk_id = p->clk_id;
	t->baddr = p->baddr;
	t->stride = p->stride;
	t->tmr_irq = p->pwm_irq->id;
	t->tmr_handler = p->pwm_handler;
}

status_t pwm_get_properties(pwm_port_t *port, sw_devid_t dev)
{
	mret_t mres;
	swdev_t *sp;
	module_t *dp;
	hw_devid_t devid;

	arch_machine_call(fetch_sp, dev, 0, 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("%p - sp node could not be found!\n", dev);
		return mres.status;
	}

	sp = (swdev_t *) mres.p;
	devid = sp->hwdev_id;
	port->pmux = sp->pmux;

	arch_machine_call(fetch_dp, (devid & 0xff00), (devid & 0xf0), 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("PWM (timer) Device %d not found!\n", devid);
		return mres.status;
	}
	dp = (module_t *) mres.p;
	port->port_id = dp->id;
	port->clk_id = dp->clk_id;
	port->baddr = dp->baddr;
	port-> stride = dp->stride;
	port->pwm_irq = &dp->interrupt[0];
	return success;
}

status_t pwm_setup(const pwm_port_t *port, unsigned int mode)
{
	status_t ret;
	/* Allocate timer port */
	timer_port_t *tport = (timer_port_t *)malloc(sizeof(timer_port_t));
	RET_ON_FAIL(tport, error_memory_low);

	/* Convert pwm to timer */
	pwm_to_timer(port, tport);

	/* Configure timer for PWM mode */
	ret = timer_setup(tport, mode, port->prescale);

	/* Release the memory */
	free(tport);

	return ret;
}

status_t pwm_set(const pwm_port_t *port, size_t value, bool invert)
{
	status_t ret;
	/* Allocate timer port */
	timer_port_t *tport = (timer_port_t *)malloc(sizeof(timer_port_t));
	RET_ON_FAIL(tport, error_memory_low);

	/* Convert pwm to timer */
	pwm_to_timer(port, tport);

	/* Set PWM value */
	ret = timer_pwm_set(tport, invert, value);

	/* Release the memory */
	free(tport);

	return ret;
}
