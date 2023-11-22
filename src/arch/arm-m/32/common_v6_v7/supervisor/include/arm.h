/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: arch.h
 * Description		: This file prototypes arch related functions and
 *			  defines inline-able arch functions.
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _ARM_H
#include<stdint.h>
#include<string.h>
#include<stdbool.h>


typedef struct context_frame
{
	uint8_t r15, r14, r13, r12, r11, r10, r9, r8,
		r7, r6, r5, r4, r3, r2, r1, APSR, r0;
}context_frame_t;

typedef uint32_t istate_t;

static inline unsigned int arch_core_impid()
{
	unsigned int ret;
	asm volatile("cpuid %0, implementer" : "=r"(ret));
	return ret;
}

static inline unsigned int arch_core_varid()
{
	unsigned int ret;
	asm volatile("cpuid %0, varid" : "=r"(ret));
	return ret;
}

static inline unsigned int arch_core_archid()
{
	unsigned int ret;
	asm volatile("cpuid %0, architecture" : "=r"(ret));
	return ret;
}

static inline unsigned int arch_core_partno()
{
	unsigned int ret;
	asm volatile("cpuid %0, partno" : "=r"(ret));
}

static inline unsigned int arch_core_revid()
{
	unsigned int ret;
	asm volatile("cpuid %0, revision" : "=r"(ret));
}

static inline void arch_update_sp(uint32_t *p)
{
	asm volatile("mov sp, %0" : : "r"(p));
}

context_frame_t *get_context_frame();
bool in_isr(void);
void arch_panic_handler_callback();
