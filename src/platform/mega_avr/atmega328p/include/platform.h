#pragma once
#include <atmega328p.h>

#define PROG_MEM	0X00000000
#define IMEM_START	0x00000000
#define IMEM_LENGTH	0x4000
#define DMEM_START	0x00800100
#define DMEM_LENGTH	0x0800
#define STACK_SIZE	0x200

#define N_ADC_MODULES	1
