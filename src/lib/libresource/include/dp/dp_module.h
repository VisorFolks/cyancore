/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp_module.h
 * Description		: This file contains prototypes of device
 *			  properties - module
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>

typedef struct module
{
	hw_devid_t id;
	uintptr_t baddr;
	uintptr_t stride;
	unsigned long clk;
	unsigned int clk_id;
	irqs_t interrupt[MAX_INTERRUPTS_PER_DEVICE];
} module_t;

#define add_modules(x)		.modules = x,		\
				.n_mods = propsize(x)

module_t *dp_get_module_info(hw_devid_t dev);
