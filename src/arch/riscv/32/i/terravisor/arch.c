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
#include <syslog.h>
#include <arch.h>
#include <lock/lock.h>
#include <terravisor/workers.h>
#include <interrupt.h>

static void arch_mcall_handler()
{
	context_frame_t *frame = get_context_frame();
	mret_t mres;
	machine_call(frame->a0, frame->a1, frame->a2, frame->a3, &mres);
	fence(w, w);
	frame->a0 = mres.p;
	frame->a1 = mres.size;
	frame->a2 = mres.status;
	return;
}

static lock_t boot_key = LOCK_INITAL_VALUE;
void arch_early_signal_boot_start()
{
	boot_key = LOCK_INITAL_VALUE;
	return;
}

void arch_wait_till_boot_done()
{
	lock_acquire(&boot_key);
	lock_release(&boot_key);
	return;
}

void arch_signal_boot_done()
{
	lock_release(&boot_key);
	return;
}

/**
 * arch_early_setup - This function is called in the early stages of boot
 *
 * @brief This function is responsible to clean reset cpu status/control registers.
 *
 */
void arch_early_setup()
{
	arch_di();
	arch_di_mei();
	arch_di_mtime();
	arch_di_msoftirq();
	riscv_update_vector();
	return;
}

/**
 * arch_setup - This function is called after initial setup is done
 *
 * @brief This function is called after initial setup is done.
 */
void arch_setup()
{
	link_interrupt(int_arch, 11, &arch_mcall_handler);
	return;
}

void arch_setup2()
{
	link_interrupt(int_arch, 11, &arch_mcall_handler);
	return;
}

void arch_di_save_state(istate_t *istate)
{
	istate_t temp;
	asm volatile("csrr %0, mie" : "=r" (temp));
	*istate = temp & (1 << 3 | 1 << 7 | 1 << 11);
	arch_di();
}

void arch_ei_restore_state(istate_t *istate)
{
	asm volatile("csrs mie, %0" : : "r" (*istate));
}

_WEAK void arch_panic_handler()
{
	const context_frame_t *frame = get_context_frame();
	syslog_stdout_enable();
	syslog(fail, "Arch Panic!\n");
	syslog(info, "Info:\nCause\t: 0x%x\t Address\t: 0x%x\n", frame->mcause, frame->mepc);
	while(1)
		arch_wfi();
}

_WEAK void arch_unhandled_irq()
{
	const context_frame_t *frame = get_context_frame();
	syslog_stdout_enable();
	syslog(fail, "Arch Unhandled IRQ!\n");
	syslog(info, "Info:\nIRQ ID\t: 0x%x\n", frame->mcause & ~(1U << 31));
	while(1)
		arch_wfi();
}
