/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: sysclk.h
 * Description		: This file consists of sysclk engine prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SYSCLK_H_

#include <status.h>
#include <stdint.h>
#include <resource.h>
#include <arch.h>
#include <visor_call.h>

typedef struct sysclk_config_clk_callback
{
	status_t (*pre_config)(void);
	status_t (*post_config)(void);
	struct sysclk_config_clk_callback *next;
} sysclk_config_clk_callback_t;

status_t sysclk_reset(void);

static inline status_t sysclk_set_clk(clock_type_t type, unsigned int clk)
{
	vret_t vres;
	arch_visor_call(config_clk, type, clk, 0, &vres);
	return vres.status;
}

static inline status_t sysclk_get_clk(unsigned int *clk)
{
	vret_t vres;
	arch_visor_call(fetch_clk, 0, 0, 0, &vres);
	*clk = (vres.status == success) ? (unsigned int) vres.p : 0;
	return vres.status;
}

status_t sysclk_register_config_clk_callback(sysclk_config_clk_callback_t *);
status_t sysclk_deregister_config_clk_callback(sysclk_config_clk_callback_t *);
status_t sysclk_execute_pre_config_clk_callback(void);
status_t sysclk_execute_post_config_clk_callback(void);
