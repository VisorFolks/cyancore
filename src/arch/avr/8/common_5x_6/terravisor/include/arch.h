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
#define _ARCH_H_

#include <plat_arch.h>
#include <avr.h>
#include <mmio.h>
#include <resource.h>
#include <machine_call.h>

/**
 * arch_early_setup - This needs to be called in early stages of boot
 */
void arch_early_setup();

/**
 * arch_setup - This needs to be called after inital setup is completed
 */
void arch_setup();

/**
 * arch_wfi - Wait for interrupt, with sleep mode
 */
void arch_wfi();
void arch_di_save_state(istate_t *);
void arch_ei_restore_state(istate_t *);

/**
 * arch_panic_handler - Executes when arch error occurs
 */
void arch_panic_handler();

/**
 * arch_register_interrupt_handler - Registers interrtup handler
 * for arch specific interrupt vectors
 */
void arch_register_interrupt_handler(unsigned int, void (*)(void));

/**
 * arch_core_index - Returns code index (0, in case of AVR)
 */
static inline unsigned int arch_core_index()
{
	/* AVR only support uni core architecture */
	return 0;
}

/**
 * arch_machine_call - perform machine call
 *
 * @brief This function emulates the machine
 * call to maintain consistency.
 *
 * @param[in] code: machine call code
 * @param[in] a0: first argument
 * @param[in] a1: second argument
 * @param[in] a2: third argument
 * @param[in] *ret: return value
 */
static inline void arch_machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2, mret_t *ret)
{
	extern void (*const p_mcall)(unsigned int, unsigned int, unsigned int, unsigned int, mret_t*);
	if(ret == NULL)
		return;
	p_mcall(code, a0, a1, a2, ret);
	return;
}

/**
 * arch_ei - arch enable global interrupts
 */
static inline void arch_ei()
{
	asm volatile("sei");
}

/**
 * arch_di - arch disable global interrupts
 */
static inline void arch_di()
{
	asm volatile("cli");
}

/**
 * arch_wdt_reset - Reset watchdog timer
 */
static inline void arch_wdt_reset()
{
	asm volatile("wdr");
}

static inline void arch_nop()
{
	asm volatile("nop");
}

/*
 * AVR CPU arch doesn't describe memory ordering
 * type and avr arch supports only 1 core.
 * Hence defining isb, dsb and dmb as nop.
 */
#define arch_isb()	arch_nop()
#define arch_dsb()	arch_nop()
#define arch_dmb()	arch_nop()

#ifdef _STDBOOL_H_
bool arch_suspended_state_was(cpu_sleep_t);
void arch_signal_suspend(cpu_sleep_t);
void arch_signal_resume(void);
#endif
