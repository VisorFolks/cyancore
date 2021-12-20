/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: arch.c
 * Description		: This file consists of architecture specific function that
 *			  cannot be inlined. Hence, present in c file.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
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
 * @brief This function is responsible to clean reset cpu status/control registers.
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
 * @brief This function is called after initial setup is done.
 */
void arch_setup()
{
	return;
}

uint8_t sreg_i_backup;

void arch_di_save_state()
{
	sreg_i_backup = MMIO8(SREG) & (1 << 7);
	arch_di();
}

void arch_ei_restore_state()
{
	MMIO8(SREG) |= sreg_i_backup;
}

/**
 * arch_wfi - wait for interrupt
 *
 * @brief This function should be called when the program needs to
 * wait for interrupt. This also ensures in lower power consumption
 * when compared to busy wait.
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
 * @brief This function pointer emulates 'mcall' instruction in risc-v.
 * This method is intentionally created for this framework so
 * as to maintain consistency across all the cpu architectures.
 *
 * @param[in] code: machine call code
 * @param[in] a0: first argument
 * @param[in] a1: second argument
 * @param[in] a2: third argument
 * @param[out] ret: pointer to return of machine call.
 */
void (*mcall)(unsigned int, unsigned int, unsigned int, unsigned int, mret_t *);

/**
 * arch_machine_call - perform machine call
 *
 * @brief This function executes function pointed by mcall. As the
 * AVR core doesn't support multiple execution levels, this
 * function emulates the machine call to maintain consistency.
 *
 * @param[in] code: machine call code
 * @param[in] a0: first argument
 * @param[in] a1: second argument
 * @param[in] a2: third argument
 * @return status: returns struct which is result of machine call operation
 */
mret_t arch_machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2)
{
	mret_t ret;
	mcall(code, a0, a1, a2, &ret);
	return ret;
}
