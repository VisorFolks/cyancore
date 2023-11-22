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
#define _ARCH_H_

#include <arm.h>
#include <machine_call.h>

/**
 * arch_early_setup - This needs to be called in early stages of boot
 */
void arch_early_setup();

/**
 * arch_setup - This needs to be called after intial setup is completed.
 */
void arch_setup();

/**
 * arch_wfi - Wait for interrupt, with sleep mode
 */
void arch_wfi();
void arch_di_save_state(istate *);
void arch_ei_restore_state(istate *);

/**
 * arch_panic_handler - Executes when arch error occurs
 */
void arch_panic_handler();

/**
 * arch_register_interrupt_handler - Registers interrupt handler for
 * arch specific interrupt vectors
 */
void arch_register_interrupt_handler(unsigned int, void(*)(void));

/**
 * arch_super_call - perform machine call
 * @brief This function performs svc call
 *
 * @param[in] code: universal call code
 * @param[in] r0: first argument
 * @param[in] r1: second argument
 * @param[in] r2: third argument
 * @param[in] *ret: return struct
 */
#define arch_machine_call	arch_super_call
static inline void arch_super_call(unsigned int code, unsigned int arg0, unsigned int arg1, unsigned int arg2, mret_t *ret)
{
	if(ret == NULL)
		return;
	register uint32_t r0 asm("r0") = code;
	register uint32_t r1 asm("r1") = arg0;
	register uint32_t r2 asm("r2") = arg1;
	register uint32_t r3 asm("r3") = arg2;
	asm volatile("svc"
				:"+r" (r0), "+r" (r1), "+r"(r2)
				:"r" (r0), "r" (r1), "r" (r2), "r" (r3)
				:"memory");

	ret->p = r0;
	ret->size = r1;
	ret->status = r2;
	return;
}

 /**
 *  arch_ei - arch enable global interrupts
 */
static inline void arch_ei()
{
	asm volatile("cpsie iaf");
}

/**
 *  arch_ei - arch enable global interrupts
 */
static inline void arch_di()
{
	asm volatile("cpsid iaf");
}

static inline void arch_nop()
{
	asm volatile("nop");
}

static inline void arch_wfi()
{
	asm volatile("wfi");
}

static inline void arch_isb()
{
	asm volatile("isb");
}

static inline void arch_dsb()
{
	asm volatile("dsb");
}

static inline void arch_dmb()
{
	asm volatile("dmb");
}

bool arch_suspended_state_was(cpu_sleep_t);
void arch_signal_suspend(cpu_sleep_t);
void arch_signal_resume(void);
