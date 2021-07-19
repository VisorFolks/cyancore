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
#include <timer_mode.h>

/*
 * This data type will be declared in
 * platform/<family>/common/include/timer_mode.h
 * This will let user choose platform specific hal
 * driver and it's corresponding modes.
 */
typedef enum timer_mode timer_mode_t;

typedef enum timer_ps
{
	div1 = 1,
	div2, div4, div8,
	div16, div32, div64,
	div128, div256, div512,
	div1024, div2048, div4096,
	ext_src_rise, ext_src_fall
} timer_ps_t;

typedef struct timer_port
{
	uint8_t port_id;
	unsigned int clk_id;
	uintptr_t baddr;
	uintptr_t stride;
	size_t tmr_irq;
	void (*tmr_handler)(void);
} timer_port_t;

