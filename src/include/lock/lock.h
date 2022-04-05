/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: lock.h
 * Description		: This file consists of various lock prototypes
 *			  This allows developer to maintain consistency
 *			  of locks used. If needed developer can always
 *			  include correcponding lock header and use it.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _LOCK_H_

#define LOCK_INITAL_VALUE	1
#define UNLOCK_INITIAL_VALUE	0

#if USE_SPINLOCK
#include <lock/spinlock.h>
typedef spinlock_t lock_t;

#define lock_acquire(X)		spinlock_acquire(X)
#define lock_release(X)		spinlock_release(X)
#endif

#if USE_BAKERYLOCK
#include <lock/bakerylock.h>
typedef bakerylock_t lock_t;

#define lock_acquire(X)		bakerylock_acquire(X)
#define lock_release(X)		bakerylock_release(X)
#endif
