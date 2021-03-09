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
 * This function is reponsible to reset all the register to 0 to
 * remove junk value that gets stored on reset due to undefined
 * state of registers.
 * As per the abi spec of AVR5-8, r1 is always supposed to be 0.
 * Hence, r1 is reset to 0 and other are moved with r1.
 */
function zero_reg
	eor	r1, r1
	mov	r0, r1
	mov	r2, r1
	mov	r3, r1
	mov	r4, r1
	mov	r5, r1
	mov	r6, r1
	mov	r7, r1
	mov	r8, r1
	mov	r9, r1
	mov	r10, r1
	mov	r11, r1
	mov	r12, r1
	mov	r13, r1
	mov	r14, r1
	mov	r15, r1
	mov	r16, r1
	mov	r17, r1
	mov	r18, r1
	mov	r19, r1
	mov	r20, r1
	mov	r21, r1
	mov	r22, r1
	mov	r23, r1
	mov	r24, r1
	mov	r25, r1
	mov	r26, r1
	mov	r27, r1
	mov	r28, r1
	mov	r29, r1
	mov	r30, r1
	mov	r31, r1
	ret

/**
 * arch_panic_handler - Panic which get invoked on arch failure
 *
 * This function is reponsible to halt the CPU and look here for
 * indefinitely to prevent faulty execution.
 */
function arch_panic_handler
	call	arch_wfi
	rjmp	arch_panic_handler

/**
 * CONTEXT_SAVE - A macro that define the context save operation
 */
.macro CONTEXT_SAVE
	push	r1
	push	r0
	in	r0, SREG
	push	r0
	push	r2
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15
	push	r16
	push	r17
	push	r18
	push	r19
	push	r20
	push	r21
	push	r22
	push	r23
	push	r25
	push	r26
	push	r27
	push	r28
	push	r29
	push	r30
	push	r31
.endm

/**
 * CONTEXT_RESTORE - A macro that defines the context restore operation
 */
.macro CONTEXT_RESTORE
	pop	r31
	pop	r30
	pop	r29
	pop	r28
	pop	r27
	pop	r26
	pop	r25
	pop	r23
	pop	r22
	pop	r21
	pop	r20
	pop	r19
	pop	r18
	pop	r17
	pop	r16
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r2
	pop	r0
	out	SREG, r0
	pop	r0
	pop	r1
.endm

/**
 * INT - a macro that defines function int_(id) with few other operations
 *
 * @id - ID of the interrupt vector
 */
.macro INT id
/**
 * int_(id) - Interrupt router function
 * A function that sets interrupt ID and jumps to ISR.
 */
function int_\id
	push	r24
	ldi	r24, \id
	rjmp	isr
.endm

/**
 * isr - interrupt service routine function
 * This function is called from interrupt router.
 * It is responsible to do context management before and after
 * calling the interrupt handler function.
 */
function isr
	CONTEXT_SAVE
	call	interrupt_handler
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
INT 1
INT 2
INT 3
INT 4
INT 5
INT 6
INT 7
INT 8
INT 9
INT 10
INT 11
INT 12
INT 13
INT 14
INT 15
INT 16
INT 17
INT 18
INT 19
INT 20
INT 21
INT 22
INT 23
INT 24
INT 25
INT 26
INT 27
INT 28
INT 29
INT 30
INT 31
INT 32
INT 33
INT 34
INT 35
INT 36
INT 37
INT 38
INT 39
INT 40
INT 41
INT 42
INT 43
INT 44
INT 45
INT 46
INT 47
INT 48
INT 49
INT 50
INT 51
INT 52
INT 53
INT 54
INT 55
INT 56
INT 57
INT 58
INT 59
INT 60
