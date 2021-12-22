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
} cpu_sleep_t;

typedef enum int_trigger
{
	i_falling_edge,
	i_rising_edge,
	i_level
} int_trigger_t;

typedef struct cpu
{
	char name[10];
	uint16_t id;
	cpu_sleep_t **states;
	size_t n_sleep_states;

} cpu_t;

typedef struct memory_info
{
	uintptr_t start;
	uintptr_t size;
} memory_t;

cpu_t *dp_get_cpu_info(uint8_t);
unsigned long *dp_get_base_clock();
memory_t *dp_get_memory_info();
