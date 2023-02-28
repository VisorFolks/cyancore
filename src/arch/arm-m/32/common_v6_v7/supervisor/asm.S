/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022-2023, Cyancore Team
 *
 * File Name		: asm.S
 * Description		: This file consists of all the function written in asm
 *			  like ISR, context management and panic handler
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
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
	mrs	r1, msp
	bl	exception_handler
	pop	{r1-r7}
	pop	{r0}
	mov	lr, r0
	pop	{r0}
	mov	pc, lr

/**
 * Interrupt Router Declaration Table
 * 1-14 Interrupt routers are define as of now. If possible more can
 * be added. But during compile time only necessary interrupt router
 * functions will be retained and others are cleaned up.
 */
/*==========< Interrupt router functions >==========*/
.set i, 1
.rept 14
	INT %i
.set i, i+1
.endr

