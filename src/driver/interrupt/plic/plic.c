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
#include <interrupt.h>
#include <resource.h>
#include <driver.h>
#include <mmio.h>
#include <platform.h>
#include <driver/interrupt_controller.h>

#ifndef PLIC_VERSION
#define PLIC_VERSION	0x0100		// 01.00
#endif

#include "plic_private.h"

static plic_port_t port;

static status_t plic_setup()
{
	mret_t mres;
	const module_t *dp;

	arch_machine_call(fetch_dp, plic, 0, 0, &mres);

	if(mres.status != success)
		return mres.status;
	dp = (module_t *)mres.p;
	port.baddr = dp->baddr;
	port.stride = dp->stride;
	port.port_id = plic;
	port.irq = dp->interrupt_id[0];
	printf("< ! > PLIC @ 0x%x found.\n", (unsigned int)port.baddr);
	return success;
}

static uint32_t plic_get_priority(uint32_t irq_id)
{
	assert(port.baddr);
	return MMIO32(port.baddr + PLIC_IPRIORITY_OFFSET(irq_id));
}

static status_t plic_set_priority(uint32_t irq_id, uint32_t priority)
{
	assert(port.baddr);
	MMIO32(port.baddr + PLIC_IPRIORITY_OFFSET(irq_id)) = priority;
	arch_dmb();
	return success;
}

static uint32_t plic_get_threshold(uint32_t core_id)
{
	assert(port.baddr);
	return MMIO32(port.baddr + PLIC_ITHRESHOLD_OFFSET(core_id));
}

static status_t plic_set_threshold(uint32_t core_id, uint32_t threshold)
{
	assert(port.baddr);
	MMIO32(port.baddr + PLIC_ITHRESHOLD_OFFSET(core_id)) = threshold;
	arch_dmb();
	return success;
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
	arch_dmb();
	return;
}

static status_t plic_int_en(uint32_t irq_id)
{
	uint32_t core_id, irq_offset, irq_shift;
	assert(port.baddr);
	core_id = arch_core_index();
	irq_offset = irq_id / 32;
	irq_shift = irq_id % 32;
	MMIO32(port.baddr + PLIC_IENABLE_OFFSET(core_id, irq_offset)) |= (1 << irq_shift);
	arch_dmb();
	return success;
}

static status_t plic_int_dis(uint32_t irq_id)
{
	uint32_t core_id, irq_offset, irq_shift;
	assert(port.baddr);
	core_id = arch_core_index();
	irq_offset = irq_id / 32;
	irq_shift = irq_id % 32;
	MMIO32(port.baddr + PLIC_IENABLE_OFFSET(core_id, irq_offset)) &= ~(1 << irq_shift);
	arch_dmb();
	return success;
}

void plic_irqhandler()
{
	uint32_t irq = plic_get_interrupt();
	plic_irq_handler[irq]();
	plic_clr_interrupt(irq);
}

static bool plic_get_pending(uint32_t irq_id)
{
	uint32_t pending;
	assert(port.baddr);
	pending = MMIO32(port.baddr + PLIC_IPENDING_OFFSET(irq_id));
	return (pending & (1 << (irq_id % 32))) ? true : false;
}

void plic_register_irq_handler(uint32_t id, void (* handler)(void))
{
	assert(id);
	assert(handler);
	plic_irq_handler[id] = handler;
	arch_dsb();
}

static ic_t plic_port =
{
	.setup			= &plic_setup,
	.get_priority		= &plic_get_priority,
	.set_priority		= &plic_set_priority,
	.get_affinity		= &plic_get_threshold,
	.set_affinity		= &plic_set_threshold,
	.get_irq		= &plic_get_interrupt,
	.en_irq			= &plic_int_en,
	.dis_irq		= &plic_int_dis,
	.pending		= &plic_get_pending,
	.register_handler	= &plic_register_irq_handler,
};

static status_t plic_driver_setup()
{
	status_t ret;
	ret = ic_attach_device(&plic_port);
	plic_clr_interrupt(plic_get_interrupt());
	return ret;
}

static status_t plic_driver_setup_pcpu()
{
	status_t ret;
	ret = link_interrupt(local, port.irq, &plic_irqhandler);
	arch_ei();
	return ret;
}

static status_t plic_driver_exit()
{
	return ic_release_device();
}

static status_t plic_driver_exit_pcpu()
{
	arch_di();
	return unlink_interrupt(local, port.irq);
}

INCLUDE_DRIVER(riscv_plic, plic_driver_setup, plic_driver_exit, 0, 0, 0);
INCLUDE_DRIVER(riscv_plic_pcpu, plic_driver_setup_pcpu, plic_driver_exit_pcpu, 1, 1, 1);