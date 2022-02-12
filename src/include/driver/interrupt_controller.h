/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: console.h
 * Description		: This file consists of console core prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _IC_H_

typedef struct interrupt_controller
{
	uint32_t (*get_priority)(uint32_t irq);
	status_t (*set_priority)(uint32_t irq, uint32_t priority);
	uint32_t (*get_affinity)(uint32_t core_id);
	status_t (*set_affinity)(uint32_t core_id, uint32_t aff);
	uint32_t (*get_irq)();
	status_t (*en_irq)(uint32_t irq);
	status_t (*dis_irq)(uint32_t irq);
	bool (*pending)(uint32_t irq);
	void (* register_handler)(uint32_t id, void (* handler)(void));
} ic_t;

status_t ic_attach_device(status_t, ic_t *pic);
status_t ic_release_device();
unsigned int ic_get_irq();
status_t ic_set_priority_of_irq(unsigned int irq_id, unsigned int priority);
unsigned int ic_get_priority_of_irq(unsigned int irq_id);
status_t ic_en_irq(unsigned int irq_id);
status_t ic_dis_irq(unsigned int irq_id);
unsigned int ic_get_affinity_of_core();
status_t ic_set_affinity_of_core(unsigned int irq_id);
void ic_register_interrupt_handler(unsigned int id, void (* handler)(void));
