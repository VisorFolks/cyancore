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

} cpu_t;

typedef struct memory_info
{
	uintptr_t start;
	uintptr_t size;
} memory_t;

cpu_t *dp_get_cpu_info(uint8_t);
uint8_t *dp_get_datawidth();
unsigned long *dp_get_base_clock();
memory_t *dp_get_memory_info();
