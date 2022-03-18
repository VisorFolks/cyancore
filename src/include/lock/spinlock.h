/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: lock.h
 * Description		: This file consists of spinlock prototype
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SPINLOCK_H_

#include <stdint.h>

typedef size_t spinlock_t;

void spinlock_acquire(volatile spinlock_t *);
void spinlock_release(volatile spinlock_t *);
