/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: timer.h
 * Description		: This file consists of prototypes for terravisor
 *			  timer drivers
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _TVISOR_TIMER_T_

typedef struct tvisor_timer
{
	uint64_t (*read_ticks)(void);
	uint64_t (*read_time)(void);
	void (*set_period)(unsigned int);
	void (*reg_cb)(void *);
} tvisor_timer_t;

status_t timer_attach_device(status_t, tvisor_timer_t *);
status_t timer_release_device();
status_t timer_link_callback(unsigned int, void *);
