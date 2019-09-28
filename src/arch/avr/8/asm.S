#include <platform.h>

.global arch_panic_handler
.section .text
.type arch_panic_handler, "function"
arch_panic_handler:
	SLEEP
	rjmp	arch_panic_handler

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
	push	r19
	push	r20
	push	r21
	push	r22
	push	r23
	push	r24
	push	r25
	push	r26
	push	r27
	push	r28
	push	r29
	push	r30
	push	r31
.endm

.macro CONTEXT_RESTORE
	pop	r31
	pop	r30
	pop	r29
	pop	r28
	pop	r27
	pop	r26
	pop	r25
	pop	r24
	pop	r23
	pop	r22
	pop	r21
	pop	r20
	pop	r19
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
	pop	r18
	reti
.endm

.macro INT id
.global int_\id
.section .text.int_\id
.type int_\id, "function"
int_\id:
	push	r18
	ldi	r18, \id
	rjmp	isr
.endm

.global isr
.section .text.isr
.type isr, "function"
isr:
	CONTEXT_SAVE
	rjmp	interrupt_handler
	CONTEXT_RESTORE

/*==========< Interrupt functions >==========*/
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
