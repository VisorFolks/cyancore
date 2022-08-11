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
#include <machine_call.h>
#include <terravisor/workers.h>
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

void arch_di_save_state(istate_t *sreg_i_backup)
{
	*sreg_i_backup = MMIO8(SREG+0x20) & (1 << 7);
	arch_di();
}

void arch_ei_restore_state(istate_t *sreg_i_backup)
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
void arch_machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2, mret_t *ret)
{
	if(ret == NULL)
		return;
	machine_call(code, a0, a1, a2, ret);
	return;
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
	sysdbg("r12=%p\tr13=%p\tr14=%p\tr15=%p\tr16=%p\tr17=%p\n",
		frame->r12, frame->r13, frame->r14, frame->r15, frame->r16, frame->r17);
	sysdbg("r18=%p\tr19=%p\tr20=%p\tr21=%p\tr22=%p\tr23=%p\n",
		frame->r18, frame->r19, frame->r20, frame->r21, frame->r22, frame->r23);
	sysdbg("r24=%p\tr25=%p\tr26=%p\tr27=%p\tr28=%p\tr29=%p\n",
		frame->r24, frame->r25, frame->r26, frame->r27, frame->r28, frame->r29);
	sysdbg("r30=%p\tr31=%p\tSP=%p\tSREG=%p\n",
		frame->r30, frame->r31, frame, frame->sreg);
#if DEBUG==0
	syslog(info, "SP=%p\tSREG = %p\n", frame, frame->sreg);
#endif
panic:
	while(1) arch_wfi();
}
