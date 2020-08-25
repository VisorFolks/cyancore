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
