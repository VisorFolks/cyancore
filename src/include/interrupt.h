/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: interrupt.h
 * Description		: This file consists of interrupt core prototypes	
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _INTERRUPT_H_

#include <stdint.h>
#include <resource.h>

typedef struct int_wait
{
	uint8_t lock;
} int_wait_t;

status_t link_interrupt(int_module_t, unsigned int, void (*)(void));
status_t unlink_interrupt(int_module_t, unsigned int);
status_t wait_till_irq(int_wait_t *);
status_t wait_lock(int_wait_t *);
status_t wait_release_on_irq(int_wait_t *);
