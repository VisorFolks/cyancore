#include <plat_arch.h>

.global spinlock_acquire
.section .text.spinlock_acquire
.type spinlock_acquire, "function"
spinlock_acquire:
	movw	r30, r24
	push	r0
	in	r0, SREG
1:
	cli
	ld	r18, Z+
	ld	r19, Z
	cpi	r18, 0x01
	cpc	r19, r1
	brne	1f
	out	SREG, r0
	eor	r1, r1
	eor	r1, r1
	eor	r1, r1
	rjmp	1b
1:
	ldi	r18, 0x01
	mov	r19, r1
	movw	r30, r24
	st	Z+, r18
	st	Z, r19
	out	SREG, r0
	pop	r0
	ret

.global spinlock_release
.section .text.spinlock_release
.type spinlock_release, "function"
spinlock_release:
	movw	r30, r24
	push	r0
	in	r0, SREG
	cli
	st	Z+, r1
	st	Z, r1
	out	SREG, r0
	pop	r0
	ret
