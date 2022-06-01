/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: platform_timer.c
 * Description		: This file contains sources for platform timer apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <string.h>
#include <driver.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <hal/timer.h>
#include <terravisor/timer.h>

#define PS	4
#define PSVALUE	256

static void (*tmr_cb)(void);
static timer_port_t tport;
static uint64_t ticks;
static uint64_t cntr;
static module_t *tm;

static void plat_tmr_isr(void)
{
	cntr += ticks;
	if(tmr_cb != NULL)
		tmr_cb();
}

static void plat_timer_reg_cb(void *cb)
{
	tmr_cb = cb;
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
	uint64_t nt = freq / (2 * PSVALUE);
	nt /= 1000;
	return nt;
}

static void plat_timer_set_period(unsigned int p)
{
	uint64_t nt = plat_get_timer_ticks_msec(tm->clk);
	ticks = (nt * p) - 1;
	tport.value = ticks;
	timer_setup(&tport, 2, PS);
}

static uint64_t plat_read_ticks(void)
{
	return cntr;
}

static uint64_t plat_read_time(void)
{
	uint64_t stamp = cntr;
	stamp <<= 10U;
	stamp /= ((tport.value + 1) << 1);
	return stamp;
}

static tvisor_timer_t plat_timer_port =
{
	.read_ticks = &plat_read_ticks,
	.read_time = &plat_read_time,
	.set_period = &plat_timer_set_period,
	.reg_cb = &plat_timer_reg_cb,
};

static status_t plat_timer_setup()
{
	status_t ret = success;
	ret |= plat_get_timer_prop();

	tport.port_id = tm->id;
	tport.clk_id = tm->clk_id;
	tport.baddr = tm->baddr;
	tport.stride = tm->stride;
	tport.tmr_irq = tm->interrupt[0].id;
	tport.tmr_handler = plat_tmr_isr;

	ret |= timer_setup(&tport, 2, PS);
	plat_timer_set_period(1);
	ret |= timer_attach_device(ret, &plat_timer_port);

	return ret;
}

static status_t plat_timer_exit(void)
{
	status_t ret = timer_shutdown(&tport);
	ticks = 0;
	tmr_cb = (void *) 0;
	memset(&tport, 0, sizeof(timer_port_t));
	ret |= timer_release_device();
	return ret;
}

INCLUDE_DRIVER(plat_timer, plat_timer_setup, plat_timer_exit, 0, 1, 1);
