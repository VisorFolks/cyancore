/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: timer.h
 * Description		: This file consists of Timer-HAL prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _TIMER_H_

#include <stdint.h>
#include <status.h>



typedef struct timer_port
{
	hw_devid_t port_id;
	unsigned int clk_id;
	uintptr_t baddr;
	uintptr_t stride;
	size_t value;
	size_t tmr_irq;
	void (*tmr_handler)(void);
} timer_port_t;

typedef enum timer_mode
{
	__timer_mode_null = 0,
	oneshot,
	periodic,
	timer_mode_other = 0xf000
} timer_mode_t;

status_t timer_setup(const timer_port_t *port, unsigned int mode, unsigned int ps);
status_t timer_shutdown(const timer_port_t *port);
status_t timer_read(const timer_port_t *port, size_t *value);
status_t timer_pwm_set(const timer_port_t *port, bool invert, size_t value);
