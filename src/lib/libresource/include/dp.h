/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp.h
 * Description		: This file contains prototypes of device properties
 *			  data structure and function prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <dp/dp_system.h>
#include <dp/dp_module.h>
#include <dp/dp_gpio.h>

typedef const struct device_properties
{
	cpu_t * const core[N_CORES];
	unsigned long base_clock;
	memory_t *memory;

	gpio_module_t * const *ports;
	size_t n_ports;

	module_t * const *modules;
	size_t n_mods;
} dp_t;

status_t dp_init(dp_t *);
