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

.altmacro
.macro INT id

function int_\id
	push	{r0}
	mov	r0, #\id
	b	isr
.endm

/**
 * isr - interrupt service routine function
 * @brief This function is called from interrupt router.
 * It is responsible to do context management before and after
 * calling the interrupt handler function.
 */

.weak isr
function isr
	push	{r1-r7, lr}
	mrs	r1, psr
	push	{r1}
	mrs	r1, msp
	bl	exception_handler
	pop	{r1}
	msr	epsr, r1
	pop	{r0}
	mov	lr, r0
	pop	{r1-r7}
	pop	{r0}
	mov	pc, lr

/*==========< Interrupt router functions >==========*/
.set i, 1
.rept (N_IRQ + N_EXCEP)
	INT %i
.set i, i+1
.endr

