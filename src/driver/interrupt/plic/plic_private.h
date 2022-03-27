/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: plic_private.h
 * Description		: This file contains PLIC core register offsets
 *			  and other private variables
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#if PLIC_VERSION == 0x0100		// v 01.00
#define PLIC_IPRIORITY_OFFSET(irq)	(0x00000000 + 0x04 * (irq))
#define PLIC_IPENDING_OFFSET(irq)	(0x00001000 + 0x04 * (irq/31))
#define PLIC_IENABLE_OFFSET(core, irq)	(0x00002000 + 0x80 * (core) + 0x04 * (irq/32))
#define PLIC_ITHRESHOLD_OFFSET(core)	(0x00200000 + 0x1000 * (core))
#define PLIC_ICLAIM_OFFSET(core)	(0x00200004 + 0x1000 * (core))
#endif

typedef struct plic_port
{
	hw_devid_t port_id;
	uintptr_t baddr;
	uintptr_t stride;
	const irqs_t *irq;
} plic_port_t;

static void (* plic_irq_handler[N_PLAT_IRQS])(void) = {[0 ... N_PLAT_IRQS-1] = &plat_panic_handler};
