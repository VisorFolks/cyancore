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

/**
 * add_cpu - Adds cpu node to dp tree
 *
 * @param[in] _index - Index of cpu node
 * @param[in] cpu - cpu node to be added
 */
#define add_cpu(_index, cpu)					\
	.core[_index] = &cpu					\

/**
 * create_dp - Instantiates DP tree
 *
 * @param[in] _name - Name of the tree
 * @param[in] clk - base clock of system
 * @param[in] mem - memory module of system
 * @param[in] ports_list - list of all available gpio ports
 * @param[in] mod_list - list of all available modules
 * @param[in] ... - CPU list as variable args, use add_cpu macro
 */
#define create_dp(_name, clk, mem, ports_list, mod_list, ...)	\
	dp_t _name =						\
	{							\
		.base_clock = clk,				\
		.memory = &mem,					\
		add_ports(port_list),				\
		add_modules(mod_list),				\
		##__VA_ARGS__					\
	}
