#pragma once
#include <atmega328p.h>

#define V_IMEM_START	0x00000000
#define V_DMEM_START	0x00800100

#define L_MEM_START	0x00000000
#define L_MEM_LENGTH	0x00008000

#define IMEM_LENGTH	0x7800
#define DMEM_LENGTH	0x0800

#define STACK_SIZE	0x0200

#define N_CORES		1

#define MEMBUF_SIZE	512
