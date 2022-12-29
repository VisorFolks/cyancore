/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
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
	cpu_sleep_t **states;
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
