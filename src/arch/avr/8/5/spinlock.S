#include <plat_arch.h>

.global spinlock_acquire
.section .text.spinlock_acquire
.type spinlock_acquire, "function"
spinlock_acquire:
	movw	r30, r24
1:
	ld	r18, Z
	ldd	r19, Z+1
	cpi	r18, 0x01
	cpc	r19, r1
	breq	1b
	ldi	r18, 0x01
	mov	r19, r1
	movw	r30, r24
	std	Z+1, r19
	st	Z, r18
	ret

.global spinlock_release
.section .text.spinlock_release
.type spinlock_release, "function"
spinlock_release:
	movw	r30, r24
	std	Z+1, r1
	st	Z, r1
	ret
