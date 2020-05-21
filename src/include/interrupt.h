#pragma once
#define _INTERRUPT_H_

typedef enum int_module
{
	arch = 1,
	local = 2,
	plat = 3
} int_module_t;

typedef struct int_wait
{
	uint8_t lock;
} int_wait_t;

status_t link_interrupt(int_module_t, unsigned int, void (*)(void));
status_t unlink_interrupt(int_module_t, unsigned int);
status_t wait_till_irq(int_wait_t *);
status_t wait_release_on_irq(int_wait_t *);
