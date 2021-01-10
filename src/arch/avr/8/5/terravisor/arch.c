/*
 * File Name		: arch.c
 * Description		: This file consists of architecture specific function that
 *			  cannot be inlined. Hence, present in c file.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 */

#include <stdint.h>
#include <status.h>
#include <machine_call.h>
#include <plat_arch.h>
#include <mmio.h>
#include <arch.h>

/**
 * arch_early_setup - This function is called in the early stages of boot
 * 
 * This function is responsible to clean reset cpu status registers.
 * 
 */
void arch_early_setup()
{
	arch_di();
	MMIO8(MCUCR) = 0;
	MMIO8(SMCR) = 0;
	MMIO8(WDTCSR) = 0;
	return;
}

/**
 * arch_setup - This function is called after initial setup is done
 * 
 */
void arch_setup()
{
	return;
}

/**
 * arch_wfi - wait for interrupt
 *
 * This function is called when the program needs to wait for interrupt.
 * This also ensures in lower power consumption when compared to busy wait.
 */
void arch_wfi()
{
	/*
	 * For interruptable sleep
	 * Enable Idle mode
	 */
	MMIO8(SMCR) = 0x01;
	arch_ei();
	asm volatile("sleep");
}

/**
 * *mcall - pointer to machine call function
 *
 * This function pointer emulates 'mcall' instruction in risc-v.
 * This method is intentionally created for this framework so
 * as to maintain consistency across all the cpu architectures.
 *
 * @code: machine call code
 * @a0: first argument
 * @a1: second argument
 * @a2: third argument
 * @ret: pointer to return of machine call.
 */
void (*mcall)(unsigned int, unsigned int, unsigned int, unsigned int, mret_t *);

/**
 * arch_machine_call - perform machine call
 *
 * This function executes function pointed by mcall. As the
 * AVR core doesn't support multiple execution levels, this
 * function emulates the machine call to maintain consistency.
 *
 * @code: machine call code
 * @a0: first argument
 * @a1: second argument
 * @a2: third argument
 * @return: returns struct which is result of machine call operation
 */
mret_t arch_machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2)
{
	mret_t ret;
	mcall(code, a0, a1, a2, &ret);
	return ret;
}

