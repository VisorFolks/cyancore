#pragma once
#define _SPINLOCK_H_

typedef unsigned int spinlock_t;

void spinlock_acquire(spinlock_t *);
void spinlock_release(spinlock_t *);
