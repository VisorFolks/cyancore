*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: asm.S
 * Description		: This file consists of all the function written in asm
 *			  like ISR, context management and panic handler
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>
#include <plat_arch.h>

/**
 * PROLOGUE - A macro that defines context save operation. Saving only argument registers (r0 - r7)
 **/

.macro PROLOGUE
	push	r0
	push	r1
	MRS	r1, APSR
	push	r1
	push	r2
	push	r3
	push	r4
	push	r5
	push 	r6
	push 	r7
.endm

/**
 * EPILOGUE - A macro that defines context restore operation
**/

.macro	EPILOGUE
	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r2
	pop	r1
	MSR	APSR, r1
	pop	r1
	pop	r0
.endm


function int_ /id
	push	r0
	mov	r0, #/id
	b	isr

/**
 * isr - interrupt service routine function
 * @brief This function is called from interrupt router.
 * It is responsible to do context management before and after
 * calling the interrupt handler function.
 */

function isr
	PROLOGUE
	MRS	r1, MPS
	add	r1, #1
	bl	exception_handler
	EPILOGUE
	pop	r0

/**
 * Interrupt Router Declaration Table
 * 1-15 Interrupt routers are define as of now. If possible more can
 * be added. But during compile time only necessary interrupt router
 * functions will be retained and others are cleaned up.
 */
/*==========< Interrupt router functions >==========*/
.set i, 1
.rept 15
	INT %i
.set i, i+1
.endr
