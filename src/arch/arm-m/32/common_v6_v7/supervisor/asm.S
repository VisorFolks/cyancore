/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: asm.S
 * Description		: This file consists of all the function written in asm
 *			  like ISR, context management and panic handler
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com],
 *			  Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>

/**
 * Note:
 * - A.R.M. : Architecture Reference Manual
 */

/**
 * isr - interrupt service routine function
 * @brief This function is called upon exceptions or irqs.
 * As per the armv6-m A.R.M., upon triggering of exception
 * CPU performs a minimal context management in which it
 * saves registers r0-r3, r12, lr, return address, psr.
 * Also it updates LR, refer to doc (B1.5.6 in A.R.M.).
 * Additionally we perform saving of LR so that
 * exception handler can update the LR as per need.
 */

.weak isr
function isr
	push	{lr}
	mrs	r0, ipsr
	mov	r1, sp
	bl	exception_handler
	pop	{r0}
	bx	r0

