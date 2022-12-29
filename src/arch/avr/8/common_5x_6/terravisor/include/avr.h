/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: arch.h
 * Description		: This file prototypes arch related functions and
 *			  defines inline-able arch functions.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _AVR_H_
#include <stdint.h>
#include <mmio.h>
#include <string.h>
#include <stdbool.h>

typedef struct context_frame
{
	uint8_t r31, r30, r29, r28, r27, r26, r25, r23,
		r22, r21, r20, r19, r18, r17, r16, r15,
		r14, r13, r12, r11, r10, r9, r8, r7,
		r6, r5, r4, r3, r2, sreg, r0, r1, r24;
} context_frame_t;

typedef uint16_t call_arg_t;
typedef uint8_t istate_t;

context_frame_t *get_context_frame();
void arch_panic_handler_callback();
bool in_isr(void);

static inline void arch_update_sp(uint16_t *p)
{
	uint16_t temp = (uint16_t) p;
	MMIO8(SPL) = (uint8_t)(temp & 0xff);
	MMIO8(SPH) = (uint8_t)((temp >> 8) & 0xff);
}
