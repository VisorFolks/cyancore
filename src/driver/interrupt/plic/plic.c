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
#include <syslog.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <arch.h>
#include <visor_call.h>
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

static plic_port_t *port;

static status_t plic_setup()
{
	vret_t vres;
	const module_t *dp;

	arch_visor_call(fetch_dp, plic, 0, 0, &vres);

	if(vres.status != success)
		return vres.status;
	dp = (module_t *)vres.p;
	port = (plic_port_t *)malloc(sizeof(plic_port_t));
	if(!port)
		return error_memory_low;
	port->baddr = dp->baddr;
	port->stride = dp->stride;
	port->port_id = plic;
	port->irq = &dp->interrupt[0];
	syslog(info, "PLIC @ 0x%x found.\n", (unsigned int)port->baddr);
	return success;
}

static uint32_t plic_get_priority(uint32_t irq_id)
{
	assert(port->baddr);
	return MMIO32(port->baddr + PLIC_IPRIORITY_OFFSET(irq_id));
}

static status_t plic_set_priority(uint32_t irq_id, uint32_t priority)
{
	assert(port->baddr);
	MMIO32(port->baddr + PLIC_IPRIORITY_OFFSET(irq_id)) = priority;
	arch_dmb();
	return success;
}

static uint32_t plic_get_threshold(uint32_t core_id)
{
	assert(port->baddr);
	return MMIO32(port->baddr + PLIC_ITHRESHOLD_OFFSET(core_id));
}

static status_t plic_set_threshold(uint32_t core_id, uint32_t threshold)
{
	assert(port->baddr);
	MMIO32(port->baddr + PLIC_ITHRESHOLD_OFFSET(core_id)) = threshold;
	arch_dmb();
	return success;
}

static uint32_t plic_get_interrupt()
{
	unsigned int irq;
	uint32_t core_id;
	assert(port->baddr);
	core_id = arch_core_index();
	irq = MMIO32(port->baddr + PLIC_ICLAIM_OFFSET(core_id));
	arch_dmb();
	return irq;
}


static void plic_clr_interrupt(uint32_t irq_id)
{
	uint32_t core_id;
	assert(port->baddr);
	core_id = arch_core_index();
	sysdbg3("Clearing IRQ#%u on Core-%u\n", irq_id, core_id);
	MMIO32(port->baddr + PLIC_ICLAIM_OFFSET(core_id)) = irq_id;
	arch_dmb();
	return;
}

static status_t plic_int_en(uint32_t irq_id)
{
	uint32_t core_id, irq_shift;
	assert(port->baddr);
	core_id = arch_core_index();
	sysdbg3("Enabling IRQ#%u on Core-%u\n", irq_id, core_id);
	irq_shift = irq_id % 32;
	MMIO32(port->baddr + PLIC_IENABLE_OFFSET(core_id, irq_id)) |= (1 << irq_shift);
	arch_dmb();
	return success;
}

static status_t plic_int_dis(uint32_t irq_id)
{
	uint32_t core_id, irq_shift;
	assert(port->baddr);
	core_id = arch_core_index();
	sysdbg3("Disabling IRQ#%u on Core-%u\n", irq_id, core_id);
	irq_shift = irq_id % 32;
	MMIO32(port->baddr + PLIC_IENABLE_OFFSET(core_id, irq_id)) &= ~(1 << irq_shift);
	arch_dmb();
	return success;
}

static void plic_irqhandler()
{
	uint32_t irq = plic_get_interrupt();
	plic_clr_interrupt(irq);
	sysdbg3("Handling IRQ#%u\n", irq);
	plic_irq_handler[irq]();
}

static bool plic_get_pending(uint32_t irq_id)
{
	uint32_t pending;
	assert(port->baddr);
	pending = MMIO32(port->baddr + PLIC_IPENDING_OFFSET(irq_id));
	return (pending & (1 << (irq_id % 32))) ? true : false;
}

static void plic_register_irq_handler(uint32_t id, void (* handler)(void))
{
	RET_ON_FAIL(id && handler,);
	plic_irq_handler[id] = handler;
	arch_dsb();
}

static ic_t *plic_port;

static status_t plic_driver_exit()
{
	free(plic_port);
	free(port);
	return ic_release_device();
}

static status_t plic_driver_exit_pcpu()
{
	arch_di_mei();
	return unlink_interrupt(port->irq->module, port->irq->id);
}

static status_t plic_driver_setup()
{
	status_t ret;
	arch_di_mei();
	ret = plic_setup();
	if(ret)
		goto cleanup_exit;
	plic_port = (ic_t *)malloc(sizeof(ic_t));
	if(!plic_port)
	{
		ret = error_memory_low;
		goto cleanup_exit;
	}
	plic_port->get_priority = &plic_get_priority;
	plic_port-> set_priority = &plic_set_priority;
	plic_port->get_affinity = &plic_get_threshold;
	plic_port->set_affinity = &plic_set_threshold;
	plic_port->get_irq = &plic_get_interrupt;
	plic_port->en_irq = &plic_int_en;
	plic_port->dis_irq = &plic_int_dis;
	plic_port->pending = &plic_get_pending;
	plic_port->register_handler = &plic_register_irq_handler;
	ret = ic_attach_device(ret, plic_port);
	if(ret)
		goto cleanup_exit;
	for(uint32_t i = 1; i <= N_PLAT_IRQS; i++)
	{
		plic_int_dis(i);
		plic_set_priority(i, 1);
	}
	goto exit;
cleanup_exit:
	plic_driver_exit();
exit:
	return ret;
}

static status_t plic_driver_setup_pcpu()
{
	status_t ret;
	unsigned int irq;
	if(!port)
		return error_driver_init_failed;
	sysdbg3("Linking local IRQ#%u on Core-%u\n", port->irq->id, arch_core_index());
	plic_set_threshold(arch_core_index(), 0);
	ret = link_interrupt(port->irq->module, port->irq->id, &plic_irqhandler);
	if(ret)
		goto cleanup_exit;
	do
	{
		irq = plic_get_interrupt();
		if(irq)
			plic_clr_interrupt(irq);
	} while(irq);
	arch_ei_mei();
	goto exit;
cleanup_exit:
	plic_driver_exit_pcpu();
exit:
	return ret;
}

INCLUDE_DRIVER(riscv_plic, plic_driver_setup, plic_driver_exit, 0, 0, 0);
INCLUDE_DRIVER(riscv_plic_pcpu, plic_driver_setup_pcpu, plic_driver_exit_pcpu, 1, 1, 1);
