#pragma once
#define _ARCH_H_

#include <plat_arch.h>
#include <mmio.h>

void arch_early_setup();
void arch_setup();
void arch_wfi();

#ifdef _MACHINE_CALL_H_
mret_t arch_machine_call(unsigned  int, unsigned int, unsigned  int, unsigned  int);
#endif

void arch_register_interrupt_handler(unsigned int, void (*)(void));

static inline unsigned int arch_core_id()
{
	/*
	 * AVR only support uni core architecture
	 */
	return 0;
}

inline void arch_ei()
{
	asm volatile("sei");
}

static inline void arch_di()
{
	asm volatile("cli");
}

static inline void arch_wdt_reset()
{
	asm volatile("wdr");
}
