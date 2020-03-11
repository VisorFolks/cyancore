#pragma once
#define _ARCH_H_

void arch_early_setup();
void arch_setup();
void arch_idle();
void arch_di();
void arch_ei();
unsigned int arch_machine_call(unsigned  int, unsigned int, unsigned  int, unsigned  int, status_t *);
