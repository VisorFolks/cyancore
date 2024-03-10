/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: arch.h
 * Description		: This file prototypes arch related functions and
 *			  defines inline-able arch functions.
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com],
 *			  Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _ARM_H

#include <stdint.h>
#include <stdbool.h>


typedef struct context_frame
{
	uint32_t elr, psr, ret_addr, lr,
		 r12, r3, r2, r1, r0;
} context_frame_t;

typedef uint32_t call_arg_t;
typedef uint32_t istate_t;

static inline unsigned int __arm_cpuid()
{
	unsigned int ret;
	asm volatile("mrs %0, cpuid" : "=r" (ret)::);
	return ret;
}

static inline unsigned int arch_core_impid()
{
	unsigned int ret;
	ret = __arm_cpuid();
	ret >>= 24;
	return ret;
}

static inline unsigned int arch_core_varid()
{
	unsigned int ret;
	ret = __arm_cpuid();
	ret >>= 20;
	ret &= 0xf;
	return ret;
}

static inline unsigned int arch_core_archid()
{
	unsigned int ret;
	ret = __arm_cpuid();
	ret >>= 16;
	ret &= 0xf;
	return ret;
}

static inline unsigned int arch_core_partno()
{
	unsigned int ret;
	ret = __arm_cpuid();
	ret >>= 4;
	ret &= 0xfff;
	return ret;
}

static inline unsigned int arch_core_revid()
{
	unsigned int ret;
	ret = __arm_cpuid();
	ret &= 0xf;
	return ret;
}

static inline void arch_update_sp(uint32_t *p)
{
	asm volatile("mov msp, %0" : : "r"(p));
}

context_frame_t *get_context_frame();
bool in_isr(void);
void arch_panic_handler_callback();
