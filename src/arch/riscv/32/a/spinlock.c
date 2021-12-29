/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: spinlock.c
 * Description		: This file consists of sources of spinlock
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <arch.h>
#include <lock/lock.h>

void spinlock_acquire(spinlock_t *key)
{
	unsigned int old, new;
	new = 1;
	while(1)
	{
		if(*key)
			continue;
		asm volatile("amoswap.w %0, %2, %1" : "=r" (old), "+A" (*key) : "r" (new) : "memory");
		fence(r, rw);
		if(!old)
			break;
	}
}

void spinlock_release(spinlock_t *key)
{
	fence(r, rw);
	*key = 0;
}
