/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: spinlock.S
 * Description		: This file consists of sources of spinlock in asm
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>
#include <plat_arch.h>

/**
 * spinlock_acquire - Acquires spinlock
 *
 * @brief This is a blocking busy-loop spinlock acquire function. When the
 * lock is not acquired, this function disables global interrupt and
 * acquires lock restores the SREG. Here global interrupt is not enable
 * directly, because there are possibilities when global interrupt is
 * disabled intentionally. The atomicity of reads and writes are ensured
 * by disabling interrupt and restoring SREG.
 * When the lock is already acquired by the same key, this function
 * first disables global interrupt, performs lock acquire check and
 * restores SREG and busy loops till the lock is released by previously
 * acquired program.
 *
 * The reason why we deal with interrupt in this spinlock is, AVR CPU
 * has mono core architecture, to run in multithreading mode, CPU needs
 * to perform interrupt based context switching. If the same resource
 * is invoked by more than 1 thread then it is ideal to have lock to
 * secure the resource. But if the interrupt is blocked till the process
 * is completed many interrupts will be ignored thereby hindering
 * performance and loss of response from the system.
 *
 * @prama key - Accepts address of key variable
 */
function spinlock_acquire
	push	r31
	push	r30
	push	r19
	push	r18
	push	r0
	movw	r30, r24
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
	pop	r18
	pop	r19
	pop	r30
	pop	r31
	ret

/**
 * spinlock_release - Releases spinlock
 *
 * @brief This function clears the key set by spinlock_acquire thereby
 * releasing the lock. This operation needs to be put in the interrupt
 * guide so that the writes are of atomic in natures.
 *
 * @param key - Accepts address of key variable
 */
function spinlock_release
	push	r31
	push	r30
	push	r0
	movw	r30, r24
	in	r0, SREG
	cli
	st	Z+, r1
	st	Z, r1
	out	SREG, r0
	pop	r0
	pop	r30
	pop	r31
	ret
