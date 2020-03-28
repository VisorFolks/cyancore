#pragma once
#define _ARCH_H_

unsigned int arch_core_id();
void arch_early_setup();
void arch_setup();
void arch_wfi();
void arch_di();
void arch_ei();
#ifdef _MACHINE_CALL_H_
mret_t arch_machine_call(unsigned  int, unsigned int, unsigned  int, unsigned  int);
#endif

void arch_register_interrupt_handler(unsigned int, void (*)(void));
