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

_WEAK void spinlock_acquire(volatile spinlock_t *key)
{
	while(1)
	{
		arch_di();
		if(!*key)
		{
			*key = 1;
			fence(r, rw);
			break;
		}
		arch_ei();
	}
	arch_ei();
}

_WEAK void spinlock_release(volatile spinlock_t *key)
{
	fence(rw, r);
	*key = 0;
}
