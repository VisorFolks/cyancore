/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: dp_system.h
 * Description		: This file contains prototypes of device
 *			  properties - system
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>
#include <sp.h>

typedef enum cpu_sleep
{
	sleep_wfi		= 0x001,
	sleep_core_clock	= 0x100,
	sleep_cluster_pclock	= 0x200,
	sleep_cluster_fclock	= 0x201,
	sleep_cluster_off	= 0x2f0,
	sleep_power_off		= 0xaaa,
	resume			= 0xffff,
} cpu_sleep_t;

/* === Intrrupts structures === */

typedef enum int_trigger
{
	int_falling_edge,
	int_rising_edge,
	int_level
} int_trigger_t;

typedef enum int_module
{
	int_arch = 1,
	int_local = 2,
	int_plat = 3
} int_module_t;

typedef const struct irqs
{
	uint32_t module : 4;
	uint32_t id	: 24;
	uint32_t trigger: 4;
} irqs_t;

typedef const struct cpu
{
	char name[10];
	uint16_t id;
	cpu_sleep_t *states;
	size_t n_sleep_states;

} cpu_t;

typedef const struct memory_info
{
	uintptr_t start;
	uintptr_t size;
} memory_t;

typedef enum clock_type
{
	internal,
	external,
	pll
} clock_type_t;

cpu_t *dp_get_cpu_info(uint8_t);
const unsigned long *dp_get_base_clock();
memory_t *dp_get_memory_info();

/**
 * create_memory - Instantiates memory module
 *
 * @param[in] _name - Name of the module
 * @param[in] _start - start address of the memory
 * @param[in] _size - size of memory segment
 */
#define create_memory(_name, _start, _size)	\
	static memory_t _name =			\
	{					\
		.start = _start,		\
		.size = _size			\
	}

/**
 * create_sleep_list - Creates CPU states list
 *
 * @param[in] _name - Name of the list
 * @param[in] state1 - Minimum of 1 states is required
 * @param[in] ... - Variable args for more states
 */
#define create_sleep_list(_name, state1, ...)	\
	static cpu_sleep_t _name[] = {state1, ##__VA_ARGS__}

/**
 * add_cpu_sleep_states - Adds cpu states to create_cpu
 *
 * @param[in] x = CPU states list
 */
#define add_cpu_sleep_states(x)			\
	.states = &x,				\
	.n_sleep_states = propsize(x)

/**
 * create_cpu - Instantitates cpu module
 *
 * @param[in] _name - Name of the module
 * @param[in] _cpu - type of cpu
 * @param[in] _id - ID of the cpu
 * @param[in] ... - Variable args for sleep modes
 */
#define create_cpu(_name, _cpu, _id, ...)		\
	static cpu_t _name =				\
	{						\
		.name = _cpu,				\
		.id = _id,				\
		##__VA_ARGS__				\
	}

