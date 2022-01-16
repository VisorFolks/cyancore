/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: plic.c
 * Description		: This file contains sources of PLIC core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <arch.h>
#include <machine_call.h>
#include <resource.h>
#include <driver.h>
#include <mmio.h>

#ifndef PLIC_VERSION
#define PLIC_VERSION	0x0100		// 01.00
#endif

#include "plic_private.h"

static plic_port_t port;

static status_t plic_setup()
{
	mret_t mres;
	module_t *dp;

	arch_machine_call(fetch_dp, plic, 0, 0, &mres);

	if(mres.status != success)
		return mres.status;
	dp = (module_t *)mres.p;
	port.baddr = dp->baddr;
	port.stride = dp->stride;
	port.port_id = plic;
	printf("< ! > PLIC @ 0x%x found.\n", port.baddr);
	return success;
}

static uint32_t plic_get_priority(uint32_t irq_id)
{
	assert(port.baddr);
	return MMIO32(port.baddr + PLIC_IPRIORITY_OFFSET(irq_id));
}

static void plic_set_priority(uint32_t irq_id, uint32_t priority)
{
	assert(port.baddr);
	MMIO32(port.baddr + PLIC_IPRIORITY_OFFSET(irq_id)) = priority;
	arch_dmb();
	return;
}

static uint32_t plic_get_threshold(uint32_t core_id)
{
	assert(port.baddr);
	return MMIO32(port.baddr + PLIC_ITHRESHOLD_OFFSET(core_id));
}

static void plic_set_threshold(uint32_t core_id, uint32_t threshold)
{
	assert(port.baddr);
	MMIO32(port.baddr + PLIC_ITHRESHOLD_OFFSET(core_id)) = threshold;
	arch_dmb();
	return;
}

static uint32_t plic_get_interrupt()
{
	uint32_t core_id;
	assert(port.baddr);
	core_id = arch_core_index();
	return MMIO32(port.baddr + PLIC_ICLAIM_OFFSET(core_id));
}

static void plic_clr_interrupt(uint32_t irq_id)
{
	uint32_t core_id;
	assert(port.baddr);
	core_id = arch_core_index();
	MMIO32(port.baddr + PLIC_ICLAIM_OFFSET(core_id)) = irq_id;
	return;
}

static status_t plic_int_en()
{
	return success;
}

static status_t plic_int_dis()
{
	return success;
}

static bool plic_get_pending(uint32_t irq_id)
{
	uint32_t pending;
	assert(port.baddr);
	pending = MMIO32(port.baddr + PLIC_IPENDING_OFFSET(irq_id));
	return (pending & (1 << (irq_id % 32))) ? true : false;
}
