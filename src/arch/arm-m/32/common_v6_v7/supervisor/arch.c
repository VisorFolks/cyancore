/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: arch.c
 * Description		: This file consists of architecture specific function that
 *			  cannot be inlined. Hence, present in c file.
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <status.h>
#include <syslog.h>
#include <mmio.h>
#include <arch.h>
#include <visor/workers.h>

static void arch_ecall_handler()
{
	context_frame_t *frame = get_context_frame();
	vret_t vres;
	machine_call(frame->r0, frame->r1, frame->r3, &vres);
	frame->r0 = vres.p;
	frame->r1 = vres.size;
	frame->r2 = vres.status;
	return;
}

/**
 *arch_early_setup - This function is called in the early stages of boot
 *
 * @brief This function is respinsible to clean reset cpu status/control registers.
 *
 */
void arch_early_setup()
{
	arch_di();

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
	*
}

void arch_ei_restore_state(istate_t *sreg_i_backup)
{

}

/**
 * arch_core_index - Returns code index
 */

_WEAK unsigned int arch_core_index()
{
	return 0;
}

void _NORETURN arch_panic_handler_callback()
{
	context_frame_t *frame;
	frame = get_context_frame();
	if(!frame)
		goto panic;
	syslog_stdout_enable();
	sysdbg("r0=%p\tr1=%p\tr2=%p\tr3=%p\tr4=%p\tr5=%p\n",
		frame->r0, frame->r1, frame->r2, frame->r3, frame->r4, frame->r5);
	sysdbg("r6=%p\tr7=%p\tr8=%p\tr9=%p\tr10=%p\tr11=%p\n",
		frame->r6, frame->r7, frame->r8, frame->r9, frame->r10, frame->r11);
	sysdbg("r12=%p\tr13=%p\tr14=%p\tr15=%p\tAPSR=%p\n",
		frame->r12, frame->r13, frame->r14, frame->r15, frame->apsr);
#if DEBUG==0
	syslog(info, "APSR=%p\n", frame->apsr);
#endif
panic:
	while(1) arch_wfi();
}

static cpu_sleep_t sleep_flag;

/**
 * arch_suspended_state_was
 *
 * @brief This function checks for the suspended state
 * and returns true or flase based on arg.
 *
 * @param[in] state: suspended state
 * @return bool: True/False
 */

bool arch_suspended_state_was(cpu_sleep_t state)
{
	assert(state != resume);
	if(!sleep_flag)
		return false;
	return (sleep_flag == state);
}

/**
 * arch_signal_suspend
 *
 * @brief This function is intended to be called before cpu enters
 * suspend state. By passing the state, we store and use to check while
 * exiting resume routine.
 *
 * @param[in] state: Suspend state of cpu
 */
void arch_signal_suspend(cpu_sleep_t state)
{
	sleep_flag = state;
}

/**
 * @brief This function signals resume of cpu. It is intended
 * to be called after exiting resume routine.
 */
void arch_signal_resume(void)
{
	sleep_flag = resume;
}
