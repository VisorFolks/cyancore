/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: riscv.h
 * Description		: This file prototypes riscv arch related functions and
 *			  structures.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _RISC_V_
#include <stdint.h>

#define fence(predecessor, successor)	asm volatile("fence " #predecessor ", " #successor ::: "memory")

typedef struct context_frame
{
	uint32_t mepc, mstatus, ra, t0,
		 t1, t2, a0, a1, a2, a3,
		 a4, a5, a6, a7, t3, t4,
		 t5, t6, pad[6];
		 /* Padding is necessary for alignment */
} context_frame_t;

void riscv_update_vector();
context_frame_t *get_context_frame();
