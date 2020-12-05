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
	ld	r18, Z
	ldd	r19, Z+1
	cpi	r18, 0x01
	cpc	r19, r1
	out	SREG, r0
	breq	1b
	cli
	ldi	r18, 0x01
	mov	r19, r1
	movw	r30, r24
	std	Z+1, r19
	st	Z, r18
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
	std	Z+1, r1
	st	Z, r1
	out	SREG, r0
	pop	r0
	ret
