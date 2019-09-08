#define SREG	0x3f

.global plat_panic_handler
.section .text
.type plat_panic_handler, "function"
plat_panic_handler:
	SLEEP
	rjmp	plat_panic_handler

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
	reti
.endm

#if USE_INT0
.global int0
.section .text
.type int0, "function"
int0:
	CONTEXT_SAVE
	jmp	int0_handler
	CONTEXT_RESTORE
#endif
