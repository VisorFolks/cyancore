/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: asm.S
 * Description		: This file consists of all the function written in asm
 *			  like ISR, context management, zero_reg and panic handler
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>
#include <plat_arch.h>

/**
 * zero_reg - Needs to be called after reset of CPU
 *
 * @brief This function is reponsible to reset all the register to 0 to
 * remove junk value that gets stored on reset due to undefined
 * state of registers.
 * As per the abi spec of AVR5-8, r1 is always supposed to be 0.
 * Hence, r1 is reset to 0 and other are moved with r1.
 */
.altmacro
.macro clear_reg n
	eor	r\n, r\n
.endm

function zero_reg
.set i, 0
.rept 32
	clear_reg %i
.set i, i+1
.endr
	ret

function arch_panic_handler
	push	r24
	ldi	r24, 255
	rjmp	isr

/**
 * CONTEXT_SAVE - A macro that define the context save operation
 */
.macro CONTEXT_SAVE
	push	r1
	push	r0
	in	r0, SREG
	push	r0
	push	r18
	push	r19
	push	r20
	push	r21
	push	r22
	push	r23
	push	r25
	push	r26
	push	r27
	push	r30
.endm

/**
 * CONTEXT_RESTORE - A macro that defines the context restore operation
 */
.macro CONTEXT_RESTORE
	pop	r30
	pop	r27
	pop	r26
	pop	r25
	pop	r23
	pop	r22
	pop	r21
	pop	r20
	pop	r19
	pop	r18
	pop	r0
	out	SREG, r0
	pop	r0
	pop	r1
.endm

/**
 * INT - a macro that defines function int_(id) with few other operations
 *
 * @param id - ID of the interrupt vector
 */
.altmacro
.macro INT id
/**
 * int_(id) - Interrupt router function
 * @brief A function that sets interrupt ID and jumps to ISR.
 */
function int_\id
	push	r24
	ldi	r24, \id
	rjmp	isr
.endm

/**
 * isr - interrupt service routine function
 * @brief This function is called from interrupt router.
 * It is responsible to do context management before and after
 * calling the interrupt handler function.
 */
function isr
	CONTEXT_SAVE
	in	r22, IO_SPL
	in	r23, IO_SPH
	/*
	 * SP at this location needs to be captured
	 * and passed to interrupt_handler as SP post
	 * decrements which results in SP pointing to
	 * incorrect stack frame.
	 */
	push	r31
	call	interrupt_handler
	pop	r31
	CONTEXT_RESTORE
	pop	r24
	reti

/**
 * Interrupt Router Declaration Table
 * 1-60 Interrupt routers are define as of now. If possible more can
 * be added. But during compile time only necessary interrupt router
 * functions will be retained and others are cleaned up.
 */
/*==========< Interrupt router functions >==========*/

.set i, 1
.rept 60
	INT %i
.set i, i+1
.endr
