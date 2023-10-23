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
#include <stdbool.h>
#include <assert.h>
#include <status.h>
#include <syslog.h>
#include <plat_arch.h>
#include <mmio.h>
#include <arch.h>
#include <visor/workers.h>

/**
 * arch_early_setup - This function is called in the early stages of boot
 *
 * @brief This function is responsible to clean reset cpu status/control registers.
 *
 */
void (* const p_vcall)(unsigned int, unsigned int, unsigned int, unsigned int, vret_t *) = &vcall_handler;
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

void arch_di_save_state(istate_t *sreg_i_backup)
{
	*sreg_i_backup = MMIO8(SREG+0x20) & (1 << 7);
	arch_di();
}

void arch_ei_restore_state(const istate_t *sreg_i_backup)
{
	MMIO8(SREG+0x20) |= *sreg_i_backup;
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

void _NORETURN arch_panic_handler_callback()
{
	context_frame_t *frame;
	frame = get_context_frame();
	if(!frame)
		goto panic;
	syslog_stdout_enable();
	sysdbg("r0=%p\tr1=%p\tr18=%p\tr19=%p\n",
		frame->r0, frame->r1, frame->r18, frame->r19);
	sysdbg("r20=%p\tr21=%p\tr22=%p\tr23=%p\n",
		frame->r20, frame->r21, frame->r22, frame->r23);
	sysdbg("r24=%p\tr25=%p\tr26=%p\tr27=%p\n",
		frame->r24, frame->r25, frame->r26, frame->r27);
	sysdbg("r30=%p\tr31=%p\tSP=%p\tSREG=%p\n",
		frame->r30, frame->r31, frame, frame->sreg);
#if DEBUG==0
	syslog(info, "SP=%p\tSREG = %p\n", frame, frame->sreg);
#endif
panic:
	while(1) arch_wfi();
}

static cpu_sleep_t sleep_flag;

/**
 * arch_suspended_state_was
 *
 * @brief This function checks for the suspended state
 * and returns true or false based on arg.
 *
 * @param[in] state: suspended state
 * @return bool: True/False
 */
bool arch_suspended_state_was(cpu_sleep_t state)
{
	assert((unsigned)state != resume);
	if(!sleep_flag)
		return false;
	return (sleep_flag == state);
}

/**
 * arch_signal_suspend
 *
 * @brief This function is intended to be called before
 * cpu enters suspend state. By passing the state, we store
 * and use to check while exiting resume routine
 *
 * @param[in] state: Suspend state of cpu
 */
void arch_signal_suspend(cpu_sleep_t state)
{
	sleep_flag = state;
}

/**
 * arch_signal_resume
 *
 * @brief This function signals resume of cpu. It is intended
 * to be called after exiting resume routine.
 */
void arch_signal_resume(void)
{
	sleep_flag = resume;
}
