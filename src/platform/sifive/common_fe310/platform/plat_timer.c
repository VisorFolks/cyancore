/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: plat_timer.c
 * Description		: This file contains sources for platform
 *			  timer
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <assert.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <machine_call.h>
#include <resource.h>
#include <hal/clint.h>
#include <terravisor/timer.h>

static void (*tmr_cb)(void);
static uint64_t ticks;
static module_t *tm;

static void plat_tmr_isr(void)
{
	arch_di_mtime();
	uint64_t t = clint_read_time();
	clint_config_tcmp(arch_core_index(), (t + ticks));
	arch_ei_mtime();

	if(tmr_cb != NULL)
		tmr_cb();
}

static void plat_timer_reg_cb(void *cb)
{
	arch_di_mtime();
	tmr_cb = cb;
	arch_ei_mtime();
}

static status_t plat_get_timer_prop(void)
{
	mret_t mres;
	swdev_t *sp;
	hw_devid_t devid;

	arch_machine_call(fetch_sp, sched_timer, 0, 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("%p - sp node could not be found!\n", sched_timer);
		return mres.status;
	}
	sp = (swdev_t *) mres.p;
	devid = sp->hwdev_id;

	arch_machine_call(fetch_dp, (devid & 0xff00), (devid & 0xff), 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("Timer Device %d not found!\n", devid);
		return mres.status;
	}
	tm = (module_t *) mres.p;
	return success;
}

static uint64_t plat_get_timer_ticks_msec(uint64_t freq)
{
	/* Compute ticks needed for 1 msec */
	return (uint64_t)(freq/1000);
}

static void plat_timer_set_period(unsigned int p)
{
	uint64_t nt;
	arch_di_mtime();
	ticks = plat_get_timer_ticks_msec(tm->clk);
	ticks *= p;
	nt = ticks + clint_read_time();
	clint_config_tcmp(arch_core_index(), nt);
	arch_ei_mtime();
}

static uint64_t plat_read_time(void)
{
	uint64_t stamp = clint_read_time();
	stamp *= 1000000U;
	return (uint64_t)(stamp / tm->clk);
}

static tvisor_timer_t plat_timer_port =
{
	.read_ticks = &clint_read_time,
	.read_time = &plat_read_time,
	.set_period = &plat_timer_set_period,
	.reg_cb = &plat_timer_reg_cb,
};

static status_t plat_timer_setup(void)
{
	status_t ret = success;
	irqs_t *irq;
	arch_di_mtime();

	/* This funcition fetches device properties */
	ret |= plat_get_timer_prop();

	irq = &tm->interrupt[0];

	/* Link timer isr handle */
	ret |= link_interrupt(irq->module, irq->id, &plat_tmr_isr);
	ret |= timer_attach_device(ret, &plat_timer_port);
	plat_timer_set_period(1);
	return ret;
}

static status_t plat_timer_exit(void)
{
	arch_di_mtime();
	tmr_cb = (void *) 0;
	ticks = 0;
	return timer_release_device();
}

INCLUDE_DRIVER(plat_timer, plat_timer_setup, plat_timer_exit, 0, 1, 1);
